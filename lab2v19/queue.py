class queue:
    def __init__(self):
        self.__items = []  # приватне поле (список)

    # get
    @property
    def items(self):
        return self.__items.copy()

    # set
    @items.setter
    def items(self, new_items):
        self.__items = list(new_items)

    # індексатор (читання)
    def __getitem__(self, index):
        return self.__items[index]

    # індексатор (запис)
    def __setitem__(self, index, value):
        self.__items[index] = value
    
    # оператор + 
    def __add__(self, other):
        new_queue = queue()
        new_queue.items = self.__items.copy()
        new_queue.__items.append(other)
        return new_queue
    
    # оператор +=
    def __iadd__(self, other):
        self.__items.append(other)
        return self

    # оператор - 
    def __sub__(self, _):
        new_queue = queue()
        new_queue.items = self.__items.copy()
        if new_queue.__items:
            new_queue.__items.pop(0)
        return new_queue
    
    # оператор -=
    def __isub__(self, _):
        if self.__items:
            self.__items.pop(0)
        return self
    
        # Друк черги
    def __str__(self):
        return f"Черга: {self.__items}"

