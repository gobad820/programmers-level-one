//
// Created by pelikan on 2024. 8. 31.
// https://school.programmers.co.kr/learn/courses/30/lessons/77484
//

/*
 * 민우는 로또를 구매, 하지만 민우 동생이 로또를 낙서를 하여 일부 번호는 알아볼 수 없음
 * 알아보지 못하는 번호는 0으로 표기
 * 민우의 로또 번호가 44, 1, 0, 0, 31, 25라 할 때
 * 당첨 로또 번호는 31, 10, 45, 1, 6, 19라고 하자.
 *
 * 민우가 받을 수 있는 최저 순위와 최고 순위를 알아보자
 * 확실히 일치하는 번호는 31, 1번이다.
 * 나머지는 알아볼 수 없는 0이 모두 다 맞거나
 * 0중 하나만 맞거나
 * 0 둘 다 맞지 않았을 경우이다.
 *
 * 따라서 최고 순위는 6개중 4개가 맞아서 3등
 * 최저 순위는 6개중 2개가 맞아서 5등이다.
 *
 * lottos 배열에는 민우가 구매한 로또 번호 6자리를 ( 0 <= 로또 번호 <= 45), 0을 제외한 다른 숫자는 중복되지 않음
 * win_num 배열에는 당첨 로또 번호가 주어진다.
 */

#include <bits/stdc++.h>

std::vector<int> l{44, 1, 0, 0, 31, 25};
std::vector<int> w{31, 10, 45, 1, 6, 19};

const std::array<int, 6> rank{6, 5, 4, 3, 2, 1};

std::vector<int> solution(std::vector<int> lottos, std::vector<int> win_nums) {
    // 0의 개수를 파악
    // 최고 점수는 0이 모두 당첨 번호와 동일할 때
    // 최저 점수는 0이 모두 당첨 번호와 불일치할 때
    std::size_t zero_number = std::count(lottos.cbegin(), lottos.cend(), 0);
    std::size_t match_number = 0;
    std::sort(lottos.begin(), lottos.end());
    for (const auto &winNum: win_nums) {
        if (std::count(lottos.cbegin(), lottos.cend(), winNum)) {
            match_number++;
        }
    }
    std::vector<int> answer;
    if (match_number + zero_number <= 1) {
        answer.emplace_back(6);
    } else {
        answer.emplace_back(rank[(zero_number + match_number) - 1]);
    }
    if (match_number <= 1) {
        answer.emplace_back(rank[0]);
    } else { answer.emplace_back(rank[match_number - 1]); }
    return answer;
}

std::vector<int> solution2(std::vector<int> lottos, std::vector<int> win_nums) {
    std::sort(win_nums.begin(), win_nums.end());

    std::size_t zero_count = std::count(lottos.cbegin(), lottos.cend(), 0);
    std::size_t match_count = std::count_if(lottos.cbegin(), lottos.cend(), [&win_nums](int num) { // &lottos를 캡처 //
        // 인자는 int number
        return num != 0 && // lottos[i] 가 0이 아니고 오염되어 보이지 않는 숫자가 아니고
               std::binary_search(win_nums.cbegin(), win_nums.cend(), num); // binary_search로 win_nums를 구한다.
    });

    auto get_rank = [](std::size_t count) -> int { return static_cast<int>(std::min(7 - count, 6UL)); };
    return {get_rank(match_count + zero_count), get_rank(match_count)};
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i != vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cout << solution2(l, w);
    return 0;
}
