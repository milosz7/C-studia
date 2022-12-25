#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <regex.h>
#include <string.h>
#include <ctype.h>

#define OPERAND_INPUT_LENGTH 3
#define NUMBERS_REGEXR "^(-?[0-9]+)?\\.?([0-9]+)?\n?$"
#define BASE_INPUT_SIZE 16

int clear_buffer(char *input)
{
  char clear_buffer[2];
  int overflow = 0;

  while (strchr(input, '\n') == NULL && clear_buffer[0] != '\n')
  {
    fgets(clear_buffer, 2, stdin);
    overflow = 1;
  }

  return overflow;
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
    printf("Czy chcesz spróbować jeszcze raz? y/n\n");
    scanf(" %c", &input);
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

void print_help()
{
  char *operations[] =
      {
          "Dodawanie: \"+\"",
          "Odejmowanie: \"-\"",
          "Dzielenie: \"/\"",
          "Mnożenie: \"*\"",
          "Potęgowanie: \"^\"",
          "Logarytm naturalny: \"l\"",
          "Sinus: \"s\"",
          "Cosinus: \"c\"",
      };
  int length = sizeof(operations) / sizeof(operations[0]);

  printf("Dostępne operacje:\n");
  for (int i = 0; i < length; i++)
  {
    printf("%s\n", operations[i]);
  }
}

char get_operand()
{
  char user_input[OPERAND_INPUT_LENGTH];
  char available_operands[] = "+-/*^lcs";
  int overflow = 0;

  printf("Wybierz działanie jakie chcesz wykonać.\n");
  print_help();
  fgets(user_input, OPERAND_INPUT_LENGTH, stdin);

  overflow = clear_buffer(user_input);
  char chosen_operand = *user_input;

  if (strchr(available_operands, tolower(chosen_operand)) == NULL || overflow)
  {
    printf("Nieprawidłowe działanie!\n");
    printf("--------------------\n");
    return get_operand();
  }

  return tolower(chosen_operand);
}

double get_num(char *which_number)
{
  size_t input_size = BASE_INPUT_SIZE;
  char *user_input = (char *)malloc(input_size);
  int is_valid;
  double output;
  char *endptr;
  regex_t number_regexr;

  printf("Podaj %s liczbę do wykonania wybranego działania:\n", which_number);

  getline(&user_input, &input_size, stdin);
  clear_buffer(user_input);

  is_valid = regcomp(&number_regexr, NUMBERS_REGEXR, REG_EXTENDED);
  is_valid = regexec(&number_regexr, user_input, 0, NULL, 0);

  if (is_valid == REG_NOMATCH)
  {
    printf("Podane dane nie są poprawną liczbą!\n");
    printf("--------------------\n");
    return get_num(which_number);
  }

  output = strtod(user_input, &endptr);

  if (errno == ERANGE)
  {
    errno = 0;
    printf("Podana liczba znajduje się poza zakresem!\n");
    printf("--------------------\n");
    return get_num(which_number);
  }

  return output;
}

void perform_one_arg_operation(double num, char operand)
{
  double result;

  switch (operand)
  {
  case 's':
    result = sin(num);
    printf("Sinus z liczby %f wynosi: %f\n", num, result);
    break;
  case 'c':
    result = cos(num);
    printf("Cosinus z liczby %f wynosi: %f\n", num, result);
    break;
  case 'l':
    if (num <= 0)
    {
      printf("Logarytm naturalny z liczby mniejszej od 0 nie istnieje!\n");
    }
    else
    {
      result = log(num);
      printf("Logarytm naturalny z liczby %f wynosi: %f\n", num, result);
    }
  default:
    break;
  }
}

void perform_two_arg_operation(double num1, double num2, char operand)
{
  double result;

  switch (operand)
  {
  case '+':
    result = num1 + num2;
    printf("Suma liczb %f + %f wynosi: %f\n", num1, num2, result);
    break;
  case '-':
    result = num1 - num2;
    printf("Różnica liczb %f i %f wynosi: %f\n", num1, num2, result);
    break;
  case '*':
    result = num1 * num2;
    printf("Iloczyn liczb %f i %f wynosi: %f\n", num1, num2, result);
    break;
  case '/':
    if (num2)
    {
      result = num1 / num2;
      printf("Wynik dzielenia %f przez %f wynosi: %f\n", num1, num2, result);
    }
    else
    {
      printf("Nie wolno dzielić przez zero!\n");
    }
    break;
  case '^':
    if (num2 < 1 && num1 < 0)
    {
      printf("Pierwiastek z liczby ujemnej nie istnieje!\n");
    }
    else
    {
      result = pow(num1, num2);
      printf("Liczba %f podniesiona do potęgi %f jest równa: %f\n", num1, num2, result);
    }
    break;
  default:
    break;
  }
}

int main()
{
  do
  {
    double num1, num2, output;
    char operand;

    operand = get_operand();

    if (isalpha(operand))
    {
      num1 = get_num("pierwszą");
      perform_one_arg_operation(num1, operand);
    }
    else
    {
      num1 = get_num("pierwszą");
      num2 = get_num("drugą");
      perform_two_arg_operation(num1, num2, operand);
    }
    printf("--------------------\n");
    reset();
  } while (1);
}
