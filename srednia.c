#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 16

void check_alocation(void *malloc_pointer)
{
  if (malloc_pointer == NULL)
  {
    printf("Błąd alokacji pamięci.");
    exit(1);
  }
}

int main()
{
  FILE *numbers_data;
  numbers_data = fopen("./programs_data/numbers.txt", "r");
  int counter = 0;
  double sum = 0;
  int chunks_to_allocate = 1;
  int array_size = sizeof(double) * chunks_to_allocate * CHUNK_SIZE;
  double *numbers_array = (double *)malloc(array_size);

  check_alocation(numbers_array);

  do
  {
    if (counter == (array_size / sizeof(double)) - 1)
    {
      chunks_to_allocate = chunks_to_allocate + 1; 
      array_size = sizeof(double) * chunks_to_allocate * CHUNK_SIZE;
      numbers_array = (double *)realloc(numbers_array, array_size);
      check_alocation(numbers_array);
    }
    fscanf(numbers_data, "%lf", &numbers_array[counter]);
    counter++;
  } while (fgetc(numbers_data) != EOF);

  fclose(numbers_data);

  for (int i = 0; i < counter; i++)
  {
    sum += *(numbers_array + i);
  }

  free(numbers_array);

  if (counter == 1) {
    printf("Nie podano żadnych liczb w pliku.\n");
    exit(1);
  }
  printf("Średnia podanych w pliku liczb wynosi: %lf\n", (sum / counter));
}
