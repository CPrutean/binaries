#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char buffer[10];
  memset(buffer, 0, sizeof(buffer));
  fgets(buffer, 10, stdin);

  int16_t val = (int16_t)strtol(buffer, NULL, 10);
  float out = ((float)val) / 100.0f;

  printf("%f\n", out);

  return 0;
}
