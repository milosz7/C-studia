#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// plik do szyfrowania umieszczamy w folderze programs_data, można również zmienić makro PATH_ROOT na dowolną istniejącą ścieżkę do folderu.

#define BASE_INPUT_SIZE 16
#define PATH_ROOT "./programs_data/"
#define MKSTEMP_SUFFIX "-XXXXXX"

void mem_err()
{
  printf("Błąd alokacji pamięci.\n");
  exit(1);
}

char *create_file_path(char *fname)
{
  char path_root[] = PATH_ROOT;
  int path_len = strlen(path_root) + strlen(fname);
  char *path_combined = (char *)malloc(path_len);

  if (path_combined == NULL)
  {
    mem_err();
  }

  strcat(path_combined, path_root);
  strcat(path_combined, fname);
  return path_combined;
}

int main(int argc, char *argv[])
{
  FILE *file, *temp_file;
  size_t input_size = BASE_INPUT_SIZE;
  char *password = (char *)malloc(input_size);
  char *filename, *temp_filename;
  int file_descriptor;
  int sign;
  int sign_idx = 0;
  int pwd_len;

  if (password == NULL)
  {
    mem_err();
  }

  if (argc < 2)
  {
    printf("Niepoprawne wejście! Aby zaszyfrować plik należy użyć komendy: ./{nazwa_programu} {nazwa_pliku}.{rozszerzenie}\n");
    exit(1);
  }

  filename = create_file_path(argv[1]);
  temp_filename = create_file_path(MKSTEMP_SUFFIX);
  file_descriptor = mkstemp(temp_filename);

  file = fopen(filename, "rb");

  if (file == NULL)
  {
    printf("Podana ścieżka nie prowadzi do pliku tekstowego!\n");
    exit(1);
  }

  if (file_descriptor == -1 || (temp_file = fdopen(file_descriptor, "wb")) == NULL)
  {
    printf("Nie udało się utworzyć pliku tymczasowego.\n");
    exit(1);
  }

  printf("Podaj hasło do zaszyfrowania/odszyfrowania pliku:\n");
  pwd_len = getline(&password, &input_size, stdin);

  if (pwd_len == -1)
  {
    printf("Błąd wczytywania hasła.\n");
    exit(1);
  }

  while ((sign = fgetc(file)) != EOF)
  {
    sign ^= password[sign_idx % pwd_len];
    putc(sign, temp_file);
    sign_idx++;
  }

  unlink(filename);
  rename(temp_filename, filename);

  printf("Operacja ukończona pomyślnie.\n");
  exit(0);
}
