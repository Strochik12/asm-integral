#include <math.h>

double f1(double);
double df1(double);
double f2(double);
double df2(double);
double f3(double);
double df3(double);

double f1(double x) {
    return pow(3, x);
}

double df1(double x) {
    return pow(3, x) * log(3);
}

double f2(double x) {
    return pow(x, 4);
}

double df2(double x) {
    return 4 * pow(x, 3);
}

double f3(double x) {
    return (double)(1 - x) / 3;
}

double df3(double x) {
    return (double)(-1) / 3;
}