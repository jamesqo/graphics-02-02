#ifndef P6_DATA_H
#define P6_DATA_H

#include "sys_headers.h"

#include "pixel.h"

typedef struct {
  pixel** pixels;
  size_t width;
  size_t height;
} p6_data;

#endif
