#include "func.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int x;
    double a, b, e;
    int K;

    for (;;) {
        scanf("%d", &x);
        if (x == 1) {
            scanf("%lf %lf %lf", &a, &b, &e);
            double res = Integrate(a, b, e);
            printf("%lf\n", res);
            x = 0;
        } else if (x == 2) {
            scanf("%d", &K);
            double res = Pi(K);
            printf("%lf\n", res);
            x = 0;
        } else {
            break;
        }
    }
    return 0;
}