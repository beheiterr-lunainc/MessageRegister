#include "MessageDispatcher.h"

#include <QMetaObject>
#include <QMetaClassInfo>
#include <QDebug>
#include "MessageRegister.h"

MessageDispatcher::MessageDispatcher(QObject *parent)
    : QObject(parent)
{
    const QMetaObject* baseMetaObj = QMetaType::fromType<MessageHandler*>().metaObject();

    auto metaObjList = MessageRegister::getMetaObjects();
    for (const QMetaObject* metaObj : metaObjList) {

        // Check that the class inherits from MessageHandler base class
        if (!metaObj->inherits(baseMetaObj)) {
            qWarning() << "Handler" << metaObj->className() << "does not inherit from MessageHandler!";
            continue;
        }

        // Check for CLASS_INFO("command", xxx)
        int infoIndex = metaObj->indexOfClassInfo("command");
        if (infoIndex < 0) {
            qWarning() << "MessageHandler" << metaObject()->className() << "does not specify command to handle. Use Q_CLASSINFO!";
            continue;
        }

        QString commandRaw = metaObj->classInfo(infoIndex).value();
        QString command = commandRaw.trimmed().toLower();

        // Create instance
        QObject *obj = metaObj->newInstance();//QGenericArgument("parent", this));
        MessageHandler *handler = qobject_cast<MessageHandler*>(obj);


        m_handlers.insert(command, handler);
        qDebug() << "Registered" << metaObj->className() << "for command" << command;
    }
}

void MessageDispatcher::handleMessage(Message m)
{
    QString command = m.command.trimmed().toLower();

    if (m_handlers.contains(command)) {
        m_handlers[command]->handle(m);
    }
    else {
        qWarning() << "Received unknown command" << command;
    }
}
