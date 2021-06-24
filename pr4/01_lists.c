#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
	double value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
	struct node *prev;  // ссылка на предыдущий элемент списка
} node;

typedef struct list {
	struct node *head;  // начало списка
	struct node *tail;  // конец списка
} list;


// инициализация пустого списка
void init(list *l)
{
	l->head=NULL;
    l->tail=NULL;
}

// удалить все элементы из списка
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

// проверка на пустоту списка
bool is_empty(list *l)
{
	if (l == NULL) return true;
    else return false;
}

// поиск элемента по значению. вернуть NULL если элемент не найден
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
// поиск элемента по номеру
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

// вставка значения в конец списка, вернуть 0 если успешно
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

// вставка значения в начало списка, вернуть 0 если успешно
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

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(struct list*l, node *n, int val)
{
	if (n != NULL)
	{
		struct node* new_node;
		new_node=(struct node*)malloc(sizeof(struct node));
		new_node->value = val;
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

// вставка значения перед указанным узлом, вернуть 0 если успешно
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

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
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

// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
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

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
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

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
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
