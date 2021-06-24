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

void tree_clean(node* t){
    if(t != NULL){
        if(t->left != NULL)
            tree_clean(t->left);
        if(t->right != NULL)
            tree_clean(t->right);
        free(t);
    }
}

node* find_node(tree* t, int value)
{
	if (t->root == NULL)
	{
		return 	NULL;
	}
    struct node* tmp = t->root;
    while (tmp) 
    {
        if (value < tmp->data) 
        {
            tmp = tmp->left;
            continue;
        } 
        else if (value > tmp->data) 
        {
            tmp = tmp->right;
            continue;
        } 
        else 
        {
			return tmp;
        }
    }
    return NULL;
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
node *min(node *root)
{
    node *l = root;
    while (l -> left != NULL)
        l = l -> left;
    return l;
}
node *max(node *root)
{
    node *r = root;
    while (r -> right != NULL)
        r = r -> right;
    return r;
}


int remove_node(node* l, int value, tree* tr)
{
	struct node *m = NULL;
    if (l->data == value)
    {
		if (l == tr->root)
		{
			if (l->left == NULL && l->right == NULL)
			{	
				l = NULL;
				init(tr);
				free(l);
				return 0;
			}
			if(l->right != NULL)
			{
				m = min(l->right);
				l->data = m->data;
				remove_node(m, m->data, tr);
				return 0;
			}
			if(l->left != NULL && l->right == NULL)
			{
				m = l->left;
				m->parent = NULL;
				tr->root = m;
				free(l);
				tr->count--;
				return 0;
			}
			
		}
		else{
		if ((l->left != NULL && l->right != NULL))
		{
			m = min(l->right);
			l->data = m->data;
			remove_node(m, m->data, tr);
			return 0;
			
		}
		if (l->left == NULL && l->right == NULL)
		{
			m = l->parent;
			if(l == m->right) m->right = NULL;
			else m->left = NULL;
			free(l);
			tr->count--;
			return 0;
		}
		if(l->left == NULL && l->right != NULL)
		{
			m = l -> parent;
			if (l == m -> right) m -> right = l -> right;
			else m -> left = l -> right;
			free(l);
			tr->count--;
			return 0;
		}
		if(l->left != NULL && l->right == NULL)
		{
			m = l -> parent;
			if (l == m -> right) m -> right = l -> left;
			else m -> left = l -> left;
			free(l);
			tr->count--;
			return 0;
		}
	}
		
    }
    else
    {
        if (value < l->data)
        {
            if (l->left != NULL) return(remove_node(l->left, value, tr));
            else return 1;
        }
        else
        {
            if (l->right != NULL) return(remove_node(l->right, value, tr));
            else return 1;
        }
    }
    return 0;
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
/*
void printNode(struct node * n, int current, int deep, int first){
  if (current == deep){
      if (first > 0){
        printf(" ");
      }
    if (n == NULL){
      printf("_");
    } else{
      printf("%d", n->data);
    }
  } else if (n != NULL){
    printNode(n->left, current + 1, deep, first);
    printNode(n->right, current + 1, deep, first + 1);
  } else {
    printNode(n, current + 1, deep, first);
    printNode(n, current + 1, deep, first + 1);
  }
}

void print(struct node * n)
{
  int m = deepness(n, 0);
  for (int i = 1; i <= m; i++){
    printNode(n, 1, i, 0);
    printf("\n");
}
}

void printTree(struct tree * t)
{
	if (t->root != 	NULL){
    print(t->root);
	}
	else{
		printf(" ");
	}
}
*/
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


int rotateRight(tree * t, node *x){
	if (x == NULL) return 1;
    node * y = x -> left;
    if ((y != NULL) && (x != NULL))
    {
        x -> left = y -> right;
        if (y -> right != NULL) y -> right -> parent = x;
        y -> parent = x -> parent;
        if (x -> parent != NULL)
        {
            if (x -> parent -> left == x) x -> parent -> left = y;
            else x -> parent -> right = y;
        }
        t -> root = y;
        y -> right = x;
        x -> parent = y;
        return 0;
    } else return 1;


}

int rotateLeft(tree * t, node *x){
	if (x == NULL) return 1;
     node * y = x -> right;
    if ((y != NULL) && (x != NULL))
    {
        x -> right = y -> left;
        if (y -> left != NULL) y -> left -> parent = x;
        y -> parent = x -> parent;
        if (x -> parent != NULL)
        {
            if (x -> parent -> right == x) x -> parent -> right = y;
            else x -> parent -> left = y;
        }
        t -> root = y;
        y -> left = x;
        x -> parent = y; 
        return 0;
    } else return 1;
}

node* get_root(tree * t)
{
    return t->root;
}

int get_count(tree * t)
{
    return t->count;
}

int main(){
    int x, i;
    struct tree tr;
    init(&tr);
    for(i= 0; i< 4; i++) 
    {
        scanf("%d", &x);
        insert(&tr ,x);
    }
    printTree(get_root(&tr));
    printf("\n");
    
    for (int i = 0; i < 3; i++) 
    {
        scanf("%d", &x);
        insert(&tr, x);
    }
    printTree(get_root(&tr));
     printf("\n");
    
    int m1;
    scanf("%d", &m1);
    struct node * n;
	n = find_node(&tr, m1);
	if (n == NULL)
    {
        printf("-\n\n");
    }
    else{ 
    if (n->parent != NULL)
    {
        printf("%d ", n->parent->data);
    }
    else 
    {
        printf("_ ");
    }
    if (n->left != NULL)
    {
        printf("%d ", n->left->data);
    } else 
    {
        printf("_ ");
    }
    if (n->right != NULL)
    {
        printf("%d\n\n", n->right->data);
    } else 
    {
        printf("_\n\n");
    }
    }
    
    int m2;
    scanf("%d", &m2);
    struct node * n2;
    n2 = find_node(&tr, m2);
    if (n2 == NULL)
    {
        printf("-\n\n");
    }
    else 
    {
        if (n2->parent != NULL)
        {
            printf("%d ", n2->parent->data);
        } 
        else 
        {
            printf("_ ");
        }
        if (n2->left != NULL)
        {
            printf("%d ", n2->left->data);
        } 
        else 
        {
            printf("_ ");
        }
        if (n2->right != NULL)
        {
            printf("%d\n\n", n2->right->data);
        } 
        else 
        {
            printf("_\n\n");
        }
    }

    int m3;
    scanf("%d", &m3);
    remove_node(get_root(&tr), m3, &tr);
    printTree(get_root(&tr));
    printf("\n");
    while (1)
    {
        int a=rotateLeft(&tr, get_root(&tr));
        if (a == 1) break;
    }
    printTree(get_root(&tr));
    printf("\n");
    while (1)
    {
        int a = rotateRight(&tr, get_root(&tr));
        if (a == 1) break;
    }
    printTree(get_root(&tr));
    printf("\n");
    printf("%d\n\n", get_count(&tr));
    printf("-\n");
    return 0;
}
