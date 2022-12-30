#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <regex.h>

#define DOUBLE_INPUT_CHAR_LIMIT 20
#define NUMBERS_REGEXR "^(-?[0-9]+)?\\.?([0-9]+)?\n?$"
#define ROOT(a, b) b == 0 ? 0 : (b * -1 / a)

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
      while ((getchar()) != '\n')
        ;
      break;
    }
    if (input == 'n')
      exit(0);
    clear();
    printf("Nieprawidłowa operacja!\n");
  } while (1);
}

double get_input(char param_symbol)
{
  double output;
  char *e;
  char user_input[DOUBLE_INPUT_CHAR_LIMIT];
  regex_t regexr;
  int is_valid;

  printf("Podaj parametr %c funkcji f(x) = ax + b:\n", param_symbol);
  fgets(user_input, DOUBLE_INPUT_CHAR_LIMIT, stdin);

  clear_buffer(user_input);

  is_valid = regcomp(&regexr, NUMBERS_REGEXR, REG_EXTENDED);
  is_valid = regexec(&regexr, user_input, 0, NULL, 0);

  output = strtod(user_input, &e);
  if (is_valid == REG_NOMATCH)
  {
    printf("Niepoprawna wartość argumentu %c.\n", param_symbol);
    return get_input(param_symbol);
  }
  if (errno == ERANGE)
  {
    errno = 0;
    printf("Nieprawidłowy argument (konwersja do double jest niemożliwa)!\n");
    return get_input(param_symbol);
  }
  return output;
}

void main()
{

  do
  {
    double a = 0;
    double b = 0;
    double output;

    a = get_input('a');
    if (a == 0)
    {
      printf("Parametr a nie może być równy 0, podaj argument jeszcze raz.\n");
      continue;
    }
    b = get_input('b');
    output = ROOT(a, b);
    printf("%s%f\n", "Miejsce zerowe: ", output);
    reset();
  } while (1);
}
