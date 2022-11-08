#include <gtk-4.0/gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

static void print_value(GtkWidget *widget, gpointer data)
{
  printf("%d\n", (int)(long)data);
}

static void populate_grid(GtkWidget *grid)
{
  int row_position = 0;
  unsigned int last_idx = 2;
  char *btn_text;
  GtkWidget *button;
  for (int i = 9; i >= 0; i--)
  {
    gpointer btn_value_pointer;
    btn_value_pointer = (void*)(long)i;
    sprintf(btn_text, "%d", i);
    button = gtk_button_new_with_label(btn_text);
    gtk_grid_attach(GTK_GRID(grid), button, last_idx, row_position, 1, 1);
    g_signal_connect(button, "clicked", G_CALLBACK(print_value), btn_value_pointer);
    last_idx = last_idx ? last_idx - 1 : 2;
    if ((i + last_idx) % 3 == 0)
    {
      row_position++;
    }
  }
}

static void activate(GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *buttons_grid;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Kalkulator");
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 600);
  buttons_grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), buttons_grid);
  populate_grid(buttons_grid);

  gtk_widget_show(window);
}

int main(int argc, char *argv[])
{
  int status;

  GtkApplication *app = gtk_application_new("milosz.kalkulator", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}