/**
 * @file newton.h
 * @brief Заголовочный файл для метода Ньютона
 * @date 2024
 * 
 * @details
 * Реализует функцию для нахождения корня уравнения методом Ньютона.
 * Используется в задаче 2 для решения нелинейных уравнений.
 */

#ifndef NEWTON_H
#define NEWTON_H

#include <QString>

/**
 * @brief Класс для работы с методом Ньютона
 */
class Newton {
public:
    /**
     * @brief Вычисляет корень n-й степени из числа
     * @param number Число, из которого извлекается корень
     * @param power Степень корня
     * @return Значение корня
     */
    double calculateRoot(double number, int power);

private:
    /**
     * @brief Вычисляет производную функции x^n
     * @param x Значение x
     * @param n Степень
     * @return Значение производной
     */
    double derivative(double x, int n);

    /**
     * @brief Вычисляет значение функции x^n
     * @param x Значение x
     * @param n Степень
     * @return Значение функции
     */
    double function(double x, int n, double number);
};

/**
 * @brief Находит корень уравнения методом Ньютона
 * @param equation Строка с уравнением
 * @param initialGuess Начальное приближение
 * @param tolerance Точность вычислений
 * @return Строка с результатом или сообщением об ошибке
 * 
 * @details
 * Функция реализует итерационный метод Ньютона для нахождения
 * корня уравнения. Процесс продолжается до достижения заданной
 * точности или максимального числа итераций.
 * 
 * @example
 * @code
 * QString result = solveNewton("x^2 - 4", 2.0, 1e-6);
 * // result = "2.000000"
 * @endcode
 * 
 * @note
 * Уравнение должно быть в формате, поддерживаемом парсером.
 * Начальное приближение должно быть достаточно близко к корню.
 */
QString solveNewton(const QString& equation, double initialGuess, double tolerance = 1e-6);

// Функция для нахождения квадратного корня с использованием метода Ньютона
double newtonMethod(double value);

#endif // NEWTON_H
