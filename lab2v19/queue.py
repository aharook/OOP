class queue:
    def __init__(self):
        self._items = []  # приватне поле (список)

    # get
    @property
    def items(self):
        return self._items.copy()

    # set
    @items.setter
    def items(self, new_items):
        self._items = list(new_items)

    # індексатор (читання)
    def __getitem__(self, index):
        return self._items[index]

    # індексатор (запис)
    def __setitem__(self, index, value):
        self._items[index] = value
    
    # оператор + 
    def __add__(self, other):
        new_queue = queue()
        new_queue.items = self._items.copy()
        new_queue._items.append(other)
        return new_queue
    
    # оператор +=
    def __iadd__(self, other):
        self._items.append(other)
        return self

    # оператор - 
    def __sub__(self, _):
        new_queue = queue()
        new_queue.items = self._items.copy()
        if new_queue._items:
            new_queue._items.pop(0)
        return new_queue
    
    # оператор -=
    def __isub__(self, _):
        if self._items:
            self._items.pop(0)
        return self
    
        # Друк черги
    def __str__(self):
        return f"Черга: {self._items}"

