#ifndef BUGGY_H_
#define BUGGY_H_

#include <cstring>
#include <iostream>
#include <atomic>
#include <map>
#include <string>
#include <thread>

struct Word
{
    char * data;
    int count;

    Word ( char * data_) :
        data( ::strdup(data_) )
    {}

    Word ( char * data_, int count_) :
        data( ::strdup(data_) ),
        count(count_)
    {}
 
    Word () :
       data((char *)"")
   {}
};


class Buggy {

    public:
        // Worker thread: consume words passed from the main thread and insert them
        // in the 'word list' (s_wordsArray), while removing duplicates. Terminate when
        // the word 'end' is encountered.
        void workerThread();

        // Read input words from STDIN and pass them to the worker thread for
        // inclusion in the word list.
        // Terminate when the word 'end' has been entered.
        void readInputWords();

        // Repeatedly ask the user for a word and check whether it was present in the word list
        // Terminate on EOF
        void lookupWords();

        // Print the word list
        void printWords();

        // Get private member variable total_found
        int getTotalFound();

    private:
        std::atomic<bool> got_word {false};
        std::map<std::string, Word*> s_wordsArray;
        Word s_word;
        int s_totalFound = 0;
};

#endif //BUGGY_H_
