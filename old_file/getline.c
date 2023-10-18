#include "shell.h"
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
  char *buffer = malloc(MAX_INPUT_SIZE * sizeof(char));
  int position = 0;
  int num_chars_read = 0;

  while (1) {
    char current_char = fgetc(stream);

    if (current_char == EOF || current_char == '\n') {
      break;
    }

    buffer[position++] = current_char;
    num_chars_read++;
  }

  buffer[position] = '\0';
  *lineptr = buffer;
  *n = num_chars_read;

  return num_chars_read;
}
