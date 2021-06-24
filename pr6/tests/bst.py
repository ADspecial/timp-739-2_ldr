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

    def __str__(self):
        return f'Node({self.value})'


class Tree:
    def __init__(self, head=None):
        self.head = head
        self.list_of_nodes = dict()

    def add(self, values):
        for value in values:
            if self.head is None:
                self.head = Node(value)
                continue

            self.head.add(value)
