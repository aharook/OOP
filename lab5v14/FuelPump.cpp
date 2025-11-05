#include <iostream>
#include <vector>
#include <string>

class InvalidSaleException : public std::runtime_error { //обробка винятків
public:
    explicit InvalidSaleException(const std::string& message)
        :std::runtime_error(message) {}
};

class Sale{
public:
    std::string brand;
    double liters;
    double pricePerLiter;
    Sale(std::string m_brand, double m_liters, double m_pricePerLiter)
    : brand(m_brand), liters(m_liters), pricePerLiter(m_pricePerLiter)
{
        if (m_liters <= 0 || m_pricePerLiter <= 0) 
        {
            throw InvalidSaleException("Liters and price per liter must be positive values."); // якщо від'ємне - кидаємо помилку
        }
}
    double total() const 
    {
        return liters * pricePerLiter;
    }

};

template<typename T> // місцевий Generics
class Repository {
private:
    std::vector<T> sales; 

public:
    void addSale(const T& sale) 
    {
        sales.push_back(sale);
    }

    double totalSales() const 
    {
        double total = 0;
        for (const auto& sale : sales) 
        {
           total += sale.total();
        }
        return total;
    }

    double totalSalesByBrand(const std::string& brand) const 
    {
        double sum;
        for (const auto& sale : sales) 
        {
            if (sale.brand == brand) 
            {
                sum += sale.total();
            }
        }
        return sum;
    }
};

class FuelPump { //робота з колекціями
private:
    Repository<Sale> salesManager; // композиція
public:
    void recordSale(const std::string& brand, double liters, double pricePerLiter) 
    {
        Sale sale(brand, liters, pricePerLiter);
        salesManager.addSale(sale);
    }
    
    double getTotalSales() const {
        return salesManager.totalSales();
    }
    
    double getTotalSalesByBrand(const std::string& brand) const {
        return salesManager.totalSalesByBrand(brand);
    }
};

int main() {
    FuelPump pump;
    try {
        pump.recordSale("BrandA", 50, 1.2);     
        pump.recordSale("BrandB", 30, 1.5);
        pump.recordSale("BrandA", 30, 1.3);

        std::cout << "Total sales: $" << pump.getTotalSales() << std::endl;
        std::cout << "Total sales for BrandA: $" << pump.getTotalSalesByBrand("BrandA") << std::endl;
        std::cout << "Total sales for BrandB: $" << pump.getTotalSalesByBrand("BrandB") << std::endl;
    } catch (const InvalidSaleException& e) // якщо ловим помилку то кидаєм текст + уточнення помилки(див class InvalidSaleException)
    {
        std::cerr << "Error recording sale: " << +e.what() << std::endl;
    }
}
