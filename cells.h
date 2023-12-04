
#ifndef UNTITLED4_CELLS_H
#define UNTITLED4_CELLS_H
//A voir si utile

typedef struct s_d_cell
{
    int value;
    struct s_d_cell *next_0;
    struct s_d_cell *next_1;
} t_d_cell;

typedef struct s_d_list
{
    t_d_cell *head_0;
    t_d_cell *head_1;
} t_d_list;
//
typedef struct s_sk_cell{
    int value;
    int level;
    struct s_sk_cell ** next;
}t_sk_cell;

typedef struct s_sk_list{
    t_sk_cell *heads;
    int max_level;
}t_sk_list;


t_sk_cell *createSkCell(int val,int level); //Création de la cellule

t_sk_list *initialiser_liste_a_niveaux(int n);

void afficher_liste_a_niveaux(t_sk_list *liste_a_niveaux);
t_sk_cell *searchLevel0(t_sk_list *list, int value);
t_sk_cell *searchFromTopLevel(t_sk_list *list, int value);
#endif //UNTITLED4_CELLS_H
