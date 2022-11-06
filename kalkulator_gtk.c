#include <gtk-4.0/gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

// static void print_value() {

// }

static void populate_grid(GtkWidget *grid) {
  int row_position = 0;
  char *btn_text;
  GtkWidget* button;
  for (int i = 9; i >= 0; i--) {
    sprintf(btn_text, "%d", i);
    button = gtk_button_new_with_label(btn_text);
    gtk_grid_attach(GTK_GRID(grid), button, abs(7 - i) % 3, row_position, 1, 1);
    if ((i + 2) % 3 == 0) {
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