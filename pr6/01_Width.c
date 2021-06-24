#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>

typedef struct node
{
  int data;
  struct node * left;
  struct node * right;
  struct node * parent;
} node;

typedef struct tree
{
  struct node * root;   // указатель на корень дерева
  int count;            // количество узлов в дереве
} tree;

void init(tree * t)
{
    t->root = NULL;
    t->count = 0;
}

node* getFreeNode(int value, node* parent) // Новый узел
{
    node* tmp = (struct node*)malloc(sizeof(struct node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}


int insert(tree* t, int value) // Вставка узла
{
    if (t->root == NULL) 
    {   // Проверка корня
        t->root = getFreeNode(value, NULL); //занесение корня
        t->count++;
        return 0;
    }
    struct node* tmp = t->root;
    while (tmp != NULL) 
    {
        if (value > tmp->data) 
        { 
            if (tmp->right != NULL) 
            {
                tmp = tmp->right;
                continue;
            } 
            else 
            {
                tmp->right = getFreeNode(value, tmp);
                t->count++;
                return 0;
            }
        } 
        else if (value < tmp->data) 
        {
            if (tmp->left != NULL) 
            {
                tmp = tmp->left;
                continue;
            } 
            else 
            {
                tmp->left = getFreeNode(value, tmp);
                t->count++;
                return 0;
            }
        }
        else if (value == tmp->data) return 0;
        else 
        {
            exit(2);
        }
    }
    return 1;
}

int deepness(struct node * t){
	/*
  if (n == NULL){
    return deep;
  }
  int d1 = deepness(n->left, deep + 1);
  int d2 = deepness(n->right, deep + 1);
  return (d1 > d2) ? d1 : d2;
  */
    int r=0, l=0;
    if ((t->right) != NULL) r = deepness(t->right);
    if ((t->left) != NULL) l = deepness(t->left);
    if (r > l) return (r+1);
    return (l+1);

}

int printTree(struct node *t)
{
    if (t == NULL)
    {
        printf("-\n");
        return 1;
    }
    struct node *Temp=t;
    int Rang=0, i, j, k, sk;
    int *comb;
    Rang = deepness(t);
    comb = (int*)malloc(sizeof(int));
    for (i = 0; i < Rang; i++)
    {
        if (i != 0)
        {
            comb = (int*)realloc(comb, i* sizeof(int));
            for (j = 0; j < i; j++)
            {
                comb[j] = 0;
            }
        }
        j = 1;
        sk = i;
        while (sk != 0)
        {
            j = j * 2;
            sk--;
        }
        while (j != 0)
        {
            k = 0;
            Temp = t;
            for (k = 0; k < i; k++)
            {
                if (comb[k] == 0)
                {
                    if ((Temp->left) != NULL) Temp = Temp->left;
                    else
                    {
                        k = -1;
                        break;
                    }
                }
                else
                {
                    if ((Temp->right) != NULL) Temp = Temp->right;
                    else
                    {
                        k = -1;
                        break;
                    }
                }
            }
            if (i != 0)
            {
                sk=i-1;
                comb[sk]++;
                while (1)
                {
                    if (comb[sk] == 2)
                    {
                        comb[sk] = 0;
                        sk--;
                        if (sk < 0) break;
                        else comb[sk]++;
                    }
                    else break;
                }
            }
            if (k==-1) printf("_");
            else printf("%d", (int)Temp->data);
            j--;
            if (j != 0) printf(" ");
        }
        printf("\n");
    }
    return 1;
}

node* get_root(tree * t)
{
    return t->root;
}

int get_count(tree * t)
{
    return t->count;
}
int printWidth(struct node* t)
{
	struct node *Temp = t;
    int Rang = 0, i, j, k, sk, Spaces = 0; 
    int *comb;
    Rang = deepness(t);
    comb = (int*)malloc(sizeof(int));
    for (i = 0; i < Rang; i++)//обработка рангов
    {
        if (i != 0)//объявление-зануление
        {
            comb = (int*)realloc(comb, i * sizeof(int)); 
            for (j = 0; j < i; j++)
                comb[j] = 0;
        }
        j = 1; 
        sk = i;

        while (sk != 0)//получение кол-ва элементов на уровне
        {
            j = j * 2; 
            sk--;
        }
        while (j != 0)//проход для каждого элемент
        {
            k = 0; 
            Temp = t;
            for (k = 0; k < i; k++)//проход до определённого узла
            {
                if (comb[k] == 0)
                {
                    if ((Temp->left) != NULL) 
                        Temp = Temp->left;
                    else
                    {
                        k = -1; 
                        break;
                    }
                }
                else
                {
                    if ((Temp->right) != NULL) 
                        Temp = Temp->right;
                    else
                    {
                        k = -1; 
                        break;
                    }
                }
            }

            if (i != 0)//изменяем массив, если он вообще существует
            {
                sk = i - 1; 
                comb[sk]++; 
                while (1)
                {
                    if (comb[sk] == 2)
                    {
                        comb[sk] = 0; 
                        sk--;
                        if (sk < 0) 
                            break;
                        else
                        comb[sk]++;
                    }
                    else
                        break;
                }
            }
            if (k != -1)//если элемент есть вообще
            {
                if (Spaces == 1)
                {
                    printf(" "); 
                    Spaces = 1;
                }
                printf("%d", (int)Temp->data); 
                Spaces = 1;
            }
        j--;
        }//конец ряда
    }
    return 0;
}


int main(){
    int x, i;
    struct tree tr;
    init(&tr);
    for (i = 0; i < 7; i++){
		scanf("%d", &x);
		insert(&tr, x);
	}
	printWidth(get_root(&tr));
	printf("\n");

    return 0;
}
