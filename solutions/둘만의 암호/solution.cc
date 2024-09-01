//
// Created by pelikan on 2024. 9. 1.
// https://school.programmers.co.kr/learn/courses/30/lessons/155652
//

/*
 * s, skip 모두 std::string
 * idnex는 int
 *
 * s의 각 글자들을 index만큼 뒤의 알파벳으로 변경 (카이사르 암호처럼)
 * index만큼 넘기다가 z 다음엔 a가 오도록
 * skip에 있는 알파벳들은 없다 치고 돌림
 *
 * 5 <= s.length() <= 50
 * 1 <= skip.length() <= 10
 * s와 skip은 모두 알파벳 소문자로만 구성
 *  skip에 있는 알파벳은 s에 없음.
 * 1 <= index.length() <= 10
 */

#include <bits/stdc++.h>

std::string input_s = "aukks";
std::string input_skip = "wbqd";
int input_index = 5;

std::string solution(std::string s, std::string skip, int index) {
    std::list<char> alphabet_list;
    std::vector<char> alphabet_vector;
    for (int i = 0; i < 26; i++) {
        char c = static_cast<char>('a' + i);
        if (skip.find(c) == std::string::npos) {
            alphabet_list.emplace_back(c);
            alphabet_vector.emplace_back(c);
            std::cout << c << "\n";
        }
    }
    std::cout << "\n";
    for (auto &item: s) {
        item = alphabet_vector[(std::find(alphabet_vector.begin(), alphabet_vector.end(), item) - std::begin
                (alphabet_vector) + index) % alphabet_vector.size()];
    }
    return s;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cout << solution(input_s, input_skip, input_index);
    return 0;
}