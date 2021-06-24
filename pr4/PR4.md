# Практическая работа №4
## 1 Введение 
Цель работы : Получение навыков реализации двусвязного списка на языке С, выработка практических умений написания программ на языке С. 

Задание на практическую работу:
1) Прочитать про двусвязные списки на СИ
2) Написать программу 01_lists.c
3) Настроить pipeline
4) Написать отчет по работе в разметке Markdown 
5) Залить на gitlab и убедиться, что pipeline проходит успешно
6) Защитить работу у преподавателя
## 2 Ход работы
### 2.1 Настойка pipeline
Настройка pipeline проходит в файле .gitlab_ci.yml. Было добавлено в пункт stages: pr4.
```sh
stages:
  - pr1
  - pr2
  - pr3
  - pr4
```
Раскомментированы настройки для четвертой практической работы.
```sh
pr4_easy_test:
  stage: pr4
  only:
    changes:
      - pr4/*.c
  script:
  - gcc pr4/01_*.c
  - python3 pr4/tests/checker.py 0
  
pr4_middle_test:
  stage: pr4
  only:
    changes:
      - pr4/*.c
  script:
  - gcc pr4/01_*.c
  - python3 pr4/tests/checker.py 1
  allow_failure: true
  
pr4_hard_test:
  stage: pr4
  only:
    changes:
      - pr4/*.c
  script:
  - gcc pr4/01_*.c
  - python3 pr4/tests/checker.py 2
  allow_failure: true
  ```
  
