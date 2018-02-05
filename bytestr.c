#include "bytestr.h"

bytestr bstr_convert_str(char* str) {
  bytestr result;
  result.data = str;
  result.data_size = strlen(str);
  return result;
}
