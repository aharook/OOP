#include <iostream>

class Vehicle {
public:
    virtual void Refuel() {
        std::cout << "Refueling vehicle with fuel..." << std::endl;
    }
};

class Car : public Vehicle {
public:
    void Refuel() override {
        std::cout << "Refueling car with fuel..." << std::endl;
    }
};

class ElectricCar : public Vehicle {
public:
    void Refuel() override {
        std::cout << "ERROR: Electric car cannot be refueled with fuel!" << std::endl;
    }
};

void ServiceStation(Vehicle* vehicle) {
    vehicle->Refuel();
}

int main() {
    Car v;
    ElectricCar e;

    ServiceStation(&v); 
    ServiceStation(&e); 
}
