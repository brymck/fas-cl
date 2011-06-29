// my first real program in C++
#include <iostream>
#include <string>
#include <stdlib.h>
#include "models/ansi.cpp"
#include "controllers/lookup.cpp"
using namespace std;
using namespace ansi;

enum Command { HELP, EXIT, ABOUT, NOT_FOUND };
struct Keyword
{
  const char* word;
  Command command;
};
Keyword keywords[] = {
  { "?",     HELP },
  { "about", ABOUT },
  { "exit",  EXIT },
  { "h",     HELP },
  { "help",  HELP },
  { "x",     EXIT }
};
const int keylen = 6;

void help()
{
  cout << "  " << BLUE <<
            "Command        Action" << RESET << endl
       << "  ?, h, help     Show help" << endl
       << "  a, about       Show about information" << endl
       << "  x, exit        Exit program" << endl
       << "  anything else  Attempt to look up input as ticker symbol" << endl;
}

void about()
{
  cout << "  Program: FinAn$u command-line" << endl
       << "  Author:  Bryan McKelvey" << endl
       << "  Email:   bryan.mckelvey@gmail.com" << endl;
}

int compareKeywords(const void * a, const void * b)
{
  Keyword* keyword = (Keyword*)a;
  string* key = (string*)b;
  /*
  cout << "  a: " << keyword->word << endl
       << "  b: " << key->c_str() << endl
       << "  c: " << strcmp(keyword->word, key->c_str()) << endl;
   */

  return strcmp(keyword->word, key->c_str());
}

bool tokenize(string command)
{
  Keyword * result;
  result = (Keyword*) bsearch (&command, keywords, keylen, sizeof (Keyword), compareKeywords);
  if (result != NULL)
  {
    switch (result->command)
    {
      case ABOUT:
        about();
        return true;
      case EXIT:
        return false;
      case HELP:
        help();
        return true;
      default:
        cout << "Default" << endl;
        return true;
    }
  }
  else
  {
    Lookup l;
    string result;
    string * url = new string("http://www.bloomberg.com/apps/quote?ticker=");
    url->append(command);
    result = l.request(url);
    cout << "  " << "Price change is " << ansi::BLUE << result << ansi::RESET << endl;
    return true;
  }
}

int main(int argc, char* argv[])
{
  string command;

  do { 
    cout << GREEN << "$ " << RESET;
    cin >> command;
  } while (tokenize(command));

  return 0;
}
