from vehicle import *

bus = Bus(12, 100)  # літрів на 100 км, км
print(f"витрати транспорту на {bus.get_distance} km: {bus.fuel_consumption_calc()} liters")

print(bus.info())
  # виклик деструктора
del bus

truck = Truck(20, 150)  # літрів на 100 км, км
print(f"витрати транспорту на {truck.get_distance} km: {truck.fuel_consumption_calc()} liters")
  # виклик деструктора
del truck

transport = [ Bus(30, 140), Truck(50, 130)]

for v in transport: #демонстрація поліморфізму
    print(f"витрати транспорту на {v.get_distance} km: {v.fuel_consumption_calc()} liters")
    del v