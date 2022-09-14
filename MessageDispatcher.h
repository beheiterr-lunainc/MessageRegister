#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include <QObject>
#include <QHash>
#include "MessageHandler.h"

class MessageDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit MessageDispatcher(QObject *parent = nullptr);

    void handleMessage(Message m);

private:
    QHash<QString, MessageHandler*> m_handlers;
};

#endif // MESSAGEDISPATCHER_H
