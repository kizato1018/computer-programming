#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Time
{
    int32_t h;
    int32_t m;
    int32_t s;
    int32_t ms;
}Time;

void printT(Time a) { printf("%02d:%02d:%02d,%03d", a.h, a.m, a.s, a.ms); }

Time s2T(double s) {
    Time r;
    int i = (int) s;
    r.ms = (s-i) * 1000;
    r.s = i % 60;
    r.m = i / 60;
    r.h = i / 3600;
    return r;
}

Time add(Time a, Time b) {
    Time r;
    int carry = 0;
    r.ms = a.ms + b.ms;
    if(r.ms > 1000) {
        carry = r.ms / 1000;
        r.ms %= 1000;
    }
    else if(r.ms < 0) {
        carry = -1;
        r.ms += 1000;
    }
    r.s = a.s + b.s + carry;
    if(r.s > 60) {
        carry = r.s / 60;
        r.s %= 60;
    }
    else if(r.s < 0) {
        carry = -1;
        r.s += 60;
    }
    else carry = 0;
    r.m = a.m + b.m + carry;
    if(r.m > 60) {
        carry = r.m / 60;
        r.m %= 60; 
    }
    else if(r.m < 0) {
        carry = -1;
        r.m += 60;
    }
    else carry = 0;
    r.h = a.h + b.h + carry;
    if(r.h < 0) {
        printf("invalid shift time\n");
        exit(1);
    }
    return r;
}


int main() {
    FILE *srtF = NULL;
    FILE *orgF = NULL;
    char srtName[256] = {}, orgName[256] = {};
    char context[1024] = {};
    int8_t mode = 0;
    double offset = 0;
    Time t1, t2, offset_T;
    int32_t id, cnt = 0;
    printf("Please enter the subtitle file: ");
    scanf("%s", srtName);
    printf("Forward Shift (1) or Backward Shift (2): ");
    scanf("%hhd", &mode);
    printf("Shift time (sec): ");
    scanf("%lf", &offset);
    if((srtF = fopen(srtName, "r+")) == NULL) {
        printf("srt file open failed\n");
        return 0;
    }
    strcpy(orgName, srtName);
    strncpy(strstr(orgName, ".srt"), ".org", 4);
    if((orgF = fopen(orgName, "w+")) == NULL) {
        printf("org file create failed\n");
        return 0;
    }
    if(mode != 1 && mode != 2) {
        printf("wrong mode\n");
        return 0;
    }
    offset *= (mode == 1) ? -1 : 1;
    offset_T = s2T(offset);

    
    while(!feof(srtF)) {
        fgets(context, sizeof(context), srtF);
        fputs(context, orgF);
        cnt++;
    }

    rewind(srtF);
    rewind(orgF);

    
    while(fgets(context, sizeof(context), orgF) != NULL) {
        fputs(context, srtF);
        if(fscanf(orgF, "%d:%d:%d,%d --> %d:%d:%d,%d\n", &t1.h, &t1.m, &t1.s, &t1.ms, &t2.h, &t2.m, &t2.s, &t2.ms) < 8) break;
        t1 = add(t1, offset_T);
        t2 = add(t2, offset_T);
        fprintf(srtF, "%02d:%02d:%02d,%03d --> %02d:%02d:%02d,%03d\n", t1.h, t1.m, t1.s, t1.ms, t2.h, t2.m, t2.s, t2.ms);
        fgets(context, sizeof(context), orgF);
        fputs(context, srtF);
        fgets(context, sizeof(context), orgF);
        fputs(context, srtF);
    }
    printf("Done!\n");
    fclose(srtF);
    fclose(orgF);
}