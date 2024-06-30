#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

double f(double a, double b, int n)
{
	int i(0); //лічильник
	double s(0); //приблизне значення інтегралу
	double h(b - a / n); // довжина інтервалу
	while (i <= n)
	{
		s = s + h * a * a;
		a = a + h;
		i++;
	}
	return s;
}

int main()
{
	std::cout << "Радоманова Софія АнД-11 Варіант 1\n";

	std::ofstream fout("outRadomanova.txt");
	
	double a, b, t, k, Save; int n = 100;
	
	do {
		std::cout << "Початок інтервалу:";
		std::cin >> a;
		std::cout << "Кінець інтервалу:";
		std::cin >> b;
	} while (b < a);

	std::cout << "підінтегральна функція y=x^2\n";
	
	std::cout << "інтервал: [" << a << ";" << b << "]\n";
	
	std::cout << "підінтегральна функція y=x^2\n";
	std::cout << "інтервал: [" << a << ", " << b << "]\n";
	Save = a;
	t = ((b * b * b)/3) - ((a * a * a)/3); // f = x^3/3 - y^3/3
	std::cout << "Інтеграл по ф. Ньютона-Лейбніца:" << t << '\n';
	std::cout << "Інтеграл по ф. Ньютона-Лейбніца:" << t << '\n';
	n = 100;
	while (n <= 1000)
	{
		k = fabs (t - f( a, b, n)); //похибка
		std::cout << "n=" << std::setw(5) << n << std::setw(15) << fabs(f(a, b, n)) << std::setw(15) << k << '\n';
		fout << "n=" << std::setw(5) << n << std::setw(15) << fabs(f(a, b, n)) << std::setw(15) << k << '\n';
		a = Save;
		n += 100;
	}
	fout.close();
	return 0;
}