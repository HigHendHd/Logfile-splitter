#include <stdio.h>

int main() {
  FILE* fp = fopen("logfile.txt", "wb");

  for (int i = 0; i < 10000; i++) {
    fprintf(fp, "This is a line: %d\r\n", i);
    if (i == 30 || i == 680) {
      fprintf(fp, "[CODE]\r\n");
    } else if (i == 550 || i == 7700) {
      fprintf(fp, "[/CODE]\r\n");
    }
  }

  fclose(fp);

  return 0;
}