### 2.2 Программа 
Написана программа, реализующая двусвязный список. Ниже представлен код структуры списка. В структуре list объявляется ссылка на начальный узел (head) и на конечный узел (tail), а в структуре node описывается узел списка. В двусвязном списке есть ссылка на следующий элемент списка и на предыдущий, то есть обходить список можно в обе стороны.
```sh
typedef struct node {
	double value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
	struct node *prev;  // ссылка на предыдущий элемент списка
} node;

typedef struct list {
	struct node *head;  // начало списка
	struct node *tail;  // конец списка
} list;
```
Были реализованы следующие функции - init (инициализация пустого списка). Происходит инициализация пустого списка.
```sh
void init(list *l)
{
	l->head=NULL;
    l->tail=NULL;
}
```
Функция clean, которая удаляет все элементы из списка. Функция free освобождает место в памяти. 
```sh
void clean(list *l)
{
	struct node* tmp;
    struct node* prev;
    tmp=l->head;
    while (tmp->next!=NULL)
    {
        prev=tmp;
        tmp=tmp->next;
        free(prev);
    }
    free(tmp);
    init(l);
}
```
Функция bool_is_empty (проверка на пустоту списка).
```sh
bool is_empty(list *l)
{
	if (l == NULL) return true;
    else return false;
}
```
Функция find, которая ищет элемент списка по значению.
```sh
node *find(list *l, int val)
{
	node *last = l->tail;
    struct node* tmp;
    tmp = l->head;
    while (tmp != last)
    {
        if (tmp->value == val) return tmp;
        tmp = tmp->next;
    }
    if (last->value == val) return last;
    return NULL;
}
```
Функция push_back (вставка значения в конец списка). Функция malloc выделят память под новый блок.
```sh
int push_back(list *l, int val)
{
	struct node* new_node;
    new_node = (struct node*)malloc(sizeof(struct node));
    new_node->value = val;
    new_node->next = NULL;
    if (l->head==NULL)
    {
        new_node->prev = NULL;
        l->head=new_node;
    }
    else if (l->head->next==NULL)
    {
        new_node->prev = l->head;
        l->head->next = new_node;
    }
	else
	{
		new_node->prev = l->tail;
		l->tail->next = new_node;
	}
    l->tail=new_node;
    return 0;
}
```
Функция push_front (вставка значения в начало списка).
```sh
int push_front(list *l, int val)
{
	struct node* new_node;
    new_node=(struct node*)malloc(sizeof(struct node));
    new_node->value = val;
    new_node->prev = NULL;
    if (l->head==NULL)
    {
        new_node->next = NULL;
        l->tail=new_node;
    }
    else if (l->head->next==NULL)
    {
        new_node->next = l->tail;
        l->tail->prev = new_node;
    }
    else
    {
		 new_node->next = l->head;
         l->head->prev = new_node;
    }
    l->head=new_node;
    return 0;
}
```
Функция insert_after, которая реализует вставку значения после указанного узла. Но для правильной работы этой функции необходимо было написать вспомагательную функцию find_n (поиск элемента по номеру).
```sh
struct node* find_n(struct list* l, int n) 
{
	int i;
	struct node* tmp;
	tmp = l->head;
	for (i = 1; i < n; i++)
	{   
	    tmp = tmp->next;
	}
	return tmp;
}
int insert_after(struct list*l, node *n, int val)
{
	if (n != NULL)
	{
	    struct node* new_node;
	    new_node=(struct node*)malloc(sizeof(struct node));
		ew_node->value = val;
		if (n->next == NULL)
		{
			push_back(l, val);
			return 0;
		}
		new_node->next = n->next;
		new_node->prev = n;
		n->next->prev = new_node;
		n->next = new_node;
		return 0;
    }
    return 1;
}
```
Функция insert_before, которая реализует вставку значения пепед указанным узлом. Также используется дополнительная функция find_n (поиск элемента по номеру).
```sh
int insert_before(struct list*l, node *n, int val)
{
	if (n != NULL)
	{
		struct node* new_node;
		new_node=(struct node*)malloc(sizeof(struct node));
		new_node->value = val;
		if (n->prev == NULL)
		{
			push_front(l, val);
			return 0;
		}
		new_node->prev = n->prev;
		new_node->next = n;
		n->prev->next = new_node;
		n->prev = new_node;
		return 0;
    }
    return 1;
}
```
Функция remove_first, которая удаляет первый элемент с указанным значением.
```sh
int remove_first(list *l, int val)
{
	if(is_empty(l) == false)
    {
    struct node* tmp;
    tmp=l->head;
    while(tmp->value!=val)
    { 
		if (tmp == l->tail) return 1;
		tmp=tmp->next;
	}
    if (tmp==l->head)
    {
		
        tmp->next->prev = NULL;
        l->head = tmp->next;
    }
    else if (tmp==l->tail)
    {
        tmp->prev->next = NULL;
        l->tail = tmp->prev;
    } else
    {
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }
    free(tmp);
    return 0;
    }
    else return 1;
}
```
Функция remove_last, которая удаляет последний элемент с указанным значением.
```sh
int remove_last(list *l, int val)
{
	if(is_empty(l) == false)
    {
	struct node* tmp;
    tmp=l->tail;
    while(tmp->value!=val)
    {
		 if (tmp == l->head) return 1;
		 tmp=tmp->prev;
	}
    if (tmp==l->head)
    {
        tmp->next->prev = NULL;
        l->head = tmp->next;
    }
    else if (tmp==l->tail)
    {
        tmp->prev->next = NULL;
        l->tail = tmp->prev;
    } else
    {
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }
    free(tmp);
    return 0;
    }
    else return 1;
}
```
Функция print, которая будет выводить в консоль все значения списка через пробел.
```sh
void print(list *l)
{
	 if(is_empty(l) == false)
    {
     struct node* tmp;
	tmp=l->head;
    while (tmp->next!=NULL)
    {
        printf("%.0lf ", tmp->value);
        tmp = tmp->next;
    }
    printf("%.0lf\n", l->tail->value);
    }
}
```
Функция print_invers, которая будет выводить в консоль все значения списка в обратном порядке через пробел.
```sh
void print_invers(list *l)
{
	if (is_empty(l)== false)
  {
     struct node* tmp;
    tmp=l->tail;
    while (tmp->prev!=NULL)
    {
        printf("%.0lf ", tmp->value);
        tmp = tmp->prev;
    }
    printf("%.0lf\n", l->head->value);
  }
}
```
Все эти функции описывают работу, которую мы можем совершить, со спиком. Используя эти функции необходимо совершить следующие действия со списком:
1) считать количество элементов n, 0 < n <= 2147483647;
2) создать пустой список, считать n элементов a, |a| <= 2147483647 и занести их в список;
3) вывести содержимое списка, используя функцию print;
4) считать k1, k2, k3 (|k| <= 2147483647) и вывести "1", если в списке существует элемент с таким значением и "0", если нет (вывести через пробел, например "1 0 1");
5) считать m, |m| <= 2147483647 и вставить его в конец списка;
6) вывести содержимое списка, используя функцию print_invers;
7) считать t, |t| <= 2147483647 и вставить его в начало списка;
8) вывести содержимое списка, используя функцию print;
9) считать j и x (0 < j <= 2147483647, |x| <= 2147483647) и вставлять значение x после j-ого элемента списка;
10) вывести содержимое списка, используя функцию print_invers;
11) считать u и y (0 < u <= 2147483647, |y| <= 2147483647) и вставлять значение y перед u-ым элементом списка;
12) вывести содержимое списка, используя функцию print;
13) считать z, |z| <= 2147483647 и удалить первый элемент (при его наличии), хранящий значение z из списка;
14) вывести содержимое списка, используя функцию print_invers;
15) считать r, |r| <= 2147483647 и удалить последний элемент (при его наличии), хранящий значение r из списка;
16) вывести содержимое списка, используя функцию print;
17) очистиь список.
Весь этот порядок действий прописан в функции main.
```sh
int main() {
	int i, n;
    double k1, k2, k3, x, j;
    struct list spisok;
    init(&spisok);
    scanf("%d", &n);
    for(i=1; i<=n; i++) // Заполнение списка значениями
    {
        scanf("%lf", &x);
        push_back(&spisok, x);
    }
    print(&spisok);
    scanf("%lf %lf %lf", &k1, &k2, &k3); 
    struct node* b;
    b = find(&spisok, k1);
    if(b != NULL) k1 = 1;
		else k1 = 0;
    b = find(&spisok, k2);
    if(b != NULL) k2 = 1;
		else k2 = 0;
    b = find(&spisok, k3);
    if(b != NULL) k3 = 1;
		else k3 = 0;
    printf("%.0lf %.0lf %.0lf\n", k1, k2, k3);
    scanf("%lf", &x); // Добавление в конец списка 
    push_back(&spisok, x);
    print_invers(&spisok);
    scanf("%lf", &x); // Добавление в начало списка
    push_front(&spisok, x);
    print(&spisok);
    scanf("%lf %lf", &j, &x); // вставка элемента после указанного элемента
    b = find_n(&spisok, j);
    insert_after(&spisok, b, x);
    print_invers(&spisok);
    scanf("%lf %lf", &j, &x); // вставка элемента перед указанного элемента
    b = find_n(&spisok, j);
    insert_before(&spisok, b, x);
    print(&spisok);
    scanf("%lf", &x); // Удаление первого указанного элемента
    remove_first(&spisok, x);
    print_invers(&spisok);
    scanf("%lf", &x); // Удаление последнего указаннаго элемента
    remove_last(&spisok, x);
    print(&spisok);
    clean(&spisok);// Очистка списка
	return 0;
};
```
### 2.3 Тестирование
Проверим программу по таблице 2.3.1.  

