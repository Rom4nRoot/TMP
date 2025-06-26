#ifndef TST_NEWTON_H
#define TST_NEWTON_H

#include <QTest>
#include <QString>
#include "newton.h"

class TestNewton : public QObject
{
    Q_OBJECT

private slots:
    void testSimpleCase();
    void testZeroDerivative();
    void testNoRoot();
    void testPerformance();
};

#endif // TST_NEWTON_H 