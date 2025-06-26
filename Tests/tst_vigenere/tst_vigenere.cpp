#include "tst_vigenere.h"
#include <QElapsedTimer>
#include <QtTest>

void TestVigenere::testSimpleEncryption()
{
    Vigenere vigenere;
    QString text = "HELLO";
    QString key = "KEY";
    QString expected = "RIJVS";
    
    QString result = vigenere.encrypt(text, key);
    QCOMPARE(result, expected);
}

void TestVigenere::testSimpleDecryption()
{
    Vigenere vigenere;
    QString text = "RIJVS";
    QString key = "KEY";
    QString expected = "HELLO";
    
    QString result = vigenere.decrypt(text, key);
    QCOMPARE(result, expected);
}

void TestVigenere::testWithSpacesAndPunctuation()
{
    Vigenere vigenere;
    QString text = "Hello, World!";
    QString key = "KEY";
    
    QString encrypted = vigenere.encrypt(text, key);
    QString decrypted = vigenere.decrypt(encrypted, key);
    
    QCOMPARE(decrypted, text);
}

void TestVigenere::testLongKey()
{
    Vigenere vigenere;
    QString text = "This is a test message";
    QString key = "ThisIsAVeryLongKeyThatShouldWorkFine";
    
    QString encrypted = vigenere.encrypt(text, key);
    QString decrypted = vigenere.decrypt(encrypted, key);
    
    QCOMPARE(decrypted, text);
}

void TestVigenere::testPerformance()
{
    Vigenere vigenere;
    QString text = QString(1000, 'A'); // Строка из 1000 символов
    QString key = "KEY";
    
    QElapsedTimer timer;
    timer.start();
    
    QString encrypted = vigenere.encrypt(text, key);
    QString decrypted = vigenere.decrypt(encrypted, key);
    
    qint64 elapsed = timer.elapsed();
    QVERIFY(elapsed < 100); // Проверяем, что шифрование и дешифрование занимают менее 100 мс
}

QTEST_APPLESS_MAIN(TestVigenere) 