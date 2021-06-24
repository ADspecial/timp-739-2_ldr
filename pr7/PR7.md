# Практическая работа №7
## 1 Введение 
Цель работы : Получение навыков реализации алгоритмов сортировки на языке С, выработка практических умений написания программ на языке С. 

Задание на практическую работу:
1) Прочитать про алгоритмы сортировки
2) Написать две программы реализующие быструю и пирамидальную сортировки
3) Настроить pipeline
4) Написать отчет по работе в разметке Markdown 
5) Залить на gitlab и убедиться, что pipeline проходит успешно
6) Защитить работу у преподавателя
## 2 Ход работы
### 2.1 Настойка pipeline
Настройка pipeline проходит в файле .gitlab_ci.yml. Было добавлено в пункт stages: pr7.
```sh
stages:
  - pr1
  - pr2
  - pr3
  - pr4
  - pr5
  - pr6
  - pr7
```
Раскомментированы настройки для четвертой практической работы.
```sh
pr7_general_test:
  stage: pr7
  only:
    changes:
      - pr7/*.c
  script:
  - gcc pr7/*.c
  - python3 pr7/tests/checker.py 0
pr7_quicksort_test:
  stage: pr7
  only:
    changes:
      - pr7/*.c
  script:
  - gcc pr7/*.c
  - python3 pr7/tests/checker.py 1
pr7_heapsort_test:
  stage: pr7
  only:
    changes:
      - pr7/*.c
  script:
  - gcc pr7/*.c
  - python3 pr7/tests/checker.py 2
  ```
  
