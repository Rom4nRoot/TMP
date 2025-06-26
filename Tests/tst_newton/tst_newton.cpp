#include "tst_newton.h"
#include <QElapsedTimer>
#include <QtMath>

void TestNewton::testSimpleCase()
{
    // Проверяем вычисление квадратного корня из 2
    double root = newtonMethod(2.0);
    QVERIFY(qAbs(root - qSqrt(2)) < 1e-6);
}

void TestNewton::testZeroDerivative()
{
    // Проверяем вычисление корня 1-й степени (должен вернуть само число)
    Newton n;
    double root = n.calculateRoot(5.0, 1);
    QVERIFY(qAbs(root - 5.0) < 1e-10);
}

void TestNewton::testNoRoot()
{
    // Проверяем вычисление корня чётной степени из отрицательного числа (ожидаем не-число)
    Newton n;
    double root = n.calculateRoot(-4.0, 2);
    QVERIFY(qIsNaN(root) || qAbs(root) > 1e10 || root == 0.0);
}

void TestNewton::testPerformance()
{
    QElapsedTimer timer;
    timer.start();
    double root = newtonMethod(2.0);
    qint64 elapsed = timer.elapsed();
    QVERIFY(elapsed < 100); // Проверяем, что решение находится быстро
}

QTEST_APPLESS_MAIN(TestNewton) 