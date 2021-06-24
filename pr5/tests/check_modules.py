from binary_tree import Tree


def check_separeted_text(tree1, tree2):
    tree_lines_1 = tree1.strip().splitlines()
    tree_lines_2 = tree2.strip().splitlines()
    
    if len(tree_lines_1) != len(tree_lines_2):
        return False

    for line1, line2 in zip(tree_lines_1, tree_lines_2):
        elems1 = line1.strip().split()
        elems2 = line2.strip().split()
        if elems1 != elems2:
            return False

    return True
    

def check_tree_by_array(output, tree_array):
    tree = Tree()
    tree.add(tree_array)
    tree_str = tree.print_tree()
    is_correct = check_separeted_text(output, tree_str)

    assert is_correct, '\nОжидал дерево:\n{}\nПолучил:\n{}\n'.format(tree_str, output)


def check_node_elements(output, tree_array, value):
    tree = Tree()
    tree.add(tree_array)
    node_str = tree.print_node(value)
    is_correct = check_separeted_text(output, node_str)
    
    assert is_correct, '\nОжидал: {}\nПолучил: {}\n'.format(node_str, output)


def check_correct_delete_node(output, tree_array):
    nodes_from_output = list(int(x) for x in output.split() if x not in ('-', '_'))
    
    assert set(nodes_from_output) == set(tree_array), (
        'Набор элементов не совпадает.\nИз дерева: {}\nДолжны быть: {}\n'
        ''.format(sorted(nodes_from_output), sorted(tree_array)))

    check_tree_by_array(output, nodes_from_output)


def check_with_left_rotate(output, tree_array):
    tree = Tree()
    tree.add(tree_array)
    tree.left_rotate()
    tree_str = tree.print_tree()
    
    is_correct = check_separeted_text(output, tree_str)

    assert is_correct, '\nОжидал дерево:\n{}\nПолучил:\n{}\n'.format(tree_str, output)
  

def check_with_right_rotate(output, tree_array):
    tree = Tree()
    tree.add(tree_array)
    tree.left_rotate()
    tree.right_rotate()
    tree_str = tree.print_tree()
    
    is_correct = check_separeted_text(output, tree_str)

    assert is_correct, '\nОжидал дерево:\n{}\nПолучил:\n{}\n'.format(tree_str, output)



def check_node_count(output, tree_array):
    assert output.strip() == str(len(tree_array)), (
        'Неверное количество ({}!={})'.format(output.strip(), str(len(tree_array))))


def check_empty_list(output):
    assert output.strip() == '-', 'Должен быть "-"'
