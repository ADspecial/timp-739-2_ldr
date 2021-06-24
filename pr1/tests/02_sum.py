import os
import random

LIMIT_NUMBER = 2147483647

NUMBERS = (
	(random.randint(0, LIMIT_NUMBER), random.randint(0, LIMIT_NUMBER)),
	(random.randint(-LIMIT_NUMBER, 0), random.randint(0, LIMIT_NUMBER)),
	(random.randint(-LIMIT_NUMBER, 0), random.randint(-LIMIT_NUMBER, 0)),
	(random.uniform(0, LIMIT_NUMBER), random.uniform(-LIMIT_NUMBER, 0)),
	(LIMIT_NUMBER, LIMIT_NUMBER),
	(-LIMIT_NUMBER, LIMIT_NUMBER),
	(-LIMIT_NUMBER, -LIMIT_NUMBER),
	
)

for a, b in NUMBERS:
	cmd = 'echo "{} {}\n" | ./a.out'.format(a, b)
	actual = os.popen(cmd).read().strip()
	expected = a + b
	assert round(float(actual), 4) == round(expected, 4), "'{}' != {}".format(actual, expected)
