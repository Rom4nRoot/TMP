/**
 * @file wavembed.h
 * @brief Заголовочный файл для стеганографии в WAV файлах
 * 
 * Реализует функции для встраивания и извлечения скрытых сообщений
 * в WAV аудиофайлах с использованием LSB-метода.
 * Используется в задаче 3 для стеганографических операций.
 */

#ifndef WAVEMBED_H
#define WAVEMBED_H

#include <QString>

/**
 * @brief Встраивает сообщение в WAV файл
 * @param inputFile Путь к исходному WAV файлу
 * @param outputFile Путь для сохранения файла с сообщением
 * @param message Сообщение для встраивания
 * @return true если встраивание успешно
 */
bool embedMessage(const QString& inputFile, const QString& outputFile, const QString& message);

/**
 * @brief Извлекает скрытое сообщение из WAV файла
 * @param inputFile Путь к WAV файлу с сообщением
 * @return Извлеченное сообщение или пустую строку в случае ошибки
 */
QString extractMessage(const QString& inputFile);

#endif // WAVEMBED_H
