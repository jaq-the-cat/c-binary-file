#include <stdio.h>
#include <stdlib.h>

static const char filename[] = "file.bin"; 

typedef struct {
  short x, y;
  char c;
} object;

object* load() {
  FILE *f = fopen(filename, "rb");
  fseek(f, 0, SEEK_END);
  int len = ftell(f);
  fseek(f, 0, SEEK_SET);

  object* os = malloc(len);
  for (int i=0; i<len/sizeof(object); i++)
    fread(&os[i], sizeof(object), 1, f);

  return os;
}

void write(object o[], int count) {
  FILE *f = fopen(filename, "wb");
  for (int i=0; i<count; i++)
    fwrite(&o[i], sizeof(object), 1, f);
  fclose(f);
}

int main() {
  object osw[] = {{1, 2, 'a'}, {3, 4, 'b'}};
  write(osw, 2);

  object* osl = load();
  for (int i=0; i<2; i++)
    printf("%d %d %c\n", osl[i].x, osl[i].y, osl[i].c);

  free(osl);

  return 0;
}
