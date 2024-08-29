//
// Created by pelikan on 2024. 8. 28.
// 대충 만든 자판
//

#include <bits/stdc++.h>

const std::vector<std::string> k{"AGZ", "BSSS"};
const std::vector<std::string> t{"ASA", "BGZ"};

std::vector<int> solution(const std::vector<std::string> &keymap, const std::vector<std::string> &targets) {
    std::vector<int> answer;
    std::unordered_map<char, int> alphabet;
    std::string sentence;
    for (const auto &item: targets) {
        sentence += item;
    }
    for (const auto &alpha: sentence) {
        unsigned long count = INT32_MAX - 1;
        for (const auto &s: keymap) {
            count = std::min(count, s.find(alpha));
        }
        alphabet[alpha] = (int) count + 1;
    }

    // 이제 입력값인 targets를 보면서 해당 문자에 맞는 숫자들을 모두 합하여 answer vector에 입력
    for (const auto &item: targets) {
        int result = 0;
        for (const auto &c: item) {
            if (alphabet[c] == INT32_MAX) {
                result = -1;
                break;
            }
            result += alphabet[c];
        }
        answer.emplace_back(result);
    }
    return answer;
}

int main(int argc, char *argv[]) {
    for (const auto &num: solution(k, t)) {
        std::cout << num << " ";
    }
    return 0;
}


