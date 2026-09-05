// SPDX-License-Identifier: GPL-3.0-only

#include "launcherapi.h"

#ifdef HAS_DBUS
#include "appsupport.h"

void LauncherApiPlugin::init()
{
    qDebug() << "init LauncherApiPlugin";
    mUnity = new UnityLauncherEntry(QStringLiteral("%1.desktop")
                                        .arg(AppSupport::getAppID()),
                                    this);
}

void LauncherApiPlugin::renderProgress(int frame,
                                       int total)
{
    qDebug() << "LauncherApiPlugin: render progress" << frame << total;
    if (!mUnity) { return; }
    if (total > 0) {
        const double currentProgress = static_cast<double>(frame) / total;
        mUnity->setProgress(currentProgress);
        mUnity->setProgressVisible(frame < total);
    } else {
        mUnity->setProgressVisible(false);
    }
}
#endif // HAS_DBUS
