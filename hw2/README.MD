# Домашня робота №2
## Порушення принципу підстановки Лісков (LSP) у C++   

### Приклад 1. банківський рахунок та депозитний рахунок
### порушення LSP

    class Account {
    public:
        virtual void withdraw(double amount) {
            balance -= amount;
        }

        double getBalance() const {
            return balance;
        }
    protected:
        double balance = 0.0;
    };

    class DepositAccount : public Account {
    public:
        void withdraw(double amount) override {
            throw std::logic_error("Withdraw is not allowed for deposit account");
        }
    };

Базовий клас Account дає можливість зняття коштів. Клас DepositAccount порушує цей контракт, забороняючи операцію. У результаті об’єкт депозитного рахунку не може підставлятися замість звичайного рахунку, оскільки код отримає помилку.

### Виправлений варіант

    class Account {
    public:
        virtual double getBalance() const = 0;

    };

    class WithAccount : public Account {
    public:
        virtual void withdraw(double amount) = 0;
    };

    class CurrAccount : public WithAccount {
    public:
        void withdraw(double amount) override {
            balance -= amount;
        }

        double getBalance() const override {
            return balance;
        }

    private:
        double balance = 0.0;
    };

    class DepositAccount : public Account {
    public:
        double getBalance() const override {
            return balance;
        }

    private:
        double balance = 0.0;
    };

Зняття коштів винесено в окремий абстрактний клас, тому кожен рахунок реалізує лише його поведінку.

### Приклад 2. Доставка товарів

### Порушення LSP

    class Delivery {
    public:
        virtual double calculateCost(double weight) const {
            return weight * 10.0;
        }
    };

    class FreeDelivery : public Delivery {
    public:
        double calculateCost(double weight) const override {
            if (weight > 5.0) {
                throw std::logic_error("Free delivery unavailable");
            }
            return 0.0;
        }
    };

Клас Delivery не обмежує розрахунок ціни. Клас FreeDelivery додає ще одну умову і змінює поведінку методу, що створює помилку при додаванні похідного класу замість базового.

### Виправлений варіант

    class Delivery {
    public:
        virtual bool isAvailable(double weight) const = 0;
        virtual double calculateCost(double weight) const = 0;
       
    };

    class StandardDelivery : public Delivery {
    public:
        bool isAvailable(double) const override {
            return true;
        }

        double calculateCost(double weight) const override {
            return weight * 10.0;
        }
    };

    class FreeDelivery : public Delivery {
    public:
        bool isAvailable(double weight) const override {
            return weight <= 5.0;
        }

        double calculateCost(double) const override {
            return 0.0;
        }
    };

Контракт базового класу змінений, щоб усі реалізації могли працювати коректно без прихованих обмежень.

## Висновок
Порушення принципу LSP виникає тоді, коли похідний клас змінює або звужує контракт базового класу. Рішенням  є правильне проєктування класів та винесення винятків в окремі абстракції.

