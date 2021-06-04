#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <assert.h>
#include <string.h>
#include <getopt.h>

typedef struct _Flight {
    char time[18];
    char dep[4];
    char arr[4];
    char airline[10];
    char flight[10];
}Flight;

int time_cmp(const void* a, const void* b) {
    const Flight x = *(const Flight*)a, y = *(const Flight*)b;
    return strcmp(x.time, y.time);
}
int flight_cmp(const void* a, const void* b) {
    const Flight x = *(const Flight*)a, y = *(const Flight*)b;
    return strcmp(x.flight, y.flight);
}
int airline_cmp(const void* a, const void* b) {
    const Flight x = *(const Flight*)a, y = *(const Flight*)b;
    return strcmp(x.airline, y.airline);
}

struct option long_options[] = {
    {"arrival-time", 0, NULL, 't'},
    {"flight-number", 0, NULL, 'f'},
    {"airline-id", 0, NULL, 'a'}
};

void show(Flight f) {
    if(f.time[0] == 0)
        printf("NULL ");
    else 
        printf("%s ",f.time);
    if(f.dep[0] == 0)
        printf("NULL-->");
    else 
        printf("%s-->", f.dep);
    if(f.arr[0] == 0)
        printf("NULL ");
    else 
        printf("%s ", f.arr);
    if(f.airline[0] == 0)
        printf("NULL ");
    else 
        printf("%s ", f.airline);
    if(f.flight[0] == 0)
        printf("NULL\n");
    else 
        printf("%s\n", f.flight);
    // printf("%s %s-->%s %s %s\n", f.time, f.dep, f.arr, f.airline, f.flight);
}


int main(int argc, char* argv[]) {
    CURL *curl;
    CURLcode res;
    FILE *header = popen("PTX_APP_ID=\'802001dbafe144269d87f7da2c702b15\' && PTX_APP_KEY=\'NoUnrCf2IiMQ3w90wlY_7ghzFRE\' && now=$(env TZ=GMT LANG=en_US date \'+%a, %d %b %Y %T %Z\') && signature=$(printf \"x-date: $now\" | openssl sha1 -binary -hmac $PTX_APP_KEY | base64) && echo \'Authorization: hmac username=\"\'$PTX_APP_ID\'\", algorithm=\"hmac-sha1\", headers=\"x-date\", signature=\"\'$signature\'\"\' && echo \''x-date': \'$now","r");
    FILE *fp = fopen("tmp.txt", "w");
    assert(fp);

    char buffer[1000] = {};
    
 
    curl = curl_easy_init();
    if(curl) {
        struct curl_slist *chunk = NULL;
        fgets(buffer, sizeof(buffer), header);
        // fputs(buffer, stdout);
        buffer[strlen(buffer)-1]=0;
        /* Remove a header curl would otherwise add by itself */ 
        chunk = curl_slist_append(chunk, buffer);


        fgets(buffer, sizeof(buffer), header);
        // fputs(buffer, stdout);
        buffer[strlen(buffer)-1]=0; 
        /* Add a custom header */ 
        chunk = curl_slist_append(chunk, buffer);
    
        /* set our custom set of headers */ 
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    
        curl_easy_setopt(curl, CURLOPT_URL, "https://ptx.transportdata.tw/MOTC/v2/Air/FIDS/Airport/Arrival");
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, fp );
    
        res = curl_easy_perform(curl);
        /* Check for errors */ 
        if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    
        /* always cleanup */ 
        curl_easy_cleanup(curl);
    
        /* free the custom headers */ 
        curl_slist_free_all(chunk);

        fclose(fp);
    }
    
    Flight all_flight[10000];
    char context[100000] = {}, c;
    char tmp[100000] = {};
    char *str = NULL;
    char *token = NULL;
    char *result = NULL;
    size_t size = 0;
    size_t flight_cnt = 0;
    int index = 0;
    char opt = 0 ;

    memset(all_flight, 0, sizeof(all_flight));
    fp = fopen("tmp.txt", "r");
    assert(fp);
    while((c = fgetc(fp)) != EOF) {
        str = NULL;
        token = NULL;
        result = NULL;
        memset(context, 0, sizeof(context));
        size = 0;
        if(c == '{') {
            while((c = fgetc(fp)) != '}') context[size++] = c;
            // printf("|| context: \n%s ||\n\n", context);
        }
        if(size > 1) {
            strcpy(tmp, context);
            if((str = strstr(tmp, "ScheduleArrivalTime")) != NULL) {

                token = strtok(str, "\"");
                token = strtok(NULL, "\"");
                token = strtok(NULL, "\"");
                if(token[0] != ',') 
                    strcpy(all_flight[flight_cnt].time, token);
                else 
                    all_flight[flight_cnt].time[0] = 0;
            }
            // printf("%s ", all_flight[flight_cnt].time);
            strcpy(tmp, context);
            if((str = strstr(tmp, "DepartureAirportID")) != NULL) {
                token = strtok(str, "\"");
                token = strtok(NULL, "\"");
                token = strtok(NULL, "\"");
                if(token[0] != ',') 
                    strcpy(all_flight[flight_cnt].dep, token);
                else 
                    all_flight[flight_cnt].dep[0] = 0;
            }
            // printf("%s-->", all_flight[flight_cnt].dep);
            strcpy(tmp, context);
            if((str = strstr(tmp, "ArrivalAirportID")) != NULL) {
                token = strtok(str, "\"");
                token = strtok(NULL, "\"");
                token = strtok(NULL, "\"");
                // token = strtok(NULL, "\"");
                if(token[0] != ',') 
                    strcpy(all_flight[flight_cnt].arr, token);
                else 
                    all_flight[flight_cnt].arr[0] = 0;
            }
            // printf("%s ", all_flight[flight_cnt].arr);
            strcpy(tmp, context);
            if((str = strstr(tmp, "AirlineID")) != NULL) {
                token = strtok(str, "\"");
                token = strtok(NULL, "\"");
                token = strtok(NULL, "\"");
                if(token[0] != ',') 
                    strcpy(all_flight[flight_cnt].airline, token);
                else 
                    all_flight[flight_cnt].airline[0] = 0;
            }
            // printf("%s ", all_flight[flight_cnt].airline);
            strcpy(tmp, context);
            if((str = strstr(tmp, "FlightNumber")) != NULL) {
                token = strtok(str, "\"");
                token = strtok(NULL, "\"");
                token = strtok(NULL, "\"");
                strcpy(all_flight[flight_cnt].flight, token);
            }
            // printf("%s\n", all_flight[flight_cnt].flight);
            ++flight_cnt;
        }

    }
    if((opt = getopt_long(argc, argv, "tfa", long_options, &index)) != -1) {
        switch (opt) {
        case 't':
            qsort(all_flight, flight_cnt, sizeof(Flight), time_cmp);
            break;
        case 'f':
            qsort(all_flight, flight_cnt, sizeof(Flight), flight_cmp);
            break;
        case 'a':
            qsort(all_flight, flight_cnt, sizeof(Flight), airline_cmp);
            break;
        default:
            break;
        }
    }
    
    for(size_t i = 0; i < flight_cnt; ++i)
        show(all_flight[i]);
    // printf("cnt: %d\n", flight_cnt);
    fclose(fp);
    remove("tmp.txt");
    
  return 0;
}