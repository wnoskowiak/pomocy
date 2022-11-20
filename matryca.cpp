#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.sync_with_stdio(false);
    char current, last_char = '}';
    int temp, iter = -1, last_char_pos = -1, distance = INT32_MAX;
    while(std::cin.get(current)) {
        iter++;
        if(current == '\n'){
            break;
        }
        if(current != '*') {
            if(last_char != current) {
                last_char = current;
                if (last_char_pos != -1) {
                    temp = iter - last_char_pos;
                    distance = std::min(temp, distance);
                }
            }
            last_char_pos = iter;
        }
    }
    std::cout << iter - std::min(distance, iter) + 1<< "\n";
}