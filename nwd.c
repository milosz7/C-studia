#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <regex.h>

#define MAX_INPUT_LENGTH 20
#define SYSTEM_BASE 10
#define NUMBERS_REGEXR "^(-?[0-9]+)?\\.?([0-9]+)?\n?$"

void clear()
{
  while ((getchar()) != '\n')
    ;
}

int reset()
{
  char input;
  do
  {
    printf("Czy chcesz spróbować jeszcze raz? y/n\n");
    scanf(" %1c", &input);
    if (input == 'y')
    {
      clear();
      break;
    }
    if (input == 'n')
      exit(0);
    clear();
    printf("Nieprawidłowa operacja!\n");
  } while (1);
}

long double input_to_double(char *input)
{
  int length = 1;
  long long int desired_number = 0;
  for (; input[length]; length++)
    ;
  int converted[length];
  for (int i = 0; i < length; i++)
  {
    char sign;
    sign = input[i];
    if (sign == '\n')
      break;
    if ((int)sign - 48 > 9 || (int)sign - 48 < 0)
      return NAN;
    converted[i] = (int)sign - 48;
  }
  for (int j = 0; j < length - 1; j++)
  {
    desired_number += (long long int)(converted[j] * pow(10, (length - 2 - j)));
  }
  return desired_number;
}

long long get_input(char param_name)
{
  char user_input[MAX_INPUT_LENGTH + 1];
  char clear_buffer[2];
  char *endptr;
  long output = 0;
  regex_t regexr;
  int is_valid;
  printf("Podaj liczbę %c do wyznaczenia NWD:\n", param_name);
  fgets(user_input, MAX_INPUT_LENGTH + 1, stdin);
  output = strtol(user_input, &endptr, SYSTEM_BASE);

  while (strchr(user_input, '\n') == NULL && clear_buffer[0] != '\n')
  {
    fgets(clear_buffer, 2, stdin);
  }

  is_valid = regcomp(&regexr, NUMBERS_REGEXR, REG_EXTENDED);
  is_valid = regexec(&regexr, user_input, 0, NULL, 0);

  if (errno == ERANGE || is_valid == REG_NOMATCH)
  {
    errno = 0;
    printf("Nieprawidłowy argument!\n");
    return get_input(param_name);
  }
  return output;
}

void print_result(long GCF, long m, long n)
{
  printf("NWD %ld i %ld wynosi: %ld\n", m, n, GCF);
}

int main()
{
  do
  {
    long long m, n;
    long long bigger, smaller;
    long long modulo;

    m = get_input('m');
    n = get_input('n');

    bigger = m > n ? m : n;
    smaller = m > n ? n : m;
    while (smaller != 0)
    {
      modulo = bigger % smaller;
      bigger = smaller;
      smaller = modulo;
    }
    print_result(bigger, m, n);
    reset();
  } while (1);
}