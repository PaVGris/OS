double Integrate(double a, double b, double epsilon)
{
    int steps = fabs(b - a) / epsilon;
    double point = a;
    double result = 0;

    for (int i = 0; i < steps; ++i)
    {
        result += sin(point) * epsilon;
        point += epsilon;
    }

    return result;
}

double Pi(int K) {
    double pi = 0;
    for(int i = 0; i <= K; i++) {
        pi += 2.0/((4*i + 1)*(4*i + 3));
    }
    return pi * 4.0;
}

