#include <stdio.h>
#include <curl/curl.h>
#include <assert.h>
 
int main(void)
{
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://ptx.transportdata.tw/MOTC/v2/Air/FIDS/Airport/Arrival");
    /* example.com is redirected, so we tell libcurl to follow redirection */ 
    // curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    FILE *pFile = fopen( "123.txt", "w" );
    assert( pFile );
    curl_easy_setopt( curl, CURLOPT_WRITEDATA, pFile );
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  return 0;
}
