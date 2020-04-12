#include <stdio.h>
#include <string.h>

int main() {
    FILE *scriptF = NULL;
    FILE *makeF = NULL;
    FILE *testF = NULL; 
    char scriptName[256] = {};
    char header[256] = {}, source[256] = {};
    char func[1024] = {}, tmp[256]  = {};
    int ans = 0, cnt = 1;
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
    fscanf(scriptF, "INCLUDE( %s )\n", header);
    fscanf(scriptF, "REQUIRE( %s )\n", source);
    printf("%s\n%s\n", header, source);
    fprintf(testF, "#include <stdio.h>\n#include \"%s\"\n", header);
    fprintf(testF, "int main(){\n                                              ");
    while(!feof(scriptF)) {
        if(fscanf(scriptF, "EXPECT_EQ(%d, %s", &ans, func) < 1) {
            fgetc(scriptF);
            continue;
        }
        fgets(tmp, sizeof(tmp), scriptF);
        func[strlen(func)-2] = 0;
        fprintf(testF, "\tprintf(\"%d) %s: %%s\\n\",(%d == %s) ? \"PASS\" : \"WRONG\");\n", cnt++, func, ans, func);
        printf("EXPECT_EQ(%d, %s);\n", ans, func);
        if(cnt > 20) {
            printf("error\n");
            break;
        }
    }
    fprintf(testF, "\treturn 0;\n}\n");
    fseek(testF, 43+strlen(header), SEEK_SET);
    fprintf(testF, "\tprintf(\"Running %d test cases:\\n\");\n", cnt-1);
    fprintf(makeF,"src=a.c %s\n", source);

    fprintf(makeF,"\nall:\n\tgcc hw0204.c -o hw0204\n\tgcc $(src)");
    printf("a.c and Makefile are generated.\n");
    fclose(makeF);
}