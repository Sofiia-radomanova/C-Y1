#include <iostream>
#include <iomanip>
#include <cmath>

const double eps = 1e-3;

// iterative
double f(double x) {
    double p = x * x, s = x;
    int i = 2;
    while (fabs(p) > eps) {
        s += p / i;
        p *= x;
        i++;
    }
    s = -s;
    return s;
}
// recursive
double g(double x, double p, int m) {
    double s = 0;
    if (fabs(p) < eps) return s;
    s += -p / m + g(x, pow(x, m + 1), m + 1);
    return s;
}

void tab(double a, double b, int n, double (*f1)(double), double (*g1)(double, double, int)) {
    double dx = (b - a) / n;
    std::cout << std::setw(5) << "x" << std::setw(15) << "f(x)" << std::setw(15) << "log(1-x)" << std::setw(15) << "g(x)" << '\n';
    while (a <= b) {
        std::cout << std::setw(5) << a << std::setw(15) << f1(a) << std::setw(15) << log(1 - a) << std::setw(15) << g1(a, a, 1) << '\n';
        a += dx;
    }
}

int main() {
    double a, b;
    int n;
    std::cout << "Input a: ";
    std::cin >> a;
    std::cout << "Input b: ";
    std::cin >> b;
    std::cout << "Input n: ";
    std::cin >> n;
    tab(a, b, n, f, g);
    return 0;
}


