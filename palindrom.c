#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_INPUT_SIZE 16

void print_result(char* result, int is_palindrome) {
  if (is_palindrome) {
    printf("%s jest palindromem.\n", result);
  } else {
    printf("%s nie jest palindromem.\n", result);
  }
}

void clear()
{
  while ((getchar()) != '\n');
}

void reset()
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

int main()
{
  do
  {
    char *user_input;
    size_t input_size = BASE_INPUT_SIZE;
    int input_len = 1;
    int is_palindrome = 1;
    user_input = (char *)malloc(input_size * sizeof(char));
    while (input_len < 2) {
      printf("Podaj frazę aby sprawdzić czy jest palindromem:\n");
      input_len = getline(&user_input, &input_size, stdin);
      if (input_len == 1) {
        printf("Niepoprawny argument!\n");
      }
    }
    user_input[input_len - 1] = '\0';
    for (int i = 0, j = input_len - 1; i < (input_len / 2); i++, j--)
    {
      if (user_input[i] != user_input[j - 1])
        is_palindrome = 0;
    }
    print_result(user_input, is_palindrome);
    reset();
  } while (1);
}
