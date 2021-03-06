# Практическая работа №1
## 1 Введение 
Цель работы : Знакомство с работой программы управления версий - git, выработка практических умений написания программ на языке С.

Задание на практическую работу:
1) Установить ubuntu, gcc, splint, git
2) Fork текущего репозитория
3) Клонировать репозиторий к себе на компьютер
4) Написать программы
5) Убедиться, что программы отрабатывают корректно
6) Отрефакторить программы по splint
7) Написать отчет по работе в разметке Markdown 
8) Залить на gitlab и убедиться, что pipeline проходит успешно
9) Защитить работу у преподавателя

## 2 Ход работы
### 2.1 Установка программ 
Была установлена операционная система Ubuntu на виртуальную машину, вся работа выполнялась в этой системе. Через терминал установлен компилятор gcc, git и splint. На рисунке 2.1 показана проверка установки программ.

![lin1.png](https://www.dropbox.com/s/6ya5jrci8bi5nbb/lin1.png?dl=0&raw=1)  
*Рисунок 2.1 - Проверка установки программ*

Репозеторий форкнут и скопирован на локальное хранилище командой: 
```sh
$ git clone https://gitlab.com/lekontsev.danil/practices
```

### 2.2 Программа №1
Написана программа, печатающая в консоль фразу "Hello, World!" на отдельной строке. Код программы представлен ниже:
```sh
#include <stdio.h>
int main()
{
    printf("Hello, World!");
    return 0;
}
```
Компиляция,работа и проверка программы splint представлена на рисунке 2.2.

![Screenshot from 2021-03-19 08-31-35.png](https://www.dropbox.com/s/dnzbnplynyenq2l/Screenshot%20from%202021-03-19%2008-31-35.png?dl=0&raw=1)  
*Рисунок 2.2 - Проверка рпботы программы №1*

Видно что программа проверилась без ошибок.
Написанная программа была выделена в git командой в терминале:
```sh
$ git add 01_hello.c
```
И загружена в gitlab командой ``` git push```.
Также программа успешно прошла pipeline.

### 2.3 Программа №2
Написана программа, принимающая на вход два числа разделённые пробелом, и суммирующую их. Ввод чисел производится через консоль, вывод результата также выводится в консоль. Вводимые числа не превосходят по модулю 2147483647. Код программы представлен ниже:
```sh
#include <stdio.h>
int main()
{
    double a,b;
    (void) scanf("%lf%lf", &a,&b);
    printf("%lf",a+b);
    return 0;
}
```
Был использован тип данных double, кторый в памяти занимает 8 байт. Double является типом с плавающей точкой. Именно с этим типом данных программа проходит pipeline в gitlab. Перед scanf стоит преобразование типа (void), чтобы корректно проходил тест splint.
Компиляция,работа и проверка программы splint представлена ниже на рисунке 2.3.

![Screenshot from 2021-03-19 08-42-23.png](https://www.dropbox.com/s/n2llr3cquel2oco/Screenshot%20from%202021-03-19%2008-42-23.png?dl=0&raw=1)  
*Рисунок 2.3 - Проверка работы программы №2*

Видно что программа проверилась без ошибок.
Написанная программа была выделена в git командой в терминале:
```sh
$ git add 02_sum.c
```
И загружена в gitlab командой ``` git push```.
Также программа успешно прошла pipeline.

### 2.4 Программа №3
Написана программа, принимающая на вход два числа x и y разделённые
пробелом, и вычисляющую x в степени y. . Ввод чисел производится через
консоль, вывод результата также выводится в консоль. Вводимые числа не
превосходят по модулю 2147483647. Код программы представлен ниже:
```sh
#include <stdio.h>
#include <math.h>
int main()
{
    double a,b;
    (void) scanf("%lf%lf", &a,&b);
    printf("%lf", pow(a,b));
    return 0;
}
```
В этой программе так же был использован тип double и преобразование типа перед scanf. Для работы команды pow был подключен заголовочный файл <math.h>.
Компиляция,работа и проверка программы splint представлена на рисунке 2.4.

![Screenshot from 2021-03-19 08-52-43.png](https://www.dropbox.com/s/yqmonb3lb6jf0t7/Screenshot%20from%202021-03-19%2008-52-43.png?dl=0&raw=1)  
*Рисунок 2.4 - Проверка работы программы №3*

Видно что программа проверилась без ошибок.
Написанная программа была выделена в git командой в терминале:
```sh
$ git add 03_pow.c
```
И загружена в gitlab командой ``` git push```.
Также программа успешно прошла pipeline.

## 3 Заключение
Вывод: в ходе данной практической работы были написаны программы на языке программирования С, были получены навыки работы с git, splint, gitlab.
