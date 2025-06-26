/**
 * @file newton.cpp
 * @brief Реализация метода Ньютона для решения уравнений
 * @author Roman
 * @date 2024
 * 
 * @details
 * Реализует функцию для нахождения корня уравнения
 * с использованием итерационного метода Ньютона.
 */

#include "newton.h"
#include <QDebug>
#include <cmath>

// Максимальное количество итераций
const int MAX_ITERATIONS = 100;

// Функция для вычисления значения уравнения
double evaluateFunction(const QString& equation, double x) {
    // TODO: Реализовать парсинг и вычисление уравнения
    // Временная заглушка для примера
    return x * x - 4; // x^2 - 4
}

// Функция для вычисления производной
double evaluateDerivative(const QString& equation, double x) {
    // TODO: Реализовать вычисление производной
    // Временная заглушка для примера
    return 2 * x; // производная от x^2 - 4
}

QString solveNewton(const QString& equation, double initialGuess, double tolerance)
{
    try {
        double x = initialGuess;
        double fx, dfx;
        int iterations = 0;

        do {
            fx = evaluateFunction(equation, x);
            dfx = evaluateDerivative(equation, x);

            if (std::abs(dfx) < tolerance) {
                return "Error: Derivative too close to zero";
            }

            double nextX = x - fx / dfx;
            if (std::abs(nextX - x) < tolerance) {
                return QString::number(nextX, 'f', 6);
        }

            x = nextX;
            iterations++;
        } while (iterations < MAX_ITERATIONS);

        return "Error: Maximum iterations reached";
    }
    catch (const std::exception& e) {
        return QString("Error: %1").arg(e.what());
    }
}

double Newton::calculateRoot(double number, int power)
{
    if (power <= 0) {
        return 0.0;
    }

    if (power == 1) {
        return number;
    }

    // Начальное приближение
    double x = number / 2.0;
    const double epsilon = 1e-10;
    const int maxIterations = 100;

    for (int i = 0; i < maxIterations; ++i) {
        double fx = function(x, power, number);
        if (std::abs(fx) < epsilon) {
            break;
        }

        double dfx = derivative(x, power);
        if (std::abs(dfx) < epsilon) {
            break;
        }

        double xNew = x - fx / dfx;
        if (std::abs(xNew - x) < epsilon) {
            break;
        }

        x = xNew;
    }

    return x;
}

double Newton::derivative(double x, int n)
{
    return n * std::pow(x, n - 1);
}

double Newton::function(double x, int n, double number)
{
    return std::pow(x, n) - number;
}

double newtonMethod(double value)
{
    Newton newton;
    return newton.calculateRoot(value, 2);
}

