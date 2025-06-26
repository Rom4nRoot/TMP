/**
 * @file sha1.cpp
 * @brief Реализация функции SHA1 хеширования
 * @date 2024
 * 
 * @details
 * Реализует функцию для вычисления SHA1 хеша строки
 * с использованием QCryptographicHash.
 */

#include "sha1.h"
#include <QCryptographicHash>

QString sha1(const QString& input)
{
    QByteArray hash = QCryptographicHash::hash(
        input.toUtf8(),
        QCryptographicHash::Sha1
    );
    return hash.toHex();
}
