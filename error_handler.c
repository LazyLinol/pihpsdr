#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_handler.h"
#include "main.h"

static GtkWidget *dialog;
static gint timer;

int timeout_cb(gpointer data) {
  gtk_widget_destroy(dialog);
  exit(1);
}

int show_error(void *data) {
  dialog = gtk_dialog_new_with_buttons("ERROR", GTK_WINDOW(top_window), GTK_DIALOG_DESTROY_WITH_PARENT, NULL, NULL);
  GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
  GtkWidget *label = gtk_label_new((char *)data);
  gtk_container_add(GTK_CONTAINER(content), label);
  gtk_widget_show(label);
  timer = g_timeout_add(5000, timeout_cb, NULL);
  int result = gtk_dialog_run(GTK_DIALOG(dialog));
  // DL1YCF added return statement to make the compiler happy.
  // however I am unsure about the correct return value.
  // I would have coded this as a void function.
  return FALSE;
}

void error_handler(char *text, char *err) {
  char message[1024];
  sprintf(message, "ERROR: %s: %s\n", text, err);
  fprintf(stderr, "%s\n", message);

  sprintf(message, "ERROR\n\n    %s:\n\n    %s\n\npiHPSDR will terminate in 5 seconds", text, err);

  g_idle_add(show_error, message);
}
