#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INPUT_LENGTH 6
#define MAX_OUTPUT_LENGTH 1000
#define SYSTEM_BASE 10
#define MAXIMUM_POSSIBLE_NUMBER 4785

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

int input_to_int(char *input)
{
  int length = 1;
  int desired_number = 0;
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
      return desired_number;
    converted[i] = (int)sign - 48;
  }
  for (int j = 0; j < length - 1; j++)
  {
    desired_number += (int)(converted[j] * pow(10, (length - 2 - j)));
  }
  return desired_number;
}

int get_input()
{
  char user_input[MAX_INPUT_LENGTH];
  char clear_buffer[2];
  int output = 0;
  int overflow = 0;
  printf("Podaj który wyraz ciągu fibonacciego chcesz obliczyć (1-4685):\n");
  fgets(user_input, MAX_INPUT_LENGTH, stdin);
  output = input_to_int(user_input);
  while (strchr(user_input, '\n') == NULL && clear_buffer[0] != '\n')
  {
    printf("test");
    fgets(clear_buffer, 2, stdin);
    overflow = 1;
  }
  clear_buffer[0] = 0;
  if ((overflow && output != 0) || output > MAXIMUM_POSSIBLE_NUMBER)
  {
    printf("Nieprawidłowy zakres liczby!\n");
    get_input();
  }
  if (overflow || output == 0)
  {
    printf("Nieprawidłowy argument!\n");
    get_input();
  }
  else
  {
    return output;
  }
}

void swap_numbers(int *f_num, int *s_num, int *fs_sum)
{
  for (int i = 0; i < MAX_OUTPUT_LENGTH; i++)
  {
    f_num[i] = s_num[i];
  }
  for (int i = 0; i < MAX_OUTPUT_LENGTH; i++)
  {
    s_num[i] = fs_sum[i];
  }
  for (int i = 0; i < MAX_OUTPUT_LENGTH; i++)
  {
    fs_sum[i] = 0;
  }
}

int main()
{
  do
  {
    int requested_num, result_length, remainder, overflow = 0;
    int second_number_idx = 1;
    int num_start_idx = 0;
    int first_number[MAX_OUTPUT_LENGTH] = {0};
    int second_number[MAX_OUTPUT_LENGTH] = {0};
    int sum_first_second[MAX_OUTPUT_LENGTH] = {0};
    second_number[MAX_OUTPUT_LENGTH - 1] = 1;

    requested_num = get_input();
    if (requested_num == 1)
    {
      printf("%d. liczba ciągu fibonacciego wynosi: 0\n", requested_num);
      reset();
    }
    if (requested_num == 2)
    {
      printf("%d. liczba ciągu fibonacciego wynosi: 1\n", requested_num);
      reset();
    }
    while (second_number_idx != requested_num)
    {
      for (int i = MAX_OUTPUT_LENGTH - 1; i >= 0; i--)
      {
        remainder = remainder + first_number[i] + second_number[i];
        sum_first_second[i] = remainder % SYSTEM_BASE;
        remainder /= 10;
      }
      swap_numbers(first_number, second_number, sum_first_second);
      if (remainder > 0)
      {
        printf("Overflow!\n");
        overflow = 1;
        reset();
        break;
      }
      second_number_idx++;
    }
    if (overflow == 1)
      continue;
    for (num_start_idx = 0; num_start_idx < MAX_OUTPUT_LENGTH; num_start_idx++)
    {
      if (second_number[num_start_idx] != 0)
        break;
    }
    printf("%d. liczba ciągu fibonacciego wynosi: ", requested_num);
    for (; num_start_idx < MAX_OUTPUT_LENGTH; num_start_idx++)
    {
      printf("%d", second_number[num_start_idx]);
    }
    printf("\n");
    reset();

  } while (1);
}