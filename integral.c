#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define abs(x) (((x) < 0) ? -(x) : (x)) // absolute value of x

const double EPS1 = 0.000001;
const double EPS2 = 0.000001;

int root_iterations = 0; // root iterations bruh

typedef double afunc(double);


extern double f1(double x);
extern double df1(double x);
extern double f2(double x);
extern double df2(double x);
extern double f3(double x);
extern double df3(double x);


typedef struct { // pair of functions which F_impl uses
    afunc *f;
    afunc *g;
} FuncPair;

double F_impl(FuncPair *funcs, double x) { // difference of 2 functions at point x
    return funcs->f(x) - funcs->g(x);
}

FuncPair curF = {NULL, NULL};     // This
FuncPair curdF = {NULL, NULL};    // is
FuncPair curddF = {NULL, NULL};   // for
                                  // convenient
#define F(x) F_impl(&curF, x)     // use
#define dF(x) F_impl(&curdF, x)   // of
#define ddF(x) F_impl(&curddF, x) // F(x)



double root(afunc *f, afunc *g, double a, double b, double eps, afunc *df, afunc *dg);
double integral(afunc *f, double a, double b, double eps);

double root(afunc *f, afunc *g, double a, double b, double eps, afunc *df, afunc *dg) {
    curF.f = f; curF.g = g;
    curdF.f = df; curdF.g = dg;

    bool sign1 = (F(a) < 0); // sign1 = true if F increases
    bool sign2 = (F((a + b) / (double)2) > (F(a) + F(b)) / (double)2); // sign2 = true if graph of F is above the chord
    bool case_flag = (sign1 != sign2); // case_flag = true if F`(x)F``(x) > 0
    
    root_iterations = 0;
    while (b - a > eps) { // exit check
        double c1 = (a * F(b) - b * F(a)) / (F(b) - F(a)); // chord method
        double d = case_flag ? b : a;
        double c2 = d - (F(d) / dF(d)); // tangent method
        if (case_flag) {
            a = c1;
            b = c2;
        } else {
            a = c2;
            b = c1;
        }
        ++root_iterations;
    }
    return (a + b) / (double)2;
}

double integral(afunc *f, double a, double b, double eps) {
    double h = b - a;
    double sum2 = f(a) + f(b), sum4 = 0; // sum2 = F0 + 2*Fi + Fn  ,  sum4 = 4*Fi
    double I = sum2 * h / 3, prev_I = 0;

    while(abs(prev_I - I) / 15 > eps) {
        double x = a + h / 2;
        sum2 += sum4 / 2;
        sum4 = 0;
        while (x < b) {
            sum4 += 4 * f(x);
            x += h;
        }
        h /= 2;
        prev_I = I;
        I = (sum2 + sum4) * h / 3;
    }

    return I;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    if (argc > 3) {
        printf("I was stupid once too...\n but just once.\n");
        return 0;
    }
    if (argc == 1) {
        double a = root(f1, f2, 6.0, 6.1, EPS1, df1, df2);
        double b = root(f3, f2, 4.2, 4.3, EPS1, df3, df2);
        double c = root(f3, f1, 2.1, 2.2, EPS1, df1, df3);
        printf("Area : %lf\n", integral(f3, c, b, EPS2) + integral(f2, b, a, EPS2) - integral(f1, c, a, EPS2));
        return 0;
    }
    if (strcmp(argv[1], "--root") == 0 || strcmp(argv[1], "-r") == 0) {
        double a = root(f1, f2, 6.0, 6.1, EPS1, df1, df2);
        double b = root(f3, f2, 4.2, 4.3, EPS1, df3, df2);
        double c = root(f3, f1, 2.1, 2.2, EPS1, df1, df3);
        printf("f1f2: %lf\nf2f3: %lf\nf3f1: %lf\n", a, b, c);
    }
    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "help") == 0) {
        printf("Use './integral [option]'\n");
        printf("Options:\n");
        printf("`Nothing` for area calculation\n");
        printf("-h or --help for help (u must have already possessed this deepest knowledge by now)\n");
        printf("-r or --root for calculation of roots obviously\n");
        printf("-i or --iterations for number of iterations in root function, idk why one needs that\n");
        printf("-R or --test-root f1:f2:a:b:eps:res to test root function\n");
        printf("-I or --test-integral f1:a:b:eps:res to test integral function, unexpected, right?\n");
        return 0;
    }
    if (strcmp(argv[1], "--iterations") == 0 || strcmp(argv[1], "-i") == 0) {
        root(f1, f2, 6.0, 6.1, EPS1, df1, df2);
        printf("%d iterations for f1f2\n", root_iterations);
        root(f3, f2, 4.2, 4.3, EPS1, df3, df2);
        printf("%d iterations for f1f3\n", root_iterations);
        root(f3, f1, 2.1, 2.2, EPS1, df1, df3);
        printf("%d iterations for f3f1\n", root_iterations);
        return 0;
    }
    if (strcmp(argv[1], "--test-root") == 0 || strcmp(argv[1], "-R") == 0) {
        if (argc < 3) {
            int rnd_ = rand() % 3;
            if (rnd_ == 0)
                printf("test root on WHAT??? AIR??? ENTER THE FCKN PARAMETERS\n");
            else if (rnd_ == 1)
                printf("no\n");
            else
                printf("Please specify the data on which the function will be tested\n");
            return 0;
        }
        int f, g;
        afunc* fs[4] = {NULL, f1, f2, f3};
        afunc* dfs[4] = {NULL, df1, df2, df3};
        double a, b, eps, r;
        sscanf(argv[2], "%d:%d:%lf:%lf:%lf:%lf", &f, &g, &a, &b, &eps, &r);
        if (f == 3) {
            f = g;
            g = 3;
        }
        double ans = root(fs[f], fs[g], a, b, eps, dfs[f], dfs[g]);
        printf("%lf %lf %lf\n", ans, abs(ans - r), abs((ans - r) / r));
        return 0;
    }
    if (strcmp(argv[1], "--test-integral") == 0 || strcmp(argv[1], "-I") == 0) {
        if (argc < 3) {
            int rnd_ = rand() % 3;
            if (rnd_ == 0)
                printf("maybe --help will help you\n");
            else if (rnd_ == 1)
                printf("no, never\n");
            else
                printf("this option needs parameters, cmon\n");
            return 0;
        }
        int f;
        afunc* fs[4] = {NULL, f1, f2, f3};
        double a, b, eps, r;
        sscanf(argv[2], "%d:%lf:%lf:%lf:%lf", &f, &a, &b, &eps, &r);
        double ans = integral(fs[f], a, b, eps);
        printf("%lf %lf %lf\n", ans, abs(ans - r), abs((ans - r) / r));
        return 0;
    }
    printf("seek help bro\n");
    return 0;
}