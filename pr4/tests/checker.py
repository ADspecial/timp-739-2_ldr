import os
import sys
import random


def task_func(args_str):
    expected_result = list()
    
    lines = args_str.strip().splitlines()
    array = lines[1].split()
    assert int(lines[0]) == len(array), "Something bad"
    expected_result.append(' '.join(array))

    k_elements = list(x for x in lines[2].split())
    assert len(k_elements) == 3, "Something bad"
    expected_result.append(' '.join('1' if k in array else '0' for k in k_elements))

    array.append(lines[3])
    expected_result.append(' '.join(array[::-1]))

    array.insert(0, lines[4])
    expected_result.append(' '.join(array))

    j, x = lines[5].split()
    array.insert(int(j), x)
    expected_result.append(' '.join(array[::-1]))

    u, y = lines[6].split()
    array.insert(int(u)-1, y)
    expected_result.append(' '.join(array))

    if lines[7] in array:
        array.remove(lines[7])
    expected_result.append(' '.join(array[::-1]))

    if lines[8] in array:
        array.reverse()
        array.remove(lines[8])
        array.reverse()
    expected_result.append(' '.join(array))

    return '\n'.join(expected_result)


def only_spaces(data):
    return ' '.join(data.split())


def main(level=0):
    if level==0:
        n = 10
    elif level==1:
        n = 1000
    else:
        n = 10000
        
    data = [str(n)]
    
    data.append(' '.join(str(random.randint(-n, n)) for _ in range(n)))
    k_arr = ' '.join(str(random.randint(-n, n)) for _ in range(3))
    data.append(k_arr)
    for _ in range(2):
        data.append(str(random.randint(-n, n)))

    if level==2:
        j = random.choice([1, n+2])
        u = random.choice([1, n+2])
    else:
        j = random.randint(2, n-2)
        u = random.randint(2, n-2)
        
    data.append('{} {}'.format(
        j, random.randint(-n, n)
    ))

    data.append('{} {}'.format(
        u, random.randint(-n, n)
    ))

    data.append(str(random.randint(-n, n)))
    
    data.append(str(random.randint(-n, n)))

    data_all = '\n'.join(data)

    cmd = 'echo "{}" | ./a.out'.format(data_all)
    actual = only_spaces(os.popen(cmd).read().strip())
    expected = only_spaces(task_func(data_all))

    assert actual == expected, ('This is not equal:\n'
                                'output:{}\n'
                                'expected:{}'.format(
                                    actual, expected))


level = int(sys.argv[1])


for _ in range(10):
    main(level)
