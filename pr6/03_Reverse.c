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

int find(tree* t, int value, node* n)
{
  struct node * n2;
  n2 = t->root;

  if (t->root == NULL){
    return 1;
  }


  while (1){
    if (n2 == NULL) {
      return 1;
    } else if (n2->data == value){

      n->data = n2->data;
      n->left = n2->left;
      n->right = n2->right;
      n->parent = n2->parent;

      return 0;
    } else if (value > n2->data){
      n2 = n2->right;
    } else {
      n2 = n2->left;
    }
  }

  return 1;
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

int remove_node(tree* t, int value)
{
	node * n = find_node(t, value);
	if ((n -> left == NULL) && (n -> right == NULL))
	{
		if (n -> parent -> right -> data == n -> data) n -> parent -> right = NULL;
		else n -> parent -> left = NULL;
	}
	else if (n -> right == NULL) *n = *n -> left;
	else if (n -> left == NULL) *n = *n -> right;
	else
	{
		node * search = n -> right;
		node *min;
		while (1)
		{
			if (search == NULL) {
			break;
			} else {
			min = search;
			search = search -> left;
			}
		}
		n -> data = min -> data;
		n = min;
		if ((n -> left == NULL) && (n -> right == NULL))
		{
			if (n -> parent -> right -> data == n -> data) n -> parent -> right = NULL;
			else n -> parent -> left = NULL;
		}
		else if (n -> right == NULL) *n = *n -> left;
		else *n = *n -> right;
	}
t -> count--;
return 0;
} 

int deepness(struct node * n, int deep){
  if (n == NULL){
    return deep;
  }
  int d1 = deepness(n->left, deep + 1);
  int d2 = deepness(n->right, deep + 1);
  return (d1 > d2) ? d1 : d2;
}

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
    print(t->root);
}

int rotateRight(tree * t, node *x){
    node * y = x->left;
    if ((y != NULL) && (x != NULL))
    {
        x->left = y->right; 
        if (y->right != NULL)
        {
            y->right->parent = x; 
        }
        y->parent = x->parent; 
        if (x->parent != NULL)
        {
            if (x->parent->left == x)
            {
                x->parent->left = y;
            } else 
            {
                x->parent->right = y;
            } 
        }
        t->root = y;
        y->right = x;
        x->parent = y; 
        return 0;
    } else 
    {
        return 1;
    }
}

int rotateLeft(tree * t, node *x){
    node * y = x->right;
    if ((y != NULL) && (x != NULL))
    {
        x->right = y->left; 
        if (y->left != NULL)
        {
            y->left->parent = x; 
        }
        y->parent = x->parent; 
        if (x->parent != NULL)
        {
            if (x->parent->right == x)
            {
                x->parent->right = y;
            } else 
            {
                x->parent->left = y;
            } 
        }
        t->root = y;
        y->left = x;
        x->parent = y; 
        return 0;
    } else 
    {
        return 1;
    }
}

node* get_root(tree * t)
{
    return t->root;
}

int get_count(tree * t)
{
    return t->count;
}
int printWidth(struct node * n)
{
  int m = deepness(n, 0);
  int flag = 0;
  for (int i = 1; i <= m; i++){
    if (flag > 0){
        printf(" ");
    } else {
        flag++;
    }
    printNode(n, 1, i, 0);
  }
  return 0;
}

int printStraight(struct tree * t)
{
    node * a[15];
    int ai = 0;
    node * write[15];
    int wi = 0;
    node * n = t->root;
    while (wi < t->count){
        while (n != NULL){
            wi++;
            if (n->right != NULL){
                ai++;
                a[ai] = n->right;
            }
            write[wi] = n;
            n = n->left;
        }
        n = a[ai];
        ai -= 1;
    }
    int flag = 0;
    for (int i = 1; i <= wi; i++){
        if (flag > 0){
            printf(" ");
        } else {
            flag++;
        }
        printf("%d", write[i]->data);
    }
    return 0;
}

int printReverse(struct node * n, int flag)
{
    if (n->left != NULL){
        printReverse(n->left, flag + 1);
    }
    if (n->right != NULL){
        printReverse(n->right, flag + 1);
    }
    printf("%d", n->data);
    if (flag > 0){
        printf(" ");
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
	struct node* n = get_root(&tr);
	printReverse(n, 0);
	printf("\n");
    return 0;
}
