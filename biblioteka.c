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

void print_data(Book *book)
{
  printf("-------------\n");
  printf("ID: %s,\n", book->id);
  printf("Tytuł: %s,\n", book->title);
  printf("Autor: %s,\n", book->author);
  printf("Gatunek: %s,\n", book->genre);
  printf("Dostępność: %s\n", (!book->is_borrowed) ? "Tak" : "Nie");
}

void get_by_id(char *id, Book *book)
{
  while (book != NULL)
  {
    if (strcmp(book->id, id) == 0)
    {
      print_data(book);
      break;
    }
    book = book->next;
  }
  if (book = NULL)
  {
    printf("Książka o podanym ID nie istnieje!\n");
  }
}

void get_all(Book *book)
{
  while (book != NULL)
  {
    print_data(book);
    book = book->next;
  }
}

Book *create_sample_data()
{
  Book *head, *second, *third;

  head = (Book *)malloc(sizeof(*head));
  head->author = (char *)malloc(strlen("J.K. Rowling"));
  strcpy(head->author, "J.K. Rowling");
  head->title = (char *)malloc(strlen("Harry Potter"));
  strcpy(head->title, "Harry Potter");
  head->genre = (char *)malloc(strlen("Fantasy"));
  strcpy(head->genre, "Fantasy");
  head->is_borrowed = 0;
  head->id = (char *)malloc(UUID_LEN + 1);
  strcpy(head->id, generate_id());

  second = (Book *)malloc(sizeof(*second));
  second->author = (char *)malloc(strlen("George Orwell"));
  strcpy(second->author, "George Orwell");
  second->title = (char *)malloc(strlen("1984"));
  strcpy(second->title, "1984");
  second->genre = (char *)malloc(strlen("Sci-fi"));
  strcpy(second->genre, "Sci-fi");
  second->is_borrowed = 0;
  second->id = (char *)malloc(UUID_LEN + 1);
  strcpy(second->id, generate_id());

  third = (Book *)malloc(sizeof(*third));
  third->author = (char *)malloc(strlen("Dmitry Glukhovsky"));
  strcpy(third->author, "Dmitry Glukhovsky");
  third->title = (char *)malloc(strlen("Futu.re"));
  strcpy(third->title, "Futu.re");
  third->genre = (char *)malloc(strlen("Sci-fi"));
  strcpy(third->genre, "Sci-fi");
  third->is_borrowed = 1;
  third->id = (char *)malloc(UUID_LEN + 1);
  strcpy(third->id, generate_id());

  head->next = second;
  second->next = third;
  third->next = NULL;

  // printf("next: %s\n", head->next->next->author);
  return head;
}

int main()
{
  Book *head;
  head = create_sample_data();
  get_all(head);
  // get_by_id("123", head);
  // printf("%s\n", head->author);
}