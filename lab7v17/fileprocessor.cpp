#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <functional>

class FileProcessor {
public:
    std::vector<std::string> LoadOrderIds(const std::string& path) {
        static int attempts = 0;
        attempts++;
        if (attempts <= 2)
            throw std::ios_base::failure("IOException while reading file");
        return { "O-100", "O-200", "O-300" };
    }
};

class NetworkClient {
public:
    std::vector<std::string> GetOrdersFromApi(const std::string& url) {
        static int attempts = 0;
        attempts++;
        if (attempts <= 3)
            throw std::runtime_error("HttpRequestException while calling API");
        return { "N-111", "N-222", "N-333" };
    }
};

class RetryHelper {
public:
    template <typename Func>
    static auto Execute(Func func, int maxAttempts, std::function<bool(const std::exception&)> shouldRetry) {
        int delayMs = 500;
        for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
            try {
                return func(); 
            }
            catch (const std::exception& ex) {
                if (!shouldRetry(ex)) throw; 
                std::cout << "Attempt " << attempt << " failed: " << ex.what() 
                          << ", retrying after " << delayMs << "ms...\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
                delayMs *= 2; 
            }
        }
        throw std::runtime_error("All retry attempts failed");
    }
};
int main() {
    FileProcessor file;
    NetworkClient client;

    auto fileRetry = [](const std::exception& ex) {
        return dynamic_cast<const std::ios_base::failure*>(&ex) != nullptr;
    };
    auto apiRetry = [](const std::exception& ex) {
        return dynamic_cast<const std::runtime_error*>(&ex) != nullptr;
    };
    try {
        std::cout << "Loading from file...\n";
        auto orders = RetryHelper::Execute(
            [&]() { return file.LoadOrderIds("orders.txt"); },
            5,
            fileRetry
        );
        std::cout << "File success. Orders: ";
        for (auto& id : orders) std::cout << id << " ";
        std::cout << "\n\n";
    }
    catch (const std::exception& ex) {
        std::cout << "File failure: " << ex.what() << "\n\n";
    }
    try {
        std::cout << "Loading from API...\n";
        auto orders = RetryHelper::Execute(
            [&]() { return client.GetOrdersFromApi("https://example.com"); },
            5,
            apiRetry
        );
        std::cout << "API success. Orders: ";
        for (auto& id : orders) std::cout << id << " ";
        std::cout << "\n";
    }
    catch (const std::exception& ex) {
        std::cout << "API failure: " << ex.what() << "\n";
    }
}
