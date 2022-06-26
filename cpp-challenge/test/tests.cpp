#include "buggy/buggy.h"
#include <gtest/gtest.h>
#include <fstream>

using namespace std;

TEST(BuggyTest, InitTest) {
    Buggy myBuggy;
    int totalfound = myBuggy.getTotalFound();
    ASSERT_EQ(0, totalfound);
    thread t1(&Buggy::readInputWords, &myBuggy);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::ifstream ifs;
    ifs.open("input_data.txt", std::ifstream::in);
    myBuggy.printWords();
    myBuggy.lookupWords();
    t1.detach();
}
 
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
