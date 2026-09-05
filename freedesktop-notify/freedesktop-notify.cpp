// SPDX-License-Identifier: GPL-3.0-only

#include "freedesktop-notify.h"

#ifdef HAS_DBUS
#include "appsupport.h"
#include <QDBusInterface>
#include <QDBusReply>
#include <QStringList>
#include <QVariantMap>

void FreeDesktopNotifyPlugin::showNotification(const QString& title,
                                               const QString& message)
{
    qDebug() << "FreeDesktopNotifyPlugin: showNotification" << title << message;
    QDBusInterface iface("org.freedesktop.Notifications",
                         "/org/freedesktop/Notifications",
                         "org.freedesktop.Notifications",
                         QDBusConnection::sessionBus());

    if (iface.isValid()) {
        QString appName = "Friction";
        uint replacesId = 0;
        QString appIcon = AppSupport::getAppID();
        QStringList actions;
        QVariantMap hints;
        int timeout = -1;

        QDBusReply<uint> reply = iface.call("Notify",
                                            appName,
                                            replacesId,
                                            appIcon,
                                            title,
                                            message,
                                            actions,
                                            hints,
                                            timeout);

        if (!reply.isValid()) {
            qWarning() << "FreeDesktopNotifyPlugin: Failed to send notification" << reply.error().message();
        }
    } else {
        qWarning() << "FreeDesktopNotifyPlugin: Notification service not available";
    }
}
#endif // HAS_DBUS
