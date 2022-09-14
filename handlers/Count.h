#ifndef COUNT_H
#define COUNT_H

#include "MessageHandler.h"
#include <QCoreApplication>
#include <QDebug>

class Count : public MessageHandler
{
    Q_OBJECT
    Q_CLASSINFO("command", "count")

public:
    Q_INVOKABLE Count() = default;

    void handle(const Message &m)
    {
        Q_UNUSED(m);

        int num = 0;
        if (!m.args.isEmpty()) {
            num = m.args[0].toInt();
        }

        for (int i = 1; i <= num; i++) {
            qInfo() << i;
        }
    }
};

REGISTER_HANDLER(Count);

#endif // COUNT_H
