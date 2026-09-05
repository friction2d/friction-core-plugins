// SPDX-License-Identifier: GPL-3.0-only

#ifndef UNITY_LAUNCHER_ENTRY_H
#define UNITY_LAUNCHER_ENTRY_H

#include <QObject>
#include <QString>

class UnityLauncherEntry : public QObject
{
    Q_OBJECT
public:
    explicit UnityLauncherEntry(const QString &desktopFileName,
                                QObject *parent = nullptr);

public slots:
    void setProgress(double progress);
    void setProgressVisible(bool visible);
    void setCount(qint64 count);
    void setCountVisible(bool visible);
    void setUrgent(bool urgent);

private:
    void sendUpdate();

    QString mAppUri;
    double mProgress;
    bool mProgressVisible;
    qint64 mCount;
    bool mCountVisible;
    bool mUrgent;
};

#endif // UNITY_LAUNCHER_ENTRY_H
