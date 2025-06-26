#ifndef TST_SHA1_H
#define TST_SHA1_H

#include <QTest>
#include <QString>
#include "sha1.h"

class TestSHA1 : public QObject
{
    Q_OBJECT

private slots:
    // Тест пустой строки
    void testEmptyString();
    
    // Тест простой строки
    void testSimpleString();
    
    // Тест длинной строки
    void testLongString();
    
    // Тест строки с специальными символами
    void testSpecialCharacters();
    
    // Тест производительности
    void testPerformance();
};

#endif // TST_SHA1_H 