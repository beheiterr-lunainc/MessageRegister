#ifndef HELLO_H
#define HELLO_H

#include "MessageHandler.h"
#include <QDebug>

class Hello : public MessageHandler
{
    Q_OBJECT
    Q_CLASSINFO("command", "hello")

public:
    Q_INVOKABLE Hello() = default;

    void handle(const Message &m)
    {
        Q_UNUSED(m);
        qInfo() << "Hi!";
    }
};

REGISTER_HANDLER(Hello);

#endif // HELLO_H
