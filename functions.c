#include <math.h>

double f1(double);
double df1(double);
double f2(double);
double df2(double);
double f3(double);
double df3(double);

double f1(double x) {
    return log(x);
}

double df1(double x) {
    return (double)1 / x;
}

double f2(double x) {
    return (double)(-2) * x + (double)14;
}

double df2(double x) {
    return (double)(-2);
}

double f3(double x) {
    return (double)1 / ((double)2 - x) + (double)6;
}

double df3(double x) {
    return (double)(-1) / (((double)2 - x) * ((double)2 - x));
}
