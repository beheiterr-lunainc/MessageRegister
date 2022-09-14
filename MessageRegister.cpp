#include "MessageRegister.h"
#include <QMetaType>
#include <QDebug>

Q_GLOBAL_STATIC(QStringList, s_typeNames);

void MessageRegister::registerType(QString typeName)
{
    if (!s_typeNames->contains(typeName)) {
        s_typeNames->append(typeName);
        qDebug() << "Registered type" << typeName;
    }
}

QList<const QMetaObject*> MessageRegister::getMetaObjects()
{
    QList<const QMetaObject*> list;

    QStringList typeNames(*s_typeNames);
    for (const QString &typeName : typeNames)
    {
        int typeId = QMetaType::type(typeName.toLocal8Bit().data());

        if (typeId == QMetaType::UnknownType) {
            qWarning() << "Unknown MessageHandler type:" << typeName;
        }
        else
        {
            list.append(QMetaType::metaObjectForType(typeId));
        }
    }
    return list;
}


