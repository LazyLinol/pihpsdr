/* Copyright (C)
 * 2016 - John Melton, G0ORX/N6LYT
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include <gtk/gtk.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <wdsp.h>

#include "meter.h"
#include "meter_menu.h"
#include "new_menu.h"
#include "radio.h"
#include "receiver.h"

static GtkWidget *parent_window = NULL;
static GtkWidget *dialog = NULL;

static void cleanup() {
  if (dialog != NULL) {
    gtk_widget_destroy(dialog);
    dialog = NULL;
    sub_menu = NULL;
  }
}

static gboolean close_cb(GtkWidget *widget, GdkEventButton *event, gpointer data) {
  cleanup();
  return TRUE;
}

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
  cleanup();
  return FALSE;
}

static void smeter_select_cb(GtkWidget *widget, gpointer data) { smeter = (uintptr_t)data; }

static void alc_meter_select_cb(GtkWidget *widget, gpointer data) { alc = (uintptr_t)data; }

static void analog_cb(GtkWidget *widget, gpointer data) { analog_meter = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)); }

void meter_menu(GtkWidget *parent) {
  parent_window = parent;

  dialog = gtk_dialog_new();
  gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(parent_window));
  //gtk_window_set_decorated(GTK_WINDOW(dialog),FALSE);
  gtk_window_set_title(GTK_WINDOW(dialog), "piHPSDR - Meter");
  g_signal_connect(dialog, "delete_event", G_CALLBACK(delete_event), NULL);

  GdkRGBA color;
  color.red = 1.0;
  color.green = 1.0;
  color.blue = 1.0;
  color.alpha = 1.0;
  gtk_widget_override_background_color(dialog, GTK_STATE_FLAG_NORMAL, &color);

  GtkWidget *content = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
  GtkWidget *grid = gtk_grid_new();

  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);

  GtkWidget *close_b = gtk_button_new_with_label("Close");
  g_signal_connect(close_b, "pressed", G_CALLBACK(close_cb), NULL);
  gtk_grid_attach(GTK_GRID(grid), close_b, 0, 0, 1, 1);

  GtkWidget *analog_b = gtk_check_button_new_with_label("Analog Meter");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(analog_b), analog_meter);
  gtk_grid_attach(GTK_GRID(grid), analog_b, 1, 0, 1, 1);
  g_signal_connect(analog_b, "toggled", G_CALLBACK(analog_cb), NULL);

  GtkWidget *smeter_peak = gtk_radio_button_new_with_label(NULL, "S Meter Peak");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(smeter_peak), smeter == RXA_S_PK);
  gtk_widget_show(smeter_peak);
  gtk_grid_attach(GTK_GRID(grid), smeter_peak, 0, 1, 1, 1);
  g_signal_connect(smeter_peak, "pressed", G_CALLBACK(smeter_select_cb), (gpointer)(long)RXA_S_PK);

  GtkWidget *smeter_average = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(smeter_peak), "S Meter Average");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(smeter_average), smeter == RXA_S_AV);
  gtk_widget_show(smeter_average);
  gtk_grid_attach(GTK_GRID(grid), smeter_average, 0, 2, 1, 1);
  g_signal_connect(smeter_average, "pressed", G_CALLBACK(smeter_select_cb), (gpointer)(long)RXA_S_AV);

  GtkWidget *alc_peak = gtk_radio_button_new_with_label(NULL, "ALC Peak");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(alc_peak), alc == TXA_ALC_PK);
  gtk_widget_show(alc_peak);
  gtk_grid_attach(GTK_GRID(grid), alc_peak, 1, 1, 1, 1);
  g_signal_connect(alc_peak, "pressed", G_CALLBACK(alc_meter_select_cb), (gpointer)(long)TXA_ALC_PK);

  GtkWidget *alc_average = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(alc_peak), "ALC Average");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(alc_average), alc == TXA_ALC_AV);
  gtk_widget_show(alc_average);
  gtk_grid_attach(GTK_GRID(grid), alc_average, 1, 2, 1, 1);
  g_signal_connect(alc_average, "pressed", G_CALLBACK(alc_meter_select_cb), (gpointer)(long)TXA_ALC_AV);

  GtkWidget *alc_gain = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(alc_average), "ALC Gain");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(alc_gain), alc == TXA_ALC_GAIN);
  gtk_widget_show(alc_gain);
  gtk_grid_attach(GTK_GRID(grid), alc_gain, 1, 3, 1, 1);
  g_signal_connect(alc_gain, "pressed", G_CALLBACK(alc_meter_select_cb), (gpointer)(long)TXA_ALC_GAIN);

  gtk_container_add(GTK_CONTAINER(content), grid);

  sub_menu = dialog;

  gtk_widget_show_all(dialog);
}
