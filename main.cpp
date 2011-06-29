// my first real program in C++
#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
#include <boost/regex.hpp>
#include "ansi.cpp"
#include "security.cpp"
using namespace std;
using namespace ansi;

struct MemoryStruct
{
  char *memory;
  size_t size;
};

static size_t write_data(char *buffer, size_t size, size_t nmemb, void *data)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)data;

  mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory == NULL)
  {
    cout << RED << "Error: insufficient memory!" << COL_RESET << endl;
    exit(EXIT_FAILURE);
  }

  // Copy buffer into last block in memory
  memcpy(&(mem->memory[mem->size]), buffer, realsize);
  mem->size += realsize;

  // Zero-terminate string;
  mem->memory[mem->size] = 0;

  return realsize;
}

char *do_web_request(char *url)
{
  boost::regex re("");
  boost::smatch what;

  // Create handle to the cURL object
  CURL *curl_handle = NULL;
  struct MemoryStruct chunk;

  chunk.memory = (char*)malloc(1);
  chunk.size = 0;

  curl_global_init(CURL_GLOBAL_ALL);

  // Initialize cURL and set URL
  curl_handle = curl_easy_init();
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);
  curl_easy_setopt(curl_handle, CURLOPT_HTTPGET, 1);

  //  Follow redirect if necessary
  curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1);

  // Set callback
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

  // Run and clean up
  curl_easy_perform(curl_handle);
  curl_easy_cleanup(curl_handle);
  curl_global_cleanup();

  return chunk.memory;
}

int main(int argc, char* argv[])
{
  char *url = (char*)("http://www.bloomberg.com/apps/quote?ticker=WFC:US");
  char *content = NULL;

  content = do_web_request(url);
  printf("%s", content);

  // Do other stuff
  Security s;
  s.price = 15;
  cout << "Price is " << YELLOW << s.price << COL_RESET << endl;
  return 0;
}
