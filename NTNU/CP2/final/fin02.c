#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

int main() {
    int64_t u = 0, n = 0, s = 0, i = 0;
    int64_t u_t = 0, n_t = 0, s_t = 0, i_t = 0;
    int64_t use = 0, all = 0;
    double usage = 0;
    FILE *fp = NULL;
    while(1) {
        if((fp = fopen("/proc/stat", "r")) == NULL) {
            printf("open error\n");
            return 1;
        }
        fscanf(fp, "%*s %ld %ld %ld %ld", &u, &n, &s, &i);
        // printf("%ld %ld %ld %ld\n", u, n, s, i);
        if(u_t == 0) u_t = u;
        if(n_t == 0) n_t = n;
        if(s_t == 0) s_t = s;
        if(i_t == 0) i_t = i;
        all = (u-u_t)+(n-n_t)+(s-s_t)+(i-i_t);
        use = (u-u_t)+(n-n_t)+(s-s_t);
        if(all != 0) {
            usage = (double)use/all * 100;
            printf("CPU usage: %.2lf%%\n", usage);
        }
        fclose(fp);
        sleep(1);
    }

    return 0;
}