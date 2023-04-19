#include <gtest/gtest.h>
#include <array>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

extern "C" {
#include <utils.h>
#include <library.h>
}

TEST(SecondLabTests, IncorrectNumberOfThreads) {
	constexpr int inputSize = 4;
	std::array<const char*, inputSize> expectedOutput = {
		"FirstTest.",
		"CCCCCCCCCCCCCCCCCCC.",
		"End;",
		"wave..."
	};
    chdir("../lab2");
	ParentRoutine("test.txt");
	std::ifstream out;
	out.open("OutputFile.txt");
    std::string tmp;
	for(int i = 0; i < inputSize && out >> tmp; i++) {
        if(tmp == "\0") {
            i--;
            continue;
        }
	EXPECT_EQ(tmp, expectedOutput[i]);
	}
    out.close();
}
