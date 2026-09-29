// SPDX-License-Identifier: GPL-3.0-only

#include "coreplugininterface.h"

#include "Animators/transformanimator.h"
#include "Boxes/containerbox.h"
#include "Private/document.h"
#include "appsupport.h"
#include "canvas.h"
#include "exceptions.h"
#include "svganimationimportdialog.h"
#include "svganimationimporter.h"

#include <QAction>
#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QObject>
#include <QWidget>

class SvgImportPlugin final : public QObject,
                              public FrictionCorePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID FrictionCorePluginInterface_iid FILE "plugin.json")
    Q_INTERFACES(FrictionCorePluginInterface)

public:
    QList<QAction*> createMenuActions(QObject *parent) override
    {
        auto *action = new QAction(tr("Import SVG Animation..."), parent);
        action->setObjectName(QStringLiteral("ImportSVGAnimationPluginAction"));
        action->setToolTip(
                    tr("Import an animated SVG as editable Friction objects"));
        return {action};
    }

    void triggerAction(Document& document, Canvas *scene,
                       const QAction *action) override
    {
        if (!scene || !action ||
                action->objectName() !=
                QStringLiteral("ImportSVGAnimationPluginAction")) {
            return;
        }

        QWidget *parent = QApplication::activeWindow();
        const QString recentDir = AppSupport::getSettings(
                    "files", "recentImportDir", QDir::homePath()).toString();
        const QString path = AppSupport::getOpenFile(
                    parent, tr("Import SVG Animation"), recentDir,
                    tr("SVG Files (*.svg)"));
        if (path.isEmpty()) { return; }

        try {
            import(path, scene, document, parent);
        } catch (const std::exception& exception) {
            gPrintExceptionCritical(exception);
        }
    }

private:
    void import(const QString& path, Canvas *scene, Document& document,
                QWidget *parent)
    {
        QSizeF svgSize;
        SVGAnimationImportDialog::ScaleMode scaleMode;
        SVGAnimationImportDialog::StructureMode structureMode;
        SVGAnimationImportDialog::SceneDurationMode durationMode;
        const SVGAnimationImportDialog::SceneInfo sceneInfo{
            QSize(scene->getCanvasWidth(), scene->getCanvasHeight()),
            scene->getMinFrame(), scene->getMaxFrame(), scene->getFps()
        };
        if (!SVGAnimationImportDialog::sExec(
                    path, sceneInfo, svgSize, scaleMode, structureMode,
                    durationMode, parent)) {
            return;
        }

        qreal scaleX = 1;
        qreal scaleY = 1;
        if (scaleMode == SVGAnimationImportDialog::ScaleMode::fitWidth) {
            scaleX = scaleY = scene->getCanvasWidth()/svgSize.width();
        } else if (scaleMode ==
                   SVGAnimationImportDialog::ScaleMode::fitHeight) {
            scaleX = scaleY = scene->getCanvasHeight()/svgSize.height();
        } else if (scaleMode == SVGAnimationImportDialog::ScaleMode::stretch) {
            scaleX = scene->getCanvasWidth()/svgSize.width();
            scaleY = scene->getCanvasHeight()/svgSize.height();
        }

        ContainerBox *target = scene->getCurrentGroup();
        auto block = scene->blockUndoRedo();
        bool technicalRoot = false;
        const auto imported = ImportSVGAnimation::loadSVGFile(
                    path, scene, durationMode, &technicalRoot);
        if (!imported) { return; }
        const QString importName = QFileInfo(path).completeBaseName();
        block.reset();
        target->prp_pushUndoRedoName(tr("Import SVG Animation"));

        const bool directObjects = structureMode ==
                SVGAnimationImportDialog::StructureMode::directObjects;
        qsptr<ContainerBox> wrapper;
        if (technicalRoot) {
            wrapper = qSharedPointerCast<ContainerBox>(imported);
            wrapper->prp_setName(importName);
        } else {
            wrapper = enve::make_shared<ContainerBox>(importName,
                                                       eBoxType::group);
            wrapper->addContained(imported);
        }
        wrapper->getBoxTransformAnimator()->setScale(scaleX, scaleY);
        target->insertContained(0, wrapper);
        if (directObjects) {
            wrapper->ungroupKeepTransform_k();
        } else {
            wrapper->planCenterPivotPosition();
            wrapper->updateAllBoxes(UpdateReason::userChange);
        }
        scene->requestUpdate();
        document.actionFinished();
        AppSupport::setSettings("files", "recentImportDir",
                                QFileInfo(path).absoluteDir().absolutePath());
    }
};

#include "svgimportplugin.moc"
