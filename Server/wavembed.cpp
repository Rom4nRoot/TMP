/**
 * @file wavembed.cpp
 * @brief Реализация стеганографии в WAV файлах
 */

#include "wavembed.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <QBitArray>

WavEmbed::WavEmbed(QObject *parent) : QObject(parent)
{
}

bool WavEmbed::embedMessage(const QString& inputFile, const QString& outputFile, const QString& message)
{
    // Открываем входной файл
    QFile file(inputFile);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    // Читаем заголовок WAV
    QByteArray header = file.read(44); // Стандартный размер заголовка WAV
    if (header.size() != 44) {
        file.close();
        return false;
    }

    // Проверяем, что это WAV файл
    if (header.mid(0, 4) != "RIFF" || header.mid(8, 4) != "WAVE") {
        file.close();
        return false;
    }

    // Читаем данные
    QByteArray data = file.readAll();
    file.close();

    // Конвертируем сообщение в биты
    QBitArray messageBits;
    QByteArray messageBytes = message.toUtf8();
    messageBits.resize(messageBytes.size() * 8);
    
    // Заполняем биты сообщения
    for (int i = 0; i < messageBytes.size(); ++i) {
        for (int j = 0; j < 8; ++j) {
            messageBits.setBit(i * 8 + j, messageBytes[i] & (1 << (7 - j)));
        }
    }

    // Добавляем маркер конца сообщения (8 нулевых бит)
    messageBits.resize(messageBits.size() + 8);
    for (int i = 0; i < 8; ++i) {
        messageBits.setBit(messageBits.size() - 8 + i, false);
    }

    // Проверяем, достаточно ли места для сообщения
    if (messageBits.size() > data.size()) {
        return false;
    }

    // Встраиваем сообщение
    for (int i = 0; i < messageBits.size(); ++i) {
        // Устанавливаем младший бит байта данных
        data[i] = (data[i] & 0xFE) | (messageBits[i] ? 1 : 0);
    }

    // Записываем результат
    QFile outFile(outputFile);
    if (!outFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    outFile.write(header);
    outFile.write(data);
    outFile.close();

    return true;
}

QString WavEmbed::extractMessage(const QString& inputFile)
{
    // Открываем файл
    QFile file(inputFile);
    if (!file.open(QIODevice::ReadOnly)) {
        return QString();
    }

    // Пропускаем заголовок
    file.seek(44);

    // Читаем данные
    QByteArray data = file.readAll();
    file.close();

    // Извлекаем биты
    QBitArray messageBits;
    messageBits.resize(data.size());
    
    for (int i = 0; i < data.size(); ++i) {
        messageBits.setBit(i, data[i] & 1);
    }

    // Ищем конец сообщения (8 нулевых бит)
    int messageEnd = 0;
    for (int i = 0; i < messageBits.size() - 8; ++i) {
        bool isEnd = true;
        for (int j = 0; j < 8; ++j) {
            if (messageBits[i + j]) {
                isEnd = false;
                break;
            }
        }
        if (isEnd) {
            messageEnd = i;
            break;
        }
    }

    // Конвертируем биты в байты
    QByteArray messageBytes;
    messageBytes.resize(messageEnd / 8);
    
    for (int i = 0; i < messageEnd; i += 8) {
        char byte = 0;
        for (int j = 0; j < 8; ++j) {
            if (messageBits[i + j]) {
                byte |= (1 << (7 - j));
            }
        }
        messageBytes[i / 8] = byte;
    }

    return QString::fromUtf8(messageBytes);
} 