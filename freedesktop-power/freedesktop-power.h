// SPDX-License-Identifier: GPL-3.0-only

#include "coreplugininterface.h"

class FreeDesktopPowerPlugin : public QObject,
                               public FrictionCorePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID FrictionCorePluginInterface_iid FILE "plugin.json")
    Q_INTERFACES(FrictionCorePluginInterface)

#ifdef HAS_DBUS
public:
    ~FreeDesktopPowerPlugin() override;
    void renderStateChanged(PreviewState state) override;

private:
    uint mScreensaverCookie = 0;
    uint mSuspendCookie = 0;

    void inhibitScreensaver(bool inhibit);
    void inhibitSuspend(bool inhibit);
#endif
};
