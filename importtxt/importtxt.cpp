// SPDX-License-Identifier: GPL-3.0-only

#include "importtxt.h"

#include "Private/document.h"
#include "canvas.h"
#include "Boxes/textbox.h"

#include <QMimeDatabase>
#include <QMimeType>

qsptr<BoundingBox> ImportTxtPlugin::importFile(Canvas * const scene,
                                               const QString &path)
{
    QFileInfo fileInfo(path);
    if (!fileInfo.exists() || !fileInfo.isFile()) { return nullptr; }

    QMimeDatabase mimeDb;
    QMimeType mimeType = mimeDb.mimeTypeForFile(path);
    if (!mimeType.inherits("text/plain")) { return nullptr; }

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return nullptr;
    }

    const QString content = file.readAll();
    file.close();

    const auto box = enve::make_shared<TextBox>();
    box->setCurrentValue(content);

    return box;
}
