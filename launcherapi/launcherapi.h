// SPDX-License-Identifier: GPL-3.0-only

#include "coreplugininterface.h"

#ifdef HAS_DBUS
#include "unitylauncherentry.h"
#endif

class LauncherApiPlugin : public QObject,
                          public FrictionCorePluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID FrictionCorePluginInterface_iid FILE "plugin.json")
    Q_INTERFACES(FrictionCorePluginInterface)

public:
    void init() override;
    void renderProgress(int frame, int total) override;

#ifdef HAS_DBUS
private:
    UnityLauncherEntry *mUnity;
#endif
};
