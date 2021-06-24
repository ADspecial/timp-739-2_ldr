# Практическая работа №3
## 1 Введение 
Цель работы : Получение навыков реализации односвязного списка на языке С, выработка практических умений написания программ на языке С. 

Задание на практическую работу:
1) Прочитать про односвязные списки на СИ
2) Написать программу 01_lists.c
3) Настроить pipeline
4) Написать отчет по работе в разметке Markdown 
5) Залить на gitlab и убедиться, что pipeline проходит успешно
6) Защитить работу у преподавателя

## 2 Ход работы
### 2.1 Настойка pipeline
Настройка pipeline проходит в файле .gitlab_ci.yml. Было добавлено в пункт stages: pr2.
```sh
stages:
  - pr1
  - pr2
  - pr3
```
Раскомментированы настройки для третьей практической работы.
```sh
pr3_easy_test:
  stage: pr3
  only:
    changes:
      - pr3/*.c
  script:
  - gcc pr3/01_*.c
  - python3 pr3/tests/checker.py 0

pr3_middle_test:
  stage: pr3
  only:
    changes:
      - pr3/*.c
  script:
  - gcc pr3/01_*.c
  - python3 pr3/tests/checker.py 1
  allow_failure: true

pr3_hard_test:
  stage: pr3
  only:
    changes:
      - pr3/*.c
  script:
  - gcc pr3/01_*.c
  - python3 pr3/tests/checker.py 2
  allow_failure: true
```

### 2.2 Программа 
Написана программа, реализующая односвязный список. Ниже представлен код структуры списка. В структуре list объявляется ссылка на начальный узел (head), а в структуре node описывается узел списка.
```sh
typedef struct node {
	double value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
} node;

typedef struct list {
	struct node *head;  // начало списка
} list;
}
```
Были реализованы следующие функции - init (инициализация пустого списка). Происходит инициализация пустого списка.
```sh
void init(list *l)
{
    l->head = NULL;
}
```
Функция clean, которая удаляет все элементы из списка. Функция free освобождает место в памяти. 
```sh
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
```
Функция push_back (вставка значения в конец списка). Функция malloc выделят память под новый блок.
```sh
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
```
Функция push_front (вставка значения в начало списка).
```sh
nt push_front(list *l, int val)
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
```
Функция insert_after, которая реализует вставку значения после указанного узла. Но для правильной работы этой функции необходимо было написать вспомагательную функцию find_n (поиск элемента по номеру).
```sh
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
nt insert_after(node *n, int val)
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
```
Функция remove_node, которая удаляют первый элемент с указанным значением.
```sh
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
```
Функция print, которая будет выводить в консоль все значения списка через пробел.
```sh
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
```
И была сделана дополнительная функция getLast для поиска последнего элемента в списке, чтобы упростить реализацию остальных функций.
```sh
node* getLast(node *head) 
{
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}
```
Все эти функции описывают работу, которую мы можем совершить, со спиком. Используя эти функции необходимо совершить следующие действия со списком:
1) считать количество элементов n, 0 < n <= 2147483647;
2) создать пустой список, считать n элементов a, |a| <= 2147483647 и занести их в список;
3) вывести содержимое списка, используя функцию print;
4) считать k1, k2, k3 (|k| <= 2147483647) и вывести "1", если в списке существует элемент с таким значением и "0", если нет (вывести через пробел, например "1 0 1");
5) считать m, |m| <= 2147483647 и вставить его в конец списка;
6) вывести содержимое списка, используя функцию print;
7) считать t, |t| <= 2147483647 и вставить его в начало списка;
8) вывести содержимое списка, используя функцию print;
9) считать j и x (0 < j <= 2147483647, |x| <= 2147483647) и вставлять значение x после j-ого элемента списка;
10) вывести содержимое списка, используя функцию print;
11) считать z, |z| <= 2147483647 и удалить первый элемент (при его наличии), хранящий значение z из списка;
12) вывести содержимое списка, используя функцию print;
13) очистиь список.
Весь этот порядок действий прописан в функции main.
```sh
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
```
### 2.3 Тестирование
Проверим программу по таблице 2.3.  

*Таблица 2.3 - Входные и выходные данные программы*
| Input | Output |
| ------ | ------ |
|5||
|1 2 3 2 4| 1 2 3 2 4|
|2 5 1| 1 0 1|
| 5 | 1 2 3 2 4 5|
|7| 7 1 2 3 2 4 5|
| 3 0 | 7 1 2 0 3 2 4 5|
|2| 7 1 0 3 2 4 5|

В колонке Input указаны входные данные, а колонке Output выходные данные. Эта таблица была дана в методических указаниях.
Компиляция, работа программы представлена на рисунке 2.3.1.
![Screenshot from 2021-04-26 09-29-40.png](https://www.dropbox.com/s/lhh4cfa1tejox23/Screenshot%20from%202021-04-26%2009-29-40.png?dl=0&raw=1)

*Рисунок 2.3.1 - Проверка работы программы*

Сравнивая работу программы на рисунке 2.3.1 с таблицей 2.3 видно, что программа работает правильно. Все выходные данные верны. Все функции отрабатывают правильно.

Написанная программа была выделена в git командой в терминале:
```sh
$ git add 01_lists.c
```
Программа загружена в gitlab командой ```git commit -m ""```, ``` git push```.
Pipeline был успешно пройден шестнадцатого раза.

## 3 Заключение
Вывод: в ходе практической работы была написана программа на языке программирования С, реализующая  односвязный список и работу с ним. Были получены навыки написания программ на языке С.

