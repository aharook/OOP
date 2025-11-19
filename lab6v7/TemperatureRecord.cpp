#include <iostream>
#include <vector>
#include <string>
#include <functional>

class TemperatureRecord {
public:
    std::string day;
    int date;
    double temperature;

    TemperatureRecord(std::string d, int dt, double t)
        : day(d), date(dt) ,temperature(t) {}
};

int main() {
   std::vector<TemperatureRecord> records = {
    {"Monday", 1 , 21.4},
    {"Tuesday", 2,  28.3},
    {"Wednesday", 3, 30.1},
    {"Thursday", 4 , 19.9},
    {"Friday", 5 , 26.7},
    {"Saturday", 6 , 32.5},
    {"Sunday", 7,  24.2},
    {"Monday", 8, 29.8}
};


    auto isHot = [](std::string day, int date, double temp) {
        return temp > 25.0;
    };

    auto showTemp = [](std::string day, int date, double temp) {
        std::cout << "Hot: " << day <<" the "<<date << "th "<< temp << "C\n";
    };

    for (const auto& r : records) {
        if (isHot(r.day, r.date, r.temperature))
            showTemp(r.day, r.date, r.temperature);
    }
}
 