### 2.2 Программа №1
 В первой программе была реализована быстрая сортировка. Изначально выбирается опорный элемент. Опорным элементом был взят серединный элемент массива. Далее разбиение - перераспределение элементов в массиве таким образом, что элементы меньше опорного помещаются перед ним, а больше или равные после. Затем рекурсивно применялись первые два шага к двум подмассивам слева и справа от опорного элемента. Это один из самых быстрых известных универсальных алгоритмов сортировки массивов (в среднем O(n log n) обменов при упорядочении n элементов). На рисунке 2.2.1 показан пример быстрой сортировки (опорным элементом взят последний элемент массива).

 ![200px-Quicksort-diagram.svg.png](https://www.dropbox.com/s/mh41yorhl1fvd7z/200px-Quicksort-diagram.svg.png?dl=0&raw=1)
  
  *Рисунок 2.2.1 - Быстрая сортировка*
  
  ![Quicksort-example.gif](https://www.dropbox.com/s/5ffa268ekt1i8hw/Quicksort-example.gif?dl=0&raw=1)
  
  *Рисунок 2.2.2 - Анимация работы быстрой сортировки*
  
 Ниже представлен код программы 01_qsort.c.
```sh
#include<stdio.h>
#include<malloc.h>
void quickSort(int *arr, int first, int last)
{
	/*for(int i = 0; i < last+1; i++)
    {
        printf("%d", arr[i]);
        if(i<last+1)
        printf(" ");
    }
    printf("\n");
    */
	int left = first, right = last, base;
    base = arr[(left + right)/2];
    do
    {
        while(arr[left] < base) left++;
        while(arr[right] > base) right--;
        if(left <= right)
        {
            int tmp = arr[left];
            arr[left] = arr[right];
            arr[right] = tmp;
            left++;
            right--;
        }
    } while(left <= right);
    if ( first < right )
        quickSort(arr, first, right);
    if ( last > left )
        quickSort(arr, left, last);

}
void print(int* arr, int arr_len)
{
	for(int i = 0; i < arr_len; i++)
    {
        printf("%d", arr[i]);
        if(i<arr_len)
        printf(" ");
    }
    printf("\n");
}
int main() {
    int arr_len;
    scanf("%d",&arr_len);
    int *arr = (int*)malloc(sizeof(int) * arr_len);
    for(int i = 0; i < arr_len; i++)
    {
        scanf("%d",&arr[i]);
    }
	quickSort(arr, 0,arr_len-1);
	print(arr, arr_len);
    free(arr);
    printf("\n");
}
 ```
 
 Проверим работу написанной программы. Компиляция, работа программы представлена на рисунке 2.2.2.
 
![Screenshot from 2021-06-02 02-06-59.png](https://www.dropbox.com/s/4t7qhislvos9m25/Screenshot%20from%202021-06-02%2002-06-59.png?dl=0&raw=1)
 
   *Рисунок 2.2.3 - Работа программы*
Вывод программы верный, входные данные были отсортированы по возрастанию.

Написанная программа была выделена в git командой в терминале:
```sh
$ git add 01_qsort.c
```
Программа загружена в gitlab командой ```git commit -m ""```, ``` git push```.
Pipeline был успешно пройден c третьего раза.

### 2.3 Программа №2
Во второй программе необходимо релизовать пирамидальную сортировку. Общая идея пирамидальной сортировки заключается в том, что сначала строится пирамида из элементов исходного массива, а затем осуществляется сортировка элементов. Выполнение алгоритма разбивается на два этапа.Построение пирамиды. Определяем правую часть дерева, начиная с n/2-1 (нижний уровень дерева). Берем элемент левее этой части массива и просеиваем его сквозь пирамиду по пути, где находятся меньшие его элементы, которые одновременно поднимаются вверх; из двух возможных путей выбираете путь через меньший элемент. Второй этап сортировка на построенной пирамиде. Берем последний элемент массива в качестве текущего. Меняем верхний (наименьший) элемент массива и текущий местами. Текущий элемент (он теперь верхний) просеиваем сквозь n-1 элементную пирамиду. Затем берем предпоследний элемент и т.д. На рисунке 2.3.1 представлена анимация пирамидальной сортировки.

  ![Sorting_heapsort_anim.gif](https://www.dropbox.com/s/lwxbmuvz87jf7i7/Sorting_heapsort_anim.gif?dl=0&raw=1)
   
*Рисунок 2.2.3 - Пирамидальная сортировка*

Код программы 02_psort.c представлен ниже.
```sh
#include <stdio.h>
#include <stdlib.h>

void sift(int *numbers, int root, int bottom)
{
  int maxChild, done = 0;
  while((root * 2 + 1 <= bottom) && (!done))
  {
    if(root * 2 + 2 <= bottom)
    {
        if(numbers[root * 2 + 2] > numbers[root * 2 + 1])
            maxChild = root * 2 + 2;
        else
            maxChild = root * 2 + 1;
    }
    else
        maxChild = root * 2 + 1;
    if(numbers[root] < numbers[maxChild])
    {
      int temp = numbers[root];
      numbers[root] = numbers[maxChild];
      numbers[maxChild] = temp;
      root = maxChild;
    }
    else
      done = 1;
  }
}

void psort(int *numbers, int array_size) 
{
  // Формируем нижний ряд пирамиды
  for (int i = (array_size / 2); i >= 0; i--)
    sift(numbers, i, array_size - 1);
  // Просеиваем через пирамиду остальные элементы
  for (int i = array_size - 1; i >= 1; i--)
  {
    int temp = numbers[0];
    numbers[0] = numbers[i];
    numbers[i] = temp;
    sift(numbers, 0, i - 1);
  }
}

int main()
{
    int arr_len;
    scanf("%d",&arr_len);
    int *arr = (int*)malloc(sizeof(int) * arr_len);
    for(int i = 0; i < arr_len; i++)
    {
        scanf("%d",&arr[i]);
    }
    psort(arr, arr_len);
    for(int i = 0; i < arr_len; i++)
    {
        printf("%d", arr[i]);
        if(i<arr_len-1)
        printf(" ");
    }
    free(arr);
    printf("\n");
}

```
 Проверим работу написанной программы. Компиляция, работа программы представлена на рисунке 2.3.2.
 
![Screenshot from 2021-06-02 02-52-35.png](https://www.dropbox.com/s/g8za36wp8rffz9u/Screenshot%20from%202021-06-02%2002-52-35.png?dl=0&raw=1)
 
   *Рисунок 2.3.2 - Работа программы*

Вывод программы верный, входные данные были отсортированы по возрастанию.
Написанная программа была выделена в git командой в терминале:
```sh
$ git add 02_psort.c
```
Программа загружена в gitlab командой ```git commit -m ""```, ``` git push```.
Pipeline был успешно пройден cо второго раза.


## 3 Заключение
Вывод: в ходе практической работы были написаны программы на языке программирования С, реализующие пирамидальную и быструю сортировки. Были получены навыки написания программ на языке С.
