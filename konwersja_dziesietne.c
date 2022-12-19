#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

#define CHUNK_SIZE 16
#define MAX_NUM_INPUT_SIZE 20
#define MAX_BASE_INPUT_SIZE 4
#define INPUT_SYSTEM_BASE 10
#define BASE_MAX 36
#define BASE_MIN 2

int clear_buffer(char *input)
{
  char clear_buffer[2];
  int overflow = 0;

  while (strchr(input, '\n') == NULL && clear_buffer[0] != '\n')
  {
    fgets(clear_buffer, 2, stdin);
    overflow = 1;
  }

  return overflow;
}

long get_digit()
{
  size_t input_size = MAX_NUM_INPUT_SIZE + 1;
  int input_len = -1;
  char *user_input = (char *)malloc(input_size * sizeof(char));
  char *errptr;
  long output;

  printf("Podaj liczbę w systemie dziesiętnym jaką chcesz przekonwertować:\n");
  input_len = getline(&user_input, &input_size, stdin);
  errno = 0;

  clear_buffer(user_input);

  for (int i = 0; i < input_len - 1; i++)
  {
    if (!isdigit(user_input[i]) || input_len == -1)
    {
      free(user_input);
      printf("Nieprawidłowy argument!\n");
      return get_digit();
    }
  }

  output = (long)strtol(user_input, &errptr, INPUT_SYSTEM_BASE);

  if (errno == ERANGE)
  {
    printf("Liczba poza zakresem!\n");
    return get_digit();
  }

  free(user_input);
  return output;
}

unsigned int get_base()
{
  int output;
  char *errptr;
  char user_input[MAX_BASE_INPUT_SIZE];
  int overflow = 0;

  printf("Podaj liczbę będącą bazą nowego systemu (2-36):\n");
  fgets(user_input, MAX_BASE_INPUT_SIZE, stdin);

  overflow = clear_buffer(user_input);

  output = (int)strtol(user_input, &errptr, INPUT_SYSTEM_BASE);

  if (output < BASE_MIN || output > BASE_MAX || overflow)
  {
    printf("Podany system liczbowy nie istnieje.\n");
    return get_base();
  }
  return output;
}

int main()
{
  char system_patterns[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int chunks_to_allocate = 1;
  int current_idx = 0;
  char *result = (char *)malloc(CHUNK_SIZE * chunks_to_allocate);
  long digit;
  unsigned int base;
  digit = get_digit();
  base = get_base();

  printf("Liczba %ld zapisana w systemie o podstawie %d: ", digit, base);
  
  while (digit > 0) {
    if (current_idx == (chunks_to_allocate * CHUNK_SIZE) - 1) {
      chunks_to_allocate += 1;
      result = (char *)realloc(result, chunks_to_allocate * CHUNK_SIZE);
    }
    char result_digit = system_patterns[digit % base];
    *(result + current_idx) = result_digit; 
    digit /= base;
    current_idx++;
  }
  for (int i = current_idx; i >= 0; i--) {
    printf(i == 0 ? "%c\n" : "%c", *(result + i));
  }
  free(result);
}
