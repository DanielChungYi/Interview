#include "buggy/buggy.cxx"

int main() {
    Buggy myBuggy;
    try
    {
        myBuggy.readInputWords();
        myBuggy.printWords();
        myBuggy.lookupWords();

        printf( "\n=== Total words found: %d\n", myBuggy.getTotalFound());
    }
    catch (std::exception & e)
    {
        std::printf( "error %s\n", e.what() );
    }
      
    return 0;
}
