// SPDX-License-Identifier: GPL-3.0-only

#include "coreplugininterface.h"

class HelloWorldPlugin : public QObject,
                         public FrictionCorePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID FrictionCorePluginInterface_iid FILE "plugin.json")
    Q_INTERFACES(FrictionCorePluginInterface)

public:
    ~HelloWorldPlugin() override;
    void init() override;

    QList<QAction*> createMenuActions(QObject* parent) override;
    QList<QAction*> createToolbarActions(QObject* parent) override;

    void triggerAction(Document &doc,
                       Canvas* const scene,
                       const QAction* act) override;
};
