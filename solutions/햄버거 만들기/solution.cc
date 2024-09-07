//
// Created by pelikan on 2024. 9. 6.
//  https://school.programmers.co.kr/learn/courses/30/lessons/133502
//

#include <bits/stdc++.h>

std::vector<int> i{2, 1, 1, 2, 3, 1, 2, 3, 1};
std::vector<int> i2{1, 3, 2, 1, 2, 1, 3, 1, 2};
std::vector<int> i3{1, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 1, 1};


std::ostream &operator<<(std::ostream &os, std::deque<int> deque);

std::deque<int> hamburger;

int solution(std::vector<int> ingredient) {
    int answer = 0;
    for (const auto &item: ingredient) {
        hamburger.emplace_back(item);
        if (hamburger.size() >= 4) {
            if (hamburger[hamburger.size() - 4] == 1 && hamburger[hamburger.size() - 3] == 2 &&
                hamburger[hamburger.size() - 2] == 3 && hamburger[hamburger.size() - 1] == 1) {
                std::cout << hamburger;
                for (int j = 0; j < 4; ++j) {
                    hamburger.pop_back();
                }
                answer++;
            }
        }
    }
    std::cout << hamburger;
    return answer;
}

std::ostream &operator<<(std::ostream &os, std::deque<int> deque){
    for (const auto &item: deque) {
        os << item << " ";
    }
    os << "\n";
    return os;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cout << solution(i);
    return 0;
}