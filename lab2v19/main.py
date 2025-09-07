from queue import queue
def main():
    # створення об'єкта черги
    object = queue()

    object -= None  # спроба видалення з порожньої черги
    
    # встановлення початкових елементів
    object.items = [1, 2, 3, 4, 5]
    print(object.items)

    # додавання елемента
    object += 6
    object = object + 7
    print(object.items)

    # видалення елемента
    object = object - None
    object -= None
    print(object.items)

    # доступ до елементів за індексом
    print(object[2])

    # зміна елемента за індексом
    object[0] = 99
    print(object.items)


if __name__ == "__main__":
    main()
