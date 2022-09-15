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

    qInfo() << "Waiting for command!" << Qt::endl;

    bool run = true;
    while (run) {
        QString line = in.readLine();

        if (!line.trimmed().isEmpty()) {
            Message msg = parseText(line);
            dispatcher.handleMessage(msg);
            qInfo() << "";
        }
    }

    return a.exec();
}
