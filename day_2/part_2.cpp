#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

bool is_valid_sequence(std::vector<int> v) {
    // Check full sequence first without any changes
    bool is_sorted = false;
    bool adjacency_check = true;

    // Check if the vector is sorted in increasing or decreasing order
    if (std::is_sorted(v.begin(), v.end()) || std::is_sorted(v.rbegin(), v.rend())) {
        is_sorted = true;
    }

    for (int i = 1; i < v.size(); i++) {
        int difference = abs(v[i - 1] - v[i]);
        if (difference >= 1 && difference <= 3) {
            continue;
        } else {
            adjacency_check = false;
            break;
        }  
    }

    if (is_sorted && adjacency_check) {
        return true;
    }

    // Now test with removal
    for (int i = 0; i < v.size(); i++) {
        bool temp_is_sorted = false;
        bool temp_adjacency_check = true;

        std::vector<int> temp = v;
        temp.erase(temp.begin() + i);

        if (std::is_sorted(temp.begin(), temp.end()) || std::is_sorted(temp.rbegin(), temp.rend())) {
            temp_is_sorted = true;
        }

        for (int i = 1; i < temp.size(); i++) {
            int difference = abs(temp[i - 1] - temp[i]);
            if (difference >= 1 && difference <= 3) {
                continue;
            } else {
                temp_adjacency_check = false;
                break;
            }  
        }

        if (temp_is_sorted && temp_adjacency_check) {
            return true;
        }
    }
    return false;
}

int main() {
    std::ifstream fp("input.txt");
    std::string line;
    int safe = 0;

    while (std::getline(fp, line)) {
        std::vector<int> v;
        std::stringstream s(line);
        int x;
        while (s >> x) {
            v.push_back(x);
        }

        if (is_valid_sequence(v)) {
            safe++;
        }
    }

    printf("safe: %d\n", safe);
   
    return 0;
}