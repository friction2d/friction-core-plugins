// SPDX-License-Identifier: GPL-3.0-only

#include "coreplugininterface.h"

class FreeDesktopNotifyPlugin : public QObject,
                                public FrictionCorePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID FrictionCorePluginInterface_iid FILE "plugin.json")
    Q_INTERFACES(FrictionCorePluginInterface)

#ifdef HAS_DBUS
public:
    void showNotification(const QString& title,
                          const QString& message) override;
#endif
};
