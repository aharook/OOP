#include <iostream>

class IChargeable {
public:
    virtual void Charge() = 0;

};

class IRefuelable {
public:
    virtual void Refuel() = 0;

};

class Car : public IRefuelable {
public:
    void Refuel() override {
        std::cout << "Refueling car with fuel..." << std::endl;
    }
};

class ElectricCar : public IChargeable {
public:
    void Charge() override {
        std::cout << "Charging electric car with electricity..." << std::endl;
    }
};

void ServiceStation(IRefuelable* vehicle) {
    vehicle->Refuel();
}

void ServiceStation(IChargeable* vehicle) {
    vehicle->Charge();
}

int main() {
    Car c;
    ElectricCar e;

    ServiceStation(&c); 
    ServiceStation(&e); 
}