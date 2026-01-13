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

class OrderProcessor {
public:
    void ProcessOrder(Order& order) {
        std::cout << "Processing order..." << std::endl;

        if (order.getTotalAmount() > 0) {
            order.setStatus("Processed");
            std::cout << "Order ID: " << order.getId() << std::endl;
            std::cout << "order status: " << order.getStatus() << std::endl;
            std::cout << "Order processed successfully." << std::endl;
            std::cout << "Sending confirmation email to " << order.getCustomerName() << std::endl;
        } else {
            order.setStatus("Failed");
            std::cout << "Order processing failed: Total amount must be greater than 1." << std::endl;
        }
    }
};

int main() {
    Order myOrder(1, "John Doe", 150.0, "waiting");
    OrderProcessor processor;
    processor.ProcessOrder(myOrder);

    std::cout << "Order status: " << myOrder.getStatus() << std::endl;
}
