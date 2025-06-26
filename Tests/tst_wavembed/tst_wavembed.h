#ifndef TST_WAVEMBED_H
#define TST_WAVEMBED_H

#include <QTest>
#include <QString>
#include "wavembed.h"

class TestWavEmbed : public QObject
{
    Q_OBJECT

private slots:
    // Тест встраивания короткого сообщения
    void testShortMessage();
    
    // Тест встраивания длинного сообщения
    void testLongMessage();
    
    // Тест извлечения сообщения
    void testMessageExtraction();
    
    // Тест с разными форматами WAV
    void testDifferentWavFormats();
    
    // Тест производительности
    void testPerformance();
};

#endif // TST_WAVEMBED_H

// Объявление вспомогательной функции для создания тестового WAV файла
void createTestWavFile(const QString& filename, int sampleRate = 44100, int bitDepth = 16); 