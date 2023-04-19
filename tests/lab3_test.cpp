#include <gtest/gtest.h>
#include <chrono>
#include <stdlib.h>
#include <time.h> 

extern "C" {
#include <library.h>
#include <bitonic.h>
}

#define INVALID_INPUT 403
#define WRONG_ANSWER 405 

char* testFile = "/home/gpavel/Desktop/OS/lab3/test.txt";

TEST(ThirdLabTests, IncorrectNumberOfThreads) {
	EXPECT_EQ(ThreadSort(-15, testFile), INVALID_INPUT);
	EXPECT_EQ(ThreadSort(0, testFile), INVALID_INPUT);
	std::cout << "Passed the test for incorrect input of the number of threads\n";
}

TEST(ThirdLabTests, SingleThread) {
	int answer = ThreadSort(1, testFile);
	ASSERT_FALSE(answer == WRONG_ANSWER);
}

TEST(ThirdLabTest, MultiThreads) {
	int maxThreadCount = 10;
        for(int i = 2; i < maxThreadCount; ++i) {
            double time_spent = 0;
            std::cout << "Max thread count is " << i << "\n";
            auto begin = std::chrono::high_resolution_clock::now();
            EXPECT_EQ(ThreadSort(i, testFile), 0);
            auto end = std::chrono::high_resolution_clock::now();
            time_spent += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
            std::cout << "Runtime is " << time_spent << " ms\n\n";
        }
}



