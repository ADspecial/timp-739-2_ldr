#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	double value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
} node;

typedef struct list {
	struct node *head;  // начало списка
} list;

node* getLast(node *head) // Получение последнего элемента списка
{
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}
// инициализация пустого списка
void init(list *l)
{
    l->head = NULL;
}
// удалить все элементы из списка
void clean(list *l)
{
    node *last = getLast(l->head);
    struct node* tmp;
    struct node* prev;
    tmp = l->head;
    while (tmp != last)
    {
        prev = tmp;
        tmp = tmp->next;
        free(prev);
    }
    free(last);
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
    node *last = getLast(l->head);
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
// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int val)
{
    struct node* new_node;
    new_node = (struct node*)malloc(sizeof(struct node));
    new_node->value = val;
    new_node->next = NULL;
    if (l->head == NULL)
    {
        l->head = new_node;
    }
    else
    {
        node *last = getLast(l->head);
        last->next = new_node;
    }
    return 0;
}
// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int val)
{
    struct node* new_node;
    new_node = (struct node*)malloc(sizeof(struct node));
    new_node->value = val;
    if (l->head == NULL)
    {
        l->head = new_node;
    }
    else 
    {
        struct node* tmp;
        tmp = l->head;
        new_node->next = tmp;
        l->head = new_node;
    }
    return 0;
}
// поиск элемента по номеру
struct node* find_n(struct list* l, int n) 
{
		node *last = getLast(l->head);
		int i;
		struct node* tmp;
		tmp = l->head;
		for (i = 1; i < n; i++)
		{   
			if (tmp == last) return NULL;
			tmp = tmp->next;
		}
		return tmp;
}
// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node *n, int val)
{
	if (n != NULL)
	{
		struct node* new_node;
		new_node = (struct node*)malloc(sizeof(struct node));
		new_node->value = val;
		new_node->next = n->next;
		n->next = new_node;
    return 0;
    }
    return 1;
}
// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_node(list *l, int val)
{
	if(is_empty(l) == false)
    {
    node *last = getLast(l->head);
    struct node* tmp;
    struct node* prev;
    tmp = l->head;
    while (tmp->value != val)
    {
		if (tmp == last) return 1;
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == l->head) l->head = tmp->next;
    else if (tmp == last)
    {
        prev->next = NULL;
        last = prev;
    }
    else prev->next = tmp->next;
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
        tmp = l->head;
        while (tmp) 
        {
            printf("%0.lf ", tmp->value);
            tmp = tmp->next;
        }
        printf("\n");
    }
}
int main() 
{
    int i, n;
    double k1, k2, k3, j, x;
    struct list spisok;
    init(&spisok);
    scanf("%d", &n);
    for(i=1; i<=n; i++) // Заполнение списка значениями
    {
        scanf("%lf", &x);
        push_back(&spisok, x);
    }
    print(&spisok);
    scanf("%lf %lf %lf", &k1, &k2, &k3); // Поиск элементов списка
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
    print(&spisok);
    scanf("%lf", &x); // Добавление в начало списка
    push_front(&spisok, x);
    print(&spisok);
    scanf("%lf %lf", &j, &x); // вставка элемента после указанного элемента
    b = find_n(&spisok, j);
    insert_after(b, x);
    print(&spisok);
    scanf("%lf", &x); // Удаление указанного элемента
    remove_node(&spisok, x);
    print(&spisok);
    clean(&spisok);// Очистка списка
	return 0;
};
