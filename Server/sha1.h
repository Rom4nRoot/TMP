/**
 * @file sha1.h
 * @brief Заголовочный файл для SHA1 хеширования
 * @author Roman
 * @date 2024
 * 
 * @details
 * Реализует функцию для вычисления SHA1 хеша строки.
 * Используется в задаче 1 для хеширования паролей и проверки хешей.
 * 
 * @see QCryptographicHash
 */

#ifndef SHA1_H
#define SHA1_H

#include <QString>
#include <QCryptographicHash>

/**
 * @brief Класс для работы с SHA1 хешированием
 */
class SHA1 {
public:
    /**
     * @brief Вычисляет SHA1 хеш для входной строки
     * @param input Входная строка для хеширования
     * @return Строка с SHA1 хешем в шестнадцатеричном формате
     */
    QString hash(const QString& input) {
        QByteArray data = input.toUtf8();
        QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha1);
        return hash.toHex();
    }
};

/**
 * @brief Вычисляет SHA1 хеш для входной строки
 * @param input Входная строка для хеширования
 * @return Строка с SHA1 хешем в шестнадцатеричном формате
 * 
 * @details
 * Функция использует QCryptographicHash для вычисления
 * SHA1 хеша входной строки. Результат возвращается в виде
 * шестнадцатеричной строки.
 * 
 * @example
 * @code
 * QString hash = sha1("password");
 * // hash = "5baa61e4c9b93f3f0682250b6cf8331b7ee68fd8"
 * @endcode
 */
QString sha1(const QString& input);

#endif // SHA1_H
