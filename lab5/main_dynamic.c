#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <math.h>
#include <stdbool.h>

const char LIB1[] = "./libd1_dynamic.so";
const char LIB2[] = "./libd2_dynamic.so";

int main(int argc, char* argv[]) {
    void *library;
    bool flag = false;
    int x, K;
    double a, b, e;

    library = dlopen(LIB2, RTLD_LAZY);
    if (!library) {
        printf("Error dlopen(): %s\n", dlerror());
        return 1;
    }

    double(*Integrate)(double a, double b, double e);
    double(*Pi)(int K);
    *(void**)(&Integrate) = dlsym(library, "Integrate");
    *(void**)(&Pi) = dlsym(library, "Pi");

    for (;;) {
        scanf("%d", &x);
        if (x == 0) {
            dlclose(library);
            if (flag) {
                library = dlopen(LIB2, RTLD_LAZY);
                flag = false;
            } else {
                library = dlopen(LIB1, RTLD_LAZY);
                flag = true;
            }
            if (!library) {
                printf("Error dlopen(): %s\n", dlerror());
                return 1;
            }
            *(void**)(&Integrate) = dlsym(library, "Integrate");
            *(void**)(&Pi) = dlsym(library, "Pi");
        } else if (x == 1) {
            scanf("%lf %lf %lf", &a, &b, &e);
            printf("Result: ");
            double res = Integrate(a, b, e);
            printf("%lf\n", res);
        } else if (x == 2) {
            scanf("%d", &K);
            printf("Result: ");
            double res = Pi(K);
            printf("%lf\n", res);
        } else {
            dlclose(library);
            return 0;
        }
    }
    return 0;
}