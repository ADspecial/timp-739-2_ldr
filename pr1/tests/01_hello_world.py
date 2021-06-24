import os

actual = os.popen('./a.out').read().strip()
expected = 'Hello, World!'
assert actual == expected, "'{}' != {}".format(actual, expected)
