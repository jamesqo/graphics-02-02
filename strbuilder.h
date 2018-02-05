#ifndef STRBUILDER_H
#define STRBUILDER_H

#include "sys_headers.h"

#include "bytestr.h"

typedef struct {
  bytestr* appended_strs;
  size_t capacity;
  size_t num_appends;
} strbuilder;

strbuilder* sb_get();
void sb_append(strbuilder* sb, char* str);
void sb_appendbyte(strbuilder* sb, uint8_t byte);
void sb_appendbytes(strbuilder* sb, bytestr bytes);
void sb_appendline(strbuilder* sb);
bytestr sb_tostring(strbuilder* sb);
void sb_free(strbuilder* sb);
bytestr sb_tostring_and_free(strbuilder* sb);

#endif
