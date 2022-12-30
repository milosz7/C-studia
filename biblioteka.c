#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <uuid/uuid.h>

// aby skompilować należy użyć flagi "-luuid"
// program został napisany na ubuntu 22.04

// #define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define UUID_LEN 36
#define MIN_INPUT_LEN 3
#define DATA_CHUNK_SIZE 32

typedef struct Book
{
  char *title;
  char *genre;
  char *author;
  int is_borrowed;
  char *id;
  struct Book *next;
} Book;

char *generate_id()
{
  uuid_t binary_uuid;
  char *uuid = (char *)malloc(UUID_LEN + 1);
  uuid_generate_random(binary_uuid);
  uuid_unparse_lower(binary_uuid, uuid);

  return uuid;
}

void update_field(char **book_field, char *data)
{
  int data_len = strlen(data);
  *book_field = (char *)malloc(data_len);
  strcpy(*book_field, data);
}

void clear_buffer(char *input)
{
  char clear_buffer[2];
  while (strchr(input, '\n') == NULL && clear_buffer[0] != '\n')
    fgets(clear_buffer, 2, stdin);
}

void print_prompt(char *print_param)
{
  printf("Podaj %s książki, którą chcesz dodać do bazy danych:\n", print_param);
}

void message_too_short()
{
  printf("Podane dane nie spełniają wymogu co do długości (minimum %d znaków).\n", MIN_INPUT_LEN);
}

void print_help()
{
  printf("-------------\n");
  printf("Dostępne operacje:\n");
  printf("\"1\" - pokaż listę wszystkich książek,\n");
  printf("\"2\" - znajdź książkę po ID,\n");
  printf("\"3\" - dodaj nową książkę do bazy danych,\n");
  printf("\"4\" - edytuj dane książki w bazie danych,\n");
  printf("\"5\" - usuń dane książki z bazy danych,\n");
  printf("\"q\" - zakończ działanie programu,\n");
}

void print_data(Book *book)
{
  printf("-------------\n");
  printf("ID: %s,\n", book->id);
  printf("Tytuł: %s,\n", book->title);
  printf("Autor: %s,\n", book->author);
  printf("Gatunek: %s,\n", book->genre);
  printf("Dostępność: %s\n", (!book->is_borrowed) ? "Tak" : "Nie");
}

void get_by_id(Book *book)
{
  char passed_id[UUID_LEN + 1];
  fgets(passed_id, UUID_LEN + 1, stdin);
  clear_buffer(passed_id);

  while (book != NULL)
  {
    if (strcmp(book->id, passed_id) == 0)
    {
      print_data(book);
      break;
    }
    book = book->next;
  }
  if (book == NULL)
    printf("Książka o podanym ID nie istnieje!\n");
}

void get_all(Book *book)
{
  while (book != NULL)
  {
    print_data(book);
    book = book->next;
  }
}

Book *get_last(Book *book)
{
  if (book == NULL)
    return NULL;
  if (book->next == NULL)
    return book;
  get_last(book->next);
}

int get_user_input(char *input_ref, size_t *input_size)
{
  int input_len = getline(&input_ref, input_size, stdin);
  return input_len;
}

