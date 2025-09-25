import abc

class Vehicle(abc.ABC):
    def __init__(self, fuel_consumption, distance):
        self.fuel_consumption = fuel_consumption
        self.__distance = distance  # приватний атрибут

    # геттер для відстані
    @property
    def get_distance(self):
        return self.__distance
    
    # сеттер для відстані
    @get_distance.setter
    def set_distance(self, distance):
        self.__distance = distance

    @abc.abstractmethod
    def fuel_consumption_calc(self):
        pass

    def __del__(self):
        print(f'Destructor called, {self.__class__.__name__} deleted.')

# наслідувальні класи
class Bus(Vehicle):

    def __init__(self, fuel_consumption, distance): 
        super().__init__(fuel_consumption, distance) # конструктор заміна base

    def fuel_consumption_calc(self):
        return self.fuel_consumption * self.get_distance / 100

class Truck(Vehicle):
    def __init__(self, fuel_consumption, distance):
        super().__init__(fuel_consumption, distance) # конструктор заміна base

    def fuel_consumption_calc(self):
        return self.fuel_consumption * self.get_distance / 100





