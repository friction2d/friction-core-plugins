// SPDX-License-Identifier: GPL-3.0-only

#include "coreplugininterface.h"

class ImportTxtPlugin : public QObject,
                        public FrictionCorePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID FrictionCorePluginInterface_iid FILE "plugin.json")
    Q_INTERFACES(FrictionCorePluginInterface)

public:

    qsptr<BoundingBox> importFile(Canvas* const scene,
                                  const QString &path) override;
};
