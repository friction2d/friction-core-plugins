// SPDX-License-Identifier: GPL-3.0-only

#include "freedesktop-power.h"

#ifdef HAS_DBUS
#include "Private/document.h"
#include <QDBusInterface>
#include <QDBusReply>

FreeDesktopPowerPlugin::~FreeDesktopPowerPlugin()
{
    qDebug() << "end FreeDesktopPowerPlugin";
    inhibitScreensaver(false);
    inhibitSuspend(false);
}

void FreeDesktopPowerPlugin::renderStateChanged(PreviewState state)
{
    inhibitScreensaver(state == PreviewState::playing);
    inhibitSuspend(state == PreviewState::rendering);
}

void FreeDesktopPowerPlugin::inhibitScreensaver(bool inhibit)
{
    if (inhibit && mScreensaverCookie == 0) {
        QDBusInterface iface("org.freedesktop.ScreenSaver",
                             "/org/freedesktop/ScreenSaver",
                             "org.freedesktop.ScreenSaver",
                             QDBusConnection::sessionBus());
        if (iface.isValid()) {
            QDBusReply<uint> reply = iface.call("Inhibit",
                                                "Friction",
                                                "Playing animation");
            if (reply.isValid()) {
                mScreensaverCookie = reply.value();
                qDebug() << "FreeDesktopPowerPlugin: Screensaver inhibited" << mScreensaverCookie;
            }
        }
    } else if (!inhibit && mScreensaverCookie != 0) {
        QDBusInterface iface("org.freedesktop.ScreenSaver",
                             "/org/freedesktop/ScreenSaver",
                             "org.freedesktop.ScreenSaver",
                             QDBusConnection::sessionBus());
        if (iface.isValid()) {
            iface.call("UnInhibit", mScreensaverCookie);
            qDebug() << "FreeDesktopPowerPlugin: Screensaver uninhibited";
            mScreensaverCookie = 0;
        }
    }
}

void FreeDesktopPowerPlugin::inhibitSuspend(bool inhibit)
{
    if (inhibit && mSuspendCookie == 0) {
        QDBusInterface iface("org.freedesktop.PowerManagement",
                             "/org/freedesktop/PowerManagement/Inhibit",
                             "org.freedesktop.PowerManagement.Inhibit",
                             QDBusConnection::sessionBus());
        if (iface.isValid()) {
            QDBusReply<uint> reply = iface.call("Inhibit",
                                                "Friction",
                                                "Rendering animation");
            if (reply.isValid()) {
                mSuspendCookie = reply.value();
                qDebug() << "FreeDesktopPowerPlugin: Suspend inhibited" << mSuspendCookie;
            }
        }
    } else if (!inhibit && mSuspendCookie != 0) {
        QDBusInterface iface("org.freedesktop.PowerManagement",
                             "/org/freedesktop/PowerManagement/Inhibit",
                             "org.freedesktop.PowerManagement.Inhibit",
                             QDBusConnection::sessionBus());
        if (iface.isValid()) {
            iface.call("UnInhibit", mSuspendCookie);
            qDebug() << "FreeDesktopPowerPlugin: Suspend uninhibited";
            mSuspendCookie = 0;
        }
    }
}
#endif // HAS_DBUS
