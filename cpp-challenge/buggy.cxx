#include <thread>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <atomic>
#include <map>
#include <string>

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

static std::map<std::string, Word*> s_wordsArray;
static Word s_word;
static int s_totalFound;
std::atomic<bool> got_word(false);

// Worker thread: consume words passed from the main thread and insert them
// in the 'word list' (s_wordsArray), while removing duplicates. Terminate when
// the word 'end' is encountered.
static void workerThread ()
{
  bool endEncountered = false;
  bool found = false;
  
  while (!endEncountered) {
  
    if (got_word) // Do we have a new word?
    {
      Word *w = new Word(s_word.data, 1); // Copy the word
      
      got_word = false; // Inform the producer that we consumed the word */
      
      endEncountered = std::strcmp( s_word.data, "end" ) == 0;
      
      if (!endEncountered)
      {
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

// Read input words from STDIN and pass them to the worker thread for
// inclusion in the word list.
// Terminate when the word 'end' has been entered.
//
static void readInputWords ()
{
  bool endEncountered = false;
  
  std::thread * worker = new std::thread( workerThread );

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

// Repeatedly ask the user for a word and check whether it was present in the word list
// Terminate on EOF
//
static void lookupWords ()
{
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

int main ()
{
  try
  {
    readInputWords();

    // Print the word list
    std::printf( "\n=== Word list:\n" );
    for ( auto p : s_wordsArray )
      std::printf( "%s %d\n", p.first.c_str(), p.second->count);

    lookupWords();

    printf( "\n=== Total words found: %d\n", s_totalFound );
  }
  catch (std::exception & e)
  {
    std::printf( "error %s\n", e.what() );
  }
  
  return 0;
}
