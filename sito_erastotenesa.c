#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_INT_NUM_SIZE 11
#define FAST_EXECUTION_AMOUNT_LIMIT 1000000

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

void print_numbers(int *numbers, int range) {
  printf("Liczby pierwsze z wybranego zakresu to:");
  for (int i = 0; i < range; i++)
  {
    if (numbers[i]) {
      printf(" %d", numbers[i]);
    }
  }
  printf("\n");
}

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
    scanf(" %c", &input);
    if (input == 'y')
    {
      clear();
      return 0;
    }
    if (input == 'n') {
      clear();
      return 1;
    }
    clear();
    printf("Nieprawidłowa operacja! (y/n)\n");
  } while (1);
}

int main()
{
  int input_converted = 0;
  int overflow = 0;
  char user_input[MAX_INT_NUM_SIZE + 1];
  char *endptr;
  int current_smallest;
  int *digits;
  int should_reset = 0;

  while (input_converted < 1 || overflow)
  {
    printf("Podaj liczbę graniczną przedziału 2-x z jakiego chcesz otrzymać liczby pierwsze:\n");
    overflow = get_input(user_input);
    input_converted = (int)strtol(user_input, &endptr, 10);
    if (overflow || input_converted < 1)
    {
      printf("Niepoprawny argument.\n");
    }
    if (input_converted > FAST_EXECUTION_AMOUNT_LIMIT) {
      printf("To może zająć dużo czasu (ale powinno zadziałać). Czy chcesz kontynuować? (y/n)\n");
      should_reset = reset();
      if (should_reset) {
        input_converted = 0;
      }
    }
  }

  if ((digits = (int *)malloc((input_converted - 2) * sizeof(int))) == NULL) {
    fprintf(stderr, "Memory allocation error.");
    exit(1);
  }
  
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

  print_numbers(digits, (input_converted - 1));
  free(digits);
}