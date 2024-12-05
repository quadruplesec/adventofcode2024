#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// I gave up on doing this in C really fast lmao. Whoever says C++ isn't high level is delusional

int main() {
   std::ifstream fp("input.txt");
   std::string line;
   int safe = 0;
   int l = 0;

   while (!fp.eof()) {
      std::vector<int> v;
      getline(fp, line);
      std::stringstream s(line);
      int x;
      while (s >> x) {
         v.push_back(x);
      }

      bool is_sorted = false;
      bool adjacency_check = true;

      // Check if the vector is sorted in increasing or decreasing order
      if (std::is_sorted(v.begin(), v.end()) || std::is_sorted(v.rbegin(), v.rend())) {
         is_sorted = true;
      }

      // Adjacency Check
      for (int i = 1; i < v.size(); i++) {
         int difference = abs(v[i - 1] - v[i]);
         if (difference >= 1 && difference <= 3) {
            continue;
         } else {
            adjacency_check = false;
            break;
         }
      }

      // If both are true, it is safe.
      if ( is_sorted && adjacency_check ) {
         safe++;
      }
   }

   printf("safe: %d\n", safe);
   
   return 0;
}