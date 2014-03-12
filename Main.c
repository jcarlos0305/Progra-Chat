#include "Agregar Amigo.h"
char nombres[100];
enum
{
  COLUMN = 0,
  NUM_COLS
} ;

void PopUp (GtkWidget *boton, GdkEventKey *event,GtkWidget *entry)
{
    entry = Interfaz(0,0);
}

void cargarContactos()
{
    int i;
    char str[999];
    FILE * file;
    file = fopen("amigos.txt" , "r");
    while (fscanf(file, "%s", str)!=EOF)
    {
        g_print("%s\n",str);
        int largo = strlen(str);
        for(i=0;i<largo;i++)
        {
            if(str[i]==';')
            {
                nombres[i]=";";
                i++;
            }
            else
            {
                nombres[i] = str[i];
            }
        }
        g_print("%c",nombres[0]);
        g_print("\n");
    }
    fclose(file);
}

/*void  on_changed(GtkWidget *widget, gpointer statusbar) 
{
  GtkTreeIter iter;
  GtkTreeModel *model;
  char *value;

  if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter)) 
  {
    gtk_tree_model_get(model, &iter, COLUMN, &value,-1);
    gtk_statusbar_push(GTK_STATUSBAR(statusbar),gtk_statusbar_get_context_id(GTK_STATUSBAR(statusbar), value), value);
    g_free(value);
  }
}*/

//GENERA LA ESTRUCTURA DEL ARBOL YA CON LOS ELEMENTOS
static GtkTreeModel * create_and_fill_model (void)
{
  GtkTreeStore *treestore;
  GtkTreeIter toplevel, child;

  treestore = gtk_tree_store_new(NUM_COLS,G_TYPE_STRING);

  gtk_tree_store_append(treestore, &toplevel, NULL);
  gtk_tree_store_set(treestore, &toplevel, COLUMN, "Amigos",-1);

  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child,COLUMN, "Python",-1);
  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child,COLUMN, "Perl",-1);
  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child,COLUMN, "PHP",-1);

  gtk_tree_store_append(treestore, &toplevel, NULL);
  gtk_tree_store_set(treestore, &toplevel,COLUMN, "Solicitud pendiente",-1);

  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child,COLUMN, "C",-1);

  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child,COLUMN, "C++",-1);

  gtk_tree_store_append(treestore, &child, &toplevel);
  gtk_tree_store_set(treestore, &child,COLUMN, "Java",-1);
  
  return GTK_TREE_MODEL(treestore);
}


//HACE VISIBLE LA ESTRUCTURA DEL ARBOL
static GtkWidget * create_view_and_model (void)
{
  GtkTreeViewColumn *col;
  GtkCellRenderer *renderer;
  GtkWidget *view;
  GtkTreeModel *model;

  view = gtk_tree_view_new();

  col = gtk_tree_view_column_new();
  gtk_tree_view_column_set_title(col, "Programming languages");
  gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

  renderer = gtk_cell_renderer_text_new();
  gtk_tree_view_column_pack_start(col, renderer, TRUE);
  gtk_tree_view_column_add_attribute(col, renderer, "text", COLUMN);

  model = create_and_fill_model();
  gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
  g_object_unref(model); //Como el modelo ya esta en el arbol, borramos el modelo

  //retornamos el puntero donde esta el arbol
  return view;
}


int main (int argc, char **argv)
{
    cargarContactos();
    GtkWidget *window;
    GtkWidget *view;
    GtkTreeSelection *selection; 
    GtkWidget *vbox;
    //GtkWidget *statusbar;
    GtkWidget *bAgregar;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Tree View");
    gtk_widget_set_size_request (window, 350, 300);


    vbox = gtk_vbox_new(FALSE, 2);
    gtk_container_add(GTK_CONTAINER(window), vbox);


    view = create_view_and_model();
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));
    gtk_box_pack_start(GTK_BOX(vbox), view, TRUE, TRUE, 1);

    //statusbar = gtk_statusbar_new();
    //gtk_box_pack_start(GTK_BOX(vbox), statusbar, FALSE, TRUE, 1);

    bAgregar = gtk_button_new_with_label("Agregar amigo");
    gtk_box_pack_start(GTK_BOX(vbox), bAgregar, FALSE, FALSE, 1);

    g_signal_connect(G_OBJECT(bAgregar), "clicked", G_CALLBACK(PopUp),NULL);

    g_signal_connect (G_OBJECT (window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
