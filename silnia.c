#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LENGTH 1000
#define SYSTEM_BASE 10
#define MAX_FACTORIAL_LENGTH 3

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
    if (input == 'n') {
      exit(0);
    }
    clear();
    printf("Nieprawidłowa operacja!\n");
  } while (1);
}

int main()
{
  do
  {
    char input[MAX_FACTORIAL_LENGTH];
    char result[MAX_LENGTH];
    int result_reverse[MAX_LENGTH] = {1};
    int digit, remainder, factorial, last_index, num_start;
    printf("Podaj liczbę z jakiej chcesz obliczyć silnię:\n");
    scanf("%3s", input);
    factorial = atoi(input);
    if (factorial == 0)
    {
      printf("Podany argument nie jest poprawny.\n\n");
      continue;
    }
    for (int i = 1; i < factorial + 1; i++)
    {
      for (int j = 0; j < MAX_LENGTH; j++)
      {
        digit = result_reverse[j] * i + remainder;
        result_reverse[j] = digit % SYSTEM_BASE;
        remainder = digit / SYSTEM_BASE;
      }
    }
    if (remainder > 0)
    {
      printf("Nastąpiło przepełnienie!\n");
      reset();
      continue;
    }
    last_index = sizeof(result_reverse) / sizeof(result_reverse[0]) - 1;
    for (int k = 0; k < MAX_LENGTH; k++)
    {
      sprintf(&result[k], "%d", result_reverse[last_index - k]);
    }
    for (num_start = 0; num_start < last_index; num_start++)
    {
      if (result[num_start] != '0')
        break;
    }
    printf("Silnia %d wynosi: ", factorial);
    for (; num_start < MAX_LENGTH; num_start++)
    {
      printf("%c", result[num_start]);
    }
    printf("\n");
    reset();
  } while (1);
}
