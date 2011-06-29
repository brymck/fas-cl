// my first real program in C++
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
#include "console/ansi.cpp"
#include "security.cpp"
using namespace std;
using namespace ansi;

static size_t write_data(char *buffer, size_t size, size_t nmemb, void *data)
{
  size_t realsize = size * nmemb;
  string *mem = (string *)data;

  // Copy buffer into last block in memory
  mem->append(buffer);

  return realsize;
}

string get_value(string str, char *start, char *end)
{
  size_t start_pos = str.find(start) + strlen(start);
  size_t end_pos = str.find(end, start_pos);
  return str.substr(start_pos, end_pos - start_pos);
}

string do_web_request(string *url)
{
  // Create handle to the cURL object
  CURL *curl_handle;
  string response;

  curl_global_init(CURL_GLOBAL_ALL);

  // Initialize cURL and set URL
  curl_handle = curl_easy_init();
  curl_easy_setopt(curl_handle, CURLOPT_URL, url->c_str());
  curl_easy_setopt(curl_handle, CURLOPT_HTTPGET, 1);

  //  Follow redirect if necessary
  curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1);

  // Set callback
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&response);

  // Run and clean up
  curl_easy_perform(curl_handle);
  curl_easy_cleanup(curl_handle);
  curl_global_cleanup();

  return get_value(response, (char*)"<div class=\"delta\">", (char*)"<");
}

int main(int argc, char* argv[])
{
  string *url = new string("http://www.bloomberg.com/apps/quote?ticker=");
  // strcat(url, "WFC:US");
  string content;
  if (argv[1])
  {
    url->append((string)argv[1]);
    
    content = do_web_request(url);

    // Do other stuff
    cout << "Price change of " << YELLOW << argv[1] << COL_RESET << " is "
         << GREEN << content << COL_RESET << "." << endl;
    return 0;
  }
  else
  {
    cout << RED << "Error: " << COL_RESET << "No symbol provided." << endl
         << "  Example: " << YELLOW << "fas WFC" << COL_RESET << endl;
  }
}
