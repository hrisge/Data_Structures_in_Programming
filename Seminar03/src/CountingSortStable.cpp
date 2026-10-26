    #include <iostream>
#include <vector>
#include <algorithm>

void countingSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());
    int range = maxVal - minVal + 1;

    std::vector<int> count(range, 0);
    std::vector<int> output(arr.size());

    // 1. Броим срещанията
    for (int x : arr) {
        count[x - minVal]++;
    }

    // 2. Натрупваме броячи
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    // 3. Поставяме елементите отдясно наляво
    // Това гарантира стабилност
    for (int i = (int)arr.size() - 1; i >= 0; i--) {
        int x = arr[i];
        output[count[x - minVal] - 1] = x;
        count[x - minVal]--;
    }

    // 4. Копираме резултата
    arr = output;
}

int main() {
    std::vector<int> arr = {4, 2, 2, 8, 3, 3, 1};

    countingSort(arr);

    for (int x : arr) {
        std::cout << x << " ";
    }

    std::cout << '\n';
    return 0;
}