#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

class ISortStrategy { // створення інтерфейсу
public:
    virtual void Sort(vector<int>& arr) = 0; // віртуальний метод для сортування
};

class AscendingSort : public ISortStrategy { // реалізація сортування за зростанням
public:
    void Sort(vector<int>& arr) override { // релізація методу з інтерфейсу
        sort(arr.begin(), arr.end());
    }
};

class DescendingSort : public ISortStrategy { // реалізація сортування за спаданням
public:
    void Sort(vector<int>& arr) override {
        sort(arr.begin(), arr.end(), greater<int>()); // релізація методу з інтерфейсу
    }
};


 
class NumberProcessor {
private:
    ISortStrategy* strategy; // агрегація стратегії сортування
public:
    NumberProcessor(ISortStrategy* s) : strategy(s) {} // конструктор приймає стратегію сортування

    void Process(vector<int> arr) { // метод для обробки масиву

        strategy->Sort(arr);

        cout << "Sorted: ";
        for (int n : arr) cout << n << " "; // виведення відсортованого масиву
        cout << endl;

        double sum = 0;
        for (int n : arr) sum += n;
        double avg = sum / arr.size(); // середнє значення

        cout << "Min: " << arr.front() << endl; // мінімум
        cout << "Max: " << arr.back() << endl; // максимум
        cout << "Avg: " << avg << endl; 
    }
};

int main() {
    vector<int> arr = {21, 1, 2, 6, 12, 44, 7, 2, 8, 9}; // вхідний масив

    AscendingSort asc; // створення об'єктів стратегій
    DescendingSort desc;

    cout << "--- Ascending ---" << endl;
    NumberProcessor processor1(&asc); // використання стратегії сортування за зростанням
    processor1.Process(arr);

    cout << "\n--- Descending ---" << endl;
    NumberProcessor processor2(&desc); // використання стратегії сортування за спаданням
    processor2.Process(arr);
    
    return 0;
}
