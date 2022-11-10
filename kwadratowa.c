#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define DELTA_FORMULA(a, b, c) ((b * b) - (4 * a * c))
#define LINEAR_FUNCTION_FORMULA(b, c) c == 0 ? 0 : ((c * -1 / b))
#define DOUBLE_INPUT_CHAR_LIMIT 20

void clear()
{
  while ((getchar()) != '\n');
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
      exit(0);
    printf("Nieprawidłowa operacja!\n");
  } while (1);
}

double get_input(char param_name)
{
  char input_ref[DOUBLE_INPUT_CHAR_LIMIT];
  char *e;
  double output;
  printf("Podaj parametr %c funkcji f(x) = ax^2 + bx + c:\n", param_name);
  fgets(input_ref, DOUBLE_INPUT_CHAR_LIMIT, stdin);
  output = strtod(input_ref, &e);
  if (!isspace(*e))
  {
    printf("Nieprawidłowy argument (konwersja do double jest niemożliwa)!\n");
    clear();
    get_input(param_name);
  }
  else
  {
    return output;
  }
}

int main()
{
  do
  {
    double a, b, c, delta, result_1, result_2;

    a = get_input('a');
    b = get_input('b');
    c = get_input('c');
    if (a == 0 && b == 0)
    {
      printf("Dla podanych parametrów funkcja nie ma miejsc zerowych. Spróbuj ponownie.\n");
      continue;
    }
    delta = DELTA_FORMULA(a, b, c);
    if (a == 0 && b != 0)
    {
      result_1 = LINEAR_FUNCTION_FORMULA(b, c);
      printf("Funkcja o podanych parametrach jest funkcją liniową. Jej miejsce zerowe wynosi: %f\n", result_1);
      reset();
      continue;
    }
    if (delta < 0)
    {
      printf("Brak rozwiązań równania.\n");
      reset();
      continue;
    }
    if (delta == 0)
    {
      result_1 = result_2 = (-b / 2 * a);
      printf("Rozwiązania równania: %f, %f\n", result_1, result_2);
      reset();
      continue;
    }
    result_1 = (-b - sqrt(delta)) / (2 * a);
    result_2 = (-b + sqrt(delta)) / (2 * a);
    printf("Rozwiązania równania: %f, %f\n", result_1, result_2);
    reset();
  } while (1);
}
