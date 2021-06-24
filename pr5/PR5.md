# Практическая работа №5
## 1 Введение 
Цель работы : Получение навыков реализации бинарного дерева поиска на языке С, выработка практических умений написания программ на языке С. 

Задание на практическую работу:
1) Прочитать про бинарные дервья на СИ
2) Написать программу 01_bst.c
3) Настроить pipeline
4) Написать отчет по работе в разметке Markdown 
5) Залить на gitlab и убедиться, что pipeline проходит успешно
6) Защитить работу у преподавателя
## 2 Ход работы
### 2.1 Настойка pipeline
Настройка pipeline проходит в файле .gitlab_ci.yml. Было добавлено в пункт stages: pr5.
```sh
stages:
  - pr1
  - pr2
  - pr3
  - pr4
  - pr5
```
Раскомментированы настройки для четвертой практической работы.
```sh
pr5_easy_test:
  stage: pr5
  only:
    changes:
      - pr5/*.c
  script:
  - gcc pr5/01_*.c
  - PYTHONIOENCODING=utf-8 python3 pr5/tests/checker.py 0

pr5_hard_test:
  stage: pr5
  only:
    changes:
      - pr5/*.c
  script:
  - gcc pr5/01_*.c
  - PYTHONIOENCODING=utf-8 python3 pr5/tests/checker.py 1
  allow_failure: true
  ```
  
### 2.2 Программа 
Написана программа, реализующая бинарное дерево. Ниже представлен код структуры списка. В структуре tree объявляется ссылка на начальный узел (root) и число узлов в дереве, а в структуре node описывается узел списка. В бинарном дереве есть ссылка на предка, на следующий элемент, меньший по значению, и на следующий правый элемент, который являтся большим по значению.
```sh
typedef struct node
{
  int data;
  struct node * left;  // указатель на левый элемент 
  struct node * right; // указатель на правый элемент
  struct node * parent; // указатель на родительский узел
} node;

typedef struct tree
{
  struct node * root;   // указатель на корень дерева
  int count;            // количество узлов в дереве
} tree;
```
Были реализованы следующие функции - init (инициализация пустого списка). Происходит инициализация пустого дерева.
```sh
void init(tree * t)
{
    t->root = NULL;
    t->count = 0;
}
```
Функция clean, которая удаляет все элементы из списка. Функция free освобождает место в памяти. 
```sh
void tree_clean(node* t){
    if(t != NULL){
        if(t->left != NULL)
            tree_clean(t->left);
        if(t->right != NULL)
            tree_clean(t->right);
        free(t);
    }
}
```
Функция find_node (поиск узда по значению).
```sh
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
```
Функция insert, которая вставляет новый узел в дерево. Была прописана дополнительная функция, которая создает новый узел для вставки.
```sh
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
```
Функция remove_node, которая реализует удаление из дерева узел указанного значения. В данной функции вызывается функция min, которая ищет самое минимальное значение в дереве.
```sh
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
```
Функция deepness (расчёт глубины дерева).
```sh
int deepness(struct node * t){
   int r=0, l=0;
    if ((t->right) != NULL) r = deepness(t->right);
    if ((t->left) != NULL) l = deepness(t->left);
    if (r > l) return (r+1);
    return (l+1);
}
```
Функция printTree, которая реализует вывод в консоль бинарного дерева.
```sh
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
```
Функция  rotateRight, которая реализует правый поворот дерева.
```sh
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
```
Функция rotateLeft, которая левый поворот дерева.
```sh
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
```
Были прописаны дополнительные функции, которые выдают количество узлов в дереве и корень дерева.
```sh
node* get_root(tree * t)
{
    return t->root;
}

int get_count(tree * t)
{
    return t->count;
}
```

Все эти функции описывают работу, которую мы можем совершить, с деревом. Используя эти функции необходимо совершить следующие действия:
1) создать пустое дерево, считать 4 элемента ai, |ai| <= 2147483647 и занести их в дерево;
2) вывести дерево (используя функцию print_tree) и пустую строку;
3) считать 3 элемента ai, |ai| <= 2147483647 и занести их в дерево;
4) вывести дерево и пустую строку;
5) считать m1, |m1| <= 2147483647 и найти элемент с заданным значением в дереве;
вывести через пробел значение предка и потомков найденного элемента,
если нет значений предка или потомков вывести "_" вместо таких значений;
вывести "-", если элемент не найден; вывести пустую строку;
6) считать m2, |m2| <= 2147483647 и найти элемент с заданным значением в дереве;
вывести через пробел значение предка и потомков найденного элемента,
если нет значений предка или потомков вывести "_" вместо таких значений;
вывести "-", если элемент не найден; вывести пустую строку;
7) считать m3, |m3| <= 2147483647 и удалить из дерева элемент с заданным значением (если такой элемент есть);
8) вывести дерево и пустую строку;
9) выполнять левый поворот дерева относительно корня, пока это возможно;
10) вывести дерево и пустую строку;
11) выполнять правый поворот дерева относительно корня, пока это возможно;
12) вывести дерево и пустую строку;
13) вывести на экран количество элементов в дереве и пустую строку
14) очистить дерево
15) вывести дерево и пустую строку;
Действия были прописаны в функции Main:
```sh
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
};
```
### 2.3 Тестирование
Проверим программу по таблице 2.3.1.  

*Таблица 2.3 - Входные и выходные данные программы*
| Input | Output |
| ------ | ------ |
|2 1 3 2|2|
|| 1 3|
|| 0 _ _ 4|
||_ _ _ _ _ _ _ 5|
|3| 2 _ 4|
|6|-|
|2|3|
||1 4|
||0 _ _ 5|
||5|
||4 _|
||3 _ _ _|
||1 _ _ _ _ _ _ _|
||0 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|
||0|
||_ 1|
||_ _ _ 3|
||_ _ _ _ _ _ _ 4|
||_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 5|
||5|
||-|

В колонке Input указаны входные данные, а колонке Output выходные данные. Эта таблица была дана в методических указаниях.
Компиляция, работа программы представлена на рисунке 2.3.1.

![Screenshot from 2021-05-31 20-50-50.png](https://www.dropbox.com/s/r53g7byo83l2rqe/Screenshot%20from%202021-05-31%2020-50-50.png?dl=0&raw=1)

*Рисунок 2.3.1 - Проверка работы программы*

Сравнивая работу программы на рисунке 2.3.1 с таблицей 2.3 видно, что программа работает правильно. Все выходные данные верны. Все функции отрабатывают правильно.

Написанная программа была выделена в git командой в терминале:
```sh
$ git add 01_bst.c
```
Программа загружена в gitlab командой ```git commit -m ""```, ``` git push```.
Pipeline был успешно пройден c двадцать шестого раза.

## 3 Заключение
Вывод: в ходе практической работы была написана программа на языке программирования С, реализующая  бинарное дерево поиска и работу с ним. Были получены навыки написания программ на языке С.

