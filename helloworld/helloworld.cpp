// SPDX-License-Identifier: GPL-3.0-only

#include "helloworld.h"

// required includes
#include "Private/document.h"
#include "canvas.h"

// used in triggerAction
#include "Boxes/textbox.h"
#include <QMessageBox>

// this function is optional
HelloWorldPlugin::~HelloWorldPlugin()
{
    qDebug() << "end plugin";
}

// this function is optional
void HelloWorldPlugin::init()
{
    qDebug() << "start plugin";
}

// add (optional) actions in plugin menu (Plugins/Group/Action)
// you MUST always return QList<QAction*>
QList<QAction*> HelloWorldPlugin::createMenuActions(QObject* parent)
{
    QList<QAction*> actions;
    {
        QAction* action = new QAction(tr("New text box"), parent);
        actions << action;
    }
    {
        QAction* action = new QAction(tr("Open dialog"), parent);
        actions << action;
    }
    return actions;
}

// add (optional) action to main toolbar
// you MUST always return QList<QAction*>
QList<QAction*> HelloWorldPlugin::createToolbarActions(QObject *parent)
{
    QList<QAction*> actions;
    {
        QAction* action = new QAction(tr("Open dialog"), parent);
        action->setIcon(QIcon::fromTheme("dialog-information")); // see friction-icon-theme for available icons
        action->setObjectName("helloWorld_openDialog"); // objectname is required for show/hide action in toolbar
        actions << action;
    }
    return actions;
}

// handle triggered actions
void HelloWorldPlugin::triggerAction(Document &doc,
                                     Canvas* const scene,
                                     const QAction *act)
{
    // do whatever if action triggered.

    if (!scene) {
        QMessageBox::warning(nullptr, "Hello World!",
                             tr("No active scene."));
        return;
    }

    if (!act) {
        QMessageBox::warning(nullptr, "Hello World!",
                             tr("Invalid action."));
        return;
    }

    if (act->text() == tr("New text box")) {
        const auto box = enve::make_shared<TextBox>();

        box->planCenterPivotPosition();
        box->setFontFamilyAndStyle(doc.fFontFamily,
                                   doc.fFontStyle);
        box->setFontSize(doc.fFontSize * 2);
        box->setCurrentValue("Hello World!");

        scene->getCurrentGroup()->addContained(box);

        box->setAbsolutePos({(qreal)scene->getCanvasWidth() / 2,
                             (qreal)scene->getCanvasHeight() / 2});

        scene->clearBoxesSelection();
        scene->addBoxToSelection(box.get());

        doc.actionFinished();
    } else if (act->text() == tr("Open dialog")) {
        QMessageBox::information(nullptr, "Hello World!",
                                 tr("Hello World!"));
    } else {
        QMessageBox::information(nullptr, "Hello World!",
                                 tr("Unknown action."));
    }
}
