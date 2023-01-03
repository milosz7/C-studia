#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

#define SYSTEM_BASE 10
#define INITIAL_CHUNK 32
#define NUMBERS_REGEXR "^[1-9][0-9]*?\n$"
#define ARR_LENGTH(arr_size) (arr_size / sizeof(int))

void clear()
{
  while ((getchar()) != '\n')
    ;
}

void clear_buffer(char *input)
{
  char clear_buffer[2];
  while (strchr(input, '\n') == NULL && clear_buffer[0] != '\n')
    fgets(clear_buffer, 2, stdin);
}

int reset()
{
  char input;
  do
  {
    printf("Czy chcesz spróbować jeszcze raz? y/n\n");
    scanf(" %c", &input);
    if (input == 'y')
    {
      clear();
      break;
    }
    if (input == 'n')
    {
      exit(0);
    }
    clear();
    printf("Nieprawidłowa operacja!\n");
  } while (1);
}

int get_input()
{
  double output;
  char *e;
  size_t base_input_size = INITIAL_CHUNK;
  char *user_input = (char *)malloc(INITIAL_CHUNK);
  regex_t regexr;
  int is_valid;

  printf("Podaj liczbę z jakiej chcesz obliczyć silnię:\n");
  getline(&user_input, &base_input_size, stdin);

  clear_buffer(user_input);

  is_valid = regcomp(&regexr, NUMBERS_REGEXR, REG_EXTENDED);
  is_valid = regexec(&regexr, user_input, 0, NULL, 0);

  output = strtod(user_input, &e);
  if (is_valid == REG_NOMATCH)
  {
    printf("Podany argument jest niepoprawny!\n");
    return get_input(user_input);
  }
  if (errno == ERANGE)
  {
    errno = 0;
    printf("Podany argument wykracza poza zasięg liczbowy typu double!\n");
    return get_input(user_input);
  }
  return (int)output;
}

int mem_err()
{
  printf("Błąd alokacji pamięci.\n");
  exit(1);
}

int main()
{
  do
  {
    int digit, remainder = 0, factorial, current_idx;
    factorial = get_input();
    int chunks_to_alloc = 1;
    int arr_size = sizeof(int) * chunks_to_alloc * INITIAL_CHUNK;
    int *result_reverse = (int *)calloc(sizeof(int), chunks_to_alloc * INITIAL_CHUNK);

    if (result_reverse == NULL)
      mem_err();
    result_reverse[0] = 1;

    for (int i = 1; i < factorial + 1; i++)
    {
      for (int j = 0; j < ARR_LENGTH(arr_size); j++)
      {
        digit = result_reverse[j] * i + remainder;
        result_reverse[j] = digit % SYSTEM_BASE;
        remainder = digit / SYSTEM_BASE;
        for (int k = ARR_LENGTH(arr_size) - 1; k >= 0; k--)
        {
          if (result_reverse[k] != 0)
          {
            current_idx = k;
            break;
          }
        }
        if (current_idx == ARR_LENGTH(arr_size) - (remainder % 10) - 1)
        {
          chunks_to_alloc += 1;
          arr_size = arr_size + sizeof(int) * (remainder % 10);
          result_reverse = (int *)realloc(result_reverse, arr_size);
          if (result_reverse == NULL)
            mem_err();
          for (int i = current_idx + 1; i < ARR_LENGTH(arr_size); i++)
            result_reverse[i] = 0;
        }
      }
    }
    printf("Silnia z liczby %d wynosi: ", factorial);
    
    for (int i = current_idx; i >= 0; i--)
      printf("%d", result_reverse[i]);
    
    free(result_reverse);
    printf("\n");
    reset();
  } while (1);
}
