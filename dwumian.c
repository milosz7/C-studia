#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define N_MAX 50
#define MAX_INPUT_SIZE 4
#define SYSTEM_BASE 10

int get_input(char param_name)
{
  size_t input_size = MAX_INPUT_SIZE + 1;
  int input_len = -1;
  char *user_input = (char *)malloc(input_len * sizeof(char));
  char *errptr;
  char clear_buffer[2];
  int output;

  printf("Podaj parametr %c do obliczenia dwumianu Newtona z przedziału 0-50:\n", param_name);
  input_len = getline(&user_input, &input_size, stdin);
  output = (int)strtol(user_input, &errptr, SYSTEM_BASE);

  while (strchr(user_input, '\n') == NULL && clear_buffer[0] != '\n')
  {
    fgets(clear_buffer, 2, stdin);
  }

  for (int i = 0; i < input_len - 1; i++)
  {
    if (!isdigit(user_input[i]) || output > N_MAX || input_len == -1)
    {
      free(user_input);
      printf("Nieprawidłowy argument!");
      return get_input(param_name);
    }
  }
  
  free(user_input);
  return output;
}

int main()
{
  int n, k;
  long *newton[N_MAX + 1];

  do
  {
    n = get_input('n');
    k = get_input('k');
    if (n < k)
    {
      printf("Niepoprawne argumenty! (n < k)\n");
    }
  } while (n < k);

  for (int i = 0; i < n + 1; i++)
  {
    int arr_size = i + 1;
    newton[i] = (long *)calloc(arr_size, sizeof(long));

    if (newton[i] == NULL)
    {
      printf("Błąd alokacji pamięci.");
      exit(1);
    }

    for (int j = 0; j < arr_size; j++)
    {
      *(*(newton + i) + j) = 1;
    }

    if (i > 1)
    {
      for (int k = 1; k < arr_size - 1; k++)
      {
        *(*(newton + i) + k) = (*(*(newton + i - 1) + k - 1) + *(*(newton + i - 1) + k));
      }
    }
  }

  printf("Dwumian Newtona o postaci %d po %d jest równy: %ld\n", n, k, *(*(newton + n) + k));
  
  for (int l = 0; l < n + 1; l++)
  {
    free(newton[l]);
  }
}
