#include <iostream>
#include <string>
#include "../controllers/lookup.cpp"
#include "../models/security.cpp"
using namespace std;

namespace ansi
{
   const char RESET[]   = "\x1b[0m";
   const char RED[]     = "\x1b[31m";
   const char GREEN[]   = "\x1b[32m";
   const char YELLOW[]  = "\x1b[33m";
   const char BLUE[]    = "\x1b[34m";
   const char MAGENTA[] = "\x1b[35m";
   const char CYAN[]    = "\x1b[36m";
}

class Console
{
  public:
    void read()
    {
      string input;

      do
      {
        cout << ansi::BLUE << "fas> " << ansi::RESET;
        cin >> input;
      } while (input != "" && input != "exit");
    }
};
