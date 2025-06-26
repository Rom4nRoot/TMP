#ifndef TST_VIGENERE_H
#define TST_VIGENERE_H

#include <QObject>
#include "../Server/vigenere.h"

class TestVigenere : public QObject
{
    Q_OBJECT
private slots:
    void testSimpleEncryption();
    void testSimpleDecryption();
    void testWithSpacesAndPunctuation();
    void testLongKey();
    void testPerformance();
};

#endif // TST_VIGENERE_H 