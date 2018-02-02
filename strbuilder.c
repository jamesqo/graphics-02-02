#include "strbuilder.h"

strbuilder* sb_get() {
  strbuilder* sb = calloc(1, sizeof(strbuilder));
  sb
}

char* sb_tostring(strbuilder* sb) {
  size_t result_size = 0;
  for (size_t i = 0; i < sb->num_appends; i++) {
    result_size += strlen(sb->appended_strs[i]);
  }

  char* result = calloc(result_size, sizeof(char));
}
