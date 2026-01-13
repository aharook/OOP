#include <string>
#include <iostream>


class Order {
public:
    Order(int Id, const std::string& CustomerName, double TotalAmount, const std::string& Status)
        : m_Id(Id), m_CustomerName(CustomerName), m_TotalAmount(TotalAmount), m_status(Status) {}

    int getId() const { return m_Id; }
    std::string getCustomerName() const { return m_CustomerName; }
    double getTotalAmount() const { return m_TotalAmount; }
    std::string getStatus() const { return m_status; }

    void setStatus(const std::string& status) { m_status = status; }

private:
    int m_Id;
    std::string m_CustomerName;
    double m_TotalAmount;
    std::string m_status;
};


class IOrderValidator {
public:
    virtual ~IOrderValidator() = default;
    virtual bool Validate(const Order& order) = 0;
};


class IOrderRepository {
public:
    virtual ~IOrderRepository() = default;
    virtual void Save(const Order& order) = 0;
    virtual Order GetById(int id) = 0;
};


class IEmailService {
public:
    virtual ~IEmailService() = default;
    virtual void SendOrderConfirmation(const Order& order) = 0;
};


class OrderService : public IOrderValidator, public IOrderRepository, public IEmailService {
public:

    void ProcessOrder(Order& order) {
        std::cout << "Processing order..." << std::endl;

        if (Validate(order)) {
            order.setStatus("Processed");
            Save(order);
            SendOrderConfirmation(order);

            std::cout << "Order ID: " << order.getId() << std::endl;
            std::cout << "Order status: " << order.getStatus() << std::endl;
            std::cout << "Order processed successfully." << std::endl;
        } else {
            order.setStatus("Failed");
            std::cout << "Order processing failed: Total amount must be greater than 0." << std::endl;
        }
    }


    bool Validate(const Order& order) override {
        return order.getTotalAmount() > 0;
    }

    void Save(const Order& order) override {
        std::cout << "Saving order ID " << order.getId() << " to repository..." << std::endl;
    }

    Order GetById(int id) override {

        return Order(id, "Sample Customer", 100.0, "waiting");
    }

    void SendOrderConfirmation(const Order& order) override {
        std::cout << "Sending confirmation email to " << order.getCustomerName() << std::endl;
    }
};

int main() {
    Order myOrder(1, "John Doe", 150.0, "waiting");
    OrderService processor;
    processor.ProcessOrder(myOrder);

    std::cout << "Final order status: " << myOrder.getStatus() << std::endl;
}
