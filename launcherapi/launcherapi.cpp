// SPDX-License-Identifier: GPL-3.0-only

#include "launcherapi.h"

#include "appsupport.h"

void LauncherApiPlugin::init()
{
    qDebug() << "init LauncherApiPlugin";
#ifdef HAS_DBUS
    mUnity = new UnityLauncherEntry(QStringLiteral("%1.desktop")
                                        .arg(AppSupport::getAppID()),
                                    this);
#endif
}

void LauncherApiPlugin::renderProgress(int frame,
                                       int total)
{
#ifdef HAS_DBUS
    if (!mUnity) { return; }
    if (total > 0) {
        const double currentProgress = static_cast<double>(frame) / total;
        mUnity->setProgress(currentProgress);
        mUnity->setProgressVisible(frame < total);
    } else {
        mUnity->setProgressVisible(false);
    }
#endif
    qDebug() << "LauncherApiPlugin: render progress" << frame << total;
}
