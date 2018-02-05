#include "sys_headers.h"

typedef struct {
  char** appended_strs;
  size_t num_appends;
} strbuilder;

strbuilder* sb_get();
void sb_append(strbuilder* sb, char* str);
void sb_appendbyte(strbuilder* sb, uint8_t byte);
void sb_appendline(strbuilder* sb);
char* sb_tostring(strbuilder* sb);
void sb_free(strbuilder* sb);
char* sb_tostring_and_free(strbuilder* sb);

