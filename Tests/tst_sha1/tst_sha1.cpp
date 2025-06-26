#include "tst_sha1.h"
#include <QElapsedTimer>
#include <QDebug>

void TestSHA1::testEmptyString()
{
    SHA1 sha1;
    QString input = "";
    QString expected = "da39a3ee5e6b4b0d3255bfef95601890afd80709";
    
    QString result = sha1.hash(input);
    QCOMPARE(result, expected);
}

void TestSHA1::testSimpleString()
{
    SHA1 sha1;
    QString input = "Hello, World!";
    QString expected = "0a0a9f2a6772942557ab5355d76af442f8f65e01";
    
    QString result = sha1.hash(input);
    QCOMPARE(result, expected);
}

void TestSHA1::testLongString()
{
    SHA1 sha1;
    QString input = QString(1000, 'a'); // Строка из 1000 символов 'a'
    QString expected = "291e9a6c66994949b57ba5e650361e98fc36b1ba";
    
    QString result = sha1.hash(input);
    QCOMPARE(result, expected);
}

void TestSHA1::testSpecialCharacters()
{
    SHA1 sha1;
    QString input = "!@#$%^&*()_+{}|:<>?~`-=[]\\;',./";
    QString expected = "40f1d4520344ca8d2983e441c5bae8faddf1e5c5";
    
    QString result = sha1.hash(input);
    qDebug() << "input:" << input;
    qDebug() << "result:" << result;
    QCOMPARE(result, expected);
}

void TestSHA1::testPerformance()
{
    SHA1 sha1;
    QString input = QString(1000000, 'a'); // Строка из 1 миллиона символов
    
    QElapsedTimer timer;
    timer.start();
    
    QString result = sha1.hash(input);
    
    qint64 elapsed = timer.elapsed();
    QVERIFY(elapsed < 1000); // Проверяем, что хеширование занимает менее 1 секунды
}

QTEST_APPLESS_MAIN(TestSHA1) 