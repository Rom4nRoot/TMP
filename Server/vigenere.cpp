/**
 * @file vigenere.cpp
 * @brief Реализация шифра Виженера
 * @author Roman
 * @date 2024
 * 
 * @details
 * Реализует функции для шифрования и дешифрования текста
 * с использованием шифра Виженера.
 */

#include "vigenere.h"
#include <QDebug>

QString encryptVigenere(const QString& text, const QString& key)
{
    QString result;
    int keyLength = key.length();
    
    // Шифруем каждый символ текста
    for (int i = 0; i < text.length(); ++i) {
        // Получаем текущий символ текста и ключа
        QChar textChar = text[i];
        QChar keyChar = key[i % keyLength];
        
        // Проверяем, является ли символ буквой
        if (textChar.isLetter()) {
            // Определяем базовый код для текущего регистра
            int base = textChar.isUpper() ? 'A' : 'a';
            
            // Вычисляем сдвиг для текущего символа ключа
            int shift = keyChar.toUpper().unicode() - 'A';
            
            // Применяем шифр Виженера
            int encrypted = ((textChar.unicode() - base + shift) % 26) + base;
            result.append(QChar(encrypted));
        } else {
            // Оставляем небуквенные символы без изменений
            result.append(textChar);
        }
    }
    
    return result;
}

QString decryptVigenere(const QString& text, const QString& key)
{
    QString result;
    int keyLength = key.length();

    // Расшифровываем каждый символ текста
    for (int i = 0; i < text.length(); ++i) {
        // Получаем текущий символ текста и ключа
        QChar textChar = text[i];
        QChar keyChar = key[i % keyLength];
        
        // Проверяем, является ли символ буквой
        if (textChar.isLetter()) {
            // Определяем базовый код для текущего регистра
            int base = textChar.isUpper() ? 'A' : 'a';
            
            // Вычисляем сдвиг для текущего символа ключа
            int shift = keyChar.toUpper().unicode() - 'A';

            // Применяем обратный шифр Виженера
            int decrypted = ((textChar.unicode() - base - shift + 26) % 26) + base;
            result.append(QChar(decrypted));
        } else {
            // Оставляем небуквенные символы без изменений
            result.append(textChar);
        }
    }

    return result;
}
