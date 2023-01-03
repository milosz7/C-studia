#include <stdio.h>
#include <regex.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define NUMBERS_REGEXR "^[1-9][0-9]*?\n$"
#define INITIAL_INPUT_SIZE 16

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

double count_factorial(double input)
{
  if (input == 1)
    return 1;
  return input * count_factorial(input - 1);
}

void clear_buffer(char *input)
{
  char clear_buffer[2];
  while (strchr(input, '\n') == NULL && clear_buffer[0] != '\n')
    fgets(clear_buffer, 2, stdin);
}

double get_input()
{
  double output;
  char *e;
  size_t base_input_size = INITIAL_INPUT_SIZE;
  char *user_input = (char *)malloc(INITIAL_INPUT_SIZE);
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

int main()
{
  do
  {
    double result, input = get_input();
    printf("Silnia z liczby %.0f wynosi: %.0f (inf oznacza przeroczenie zakresu).\n",
           input, count_factorial(input));
    reset();
  } while (1);
}