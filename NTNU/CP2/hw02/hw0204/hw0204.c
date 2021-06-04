#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    FILE *scriptF = NULL;
    FILE *makeF = NULL;
    FILE *testF = NULL; 
    char scriptName[256] = {};
    char header[16][256] = {}, source[16][256] = {}, buffer[1024] = {};
    char func[1024] = {}, tmp[256]  = {};
    int ans = 0, cnt = 1, h = 0, s = 0, len = 20;
    bool flag = true;
    printf("Please enter the test script: ");
    scanf("%s", scriptName);
    if((scriptF = fopen(scriptName, "r")) == NULL) {
        printf("script open failed");
        return 0;
    }
    if((makeF = fopen("Makefile", "w")) == NULL) {
        printf("Makefile open failed");
        return 0;
    }
    if((testF = fopen("a.c", "w")) == NULL) {
        printf("a.c open failed");
        return 0;
    }
    while(flag) {
        flag = false;
        if(fscanf(scriptF, "INCLUDE( %s )\n", header[h++]) > 1) flag = true;
        if(fscanf(scriptF, "REQUIRE( %s )\n", source[s++]) > 1) flag = true;
    }
    //printf("%s\n%s\n", header, source);
    fprintf(testF, "#include <stdio.h>\n");
    for(int i = 0; i < h; i++) {
        fprintf(testF, "#include \"%s\"\n", header[i]);
        len += 13 + strlen(header[i]);
    }
    memset(buffer, ' ', sizeof(buffer));
    fprintf(testF, "int main(){\n%s\n", buffer);
    while(!feof(scriptF)) {
        if(fscanf(scriptF, "EXPECT_EQ(%d, %s\n", &ans, func) < 1) {
            fgetc(scriptF);
            continue;
        }
        //fgetc(scriptF);
        //fgets(tmp, sizeof(tmp), scriptF);
        func[strlen(func)-2] = 0;
        fprintf(testF, "\tprintf(\"%d) %s: \");\n", cnt++, func);
        fprintf(testF, "\tif(%d == %s)\n\t\tprintf(\"PASS\\n\");\n\telse\n\t\tprintf(\"return value = %%d, expected value = %%d\\n\", %s, %d);\n", ans, func, func, ans);
        printf("EXPECT_EQ(%d, %s);\n", ans, func);
        if(cnt > 20) {
            printf("error\n");
            break;
        }
    }
    fprintf(testF, "\treturn 0;\n}\n");
    fseek(testF, 43+len, SEEK_SET);
    fprintf(testF, "\tprintf(\"Running %d test cases:\\n\");\n", cnt-1);
    fprintf(makeF,"src=a.c ");
    for(int i = 0; i < s; i++)
        fprintf(makeF, "%s%c", source[i], " \n"[i==s-1]);

    fprintf(makeF,"\nall:\n\tgcc hw0204.c -o hw0204\n\tgcc $(src)");
    printf("a.c and Makefile are generated.\n");
    fclose(makeF);
}

