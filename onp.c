#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define BASE_INPUT_SIZE 16
#define CHUNK_SIZE 16
#define SYSTEM_BASE 10

void throw_error(char *message)
{
  printf("%s\n", message);
  exit(1);
}

void perform_two_operand_stack_operation(double *stack, int current_idx, char operand)
{
  double num1, num2;

  if (current_idx > 0)
  {
    double num1 = *(stack + current_idx - 1);
    double num2 = *(stack + current_idx);
    switch (operand)
    {
    case '+':
      *(stack + current_idx - 1) = num1 + num2;
      break;
    case '-':
      *(stack + current_idx - 1) = num1 - num2;
      break;
    case '*':
      *(stack + current_idx - 1) = num1 * num2;
      break;
    case '/':
      if (num2 == 0)
      {
        throw_error("Nie wolno dzielić przez zero.");
        break;
      }
      *(stack + current_idx - 1) = num1 / num2;
      break;
    case '^':
      *(stack + current_idx - 1) = pow(num1, num2);
      break;
    default:
      throw_error("Nieprawidłowe wejście.");
    }
  }
  else
  {
    throw_error("Nieprawidłowe wejście.");
  }
}

void perform_one_operand_stack_operation(double *stack, int current_idx, char operand)
{
  if (current_idx >= 0)
  {
    double num = *(stack + current_idx);
    switch (operand)
    {
    case 's':
      *(stack + current_idx) = sin(num);
      break;
    case 'c':
      *(stack + current_idx) = cos(num);
      break;
    case 'l':
      if (num <= 0)
      {
        throw_error("Logarytm z liczby mniejszej lub równej zero nie istnieje.");
      }
      *(stack + current_idx) = log(num);
      break;
    default:
      throw_error("Nieprawidłowe wejście.");
    }
  }
}

void print_help()
{
  printf("Podaj wyrażenie w ONP do obliczenia oddzielając spacją kolejne elementy.\n");
  printf("Nieoddzielony znak \"-\" sprawi że liczba zostanie zinterpretowana jako ujemna.\n");
  printf("Dostępne operacje:\n");
  printf("\"+\" - dodawanie\n");
  printf("\"-\" - odejmowanie\n");
  printf("\"/\" - dzielenie\n");
  printf("\"*\" - mnożenie\n");
  printf("\"^\" - potęgowanie\n");
  printf("\"l\" - logarytm naturalny\n");
  printf("\"c\" - cosinus\n");
  printf("\"s\" - sinus\n");
}

int main()
{
  size_t input_size = BASE_INPUT_SIZE;
  char *user_input = (char *)malloc(input_size);
  char separator[] = " \n";
  char operations_without_subtraction[] = "*^/+";
  char single_arg_operations[] = "lcs";
  int chunks = 1;
  int stack_size = chunks * sizeof(int) * CHUNK_SIZE;
  double *stack = (double *)malloc(stack_size);
  int current_stack_idx = -1;
  int input_len = -1;

  print_help();
  
  input_len = getline(&user_input, &input_size, stdin);

  char *word_ptr = strtok(user_input, separator);

  while (word_ptr != NULL)
  {
    if (current_stack_idx == (stack_size) / sizeof(double) - 1)
    {
      chunks++;
      stack_size = chunks * sizeof(double) * CHUNK_SIZE;
      stack = (double *)realloc(stack, stack_size);
    }
    
    char *endptr;

    if (isdigit(*word_ptr))
    {
      for (int i = 1; *(word_ptr + i); i++)
      {
        if (!isdigit(*(word_ptr + i)))
        {
          throw_error("Nieprawidłowe wejście!");
        }
      }
      current_stack_idx++;
      *(stack + current_stack_idx) = strtod(word_ptr, &endptr);
    }

    if (*word_ptr == '-')
    {
      if (isdigit(word_ptr[1]))
      {
        current_stack_idx++;
        *(stack + current_stack_idx) = strtod(&word_ptr[1], &endptr) * -1;
      }
      if (!(word_ptr + 1)) // null check
      {
        perform_two_operand_stack_operation(stack, current_stack_idx, *word_ptr);
        current_stack_idx--;
      }
    }

    if (strchr(operations_without_subtraction, *word_ptr) != NULL)
    {
      perform_two_operand_stack_operation(stack, current_stack_idx, *word_ptr);
      current_stack_idx--;
    }

    if (strchr(single_arg_operations, *word_ptr) != NULL) {
      perform_one_operand_stack_operation(stack, current_stack_idx, *word_ptr);
    }
    word_ptr = strtok(NULL, separator);
  }

  if (current_stack_idx != 0)
  {
    throw_error("Nieprawidłowa operacja.");
  }

  printf("Wynik: %f\n", *(stack));
  exit(0);
}
