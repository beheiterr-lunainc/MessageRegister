#ifndef MESSAGEHANDLERREGISTRATION_H
#define MESSAGEHANDLERREGISTRATION_H

#include <QList>
#include <QMetaType>

namespace MessageRegister
{
    void registerType(QString typeName);
    QList<const QMetaObject*> getMetaObjects();

    // Dummy struct used by the REGISTER_HANDLER() macro in order
    // to call the registerType() method at global level, similar to Q_DECLARE_METATYPE
    template <class T>
    struct Registration {
        Registration() {
            registerType(QMetaType::fromType<T*>().name());
        }
    };

#define REGISTER_HANDLER(CLASS)  static MessageRegister::Registration<CLASS> _CLASS_registration;
}

#endif // MESSAGEHANDLERREGISTRATION_H
