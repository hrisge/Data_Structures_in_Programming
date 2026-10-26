#include <iostream>
#include <vector>
#include <algorithm>

void countingSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());
    int minVal = *min_element(arr.begin(), arr.end());

    int range = maxVal - minVal + 1;
    std::vector<int> count(range, 0);

    // Броим срещанията на всеки елемент
    for (int x : arr) {
        count[x - minVal]++;
    }

    // Възстановяваме сортирания масив
    int index = 0;
    for (int i = 0; i < range; i++) {
        while (count[i] > 0) {
            arr[index++] = i + minVal;
            count[i]--;
        }
    }
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