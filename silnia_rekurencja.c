#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_LENGTH 1000
#define SYSTEM_BASE 10
#define MAX_FACTORIAL_LENGTH 5
#define MAXIMUM_POSSIBLE_NUMBER 449
#define ASCII_ZERO 48

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

int input_to_int(char *input)
{
  int length = 1;
  int desired_number = 0;
  int converted[length];
  for (; input[length]; length++)
    ;
  for (int i = 0; i < length; i++)
  {
    char sign;
    sign = input[i];
    if (sign == '\n')
      break;
    if ((int)sign - ASCII_ZERO > 9 || (int)sign - ASCII_ZERO < 0)
      return desired_number;
    converted[i] = (int)sign - ASCII_ZERO;
  }
  for (int j = 0; j < length - 1; j++)
  {
    desired_number += (int)(converted[j] * pow(SYSTEM_BASE, (length - 2 - j)));
  }
  return desired_number;
}

int get_input()
{
  do
  {
    char user_input[MAX_FACTORIAL_LENGTH];
    char clear_buffer[2];
    int output = 0;
    int overflow = 0;
    printf("Podaj liczbę z jakiej chcesz obliczyć silnię:\n");
    fgets(user_input, MAX_FACTORIAL_LENGTH, stdin);
    output = input_to_int(user_input);
    while (strchr(user_input, '\n') == NULL && clear_buffer[0] != '\n')
    {
      fgets(clear_buffer, 2, stdin);
      overflow = 1;
    }
    clear_buffer[0] = 0;
    if ((overflow && output != 0))
    {
      printf("Nieprawidłowy zakres liczby!\n");
      continue;
    }
    if (overflow || output == 0)
    {
      printf("Nieprawidłowy argument!\n");
      continue;
    }
    else
    {
      return output;
    }
  } while (1);
}

void print_result(int *result_reverse)
{
  int num_start = 0;
  char result[MAX_LENGTH];
  for (int k = 0; k < MAX_LENGTH; k++)
  {
    sprintf(&result[k], "%d", result_reverse[MAX_LENGTH - 1 - k]);
  }
  for (num_start = 0; num_start < MAX_LENGTH - 1; num_start++)
  {
    if (result[num_start] != '0')
      break;
  }
  for (; num_start < MAX_LENGTH; num_start++)
  {
    printf("%c", result[num_start]);
  }
  printf("\n");
}

int count_factorial(int *current_result, int multiplier)
{
  int result_length, digit, last_index, num_start, current_length;
  int remainder = 0;
  char result[MAX_LENGTH];
  for (int j = 0; j < MAX_LENGTH; j++)
  {
    digit = current_result[j] * (multiplier) + remainder;
    current_result[j] = digit % SYSTEM_BASE;
    remainder = digit / SYSTEM_BASE;
  }
  if (remainder > 0)
  {
    printf("Nastąpiło przepełnienie!\n");
  } else if (multiplier > 1)
  {
    count_factorial(current_result, multiplier - 1);
  } else {
    print_result(current_result);
  }
}

int main()
{
  do
  {
    char input[MAX_FACTORIAL_LENGTH];
    char result[MAX_LENGTH];
    char clear_buffer[2];
    int *overflow = 0;
    int result_reverse[MAX_LENGTH] = {1};
    int digit, remainder, factorial, factorial_remainder, result_length;
    int idx = 0;
    factorial = get_input();
    if (factorial == 0)
    {
      printf("Podany argument nie jest poprawny.\n\n");
      continue;
    }
    factorial_remainder = factorial;
    while (factorial_remainder != 0)
    {
      digit = factorial_remainder % SYSTEM_BASE;
      result_reverse[idx] = digit;
      idx++;
      factorial_remainder /= SYSTEM_BASE;
    }
    count_factorial(result_reverse, factorial - 1);
    reset();
  } while (1);
}
