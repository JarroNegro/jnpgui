#include <stdlib.h>
#include <string.h>
void instalar_paquete(GtkWidget *widget ,gpointer paquete2);
void instalar_paquete(GtkWidget *widget, gpointer data);
void desinstalar_paquete(GtkWidget *widget, gpointer data);



int actualizar()
{

g_print("Actualizando lista de paquetes...");
system("servidor=`cat /etc/jnp/mirror`|| mkdir /var/cache/jnp &> /dev/null&&cd /var/cache/jnp && wget  -c  \"$servidor\"paquetes.txt");

return 0;
}

enum
{
  
PAQUETE = 0,
VERSION,
DESCRIPCION,
TAMANO,
TIPO,
NUM_COLS
} ;

static GtkTreeModel *
create_and_fill_model (void)
{
 FILE *fp;
  int i=0,j=0;
  char str[512],paquete[256],version[256],descripcion[256],tamano[256],tipo[256];
  GtkTreeStore  *treestore;
  GtkTreeIter    toplevel;
  treestore = gtk_tree_store_new(NUM_COLS,
                                 G_TYPE_STRING,                                 G_TYPE_STRING,
				G_TYPE_STRING,
				G_TYPE_STRING,
			G_TYPE_STRING);




//empieza llenado
if((fp = fopen("/var/cache/jnp/paquetes.txt", "r"))==NULL) {
    g_print("No se puede abrir el archivo.\n");
  }

  while(!feof(fp)) {
i=0;
j=0;

while(i<255)
{
paquete[i]=' ';
version[i]=' ';
descripcion[i]=' ';
tamano[i]=' ';
tipo[i]=' ';

i++;
}
i=0;


    if(fgets(str, 510, fp))
       {

                        while(str[i]!='^')
                        {
                        paquete[i]=str[i];

                        i++;
                        }
                        i++;
                        paquete[i]='\0';

/////
                        j=0;
                        while(str[i]!='^')
                        {
                        version[j]=str[i];
                        i++;
                        j++;
                        }
                         i++;
                         version[i]='\0';

			j=0;
			while(version[j]!=' ')
			{
			j++;
			}
			version[j]='\0';
/////


/////
                        j=0;
                        while(str[i]!='^')
                        {
                        descripcion[j]=str[i];
                        i++;
                        j++;
                        }
                         i++;
                         descripcion[i]='\0';

                     //   j=0;
                   //     while(descripcion[j]!=' ')
                       // {
                        //j++;
                        //}
                        //descripcion[j]='\0';
/////



/////
                        j=0;
                        while(str[i]!='^')
                        {
                        tamano[j]=str[i];
                        i++;
                        j++;
                        }
                         i++;
                         tamano[i]='\0';

                        j=0;
                        while(tamano[j]!=' ')
                        {
                        j++;
                        }
                        tamano[j]='\0';
/////



/////
                        j=0;
                        while(str[i]!='^')
                        {
                        tipo[j]=str[i];
                        i++;
                        j++;
                        }
                         i++;
                         tipo[i]='\0';

                        j=0;
                        while(tipo[j]!=' ')
                        {
                        j++;
                        }
                        tipo[j]='\0';
/////
gchar *descripcion2;

 descripcion2 = g_convert (descripcion, -1, "UTF-8", "ISO-8859-1",
                            NULL, NULL, NULL);


 gtk_tree_store_append(treestore, &toplevel, NULL);
        gtk_tree_store_set(treestore, &toplevel,
                     PAQUETE,paquete,
                     VERSION, version,
                     DESCRIPCION, descripcion2,
                     TAMANO, tipo,
			TIPO, tamano,
                     -1);





        }

  }

fclose(fp);





  return GTK_TREE_MODEL(treestore);
}

