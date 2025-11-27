#include <iostream>
#include <chrono>
#include <thread>
#include <future>

bool callAPI() {
    static int callCount = 0;
    callCount++;
    if (callCount <= 2)
    throw std::runtime_error("API call failed");

    return true;
};

int longOperation() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 42;
}

int main() {
std::cout << "Starting API call with retries...\n";

const int maxRetries = 5;
    for (int attempt = 1; attempt <= maxRetries; attempt++) {
        try {
            std::cout << "Attempt " << attempt << std::endl;
            bool ok = callAPI();
            std::cout << "API call successful!" << std::endl;
            break;
        }
        catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << std::endl;
            if (attempt == maxRetries) std::cout << "Retries exhausted.\n";
            else std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    std::cout << "Starting long operation with timeout...\n";

    auto fut = std::async(std::launch::async, longOperation);
    if (fut.wait_for(std::chrono::seconds(4)) == std::future_status::timeout) {
        std::cout << "Timeout! Operation cancelled.\n";
    } else {
        std::cout << "Operation result: " << fut.get() << std::endl;
    }

};