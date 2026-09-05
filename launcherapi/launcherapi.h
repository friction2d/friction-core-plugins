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

#ifdef HAS_DBUS
public:
    void init() override;
    void renderProgress(int frame, int total) override;

private:
    UnityLauncherEntry *mUnity;
#endif
};
