#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_PHRASE_LEN 1000
#define VALID_NUMBER "^\\-?[0-9]+\\.?([0-9]+)?\n$"
#define CHUNK_SIZE 16

// plik należy umieścić w programs_data i nazwać go digits.txt
// program używa znaku nowej linii do oddzielania liczb
// ostatnia liczba musi być również zakończona znakiem nowej linii
// ze względu na walidację danych za pomocą wyrażenia regularnego

int compare(const void *a, const void *b)
{
  return strcmp(*(const char**)a, *(const char**)b);
}

int main()
{
  FILE *numbers_to_sort;
  numbers_to_sort = fopen("./programs_data/digits.txt", "r");
  char scanned_number[MAX_PHRASE_LEN + 1];
  int sign_counter, nums_counter = 0;
  int num_len;

  int chunks_to_allocate = 1;
  int arr_size = chunks_to_allocate * CHUNK_SIZE;
  char **num_pointers_arr = (char **)malloc(arr_size);

  while (fgets(scanned_number, MAX_PHRASE_LEN, numbers_to_sort))
  {

    regex_t numbers_regexr;
    int is_valid;

    is_valid = regcomp(&numbers_regexr, VALID_NUMBER, REG_EXTENDED);
    is_valid = regexec(&numbers_regexr, scanned_number, 0, NULL, 0);
    regfree(&numbers_regexr);

    num_len = strlen(scanned_number);
    scanned_number[num_len - 1] = '\0';

    if (is_valid == REG_NOMATCH)
    {
      printf("----------------\n");
      printf("Nieprawidłowe wejście w linii %d.\n", nums_counter + 1);
      printf("Fraza, która nie przeszła walidacji: %s\n", scanned_number);
      exit(1);
    }

    if (nums_counter == arr_size - 1)
    {
      chunks_to_allocate++;
      arr_size = chunks_to_allocate * CHUNK_SIZE;
      num_pointers_arr = (char **)realloc(num_pointers_arr, arr_size);
    }

    *(num_pointers_arr + nums_counter) = (char *)malloc(num_len);
    strcpy(*(num_pointers_arr + nums_counter), scanned_number);
    nums_counter++;
  }

  printf("Przed sortowaniem:\n");
  for (int i = 0; i < nums_counter; i++)
  {
    printf("%s\n", *(num_pointers_arr + i));
  }

  qsort(num_pointers_arr, nums_counter, sizeof(num_pointers_arr), compare);

  printf("Po sortowaniu:\n");
  for (int i = 0; i < nums_counter; i++)
  {
    printf("%s\n", *(num_pointers_arr + i));
  }
}