gchar *name;
int flag;


 void
  view_onRowActivated (GtkTreeView        *treeview,
                       GtkTreePath        *path,
                       GtkTreeViewColumn  *col,
                       gpointer            userdata)
  {
    GtkTreeModel *model;
    GtkTreeIter   iter;

gchar *descripcion;
     model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path))
    {


       gtk_tree_model_get(model, &iter, PAQUETE, &name, -1);

gtk_tree_model_get(model, &iter, DESCRIPCION, &descripcion, -1);




GtkWidget *ventana2,*tabla,*boton,*label,*logo;

ventana2= gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title (GTK_WINDOW (ventana2), name);
gtk_container_set_border_width(GTK_CONTAINER(ventana2),10);
gtk_window_set_position(GTK_WINDOW(ventana2), GTK_WIN_POS_CENTER);


g_signal_connect_swapped(G_OBJECT(ventana2), "destroy",G_CALLBACK(gtk_widget_hide_all), G_OBJECT(ventana2));

tabla = gtk_table_new(4,4, FALSE);
gtk_container_add(GTK_CONTAINER(ventana2), tabla);


logo = gtk_image_new_from_file("/usr/share/jn/logo.jpg");
gtk_table_attach_defaults(GTK_TABLE(tabla), logo, 0, 4, 0,1);



label = gtk_label_new(descripcion);


gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
gtk_table_attach_defaults(GTK_TABLE(tabla), label, 0, 4, 1,2);


boton=gtk_button_new_with_label("Instalar");
gtk_table_attach_defaults(GTK_TABLE(tabla), boton, 0, 1, 3,4);



g_signal_connect (G_OBJECT (boton), "clicked",G_CALLBACK (instalar_paquete),NULL);


boton=gtk_button_new_with_label("Desinstalar");
gtk_table_attach_defaults(GTK_TABLE(tabla), boton, 1, 2, 3,4);

g_signal_connect (G_OBJECT (boton), "clicked",G_CALLBACK (desinstalar_paquete), NULL);




boton=gtk_button_new_with_label("Cerrar");
gtk_table_attach_defaults(GTK_TABLE(tabla), boton, 3, 4, 3,4);

g_signal_connect (G_OBJECT (boton), "clicked",G_CALLBACK (cerrarventana),G_OBJECT(ventana2));

gtk_widget_show_all(ventana2);








    }



  }


void instalar_paquete(GtkWidget *widget, gpointer data)
{

char paquete2[250];
char comando[250]="servidor=`cat /etc/jnp/mirror`&&cd /var/cache/jnp && wget -c \"$servidor\"paquetes/";

int i=0;
while(name[i]!=' ')
{
paquete2[i]=name[i];
i++;
}
paquete2[i]='\0';
strcat(comando,paquete2);
strcat(comando,".jnp");
strcat(comando,"&& jnpi instalar ");
strcat(comando,paquete2);
strcat(comando,".jnp");

system(comando);

}


void desinstalar_paquete(GtkWidget *widget, gpointer data)
{

char paquete2[250];
char comando[250]="servidor=`cat /etc/jnp/mirror`&&cd /var/cache/jnp";

int i=0;
while(name[i]!=' ')
{
paquete2[i]=name[i];
i++;
}
paquete2[i]='\0';

strcat(comando,"&& jnpi desinstalar ");
strcat(comando,paquete2);
strcat(comando,".jnp");

system(comando);
}




static GtkWidget *
create_view_and_model (void)
{
  GtkTreeViewColumn   *col;
  GtkCellRenderer     *renderer;
  GtkWidget           *view;
  GtkTreeModel        *model;
  view = gtk_tree_view_new();


g_signal_connect(view, "row-activated", (GCallback) view_onRowActivated, NULL);


//columna1

  col = gtk_tree_view_column_new();

  gtk_tree_view_column_set_title(col, "PAQUETE");

  gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);



  renderer = gtk_cell_renderer_text_new();

  gtk_tree_view_column_pack_start(col, renderer, TRUE);


  g_object_set(renderer,
               "weight", PANGO_WEIGHT_BOLD,
               "weight-set", TRUE,
               NULL);



  gtk_tree_view_column_add_attribute(col, renderer, "text", PAQUETE);



//columna2
  col = gtk_tree_view_column_new();

  gtk_tree_view_column_set_title(col,  g_convert ("VERSIÓN", -1, "UTF-8", "ISO-8859-1",NULL, NULL, NULL));



  gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

  renderer = gtk_cell_renderer_text_new();

  gtk_tree_view_column_pack_start(col, renderer, TRUE);
  gtk_tree_view_column_add_attribute(col, renderer, "text", VERSION);


//columna3
  col = gtk_tree_view_column_new();

gtk_tree_view_column_set_title(col,  g_convert ("DESCRIPCIÓN", -1, "UTF-8", "ISO-8859-1",NULL, NULL, NULL));


  gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

  renderer = gtk_cell_renderer_text_new();

  gtk_tree_view_column_pack_start(col, renderer, TRUE);





  gtk_tree_view_column_add_attribute(col, renderer, "text", DESCRIPCION);


//columna4
  col = gtk_tree_view_column_new();

gtk_tree_view_column_set_title(col, g_convert ("TAMAÑO", -1, "UTF-8", "ISO-8859-1",NULL, NULL, NULL));



  gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

  renderer = gtk_cell_renderer_text_new();

  gtk_tree_view_column_pack_start(col, renderer, TRUE);

  gtk_tree_view_column_add_attribute(col, renderer, "text", TAMANO);

//



//columna4
  col = gtk_tree_view_column_new();

  gtk_tree_view_column_set_title(col, "TIPO");

  gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

  renderer = gtk_cell_renderer_text_new();

  gtk_tree_view_column_pack_start(col, renderer, TRUE);

  gtk_tree_view_column_add_attribute(col, renderer, "text", TIPO);

//


model = create_and_fill_model();

  gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);

  g_object_unref(model); /* destroy model automatically with view */

  gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(view)),
                              GTK_SELECTION_NONE);


  return view;
}

