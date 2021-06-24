import os
import random

LIMIT_NUMBER_A = 20
LIMIT_NUMBER_B = 10

NUMBERS = (
	(random.randint(0, LIMIT_NUMBER_A), random.randint(0, LIMIT_NUMBER_B)),
	(random.randint(-LIMIT_NUMBER_A, 0), random.randint(0, LIMIT_NUMBER_B)),
	(random.uniform(0, LIMIT_NUMBER_A), random.uniform(0, LIMIT_NUMBER_B)),
	(LIMIT_NUMBER_A, LIMIT_NUMBER_B),
	(-LIMIT_NUMBER_A, LIMIT_NUMBER_B),
	
)

for a, b in NUMBERS:
	cmd = 'echo "{} {}\n" | ./a.out'.format(a, b)
	actual = os.popen(cmd).read().strip()
	expected = a ** b
	assert round(float(actual), 4) == round(expected, 4), "'{}' != {}".format(actual, expected)
