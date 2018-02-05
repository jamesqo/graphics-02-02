#include "strbuilder.h"

#include "bytestr.h"

#define SB_INIT_CAPACITY 4
#define SB_GROWTH_FACTOR 2

void sb_resize_(strbuilder* sb) {
  assert(sb->num_appends == sb->capacity);

  sb->capacity *= SB_GROWTH_FACTOR;
  sb->appended_strs = realloc(sb->appended_strs, sb->capacity * sizeof(bytestr));
}

strbuilder* sb_get() {
  strbuilder* sb = calloc(1, sizeof(strbuilder));
  sb->capacity = SB_INIT_CAPACITY;
  sb->appended_strs = calloc(sb->capacity, sizeof(bytestr));
  sb->num_appends = 0;
  return sb;
}

void sb_append(strbuilder* sb, char* str) {
  bytestr bstr = bstr_convert_str(str);
  sb_appendbytes(sb, bstr);
}

void sb_appendbyte(strbuilder* sb, uint8_t byte) {
  bytestr bstr;
  bstr.data = &byte;
  bstr.data_size = 1;

  sb_appendbytes(sb, bstr);
}

void sb_appendbytes(strbuilder* sb, bytestr bstr) {
  if (sb->num_appends == sb->capacity) {
    sb_resize_(sb);
  }
  sb->appended_strs[sb->num_appends] = bstr;
  sb->num_appends++;
}

void sb_appendline(strbuilder* sb) {
  sb_append(sb, "\n");
}

bytestr sb_tostring(strbuilder* sb) {
  bytestr result;
  memset(&result, 0, sizeof(result));

  for (size_t i = 0; i < sb->num_appends; i++) {
    result.data_size += sb->appended_strs[i].data_size;
  }

  result.data = calloc(result.data_size, sizeof(uint8_t));

  uint8_t* dest_ptr = result.data;
  for (size_t i = 0; i < sb->num_appends; i++) {
    bytestr src = sb->appended_strs[i];
    memcpy(dest_ptr, src.data, src.data_size * sizeof(uint8_t));
    dest_ptr += src.data_size;
  }

  return result;
}

void sb_free(strbuilder* sb) {
  free(sb->appended_strs);
  free(sb);
}

bytestr sb_tostring_and_free(strbuilder* sb) {
  bytestr result = sb_tostring(sb);
  sb_free(sb);
  return result;
}
