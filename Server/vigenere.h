/**
 * @file vigenere.h
 * @brief Заголовочный файл для шифра Виженера
 * @author Roman
 * @date 2024
 * 
 * @details
 * Реализует функции для шифрования и дешифрования текста
 * с использованием шифра Виженера.
 * Используется в задаче 4 для криптографических операций.
 */

#ifndef VIGENERE_H
#define VIGENERE_H

#include <QString>

/**
 * @brief Класс для работы с шифром Виженера
 */
class Vigenere {
public:
    /**
     * @brief Шифрует текст с использованием шифра Виженера
     * @param text Исходный текст для шифрования
     * @param key Ключ шифрования
     * @return Зашифрованный текст
     */
    QString encrypt(const QString& text, const QString& key) {
        QString result;
        QString upperKey = key.toUpper();
        int keyLength = upperKey.length();
        int keyIndex = 0;

        for (QChar c : text) {
            if (c.isLetter()) {
                bool isUpper = c.isUpper();
                QChar base = isUpper ? 'A' : 'a';
                QChar keyChar = upperKey[keyIndex % keyLength];
                int shift = keyChar.toLatin1() - 'A';
                
                int charValue = c.toLatin1() - base.toLatin1();
                charValue = (charValue + shift) % 26;
                result.append(QChar(base.toLatin1() + charValue));
                
                keyIndex++;
            } else {
                result.append(c);
            }
        }
        
        return result;
    }

    /**
     * @brief Дешифрует текст, зашифрованный шифром Виженера
     * @param text Зашифрованный текст
     * @param key Ключ шифрования
     * @return Расшифрованный текст
     */
    QString decrypt(const QString& text, const QString& key) {
        QString result;
        QString upperKey = key.toUpper();
        int keyLength = upperKey.length();
        int keyIndex = 0;

        for (QChar c : text) {
            if (c.isLetter()) {
                bool isUpper = c.isUpper();
                QChar base = isUpper ? 'A' : 'a';
                QChar keyChar = upperKey[keyIndex % keyLength];
                int shift = keyChar.toLatin1() - 'A';
                
                int charValue = c.toLatin1() - base.toLatin1();
                charValue = (charValue - shift + 26) % 26;
                result.append(QChar(base.toLatin1() + charValue));
                
                keyIndex++;
            } else {
                result.append(c);
            }
        }
        
        return result;
    }
};

/**
 * @brief Шифрует текст с использованием шифра Виженера
 * @param text Исходный текст для шифрования
 * @param key Ключ шифрования
 * @return Зашифрованный текст
 * 
 * @details
 * Функция применяет шифр Виженера к входному тексту.
 * Каждая буква текста сдвигается на соответствующую букву ключа.
 * Небуквенные символы остаются без изменений.
 * 
 * @example
 * @code
 * QString encrypted = encryptVigenere("HELLO", "KEY");
 * // encrypted = "RIJVS"
 * @endcode
 * 
 * @note
 * Ключ должен содержать только буквы. Регистр букв в ключе
 * не имеет значения.
 */
QString encryptVigenere(const QString& text, const QString& key);

/**
 * @brief Дешифрует текст, зашифрованный шифром Виженера
 * @param text Зашифрованный текст
 * @param key Ключ шифрования
 * @return Расшифрованный текст
 * 
 * @details
 * Функция применяет обратный шифр Виженера к зашифрованному тексту.
 * Каждая буква текста сдвигается назад на соответствующую букву ключа.
 * Небуквенные символы остаются без изменений.
 * 
 * @example
 * @code
 * QString decrypted = decryptVigenere("RIJVS", "KEY");
 * // decrypted = "HELLO"
 * @endcode
 * 
 * @note
 * Ключ должен быть тем же, что использовался при шифровании.
 * Регистр букв в ключе не имеет значения.
 */
QString decryptVigenere(const QString& text, const QString& key);

#endif // VIGENERE_H
