#ifndef CAPSULEHELPER_H
#define CAPSULEHELPER_H

#include <QObject>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QTimer>

class CapsuleHelper : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.lingmo.Statusbar")
    Q_PROPERTY(int progressValue READ getProgressValue NOTIFY progressValueChanged)
    Q_PROPERTY(QString progressIcon READ getProgressIcon NOTIFY progressIconChanged)
    Q_PROPERTY(bool progressVisible READ getProgressVisible NOTIFY progressVisibleChanged)

public:
    explicit CapsuleHelper(QObject *parent = nullptr);
    int getProgressValue();
    QString getProgressIcon();
    bool getProgressVisible();
    bool m_CapsuleVisible;

public slots:
    void sendCapsule(QString text);

private slots:
    void onProgressVisibleChanged();

private:
    QTimer *Timer=new QTimer;
    int m_ProgressValue;
    QString m_ProgressIcon;
    bool m_ProgressVisible;

signals:
    void progressValueChanged();
    void progressIconChanged();
    void progressVisibleChanged();

};

#endif // CAPSULEHELPER_H
