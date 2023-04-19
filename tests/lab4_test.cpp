#include <gtest/gtest.h>
#include <array>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>

extern "C" {
#include <library.h>
}

TEST(FourthLabTests, CorrectAnswer) {
	constexpr int inputSize = 4;
	
	std::array<const char*, inputSize> expectedOutput = {
		"FirstTest.",
		"CCCCCCCCCCCCCCCCCCC.",
		"End;",
		"wave...;"
	};
    chdir("../lab4");
	ParentRoutine("test.txt");
	std::ifstream out;
	out.open("OutputFile.txt");
    std::string tmp;
	for(int i = 0; i < inputSize && out >> tmp; i++) {
        tmp.erase(std::remove(tmp.begin(), tmp.end(), '\0'), tmp.end());
	    EXPECT_EQ(tmp, expectedOutput[i]);
	}
    out.close();
}
