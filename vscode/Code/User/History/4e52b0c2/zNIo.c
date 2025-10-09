#include <math.h>
#include <stdio.h>
#include <stdlib.h>
double pythag(double a, double b);
int main(int argc, char *argv[])
{
    double a;
    double b;
    double c;

    if (argc < 3) {
        printf("usage: %s <length> <length>\n", argv[0]);
        exit(1);
    }

    a = atof(argv[1]);
    b = atof(argv[2]);

    c = pythag(3.3, 2.2);

    printf("Right triangle with sides %.2f and %.2f has "
        "hypotenuse of length %.2f\n", a, b, c);
}

double pythag(double a, double b){
    return sqrt(a * a + b * b);
}