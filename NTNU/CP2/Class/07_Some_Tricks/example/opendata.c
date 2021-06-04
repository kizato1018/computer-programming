#include <stdio.h>
#include <curl/curl.h>
#include <assert.h>
 
int main(void)
{
    CURL *curl;
    CURLcode res;
 
    curl = curl_easy_init();
  
    if(curl) 
    {
        curl_easy_setopt( curl, CURLOPT_URL, "https://data.taipei/opendata/datalist/apiAccess?scope=resourceAquire&rid=35aa3c53-28fb-423c-91b6-2c22432d0d70" );
        
        FILE *pFile = fopen( "123.txt", "w" );
        assert( pFile );
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, pFile );
        
        /* Perform the request, res will get the return code */ 
        res = curl_easy_perform(curl);
        /* Check for errors */ 
        if( res != CURLE_OK )
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
         
        /* always cleanup */ 
        curl_easy_cleanup(curl);
        fclose( pFile );
    }
    return 0;
}
