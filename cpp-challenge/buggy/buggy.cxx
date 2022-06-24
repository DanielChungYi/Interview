#include "buggy.h"

void Buggy::workerThread() {
    bool endEncountered = false;
    bool found = false;
  
    while (!endEncountered) {

        if (got_word) { // Do we have a new word?

                got_word = false; // Inform the producer that we consumed the word */

                endEncountered = std::strcmp( s_word.data, "end" ) == 0;

                Word *w = new Word(s_word.data, 1); // Copy the word

            if (!endEncountered) {
                    // Do not insert duplicate words, use input string as hash key
                    std::string input_word = s_word.data;
                if (s_wordsArray.find(input_word) == s_wordsArray.end()) {
                    //not found
                    s_wordsArray.insert(std::pair<std::string, Word*>(input_word, w));
                } else {
                    //found
                    s_wordsArray[input_word]->count++;
                }
            }
        }
    }// end while
};

void Buggy::readInputWords() {
    bool endEncountered = false;

    std::thread * worker = new std::thread( [this] { workerThread(); } );

    char * linebuf = new char[32];

    while (!endEncountered)
    {
        std::cin >> linebuf;
        if (!std::cin.good()) return;

        endEncountered = std::strcmp( linebuf, "end" ) == 0;

        // Pass the word to the worker thread
        s_word.data = linebuf;
        got_word = true;
        while(got_word); // Wait for the worker thread to consume it
    }

    worker->join(); // Wait for the worker to terminate
}

void Buggy::lookupWords() {
    bool found;
    std::string linebuf;

    for(;;)
    {
        std::printf( "\nEnter a word for lookup:" );
        std::cin >> linebuf;
        if (!std::cin.good()) return;


        // Search for the word
        if (s_wordsArray.find(linebuf) == s_wordsArray.end()) {
            //not found
            std::printf( "'%s' was NOT found in the initial word list\n", linebuf.c_str());
        } else {
            //found
            std::printf( "SUCCESS: '%s' was present %d times in the initial word list\n",
            linebuf.c_str(), s_wordsArray[linebuf]->count );
            ++s_totalFound;
        }
    }
}

void Buggy::printWords() {
    std::printf( "\n=== Word list:\n" );
    for ( auto p : s_wordsArray )
        std::printf( "%s %d\n", p.first.c_str(), p.second->count);
}

int Buggy::getTotalFound() {
    return s_totalFound;
}
