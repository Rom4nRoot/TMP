#include "tst_wavembed.h"
#include <QElapsedTimer>
#include <QFile>
#include <QDir>

void TestWavEmbed::testShortMessage()
{
    WavEmbed wavEmbed;
    QString inputFile = "test_input.wav";
    QString outputFile = "test_output.wav";
    QString message = "Test message";
    
    // Создаем тестовый WAV файл
    createTestWavFile(inputFile);
    
    bool success = wavEmbed.embedMessage(inputFile, outputFile, message);
    QVERIFY(success);
    
    QString extractedMessage = wavEmbed.extractMessage(outputFile);
    QCOMPARE(extractedMessage, message);
    
    // Очистка
    QFile::remove(inputFile);
    QFile::remove(outputFile);
}

void TestWavEmbed::testLongMessage()
{
    WavEmbed wavEmbed;
    QString inputFile = "test_input.wav";
    QString outputFile = "test_output.wav";
    QString message = QString(1000, 'A'); // Длинное сообщение
    
    createTestWavFile(inputFile);
    
    bool success = wavEmbed.embedMessage(inputFile, outputFile, message);
    QVERIFY(success);
    
    QString extractedMessage = wavEmbed.extractMessage(outputFile);
    QCOMPARE(extractedMessage, message);
    
    QFile::remove(inputFile);
    QFile::remove(outputFile);
}

void TestWavEmbed::testMessageExtraction()
{
    WavEmbed wavEmbed;
    QString inputFile = "test_input.wav";
    QString outputFile = "test_output.wav";
    QString message = "Secret message";
    
    createTestWavFile(inputFile);
    wavEmbed.embedMessage(inputFile, outputFile, message);
    
    QString extractedMessage = wavEmbed.extractMessage(outputFile);
    QCOMPARE(extractedMessage, message);
    
    QFile::remove(inputFile);
    QFile::remove(outputFile);
}

void TestWavEmbed::testDifferentWavFormats()
{
    WavEmbed wavEmbed;
    QString inputFile = "test_input.wav";
    QString outputFile = "test_output.wav";
    QString message = "Test message";
    
    // Тест с разными параметрами WAV
    int sampleRates[] = {8000, 16000, 44100, 48000};
    int bitDepths[] = {8, 16, 24, 32};
    
    for (int rate : sampleRates) {
        for (int depth : bitDepths) {
            createTestWavFile(inputFile, rate, depth);
            
            bool success = wavEmbed.embedMessage(inputFile, outputFile, message);
            QVERIFY(success);
            
            QString extractedMessage = wavEmbed.extractMessage(outputFile);
            QCOMPARE(extractedMessage, message);
        }
    }
    
    QFile::remove(inputFile);
    QFile::remove(outputFile);
}

void TestWavEmbed::testCorruptedFile()
{
    WavEmbed wavEmbed;
    QString inputFile = "test_input.wav";
    QString outputFile = "test_output.wav";
    QString message = "Test message";
    
    createTestWavFile(inputFile);
    
    // Повреждаем файл
    QFile file(inputFile);
    file.open(QIODevice::ReadWrite);
    file.seek(100);
    file.write("CORRUPTED", 9);
    file.close();
    
    bool success = wavEmbed.embedMessage(inputFile, outputFile, message);
    QVERIFY(!success);
    
    QFile::remove(inputFile);
    QFile::remove(outputFile);
}

void TestWavEmbed::testPerformance()
{
    WavEmbed wavEmbed;
    QString inputFile = "test_input.wav";
    QString outputFile = "test_output.wav";
    QString message = QString(10000, 'A'); // Очень длинное сообщение
    
    createTestWavFile(inputFile);
    
    QElapsedTimer timer;
    timer.start();
    
    wavEmbed.embedMessage(inputFile, outputFile, message);
    QString extractedMessage = wavEmbed.extractMessage(outputFile);
    
    qint64 elapsed = timer.elapsed();
    QVERIFY(elapsed < 5000); // Проверяем, что операции занимают менее 5 секунд
    
    QFile::remove(inputFile);
    QFile::remove(outputFile);
}

// Вспомогательная функция для создания тестового WAV файла
void createTestWavFile(const QString& filename, int sampleRate, int bitDepth)
{
    // Создаем заголовок WAV файла
    QByteArray header;
    header.append("RIFF");
    header.append(QByteArray(4, 0)); // Размер файла
    header.append("WAVE");
    header.append("fmt ");
    header.append(QByteArray(4, 0)); // Размер формата
    header.append(QByteArray(2, 0)); // Тип формата
    header.append(QByteArray(2, 0)); // Количество каналов
    header.append(QByteArray(4, 0)); // Частота дискретизации
    header.append(QByteArray(4, 0)); // Байт в секунду
    header.append(QByteArray(2, 0)); // Блок выравнивания
    header.append(QByteArray(2, 0)); // Бит на сэмпл
    header.append("data");
    header.append(QByteArray(4, 0)); // Размер данных
    
    // Записываем файл
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    file.write(header);
    file.close();
}

QTEST_APPLESS_MAIN(TestWavEmbed) 