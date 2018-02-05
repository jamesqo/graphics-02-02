#include "sys_headers.h"

#include "p6_data.h"
#include "strbuilder.h"

#define IMAGE_WIDTH 1000
#define IMAGE_HEIGHT 1000
#define P6_MAXVAL 255

pixel get_pixel(size_t row, size_t column) {
  pixel p;
  p.red = (uint8_t)row; // Casting to smaller unsigned type: Well-defined
  p.green = (uint8_t)column;
  p.blue = (uint8_t)(row + column); // Unsigned type overflow: Well-defined
  return p;
}

p6_data get_p6_data() {
  p6_data data;
  data.height = IMAGE_HEIGHT;
  data.width = IMAGE_WIDTH;

  data.pixels = calloc(data.height, sizeof(pixel*));
  for (size_t i = 0; i < data.height; i++) {
    data.pixels[i] = calloc(data.width, sizeof(pixel));

    for (size_t j = 0; j < data.width; j++) {
      data.pixels[i][j] = get_pixel(i, j);
    }
  }

  return data;
}

void free_p6_data(p6_data data) {
  for (size_t i = 0; i < data.height; i++) {
    free(data.pixels[i]);
  }

  free(data.pixels);
}

char* get_p6_content(p6_data data) {
  char width_str[25];
  char height_str[25];
  char maxval_str[25];

  snprintf(width_str, sizeof(width_str), "%zu", data.width);
  snprintf(height_str, sizeof(height_str), "%zu", data.height);
  snprintf(maxval_str, sizeof(maxval_str), "%d", P6_MAXVAL);

  strbuilder* sb = sb_get();
  sb_append(sb, "P6");
  sb_appendline(sb);
  sb_append(sb, width_str);
  sb_appendline(sb);
  sb_append(sb, height_str);
  sb_appendline(sb);
  sb_append(sb, maxval_str);
  sb_appendline(sb);

  for (size_t i = 0; i < data.height; i++) {
    for (size_t j = 0; j < data.width; j++) {
      pixel p = data.pixels[i][j];
      sb_appendbyte(sb, p.red);
      sb_appendbyte(sb, p.green);
      sb_appendbyte(sb, p.blue);
    }
  }

  return sb_tostring(sb);
}

void write_p6_to_file(const char* path, p6_data data) {
  int fd = open(path, O_CREAT | O_WRONLY);
  char* content = get_p6_content(data);
  write(fd, content, sizeof(content));
  free(content);
  close(fd);
}

int main() {
  const char destfile[] = "output.ppm";

  p6_data data = get_p6_data();
  write_p6_to_file(destfile, data);
  free_p6_data(data);

  exit(0);
}
