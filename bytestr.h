#ifndef BYTESTR_H
#define BYTESTR_H

#include "sys_headers.h"

typedef struct {
  void* data;
  size_t data_size;
} bytestr;

bytestr bstr_convert_str(char* str);

#endif
