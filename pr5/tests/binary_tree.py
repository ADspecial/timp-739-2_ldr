class Node:
    def __init__(self, value, parent=None, left=None, right=None):
        self.value = value
        self.parent = parent
        self.left = left
        self.right = right

    def search(self, value):
        if self.value == value:
            return self

        if self.left and value < self.value:
            return self.left.search(value)

        if self.right and value > self.value:
            return self.right.search(value)

        return None

    def min_left(self):
        if self.left:
            return self.left.min_left()
        
        return self
    

    def add(self, value):
        if value > self.value:
            if not self.right is None:
                self.right.add(value)
            else:
                self.right = Node(value, parent=self)

        elif value < self.value:
            if not self.left is None:
                self.left.add(value)
            else:
                self.left = Node(value, parent=self)

    def print_node(self):
        parent = self.parent.value if self.parent else '_'
        left = self.left.value if self.left else '_'
        right = self.right.value if self.right else '_'
        return f'{parent} {left} {right}'

    def __str__(self):
        return f'Node({self.value})'


class Tree:
    def __init__(self, head=None):
        self.head = head
        self.list_of_nodes = dict()

    def right_rotate(self):
        if self.head is None:
            return

        if self.head.left is None:
            return

        p = self.head
        l = p.left
        p.left = l.parent = None

        p.left = l.right
        l.right = p

        self.head = l
        self.right_rotate()

    def left_rotate(self):
        if self.head is None:
            return
            
        if self.head.right is None:
            return

        p = self.head
        r = p.right
        p.right = r.parent = None

        p.right = r.left
        r.left = p

        self.head = r
        self.left_rotate()

    def add(self, values):
        for value in values:
            if self.head is None:
                self.head = Node(value)
                continue

            self.head.add(value)

    def to_list(self, node=None, index=None):
        if index is None:
            self.list_of_nodes = dict()
            self.to_list(self.head, 0)
            return

        if node is None:
            return

        self.list_of_nodes[index] = node
        self.to_list(node.left, 2*index+1)
        self.to_list(node.right, 2*index+2)

    def print_node(self, value):
        node = self.head.search(value)
        if node:
            return node.print_node()
        else:
            return '-'

    def print_tree(self):
        if not self.head:
            return '-'
        
        self.list_of_nodes = None
        self.to_list()
        l = 0
        range_l, range_r = 0, 1

        result_list = list()
        
        while any(n in self.list_of_nodes for n in range(range_l, range_r)):
            result_row = list()

            for n in range(range_l, range_r):
                if n in self.list_of_nodes:
                    result_row.append(f'{self.list_of_nodes[n].value}')
                else:
                    result_row.append('_')
                    
            result_list.append(' '.join(result_row))
            l += 1
            range_l = 2**l - 1
            range_r = 2**(l+1) - 1

        return '\n'.join(result_list)
