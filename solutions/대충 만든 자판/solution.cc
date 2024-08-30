//
// Created by pelikan on 2024. 8. 28.
// 대충 만든 자판
//

#include <bits/stdc++.h>

const std::vector<std::string> k{"ABACD", "BCEFD"};
const std::vector<std::string> t{"ABCD","AABB"};

const std::size_t MAX_COUNT = 200;
const int NOT_EXIST_KEY= -1;

std::vector<int> solution(const std::vector<std::string>& keymap, const std::vector<std::string>& targets) {
    std::vector<int> answer;
    std::unordered_map<char, int> alphabet;

    for(const auto& target: targets){
        for(const auto& c: target){
            alphabet.emplace(c,0);
        }
    }

    for (const auto &[alpha, _]: alphabet) {
        std::size_t count = MAX_COUNT;
        for (const auto &s: keymap) {
            count = std::min(count, s.find(alpha));
        }
        if(count == MAX_COUNT){
            alphabet[alpha] = NOT_EXIST_KEY;
            continue;
        }
        alphabet[alpha] = static_cast<int>(count)+1;
    }

    for (const auto &target: targets) {
        int result = 0;
        for (const auto &c: target) {
            if (alphabet[c] == NOT_EXIST_KEY) {
                result = NOT_EXIST_KEY;
                break;
            }
            result += alphabet[c];
        }
        answer.emplace_back(result);
    }
    return answer;
}



int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    for (const auto &num: solution(k, t)) {
        std::cout << num << " ";
    }
    return 0;
}