#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_INT_NUM_SIZE 11

int get_input(char *user_input)
{
  char clear_buffer[2];
  int overflow = 0;

  fgets(user_input, MAX_INT_NUM_SIZE + 1, stdin);
  while (strchr(user_input, '\n') == NULL && clear_buffer[0] != '\n')
  {
    fgets(clear_buffer, 2, stdin);
    overflow = 1;
  }
  clear_buffer[0] = 0;
  return overflow;
}

int input_to_int(char *input)
{
  int length = 1;
  int desired_number = 0;
  for (; input[length]; length++)
    ;
  printf("Length: %d\n", length);
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

void print_numbers(int *numbers) {

}

int main()
{
  int input_converted = 0;
  int overflow = 0;
  char user_input[MAX_INT_NUM_SIZE + 1];
  int current_smallest;
  // int *digits;

  while (input_converted < 1 || overflow)
  {
    printf("Podaj liczbę graniczną przedziału 2-x z jakiego chcesz otrzymać liczby pierwsze:\n");
    overflow = get_input(user_input);
    input_converted = input_to_int(user_input);
    printf("%d", input_converted);
    if (overflow || input_converted < 1)
    {
      printf("Niepoprawny argument.\n");
    }
  }

  int digits[input_converted - 2];
  for (int i = 0; i < (input_converted - 1); i++)
  {
    digits[i] = i + 2;
  }

  current_smallest = 0;
  
  while (digits[current_smallest] <= sqrt(input_converted))
  {
    for (int j = current_smallest + 1; j < input_converted - 1; j++)
    {
      if ((digits[j] % digits[current_smallest]) == 0)
      {
        digits[j] = 0;
      }
    }
    for (int k = current_smallest + 1; k < input_converted - 1; k++)
    {
      if (digits[k] != 0)
      {
        current_smallest = k;
        break;
      }
    }
  }

  printf("Liczby pierwsze z wybranego zakresu to: ");

  for (int i = 0; i < (input_converted - 1); i++)
  {
    if (digits[i]) {
      printf("%d ", digits[i]);
    }
  }
}