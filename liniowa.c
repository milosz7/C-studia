#include <stdio.h>
#include <stdlib.h>

#define FLOAT_CHAR_LIMIT 20

int reset()
{
  char input;
  do
  {
    printf("Czy chcesz spróbować jeszcze raz? y/n\n");
    scanf(" %c", &input);
    if (input == 'y') {
      while((getchar()) != '\n');
      break;
    }
    if (input == 'n')
      exit(0);
    printf("Nieprawidłowa operacja!\n");
  } while (1);
}

void main()
{
#define miejsce_zerowe(a, b) (b * -1 / a)

  do
  {

    char input_a[FLOAT_CHAR_LIMIT];
    char input_b[FLOAT_CHAR_LIMIT];     
    float a = 0;
    float b = 0;
    float output;

    printf("Podaj parametr a funkcji f(x) = ax + b: \n");
    fgets(input_a, FLOAT_CHAR_LIMIT, stdin);
    a = atof(input_a);
    if (a == 0) {
      printf("Parametr a nie może być równy 0, podaj argument jeszcze raz.\n");
      continue;
    }
    printf("Podaj parametr b funkcji f(x) = ax + b: \n");
    fgets(input_b, FLOAT_CHAR_LIMIT, stdin);
    b = atof(input_b);
    output = miejsce_zerowe(a, b);
    printf("%s %f\n", "Miejsce zerowe: ", output);
    reset();
  } while (1);
}
