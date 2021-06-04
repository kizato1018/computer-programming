#include <stdio.h>
#include <stddef.h>
#include <dirent.h>


int main(int argc, char * argv[]) {
    DIR * dp;
    struct dirent * dirp;
    
    if (argc != 2) {
        printf("usage: ./hw0505 'directory name\n'");
        return -1;
    }

    if ( (dp = opendir(argv[1])) == NULL) {
        printf("open %s failed", argv[1]);
        return -1;
    }

    while ( (dirp = readdir(dp)) != NULL ) {
        printf("%s  ", dirp->d_name);
    }

    closedir(dp);
    return 0;
}
