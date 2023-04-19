#include <gtest/gtest.h>
#include <vector>
#include <math.h>
extern "C" {
    #include <func.h>
}


TEST(FiveLabTests, IntegrateTest) { 
    constexpr int inputSize = 3;

    const std::vector <std::vector <double>> input = {
        {1, 3, 0.0001},
        {-5, 1, 0.00001},
        {3.14, 6.28, 0.000001}
    };

    for (int i = 0; i < inputSize; i++){
        double output = Integrate(input[i][0],input[i][1], input[i][2]);
        double answer = -cos(input[i][1]) + cos(input[i][0]);
        EXPECT_NEAR(output, answer, 0.001);
    }


}

TEST(FiveLabTests, PiTest) { 

    constexpr int inputSize = 3;

    const std::vector <int> input = {3, 4, 7};
    const std::vector <double> expectedOutput = {3.01707, 3.04184, 3.07915};

    for (int i = 0; i < inputSize; i++){
        double output = Pi(input[i]);
        EXPECT_NEAR(output, expectedOutput[i], 0.1);
    }

}
