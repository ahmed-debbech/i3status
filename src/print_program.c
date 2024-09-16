// vim:ts=4:sw=4:expandtab
#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include "i3status.h"
#include <yajl/yajl_gen.h>
#include <yajl/yajl_version.h>
#include <mntent.h>

#define STRING_SIZE 20

void script1(){
    char bash_cmd[256] = "node /home/swared/fun/newp/n.js";
    char buffer[1000];
    FILE *pipe;
    int len; 

    pipe = popen(bash_cmd, "r");

    if (NULL == pipe) {
        perror("pipe");
        exit(1);
    } 

    fgets(buffer, sizeof(buffer), pipe);

    len = strlen(buffer);
    buffer[len-1] = '\0'; 

    pclose(pipe);
}
char * script2(){
    char bash_cmd[256] = "cat /home/swared/fun/newp/g";
    char * buffer = malloc(sizeof(char) * 1000);

    FILE *pipe;
    int len; 

    pipe = popen(bash_cmd, "r");

    if (NULL == pipe) {
        perror("pipe");
        exit(1);
    } 

    fgets(buffer, sizeof(char) * 1000, pipe);

    len = strlen(buffer);
    buffer[len-1] = '\0'; 
    pclose(pipe);
    return buffer;
}
/*
 * Does a print on 
 *
 */
void print_program(program_ctx_t *ctx) {
    const char *selected_format = ctx->format;
    char *outwalk = ctx->buf;
    bool colorful_output = false;

    INSTANCE("x");

    char stringer_result[STRING_SIZE];

    placeholder_t placeholders[] = {
        {.name = "%out", .value = stringer_result}};

    const size_t num = sizeof(placeholders) / sizeof(placeholder_t);
    char *formatted = format_placeholders(selected_format, &placeholders[0], num);
    printf("ddddd\n");
    OUTPUT_FORMATTED;
    free(formatted);

    if (colorful_output)
        END_COLOR;

    *outwalk = '\0';

    script1();
    char *t = script2();
    ctx->buf = t;
    OUTPUT_FULL_TEXT(ctx->buf);
}
