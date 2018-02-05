#include "strbuilder.h"

#define SB_INIT_CAPACITY 4
#define SB_GROWTH_FACTOR 2

void sb_resize_(strbuilder* sb) {
  assert(sb->num_appends == sb->capacity);

  sb->capacity *= SB_GROWTH_FACTOR;
  sb->appended_strs = realloc(sb->appended_strs, sb->capacity * sizeof(char*));
}

strbuilder* sb_get() {
  strbuilder* sb = calloc(1, sizeof(strbuilder));
  sb->capacity = SB_INIT_CAPACITY;
  sb->appended_strs = calloc(sb->capacity, sizeof(char*));
  sb->num_appends = 0;
  return sb;
}

void sb_append(strbuilder* sb, char* str) {
  if (sb->num_appends == sb->capacity) {
    sb_resize_(sb);
  }
  sb->appended_strs[sb->num_appends] = str;
  sb->num_appends++;
}

void sb_appendbyte(strbuilder* sb, uint8_t byte) {
  // TODO: This is not proper
  sb_append(sb, &byte);
}

void sb_appendline(strbuilder* sb) {
  sb_append(sb, "\n");
}

char* sb_tostring(strbuilder* sb) {
  size_t result_size = 0;
  for (size_t i = 0; i < sb->num_appends; i++) {
    result_size += strlen(sb->appended_strs[i]);
  }
  result_size += 1; // Null terminator

  char* result = calloc(result_size, sizeof(char));
  for (size_t i = 0; i < sb->num_appends; i++) {
    strcat(result, sb->appended_strs[i]);
  }
  return result;
}

void sb_free(strbuilder* sb) {
  free(sb->appended_strs);
  free(sb);
}

char* sb_tostring_and_free(strbuilder* sb) {
  char* result = sb_tostring(sb);
  sb_free(sb);
  return result;
}
