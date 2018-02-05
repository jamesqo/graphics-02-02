#include "strbuilder.h"

#include "bytestr.h"

#define SB_INIT_CAPACITY 4
#define SB_GROWTH_FACTOR 2

void sb_resize_(strbuilder*);
void sb_add_entry_(strbuilder*, sb_entry);

void sb_add_entry_(strbuilder* sb, sb_entry entry) {
  if (sb->num_appends == sb->capacity) {
    sb_resize_(sb);
  }
  sb->entries[sb->num_appends] = entry;
  sb->num_appends++;
}

void sb_resize_(strbuilder* sb) {
  assert(sb->num_appends == sb->capacity);

  sb->capacity *= SB_GROWTH_FACTOR;
  sb->entries = realloc(sb->entries, sb->capacity * sizeof(sb_entry));
}

strbuilder* sb_get() {
  strbuilder* sb = calloc(1, sizeof(strbuilder));
  sb->capacity = SB_INIT_CAPACITY;
  sb->entries = calloc(sb->capacity, sizeof(sb_entry));
  sb->num_appends = 0;
  return sb;
}

void sb_append(strbuilder* sb, char* str) {
  bytestr bstr = bstr_convert_str(str);
  sb_appendbytes(sb, bstr);
}

void sb_appendbyte(strbuilder* sb, uint8_t byte) {
  sb_entry entry;
  memset(&entry, 0, sizeof(entry));

  entry.is_byte = true;
  entry.byte = byte;

  sb_add_entry_(sb, entry);
}

void sb_appendbytes(strbuilder* sb, bytestr bstr) {
  sb_entry entry;
  memset(&entry, 0, sizeof(entry));

  entry.is_byte = false;
  entry.bstr = bstr;

  sb_add_entry_(sb, entry);
}

void sb_appendline(strbuilder* sb) {
  sb_append(sb, "\n");
}

bytestr sb_tostring(strbuilder* sb) {
  bytestr result;
  memset(&result, 0, sizeof(result));

  for (size_t i = 0; i < sb->num_appends; i++) {
    sb_entry entry = sb->entries[i];
    result.data_size += (entry.is_byte ? 1 : entry.bstr.data_size);
  }

  result.data = calloc(result.data_size, 1);

  void* dest_ptr = result.data;
  for (size_t i = 0; i < sb->num_appends; i++) {
    sb_entry entry = sb->entries[i];
    if (entry.is_byte) {
      memcpy(dest_ptr, &entry.byte, sizeof(uint8_t));
      dest_ptr += 1;
    } else {
      bytestr src = entry.bstr;
      memcpy(dest_ptr, src.data, src.data_size * 1);
      dest_ptr += src.data_size;
    }
  }

  return result;
}

void sb_free(strbuilder* sb) {
  free(sb->entries);
  free(sb);
}

bytestr sb_tostring_and_free(strbuilder* sb) {
  bytestr result = sb_tostring(sb);
  sb_free(sb);
  return result;
}
