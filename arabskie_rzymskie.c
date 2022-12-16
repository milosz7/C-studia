#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define BASE_INPUT_SIZE 15
#define MAX_ARABIC 3999
#define AR_TO_ROM_LEN 12
#define MAX_STRUCT_ELEM_LEN 3
#define ROM_TO_AR_LEN 6
#define SYSTEM_BASE 10
#define ROMAN_REGEXR "^M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})\n$"

typedef struct
{
  int arab;
  char *rzym;
} AR_TO_ROM;

typedef struct
{
  int arab;
  char rzym;
} ROM_TO_AR;

int is_arabic(char first_char)
{
  return isdigit(first_char);
}

void arabic_to_roman(char *user_input, AR_TO_ROM *rz)
{
  char *errptr;
  int input_converted = (int)strtol(user_input, &errptr, SYSTEM_BASE);
  char output[BASE_INPUT_SIZE] = {};
  char *roman_from_struct;
  int output_current_idx = 0;
  int length = 0;
  for (int i = 0; i < AR_TO_ROM_LEN + 1; i++)
  {
    int current_arabic = (rz + AR_TO_ROM_LEN - i)->arab;
    while (input_converted - current_arabic >= 0)
    {
      roman_from_struct = (rz + AR_TO_ROM_LEN - i)->rzym;
      for (; roman_from_struct[length]; length++)
        ;
      for (int j = 0; j < length; j++)
      {
        output[output_current_idx] = roman_from_struct[j];
        output_current_idx += 1;
      }
      input_converted = input_converted - current_arabic;
    }
  }
  printf("Wynik: %s\n", output);
}

void roman_to_arabic(char *user_input, ROM_TO_AR *rz, int input_len)
{
  int result = 0;
  int last_value = 0;

  for (int i = input_len; i >= 0; i--)
  {
    char current = user_input[i];
    for (int j = 0; j < ROM_TO_AR_LEN + 1; j++)
    {
      if (current == ((rz + j)->rzym))
      {
        int current_value = ((rz + j)->arab);
        if (last_value > current_value)
        {
          result -= current_value;
        }
        else
        {
          result += current_value;
        }
        last_value = current_value;
        break;
      }
    }
  }
  printf("Wynik: %d\n", result);
}

int validate_input(char *user_input, int input_size)
{
  char *errptr;
  int is_arabic = (isdigit(user_input[0])) ? 1 : 0;

  if (is_arabic)
  {
    for (int i = 0; i < input_size; i++)
    {
      if (!isdigit(user_input[i]))
      {
        return 0;
      }
    }
    int converted = (int)strtol(user_input, &errptr, SYSTEM_BASE);
    if (converted > MAX_ARABIC || converted == 0)
    {
      return 0;
    }
  }
  else
  {
    for (int i = 0; i < input_size; i++)
    {
      user_input[i] = toupper(user_input[i]);
    }
    int is_valid;
    regex_t regexr;
    is_valid = regcomp(&regexr, ROMAN_REGEXR, REG_EXTENDED);
    is_valid = regexec(&regexr, user_input, 0, NULL, 0);
    if (is_valid == REG_NOMATCH)
    {
      regfree(&regexr);
      return 0;
    }
  }
  return 1;
}

int main()
{
  AR_TO_ROM ar_to_rom[] = {{1, "I"}, {4, "IV"}, {5, "V"}, {9, "IX"}, {10, "X"}, {40, "XL"}, {50, "L"}, {90, "XC"}, {100, "C"}, {400, "CD"}, {500, "D"}, {900, "CM"}, {1000, "M"}};
  ROM_TO_AR rom_to_ar[] = {{1, 'I'}, {5, 'V'}, {10, 'X'}, {50, 'L'}, {100, 'C'}, {500, 'D'}, {1000, 'M'}};

  do
  {
    char *user_input;
    size_t input_size = BASE_INPUT_SIZE;
    int input_len = -1;
    user_input = (char *)malloc(input_size * sizeof(char));
    int is_valid = 0;

    while (!is_valid)
    {
      printf("Podaj liczbę arabską lub rzymską, którą chcesz przekonwertować (1-3999):\n");
      input_len = getline(&user_input, &input_size, stdin);
      if (input_len == -1 || input_len > BASE_INPUT_SIZE + 1)
      {
        is_valid = 0;
        continue;
      }
      is_valid = validate_input(user_input, input_len - 1);
      if (!is_valid)
      {
        printf("Nieprawidłowy argument!\n");
      }
    }
    if (is_arabic(user_input[0]))
    {
      arabic_to_roman(user_input, ar_to_rom);
    }
    else
    {
      roman_to_arabic(user_input, rom_to_ar, input_len - 1);
    }
    return 0;
  } while (1);
}
