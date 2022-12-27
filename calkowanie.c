#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <regex.h>
#include <errno.h>

#define BASE_INPUT_SIZE 16
#define CHUNK_SIZE 16
#define SYSTEM_BASE 10
#define NUMBERS_REGEXR "^(-?[0-9]+)?\\.?([0-9]+)?$"
#define VALID_INPUT_REGEXR "(^[+/*lcsx^]|\\-$)|(^((-?[0-9]+)?\\.?([0-9]+)?)$)"

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
      clear();
      break;
    }
    if (input == 'n')
    {
      exit(0);
    }
    clear();
    printf("Nieprawidłowa operacja!\n");
  } while (1);
}

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
  printf("Podaj funkcję w ONP do obliczenia jej całki oddzielając spacją kolejne elementy.\n");
  printf("Nieoddzielony znak \"-\" sprawi że liczba zostanie zinterpretowana jako ujemna.\n");
  printf("Dostępne operacje i znaki:\n");
  printf("\"x\" - zmienna za którą będą podstawiane argumenty funkcji z wybranego przedziału (wymagana)!\n");
  printf("\"+\" - dodawanie\n");
  printf("\"-\" - odejmowanie\n");
  printf("\"/\" - dzielenie\n");
  printf("\"*\" - mnożenie\n");
  printf("\"^\" - potęgowanie\n");
  printf("\"l\" - logarytm naturalny\n");
  printf("\"c\" - cosinus\n");
  printf("\"s\" - sinus\n");
}

double get_value(char *prompt)
{
  int input_len = -1;
  size_t input_size = BASE_INPUT_SIZE;
  char *user_input = (char *)malloc(input_size);
  char *endptr;
  double output;

  printf("%s\n", prompt);
  input_len = getline(&user_input, &input_size, stdin);
  output = strtod(user_input, &endptr);
  free(user_input);

  if (input_len == -1 || errno == ERANGE)
  {
    printf("Nieprawidłowe wejście!\n");
    return get_value(prompt);
  }

  return output;
}

double evaluate_function(char *user_input, double x)
{
  char separator[] = " \n";
  char two_arg_operations[] = "*^/+";
  char single_arg_operations[] = "lcs";
  int current_stack_idx = -1;
  int chunks = 1;
  int stack_size = chunks * sizeof(double) * CHUNK_SIZE;
  double *stack = (double *)malloc(stack_size);

  char *expression = strtok(user_input, separator);

  while (expression != NULL)
  {
    if (current_stack_idx == (stack_size) / sizeof(double) - 1)
    {
      chunks++;
      stack_size = chunks * sizeof(double) * CHUNK_SIZE;
      stack = (double *)realloc(stack, stack_size);
    }

    char *endptr;
    int is_valid_number, is_valid_input;
    regex_t number_regexr, input_regexr;

    is_valid_input = regcomp(&input_regexr, VALID_INPUT_REGEXR, REG_EXTENDED);
    is_valid_input = regexec(&input_regexr, expression, 0, NULL, 0);
    regfree(&input_regexr);

    if (is_valid_input == REG_NOMATCH)
    {
      throw_error("Nieprawidłowe wejście!");
    }

    is_valid_number = regcomp(&number_regexr, NUMBERS_REGEXR, REG_EXTENDED);
    is_valid_number = regexec(&number_regexr, expression, 0, NULL, 0);
    regfree(&number_regexr);

    if (*expression == '-' && !*(expression + 1))
    {
      perform_two_operand_stack_operation(stack, current_stack_idx, *expression);
      current_stack_idx--;
    }

    if (*expression == 'x')
    {
      current_stack_idx++;
      *(stack + current_stack_idx) = x;
    }

    if (strchr(two_arg_operations, *expression) != NULL)
    {
      perform_two_operand_stack_operation(stack, current_stack_idx, *expression);
      current_stack_idx--;
    }

    if (strchr(single_arg_operations, *expression) != NULL)
    {
      perform_one_operand_stack_operation(stack, current_stack_idx, *expression);
    }

    if (is_valid_number != REG_NOMATCH)
    {
      current_stack_idx++;
      *(stack + current_stack_idx) = strtod(expression, &endptr);
    }

    expression = strtok(NULL, separator);
  }

  if (current_stack_idx != 0)
  {
    throw_error("Nieprawidłowa operacja.");
  }

  return *stack;
}

int count_occurences(char *str, char c)
{
  int len = strlen(str);
  int count = 0;

  for (int i = 0; i < len; i++)
  {
    if (str[i] == c)
      count++;
  }

  return count;
}

int main()
{
  do
  {
    size_t input_size = BASE_INPUT_SIZE;
    char *user_input = (char *)malloc(input_size);
    int chunks = 1;
    int stack_size = chunks * sizeof(int) * CHUNK_SIZE;
    double *stack = (double *)malloc(stack_size);
    double result = 0;
    int current_stack_idx = -1;
    double x_start, x_end, x_jump, x_range, x_occurences;

    print_help();

    getline(&user_input, &input_size, stdin); // zapytanie uzytkownika o funkcję
    x_occurences = count_occurences(user_input, 'x');

    if (!x_occurences)
    {
      throw_error("Brak zmiennej x w wejściowej funkcji.");
    }

    x_start = get_value("Podaj początek zakresu parametrów funkcji do obliczenia całki:");
    x_end = get_value("Podaj koniec zakresu parametrów funkcji do obliczenia całki:");

    if (x_start >= x_end)
    {
      printf("Początek zakresu musi być liczbą mniejszą od liczby końca zakresu!\n");
      x_end = get_value("Podaj koniec zakresu parametrów funkcji do obliczenia całki:");
    }

    x_range = fabs(x_end) - fabs(x_start);

    x_jump = get_value("Podaj wartość o jaką będą zwiększane kolejne argumenty funkcji:");

    if (x_jump > x_range || x_jump <= 0)
    {
      printf("Wartość o jaką będą zwiększane argumenty musi być liczbą większą od zera i musi być mniejsza lub równa odległości między początkiem a końcem przedziału!\n");
      x_jump = get_value("Podaj wartość o jaką będą zwiększane kolejne argumenty funkcji:");
    }

    double rect_x, rect_y, partial, remaining_range;

    while (x_start < x_end)
    {
      remaining_range = fabs(x_end) - fabs(x_start);

      char *input_copy[strlen(user_input)];
      strcpy(input_copy, user_input);

      rect_y = evaluate_function(input_copy, x_start);
      rect_x = (remaining_range > x_jump) ? x_jump : remaining_range;
      partial = fabs(rect_x * rect_y);

      result = rect_y > 0 ? result + partial : result - partial;

      x_start += x_jump;

    }

    printf("Całka z zadanej funkcji na podanym przedziale wynosi: %f\n", result);
    free(stack);
    free(user_input);
    reset();
  } while (1);
}
