import re
import os
import sys
import random

from check_modules import *


N = 10

ABS_MAX = 2147483647


def remove_dublicates(lst):
    n_lst = list()
    for x in lst:
        if x not in n_lst:
            n_lst.append(x)
    return n_lst


def main(level, fatality=False):
    if level == 0:
        # Числа разные, ищем и удаляем случайные сущ числа
        array = list(x for x in range(1, 8))
        random.shuffle(array)
        check_value_1 = random.choice(array)
        check_value_2 = random.choice(list(set(array) - {check_value_1}))
        value_for_delete = random.choice(array)
    elif level == 1:
        if fatality:
            neo = random.randint(-ABS_MAX, ABS_MAX)
            array = list(neo for _ in range(1, 6))
            is_in_array_3 = fatality % 2
        else:
            array = list(random.randint(-ABS_MAX, ABS_MAX) for _ in range(1, 6))
            is_in_array_3 = random.choice([True, False])
        doubled = random.choice(array)
        array.insert(random.randint(0, 7), doubled)
        array.insert(random.randint(0, 7), doubled)
        is_in_array_1 = random.choice([True, False])
        is_in_array_2 = random.choice([True, False])
        check_value_1 = random.choice(array) if is_in_array_1 else random.randint(-ABS_MAX, ABS_MAX)
        check_value_2 = random.choice(array) if is_in_array_2 else random.randint(-ABS_MAX, ABS_MAX)
        value_for_delete = random.choice(array) if is_in_array_3 else random.randint(-ABS_MAX, ABS_MAX)
    else:
        raise NotImplementedError

    args = '{} {} {} {} {} {} {} {} {} {}'.format(
        *array, check_value_1, check_value_2, value_for_delete)
    print('Проверяемые входные данные: {}'.format(args))

    cmd = 'echo "{}" | ./a.out'.format(args)
    output = os.popen(cmd).read().strip()
    print('Результат от программы:\n{}'.format(output))

    outputs = re.split(r'\n(?:\s*\n)+', output)
    n = len(outputs)
    assert n == 9, ('Ожидалось 9 результатов заданий от программы, '
                    'получили {}'.format(n))

    print('\nПроверка создания дерева')
    check_tree_by_array(outputs[0], array[:4])

    print('Проверка добавления элементов в дерево')
    check_tree_by_array(outputs[1], array)

    print('Первая проверка элемента в ноде')
    check_node_elements(outputs[2], array, check_value_1)
    
    print('Вторая проверка элемента в ноде')
    check_node_elements(outputs[3], array, check_value_2)

    array = remove_dublicates(array)

    print('Проверка удаления элемента в дереве')
    if value_for_delete in array:
        array.remove(value_for_delete)
    check_correct_delete_node(outputs[4], array)

    array = list(int(x) for x in outputs[4].split() if x.strip() not in ('-', '_'))

    print('Проверка левого поворота')
    check_with_left_rotate(outputs[5], array)

    print('Проверка правого поворота')
    check_with_right_rotate(outputs[6], array)

    print('Проверка количества')
    check_node_count(outputs[7], array)

    print('Проверка пустого дерева')
    check_empty_list(outputs[8])

    print('Ok!\n')


level = int(sys.argv[1])

for i in range(N):
    if i >= N-2 and level == 1:
        main(level, i)
        continue
    
    main(level)
    
