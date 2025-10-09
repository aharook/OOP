#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class ISortStrategy {
public:
    virtual void Sort(vector<int>& arr) = 0;
};

class AscendingSort : public ISortStrategy {
public:
    void Sort(vector<int>& arr) override {
        sort(arr.begin(), arr.end());
    }
};

class DescendingSort : public ISortStrategy {
public:
    void Sort(vector<int>& arr) override {
        sort(arr.begin(), arr.end(), greater<int>());
    }
};


 
class NumberProcessor {
private:
    ISortStrategy* strategy;
public:
    NumberProcessor(ISortStrategy* s) : strategy(s) {}

    void Process(vector<int> arr) {
        if (arr.empty()) {
            cout << "Array is empty\n";
            return;
        }

        strategy->Sort(arr);

        cout << "Sorted: ";
        for (int n : arr) cout << n << " ";
        cout << endl;

        double sum = 0;
        for (int n : arr) sum += n;
        double avg = sum / arr.size();

        cout << "Min: " << arr.front() << endl;
        cout << "Max: " << arr.back() << endl;
        cout << "Avg: " << avg << endl;
    }
};

int main() {
    vector<int> arr = {21, 1, 2, 6, 12, 44, 7, 2, 8, 9};

    AscendingSort asc;
    DescendingSort desc;

    cout << "--- Ascending ---" << endl;
    NumberProcessor processor1(&asc);
    processor1.Process(arr);

    cout << "\n--- Descending ---" << endl;
    NumberProcessor processor2(&desc);
    processor2.Process(arr);
    
    return 0;
}
