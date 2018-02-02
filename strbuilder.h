typedef struct {
  
} strbuilder;

strbuilder* sb_get();
void sb_append(strbuilder* sb, char* str);
char* sb_tostring(strbuilder* sb);
void sb_free(strbuilder* sb);

