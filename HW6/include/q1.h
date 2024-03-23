#ifndef Q1_H
#define Q1_H

#include <functional>

namespace q1 {
	template<typename T, typename Func = double (*)(double)>
	T gradient_descent(T init_value, T step, Func f);

	template<typename T, typename Func = double (*)(double)>
	T gradient_descent(T init_value, T step);

	template<typename T, typename Func>
	T numericGradient(Func f, T x);

	template<typename T, typename Func>
	T gradient_descent(T init_value, T step, Func f)
	{
		const T eps = 1e-5; // if |x2 - x1| < eps, then stop
		T gradient = numericGradient(f, init_value);
		T x1 = init_value, x2 = 0;

		x2 = init_value - step * gradient;

		while (abs(x2 - x1) > eps) {
			x1 = x2;
			gradient = numericGradient(f, x2);
			x2 -= step * gradient;
		}

		return x2;
	}

	template<typename T, typename Func>
	T gradient_descent(T init_value, T step)
	{
		Func f;
		const T eps = 1e-5; // if |x2 - x1| < eps, then stop
		T gradient = numericGradient(f, init_value);
		T x1 = init_value, x2 = 0;

		x2 = init_value - step * gradient;

		while (abs(x2 - x1) > eps) {
			x1 = x2;
			gradient = numericGradient(f, x2);
			x2 -= step * gradient;
		}

		return x2;

	}

	template<typename T, typename Func>
	T numericGradient(Func f, T x)
	{
		// Calculate the gradient of the given function f, using numeric method.
		const T h = 1e-6;
		return (f(x + h) - f(x - h)) / (2 * h);
	}

}
#endif //Q1_H