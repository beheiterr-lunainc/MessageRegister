#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QObject>
#include "Message.h"
#include "MessageRegister.h"

// NOTE: All MessageHandler subclasses must do the following:
// - Include Q_CLASSINFO("command", xxx) on the line after Q_OBJECT, where xxx is replaced by a string.
//     This is used by MessageDispatcher to figure out what command word
//     is associated with each subclass.
// - Provide implementation for the handle() method.
// - Include the REGISTER_HANDLER(T) macro after the subclass declaration
//     This is used by the global methods in the MessageRegister namespace in order
//     automatically find all of the MessageHandler implementations.

class MessageHandler
        : public QObject
{
    Q_OBJECT

public:
    explicit MessageHandler() : QObject(nullptr) {}

    virtual void handle(const Message &m) = 0;
};

#endif // MESSAGEHANDLER_H
