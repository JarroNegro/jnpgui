int cerrarventana( GtkWidget *widget, gpointer data)
{
GtkWidget *ventana2;
ventana2=data;
gtk_widget_hide_all(ventana2);

return 0;
}


