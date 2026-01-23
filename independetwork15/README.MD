# Звіт з аналізу SOLID принципів (SRP, OCP) в Open-Source проєкті
## 1. Обраний проєкт

**Назва:** SFML (Simple and Fast Multimedia Library)

**Посилання на GitHub:** https://github.com/SFML/SFML

## 2. Аналіз SRP (Single Responsibility Principle)
### 2.1. Приклади дотримання SRP

### Клас: Texture

**Відповідальність:** Завантаження, зберігання та керування текстурою у відеопам’яті.

**Обґрунтування:** Клас не займається рендерингом, логікою гри або керуванням вікном. Він працює виключно за роботу з графічним ресурсом — текстурою, що відповідає SRP.

    class Texture
    {
    public:
        bool loadFromFile(const std::string& filename);
        Vector2u getSize() const;
    };

### Клас: Event

**Відповідальність:** Зберігання інформації про події.

**Обґрунтування:** Він не обробляє події самостійно, а лише передає дані про них. Обробка реалізована окремо, в інших частинах програми.

    class Event
    {
    public:
        EventType type;

        struct KeyEvent
        {
            Keyboard::Key code;
            bool alt;
            bool control;
        };
    };

### Клас: Drawable

**Відповідальність:** Надання  інтерфейсу об’єктам, які можуть бути відмальовані.

**Обґрунтування:** Клас має лише абстрактний метод draw і не реалізує іншої логіки рендеру.

    class Drawable
    {
    protected:
        virtual void draw(RenderTarget& target,
                        RenderStates states) const = 0;
    };

## 2.2. Приклади порушення SRP
### Клас: Window

**Множинні відповідальності:** створення та керування вікном, обробка подій, робота з OpenGL-контекстом, взаємодія з операційною системою.

**Проблеми:** Клас має кілька причин для змін (графіка, події, платформа), що створює проблеми з підтримкою, тестуванням та розширенням.

    class Window
    {
    public:
        void create(VideoMode mode, const String& title);
        void close();
        bool pollEvent(Event& event);
        void setActive(bool active = true);
    };

## 3. Аналіз OCP (Open/Closed Principle)
## 3.1. Приклади дотримання OCP

### Сценарій/Модуль: Ієрархія Drawable

**Механізм розширення:** Абстрактний клас та поліморфізм.

**Обґрунтування:** Нові графічні об’єкти можна додавати наслідуючи Drawable без змін існуючого коду.

    class CircleShape : public Drawable
    {
    protected:
        void draw(RenderTarget& target,
                RenderStates states) const override;
    };

### Сценарій/Модуль: InputStream

**Механізм розширення:** Абстрактний інтерфейс.

**Обґрунтування:** Дозволяє працювати з різними  даниими (файл, пам’ять, мережа) без зміни коду.

    class InputStream
    {
    public:
        virtual Int64 read(void* data, Int64 size) = 0;
        virtual Int64 seek(Int64 position) = 0;
    };

## 3.2. Приклади порушення OCP
### Сценарій/Модуль: Обробка подій через switch

**Проблема:** Для додавання нового типу потрібно змінювати існуючий switch.

**Наслідки:** Порушення OCP, збільшує складність коду та створює ризик появи помилок.

    switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;
    case sf::Event::KeyPressed:
        handleKey(event.key);
        break;
    }

## 4. Загальні висновки

Проєкт SFML  добре реалізує принципи SRP та OCP завдяки використанню абстрактних класів, чіткого розподілу відповідальностей і поліморфізму. 
Водночас деякі класи мають надмірну кількість обов’язків, що порушує SRP, а використання умовних конструкцій ускладнює дотримання OCP.І