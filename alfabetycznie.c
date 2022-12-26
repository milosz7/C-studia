#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_PHRASE_LEN 1000
#define VALID_PHRASE "\\b[A-Za-z\\s]+[A-Za-z]+\n"
#define CHUNK_SIZE 16

// plik należy umieścić w programs_data i nazwać go words.txt
// program używa znaku nowej linii do oddzielania słów
// ostatnie słowo musi być również zakończone znakiem nowej linii
// ze względu na walidację danych za pomocą wyrażenia regularnego

int compare(const void *a, const void *b)
{
  return strcmp(*(const char**)a, *(const char**)b);
}

int main()
{
  FILE *words_to_sort;
  words_to_sort = fopen("./programs_data/words.txt", "r");
  char scanned_phrase[MAX_PHRASE_LEN + 1];
  int sign_counter, words_counter = 0;
  int word_len;

  int chunks_to_allocate = 1;
  int arr_size = chunks_to_allocate * CHUNK_SIZE;
  char **word_pointers_arr = (char **)malloc(arr_size);

  while (fgets(scanned_phrase, MAX_PHRASE_LEN, words_to_sort))
  {

    regex_t word_regexr;
    int is_valid;

    is_valid = regcomp(&word_regexr, VALID_PHRASE, REG_EXTENDED);
    is_valid = regexec(&word_regexr, scanned_phrase, 0, NULL, 0);
    regfree(&word_regexr);

    word_len = strlen(scanned_phrase);
    scanned_phrase[word_len - 1] = '\0';

    if (is_valid == REG_NOMATCH)
    {
      printf("----------------\n");
      printf("Nieprawidłowe wejście w linii %d.\n", words_counter + 1);
      printf("Fraza, która nie przeszła walidacji: %s\n", scanned_phrase);
      exit(1);
    }

    if (words_counter == arr_size - 1)
    {
      chunks_to_allocate++;
      arr_size = chunks_to_allocate * CHUNK_SIZE;
      word_pointers_arr = (char **)realloc(word_pointers_arr, arr_size);
    }

    *(word_pointers_arr + words_counter) = (char *)malloc(word_len);
    strcpy(*(word_pointers_arr + words_counter), scanned_phrase);
    words_counter++;
  }

  printf("Przed sortowaniem:\n");
  for (int i = 0; i < words_counter; i++)
  {
    printf("%s\n", *(word_pointers_arr + i));
  }

  qsort(word_pointers_arr, words_counter, sizeof(word_pointers_arr), compare);

  printf("Po sortowaniu:\n");
  for (int i = 0; i < words_counter; i++)
  {
    printf("%s\n", *(word_pointers_arr + i));
  }
}