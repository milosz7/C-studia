#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define DELTA_FORMULA(a, b, c) ((b * b) - (4 * a * c))
#define LINEAR_FUNCTION_FORMULA(b, c) ((c * -1 / b))
#define FLOAT_CHAR_LIMIT 20


int reset()
{
  char input;
  do
  {
    printf("Czy chcesz spróbować jeszcze raz? y/n\n");
    scanf(" %c", &input);
    if (input == 'y')
    {
      while ((getchar()) != '\n');
      break;
    }
    if (input == 'n')
      exit(0);
    printf("Nieprawidłowa operacja!\n");
  } while (1);
}

float get_input(char param_name) {
  char input_ref[20];
  printf("Podaj parametr %c funkcji f(x) = ax^2 + bx + c: ", param_name);
  fgets(input_ref, FLOAT_CHAR_LIMIT, stdin);
  return atof(input_ref);
}

int main()
{
  do
  {
    char input_a[FLOAT_CHAR_LIMIT], input_b[FLOAT_CHAR_LIMIT], input_c[FLOAT_CHAR_LIMIT];
    float a, b, c, delta, rozw1, rozw2;

    a = get_input('a');
    b = get_input('b');
    c = get_input('c');
    if (a == 0 && b == 0) {
      printf("Dla podanych parametrów funkcja nie ma miejsc zerowych. Spróbuj ponownie.\n");
      continue;
    }
    delta = DELTA_FORMULA(a, b, c);
    if (a == 0 && b != 0) {
      rozw1 = LINEAR_FUNCTION_FORMULA(b, c);
      printf("Funkcja o podanych parametrach jest funkcją liniową. Jej miejsce zerowe wynosi: %f\n", rozw1);
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
      rozw1 = (-b / 2 * a);
      printf("%s%f\n", "Rozwiązanie równania: ", rozw1);
      reset();
      continue;
    }
    rozw1 = (-b - sqrt(delta)) / (2 * a);
    rozw2 = (-b + sqrt(delta)) / (2 * a);
    printf("%s%f%c%f\n", "Rozwiązania równania:", rozw1, ',', rozw2);
    reset();
  } while (1);
}
