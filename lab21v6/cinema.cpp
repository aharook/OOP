#include <iostream>
#include <string>

class ITicketStrategy {
public:
    virtual double calculatePrice(double basePrice, int seats) = 0;
    virtual ~ITicketStrategy() = default;
};

class RegularTicket : public ITicketStrategy {
public:
    double calculatePrice(double basePrice, int seats) override {
        return basePrice * seats;
    }
};

class StudentTicket : public ITicketStrategy {
public:
    double calculatePrice(double basePrice, int seats) override {
        return basePrice * seats * 0.8;
    }
};

class VipTicket : public ITicketStrategy {
public:
    double calculatePrice(double basePrice, int seats) override {
        return basePrice * seats * 1.5;
    }
};

class NightmareTicket : public ITicketStrategy {
public:
    double calculatePrice(double basePrice, int seats) override {
        return basePrice * seats * 2.0 + 50; 
    }
};

class TicketStrategyFactory 
{
public:
    static ITicketStrategy* createStrategy(const std::string& ticket_type) 
    {
        return ticket_type == "Regular" ? static_cast<ITicketStrategy*>(new RegularTicket()) :
               ticket_type == "Student" ? static_cast<ITicketStrategy*>(new StudentTicket()) :
               ticket_type == "Vip" ? static_cast<ITicketStrategy*>(new VipTicket()) :
               ticket_type == "Nightmare" ? static_cast<ITicketStrategy*>(new NightmareTicket()) :
               throw std::invalid_argument("unknown ticket type");
    }
};

class CinemaService {
public:
    double calculateTotal(double basePrice, int seats, ITicketStrategy& strategy) {
        return strategy.calculatePrice(basePrice, seats);
    }
};

int main() {
    std::string type;
    double basePrice;
    int seats;

    std::cout << "Enter ticket type (Regular, Student, Vip): ";
    std::cin >> type;

    std::cout << "Enter base price: ";
    std::cin >> basePrice;
    std::cout << "Enter number of seats: ";
    std::cin >> seats;

    try {
        auto strategy = TicketStrategyFactory::createStrategy(type);

        CinemaService service;
        double total = service.calculateTotal(basePrice, seats, *strategy);

    std::cout << "Total ticket price: " << total << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
