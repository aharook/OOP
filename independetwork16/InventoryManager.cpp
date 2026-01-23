#include <iostream>
#include <string>

class inventoryManager {
public:
    int itemCount = 0;
    int maxCapacity = 100;
    std::string message = "there is not enough space left in inventory";
    
    inventoryManager(int maxCap, int itemCou, std::string message) 
    : maxCapacity(maxCap), itemCount(itemCou), message(message) {}

    void UpdateItem(const std::string& item) {
        std::cout << "Updating item`s : " << item << std::endl;
    }
    void Loging(const std::string& action) {
        std::cout << "Logging action: " << action << std::endl;
    } 
    void NotifyUser(const std::string& message) {
        std::cout << "Notifying user: " << message << std::endl;
    }
        void addItem(const std::string& item) {
        std::cout << "Adding item: " << item << std::endl;
        itemCount++;
        if (itemCount > maxCapacity) {
            std::cout << message << std::endl;
            NotifyUser(message);
        }
    }
};