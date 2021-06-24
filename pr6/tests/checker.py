import sys
import os
import random

from bst import Tree


def breadth_first_search(tree):
    array = list()
    nodes = [tree.head]

    while any(nodes):
        next_nodes = list()

        for node in nodes:
            if not node:
                next_nodes.append(None)
                next_nodes.append(None)
                continue

            array.append(node.value)

            next_nodes.append(node.left)
            next_nodes.append(node.right)

        nodes = next_nodes.copy()

    return array


def pre_order_search(tree, node=None):
    array = list()

    if not node:
        return pre_order_search(tree, tree.head)

    array.append(node.value)

    if node.left:
        array.extend(pre_order_search(tree, node.left))

    if node.right:
        array.extend(pre_order_search(tree, node.right))

    return array


def post_order_search(tree, node=None):
    array = list()

    if not node:
        return post_order_search(tree, tree.head)

    if node.left:
        array.extend(post_order_search(tree, node.left))

    if node.right:
        array.extend(post_order_search(tree, node.right))

    array.append(node.value)

    return array


def main():
    level = int(sys.argv[1])

    for _ in range(100):
        r_array = list(random.randint(-20, 20) for _ in range(7))
        r_in = ' '.join(map(str, r_array))
        user_out = os.popen('echo "{}" | ./a.out'.format(r_in)).read().strip()
        user_array = list(map(int, user_out.split()))
        print('{}\t->\t{}'.format(r_in, user_out))

        tree = Tree()
        tree.add(r_array)

        if level == 0:
            expected_array = breadth_first_search(tree)
        elif level == 1:
            expected_array = pre_order_search(tree)
        elif level == 2:
            expected_array = post_order_search(tree)
        else:
            raise NotImplementedError

        assert user_array == expected_array, 'expected {}, got {}'.format(
            expected_array, user_array)


main()
