# Домашня робота №3. Принципи ISP та DIP

##  приклад інтерфейсу, що порушує ISP

    class IDocument {
    public:
        virtual void open() = 0;
        virtual void save() = 0;
        virtual void print() = 0;
        virtual void scan() = 0;
        virtual ~IDocument() {}
    };

Інтерфейс IDocument порушує принципи через те, що при релізації цього інтерфейсу 1 класом, до прикладу TextDocument, ми реалізуємо всі методи крім scan(), хоча він буде змушений його реалізовувати, а при використанні цього ж інтерфейсу в ScannerDevice нам потрібен лише  scan(), але через логіку інтерфейсу ми вимушені реалізовувати всі.


    class TextDocument : public IDocument {
    public:
        void open() override {
            std::cout << "Open text document";
        }

        void save() override {
            std::cout << "Save text document";
        }

        void print() override {
            std::cout << "Print text document";
        }

        void scan() override {
        
        }
        };

    class ScannerDevice : public IDocument {
    public:
        void open() override {
            // не потрібно
        }

        void save() override {
            // не потрібно
        }

        void print() override {
            // не потрібно
        }

        void scan() override {
            std::cout << "Scan document";
        }
        };

## Вирішення проблеми (дотримання ISP)
    class IOpenable {
    public:
        virtual void open() = 0;
        virtual ~IOpenable() {}
    };

    class ISavable {
    public:
        virtual void save() = 0;
        virtual ~ISavable() {}
    };

    class IPrintable {
    public:
        virtual void print() = 0;
        virtual ~IPrintable() {}
    };

    class IScannable {
    public:
        virtual void scan() = 0;
        virtual ~IScannable() {}
    };

Опираючись на принципи ISP, ми розбиваємо інтерфейс на менші, які реалізують лише конкретну задачу, що дозоляє зручно використовувати їх. Таким чином ми не змушені реалізовувати надлишкові методи. Кожен клас реалізує тільки потрібну функціональність.

## переваги застосування DIP (через Dependency Injection).

### Приклад без DIP

    class FileLogger {
    public:
        void log(const std::string& msg) {}
    };

    class OrderService {
        FileLogger logger;
    public:
        void createOrder() {
            logger.log("Order created");
        }
    };

Основними проблемами при такій реалізації є те, що OrderService напряму залежить від FileLogger, неможливо легко замінити логер, для тестування або інших змін а також при відстуності реального логера тестування стає неможливим.

### Приклад з DIP
    class ILogger {
    public:
        virtual void log(const std::string& msg) = 0;
        virtual ~ILogger() {}
    };

    class FileLogger : public ILogger {
    public:
        void log(const std::string& msg) override {}
    };

    class OrderService {
        ILogger& logger;
    public:
        OrderService(ILogger& logger) : logger(logger) {}

        void createOrder() {
            logger.log("Order created");
        }
    };

Переробивши код під принципи DIP ми отримали те, що тепер OrderService залежить від абстракції (ILogger), реалізацію можна міняти без змін сервісу, тестуаання стало набагато зручнішим, адже дозволяє нам використовувати заглушки

## Як “вузькі” інтерфейси (ISP) покращують DI та тестування

Принцип ISP робить систему зручнішою для дій над нею, оскільки «вузькі» інтерфейси дозволяють DI постачати  функціональність, яка необхідна конкретному класу. Це позбавляє компоненти надлишкової інформації, що  зменшує зв’язність коду та запобігає появі великих залежностей. У тестуванні це відіграє велику роль, адже  не потрібно створювати складні заглушки, що суттєво скорочує обсяг тестового коду та прискорює тестування. Таким чином, DI перетворює кожен тест на ізольовану перевірку логіки, де інтерфейс виступає чітким контрактом.