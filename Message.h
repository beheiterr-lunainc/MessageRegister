#ifndef MESSAGE_H
#define MESSAGE_H

#include <QList>

struct Message
{
    QString command;
    QStringList args;
};

#endif // MESSAGE_H
