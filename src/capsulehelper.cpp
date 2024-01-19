#include "capsulehelper.h"

#include <QApplication>
#include <QDebug>

CapsuleHelper::CapsuleHelper(QObject *parent)
    : QObject(parent)
{
    m_CapsuleVisible = false;
    //建立到session bus的连接
    QDBusConnection connection = QDBusConnection::sessionBus();
    if(!connection.registerService("com.lingmo.Statusbar"))
    {
        qDebug() << "error:" << connection.lastError().message();
    }
    if(!connection.registerObject("/Statusbar/Capsule", this,QDBusConnection::ExportAllSlots))
    {
        qDebug() << "error:胶囊通知对象注册失败";
    }
    connect(Timer, SIGNAL(timeout()), this, SLOT(onProgressVisibleChanged()));
}

void CapsuleHelper::sendCapsule(QString text)
{
    qDebug() << "接受到胶囊通知信号！！！";
    
    QStringList list = text.split(";");
    int type=0;
    QString info;
    QString icon;
    foreach(QString s,list)
    {
        if(s.left(7) == "{TYPE}=")
        {
            QString tmp = s.mid(7).toLower();
            if(tmp == "progress")
            {
                type=0;
            }
        }else if(s.left(7) == "{INFO}=")
        {
            info = s.mid(7);
        }else if(s.left(7) == "{ICON}=")
        {
            icon = s.mid(7);
        }
    }
    switch(type){
        case 0 :
            m_ProgressValue = info.toInt();
            m_ProgressIcon = icon;
            m_ProgressVisible = true;
            emit progressValueChanged();
            emit progressIconChanged();
            Timer->stop();
            Timer->start(10000);
            Timer->setSingleShot(true);
            emit progressVisibleChanged();
            break;
    }
}

QString CapsuleHelper::getProgressIcon()
{
    return m_ProgressIcon;
}

int CapsuleHelper::getProgressValue()
{
    return m_ProgressValue;
}

bool CapsuleHelper::getProgressVisible()
{
    return m_ProgressVisible;
}

void CapsuleHelper::onProgressVisibleChanged()
{
    m_ProgressVisible = false;
    emit progressVisibleChanged();
}