*Таблица 2.3 - Входные и выходные данные программы*
| Input | Output |
| ------ | ------ |
|5||
|1 2 3 2 4| 1 2 3 2 4|
|2 5 1| 1 0 1|
|1|1 4 2 3 2 1 |
|7| 7 1 2 3 2 4 1|
|3 0|1 4 2 3 0 2 1 7|
|5 8|7 1 2 0 8 3 2 4 1|
|2|1 4 2 3 8 0 1 7|
|1|7 1 0 8 3 2 4|

В колонке Input указаны входные данные, а колонке Output выходные данные. Эта таблица была дана в методических указаниях.
Компиляция, работа программы представлена на рисунке 2.3.1.

![Screenshot from 2021-05-05 20-02-54.png](https://www.dropbox.com/s/26321sr5xclwml5/Screenshot%20from%202021-05-05%2020-02-54.png?dl=0&raw=1)

*Рисунок 2.3.1 - Проверка работы программы*

Сравнивая работу программы на рисунке 2.3.1 с таблицей 2.3 видно, что программа работает правильно. Все выходные данные верны. Все функции отрабатывают правильно.

Написанная программа была выделена в git командой в терминале:
```sh
$ git add 01_lists.c
```
Программа загружена в gitlab командой ```git commit -m ""```, ``` git push```.
Pipeline был успешно пройден c четвертого раза.

## 3 Заключение
Вывод: в ходе практической работы была написана программа на языке программирования С, реализующая  двусвязный список и работу с ним. Были получены навыки написания программ на языке С.



