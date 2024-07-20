#include <gtk/gtk.h>

static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *switch_widget;
    GtkWidget *label;
    GtkCssProvider *provider;
    GtkStyleContext *context;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Advanced GTK UI");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Custom-styled button
    button = gtk_button_new_with_label("Unique Button");
    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "button { background: linear-gradient(to bottom, #4CAF50, #45a049); color: white; border-radius: 5px; }"
        "button:hover { background: linear-gradient(to bottom, #45a049, #4CAF50); }", -1, NULL);
    context = gtk_widget_get_style_context(button);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);

    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_window_close), window);

    // Switch
    switch_widget = gtk_switch_new();
    gtk_grid_attach(GTK_GRID(grid), switch_widget, 0, 1, 1, 1);

    // Label for switch
    label = gtk_label_new("Toggle Switch");
    gtk_grid_attach(GTK_GRID(grid), label, 1, 1, 1, 1);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
