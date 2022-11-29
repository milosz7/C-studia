#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DOUBLE_INPUT_CHAR_LIMIT 20

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
      while ((getchar()) != '\n')
        ;
      break;
    }
    if (input == 'n')
      exit(0);
    printf("Nieprawidłowa operacja!\n");
  } while (1);
}

double get_input(char param_symbol)
{
  double output;
  char *e;
  char user_input[DOUBLE_INPUT_CHAR_LIMIT];
  printf("Podaj parametr %c funkcji f(x) = ax + b:\n", param_symbol);
  fgets(user_input, DOUBLE_INPUT_CHAR_LIMIT, stdin);
  output = strtod(user_input, &e);
  if (isdigit(*user_input) == 0)
  {
    printf("Niepoprawna wartość argumentu %c.\n", param_symbol);
    return get_input(param_symbol);
  }
  if (!isspace(*e))
  {
    printf("Nieprawidłowy argument (konwersja do double jest niemożliwa)!\n");
    clear();
    return get_input(param_symbol);
  }
  return output;
}

void main()
{
#define miejsce_zerowe(a, b) b == 0 ? 0 : (b * -1 / a)

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
    output = miejsce_zerowe(a, b);
    printf("%s%f\n", "Miejsce zerowe: ", output);
    reset();
  } while (1);
}
