#include <iostream>
#include <string>

class IItemValidator {
public:
    virtual bool CanAddItem(int currentCount, int maxCapacity) const = 0;
    virtual ~IItemValidator() = default;
};

class IItemRepository {
public:
    virtual void AddItem(const std::string& item) = 0;
    virtual ~IItemRepository() = default;
};
class ILogger {
public:
    virtual void Log(const std::string& message) = 0;
    virtual ~ILogger() = default;
};
class IStockNotifier {
public:
    virtual void Notify(const std::string& message) = 0;
    virtual ~IStockNotifier() = default;
};
class ItemValidator : public IItemValidator {
public:
    bool CanAddItem(int currentCount, int maxCapacity) const override {
        return currentCount < maxCapacity;
    }
};
class ItemRepository : public IItemRepository {
public:
    void AddItem(const std::string& item) override {
        std::cout << "Adding item: " << item << std::endl;
    }
};
class ConsoleLogger : public ILogger {
public:
    void Log(const std::string& message) override {
        std::cout << "Log: " << message << std::endl;
    }
};
class StockNotifier : public IStockNotifier {
public:
    void Notify(const std::string& message) override {
        std::cout << "Notification: " << message << std::endl;
    }
};

class InventoryService {
private:
    int itemCount;
    int maxCapacity;

    IItemValidator& validator;
    IItemRepository& repository;
    ILogger& logger;
    IStockNotifier& notifier;

public:
    InventoryService(
        int maxCap,
        IItemValidator& val,
        IItemRepository& repo,
        ILogger& log,
        IStockNotifier& notif
    )
        : itemCount(0),
          maxCapacity(maxCap),
          validator(val),
          repository(repo),
          logger(log),
          notifier(notif) {}

    void AddItem(const std::string& item) {
        if (!validator.CanAddItem(itemCount, maxCapacity)) {
            notifier.Notify("There is not enough space left in inventory");
            return;
        }

        repository.AddItem(item);
        itemCount++;

        logger.Log("Item added: " + item);
    }
};

int main() {
    ItemValidator validator;
    ItemRepository repository;
    ConsoleLogger logger;
    StockNotifier notifier;

    InventoryService inventory(
        2,
        validator,
        repository,
        logger,
        notifier
    );

    inventory.AddItem("Sword");
    inventory.AddItem("Shield");
    inventory.AddItem("Potion");

    return 0;
}

