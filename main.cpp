#include <QCoreApplication>
#include <QRegularExpression>
#include <QTextStream>
#include <QDebug>

#include "MessageDispatcher.h"

Message parseText(const QString &text)
{
    static QRegularExpression exp("\\s+");

    QStringList splitList = text.trimmed().split(exp);
    if (!splitList.isEmpty()) {
        QString command = splitList.takeFirst();
        QStringList args = splitList;
        return { command, args };
    }
    return { /* empty message */ };
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MessageDispatcher dispatcher;
    QTextStream in(stdin);

    qInfo() << "Waiting for command!";

    bool run = true;
    while (run) {
        qInfo() << "";
        QString line = in.readLine();
        Message msg = parseText(line);

        dispatcher.handleMessage(msg);
    }

    return a.exec();
}
