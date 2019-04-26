#include "mlisp.h"

double a = 19;
double b = 20;

double fun(double x);

double eps = 0.00001;

double golden__section__search(double a, double b);

double golden__start(double a, double b);

double mphi = 0.5 * (1 + sqrt(5));

double __dao__try(double a, double b, double x1, double y1, double x2, double y2);

double xmin = 0;

int main() {

    xmin = golden__section__search(a, b);
    display("interval=\t[");
    display(a);
    display(" , ");
    display(b);
    display("]\n");
    display("xmin=\t\t");
    std::cout << xmin << std::endl;
    display("f(xmin)=\t");
    std::cout << fun(xmin) << std::endl;
    return 0;
}

double fun(double x) {
    x = x - (107 / (108 / e));
    return 0.1 * expt(x, 2) - x * log(x);
}

double golden__section__search(double a, double b) {
    double xmin((a < b) ? golden__start(a, b) : golden__start(b, a));
    newline();
    return xmin;
}

double golden__start(double a, double b) {
    double x1 = (b - ((double) (b - a) / mphi));
    double x2 = (a + ((double) (b - a) / mphi));

    return __dao__try(a, b, x1, fun(x1), x2, fun(x2));
}

double __dao__try(double a, double b, double x1, double y1, double x2, double y2) {
    return (abs(a - b) < eps)
           ? ((a + b) * 0.5)
           : (true ?
              (display("+"), (y1 < y2)
                             ?
                             (
                                     b = x2,
                                     x2 = a + ((double) (b - a) / mphi),
                                     x1 = b - ((double) (b - a) / mphi),
                                     __dao__try(a, b, x1, fun(x1), x2, fun(x2))
                             )
                             :
                             (
                                     a = x1,
                                     x2 = a + ((double) (b - a) / mphi),
                                     x1 = b - ((double) (b - a) / mphi),
                                     __dao__try(a, b, x1, fun(x1), x2, fun(x2))
                             )
              )

                   : _infinity
           );
}
