import os
import sys
import random


def bracket_balance(brackets):
    return int(brackets.startswith('(') and brackets.count('(') == brackets.count(')'))   


def mul(numbers):
    result = 1
    for x in numbers:
        result *= x
    return result


FUNC_MAPPING = {
    1: min,
    2: max,
    3: sum,
    4: lambda numbers: -sum(numbers),
    5: lambda numbers: sum(numbers)/len(numbers),
    6: lambda numbers: len(tuple(x for x in numbers if x>0)),
    7: lambda numbers: len(tuple(x for x in numbers if x<0)),
    8: lambda numbers: len(tuple(x for x in numbers if x<=0)),
    9: lambda numbers: len(tuple(x for x in numbers if x>=0)),
    10: lambda numbers: 1 if all(numbers[i]<=numbers[i+1] for i in range(len(numbers)-1)) else 0,
    11: lambda numbers: 1 if all(numbers[i]>=numbers[i+1] for i in range(len(numbers)-1)) else 0,
    12: bracket_balance,
    13: lambda numbers: sum(x**2 for x in numbers),
    14: lambda numbers: sum((i%2)*x**2 for i, x in enumerate(numbers, 1)),
    15: lambda numbers: sum(((i+1)%2)*x**3 for i, x in enumerate(numbers, 1)),
    16: lambda numbers: sum((-1)**(i+1)*x**3 for i, x in enumerate(numbers, 1)),
    17: lambda numbers: sum(((-1)**i)*x**2 for i, x in enumerate(numbers, 1)),
    18: lambda numbers: sum(x-i for i, x in enumerate(numbers, 1)),
    19: lambda numbers: mul(numbers),
    20: lambda numbers: mul(x-i for i, x in enumerate(numbers, 1)),
}

task = int(sys.argv[-1])

for i in range(0, 5):
    for _ in range(10):
        if task == 10:
            lst = sorted(random.randint(-1000, 1000) for _ in range(10**i))
        elif task == 11:
            lst = sorted((random.randint(-1000, 1000) for _ in range(10**i)), reverse=True)
        elif task == 12:
            lst = ''.join(random.choice(['(', ')']) for _ in range(i+1))
        elif task in (19, 20):
            lst = list(random.randint(-10, 10) for _ in range(i))
        else:
            lst = list(random.randint(-1000, 1000) for _ in range(10**i))

        cmd = 'echo "{}\n{}\n" | ./a.out'.format(
            len(lst),
            ' '.join(str(x) for x in lst)
        )
        actual = os.popen(cmd).read().strip()
        expected = FUNC_MAPPING[task](lst)
        assert round(float(actual), 4) == round(expected, 4), "'{}' != '{}' (lst: {})".format(
            actual, expected, lst)