Book *add_new(Book *head)
{
  Book *new_book, *last;

  new_book = (Book *)malloc(sizeof(*new_book));

  int author_len = 0, title_len = 0, genre_len = 0;
  size_t author_inp_size = DATA_CHUNK_SIZE;
  size_t title_inp_size = DATA_CHUNK_SIZE;
  size_t genre_inp_size = DATA_CHUNK_SIZE;

  last = get_last(head);
  char *author_input = (char *)malloc(author_inp_size);
  char *title_input = (char *)malloc(title_inp_size);
  char *genre_input = (char *)malloc(genre_inp_size);

  while (title_len < MIN_INPUT_LEN + 1)
  {
    print_prompt("tytuł");
    title_len = get_user_input(title_input, &title_inp_size);
    *(title_input + title_len - 1) = '\0';
    if (title_len < MIN_INPUT_LEN + 1)
      message_too_short();
  }

  while (author_len < MIN_INPUT_LEN + 1)
  {
    print_prompt("autora");
    author_len = get_user_input(author_input, &author_inp_size);
    *(author_input + author_len - 1) = '\0';
    if (author_len < MIN_INPUT_LEN + 1)
      message_too_short();
  }

  while (genre_len < MIN_INPUT_LEN + 1)
  {
    print_prompt("gatunek");
    genre_len = get_user_input(genre_input, &genre_inp_size);
    *(genre_input + genre_len - 1) = '\0';
    if (genre_len < MIN_INPUT_LEN + 1)
      message_too_short();
  }

  update_field(&new_book->title, title_input);
  update_field(&new_book->author, author_input);
  update_field(&new_book->genre, genre_input);
  update_field(&new_book->id, generate_id());
  new_book->is_borrowed = 0;
  new_book->next = NULL;

  if (last)
    last->next = new_book;

  printf("Dodano nową książkę:\n");
  print_data(new_book);

  return (last == NULL) ? new_book : head;
}

Book *delete_data(Book *book)
{
  printf("Podaj ID książki, którą chcesz usunąć:\n");
  char passed_id[UUID_LEN + 1];
  fgets(passed_id, UUID_LEN + 1, stdin);
  clear_buffer(passed_id);

  Book *to_remove, *prev, *head;
  head = book;

  if (strcmp(head->id, passed_id) == 0)
  {
    to_remove = head;
    head = book->next;
    free(to_remove);
    return head;
  }

  while (book != NULL)
  {
    if (strcmp(book->next->id, passed_id) == 0)
    {
      to_remove = book->next;
      book->next = (to_remove->next != NULL) ? to_remove->next : NULL;
      free(to_remove);
      return head;
    }
    book = book->next;
  }
}

Book *create_sample_data()
{
  Book *head, *second, *third;

  head = (Book *)malloc(sizeof(*head));
  update_field(&head->author, "J.K Rowling");
  update_field(&head->title, "Harry Potter");
  update_field(&head->genre, "Fantasy");
  update_field(&head->id, generate_id());
  head->is_borrowed = 0;

  second = (Book *)malloc(sizeof(*second));
  update_field(&second->author, "George Orwell");
  update_field(&second->title, "1984");
  update_field(&second->genre, "Sci-fi");
  update_field(&second->id, generate_id());
  second->is_borrowed = 0;

  third = (Book *)malloc(sizeof(*third));
  update_field(&third->author, "Dmitry Glukhovsky");
  update_field(&third->title, "Futu.re");
  update_field(&third->genre, "Sci-fi");
  update_field(&third->id, generate_id());
  third->is_borrowed = 1;

  head->next = second;
  second->next = third;
  third->next = NULL;

  // printf("next: %s\n", head->next->next->author);
  return head;
}

void perform_operation(char user_choice, Book *head)
{
}

int main()
{
  Book *head, *test;
  head = create_sample_data();
  print_help();

  do
  {
    char user_choice[2];

    printf("Wybierz operację jaką chcesz przeprowadzić: (h - wyświetl pomoc)\n");
    fgets(user_choice, 2, stdin);
    clear_buffer(user_choice);

    switch (*user_choice)
    {
    case '1':
      get_all(head);
      break;
    case '2':
      get_by_id(head);
      break;
    case '3':
      head = add_new(head);
      break;
    case '5':
      head = delete_data(head);
      break;
    case 'h':
      print_help();
      break;
    case 'q':
      printf("Opuszczanie programu...\n");
      exit(0);
    default:
      printf("Nieprawidłowa operacja.\n");
      print_help();
      break;
    }

  } while (1);

  add_new(head);
  get_all(head);
  // get_by_id("123", head);
  // printf("%s\n", test->author);
}