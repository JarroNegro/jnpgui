#include <gtk/gtk.h>
#include "ventanas.h"
#include "paquetes.h"
int main(int argc,char *argv[])
{

GtkWidget *label,*boton,*lista;
 
GtkWidget *window;
GtkWidget *scrolled_window;
    
GtkWidget *tabla; 


gtk_init(&argc,&argv);

actualizar();


    /* Create a new dialog window for the scrolled window to be
     * packed into.  */
    window = gtk_dialog_new ();
    gtk_window_set_title (GTK_WINDOW (window), "Administrador JNP -JarroNegro-");
    gtk_container_set_border_width (GTK_CONTAINER (window), 0);
    gtk_widget_set_size_request (window, 600, 500);


//label
label = gtk_label_new("Administrador JNP!");
gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);


gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window)->vbox), label, FALSE, FALSE, 0);
    /* create a new scrolled window. */
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);

    gtk_container_set_border_width (GTK_CONTAINER (scrolled_window), 10);

    /* the policy is one of GTK_POLICY AUTOMATIC, or GTK_POLICY_ALWAYS.
     * GTK_POLICY_AUTOMATIC will automatically decide whether you need
     * scrollbars, whereas GTK_POLICY_ALWAYS will always leave the scrollbars
     * there.  The first one is the horizontal scrollbar, the second,
     * the vertical. */
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
                                    GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

    /* The dialog window is created with a vbox packed into it. */
    gtk_box_pack_start (GTK_BOX (GTK_DIALOG(window)->vbox), scrolled_window,
                        TRUE, TRUE, 0);







//tabla contenedora
  tabla = gtk_table_new(3,4, FALSE);


  /* pack the table into the scrolled window */
    gtk_scrolled_window_add_with_viewport (
                   GTK_SCROLLED_WINDOW (scrolled_window), tabla);

lista = create_view_and_model();
gtk_table_attach_defaults(GTK_TABLE(tabla), lista, 0, 3, 1,2);




boton=gtk_button_new_with_label("Cerrar");


g_signal_connect (G_OBJECT (boton), "clicked",G_CALLBACK (gtk_main_quit), G_OBJECT(window));


gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window)->action_area), boton, TRUE, TRUE, 0);



gtk_widget_show_all(window);
g_signal_connect_swapped(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), G_OBJECT(window));



gtk_main();
return 0;



}
