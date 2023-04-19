double Integrate(double a, double b, double epsilon)
{
    int steps = fabs(b - a) / epsilon;
    double point = a;
    double result = 0;

    for (int i = 0; i < steps; ++i)
    {
        result += sin(point + epsilon / 2) * epsilon;
        point += epsilon;
    }

    return result;
}

double Pi(int K) {
    double pi = 1;
    for (int i = 1; i <= K; i++) {
        pi *= (double)4*i*i/(4*i*i-1);
    }
    return (double)pi * 2;
}
