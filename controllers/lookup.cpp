#include <iostream>
#include <string>
#include <string.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
using namespace std;

class Lookup 
{
  private:
    static size_t write_data(char *buffer, size_t size, size_t nmemb, void *data)
    {
      size_t realsize = size * nmemb;
      string *mem = (string *)data;

      // Copy buffer into last block in memory
      mem->append(buffer);

      return realsize;
    }

    string parse(string str, char *start, char *end)
    {
      size_t start_pos = str.find(start) + strlen(start);
      size_t end_pos = str.find(end, start_pos);
      return str.substr(start_pos, end_pos - start_pos);
    }

  public:
    string request(string* url)
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

      return parse(response, (char*)"<div class=\"delta\">", (char*)"<");
    }
};
