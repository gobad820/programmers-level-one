//
// Created by 김상해 on 2024. 8. 29.
//
#include <bits/stdc++.h>

bool comp(const std::pair<int, double>& a, const std::pair<int, double>& b){
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second > b.second;
}

// 실패율: 해당 스테이지에서 진행중인 플레이어 수 / (해당 스테이지에서 진행중인 플레이어 수 + 해당 스테이지를 완료한 플레이어의 수)
// N: 전체 스테이지 수(1<= N <= 500 인 자연수)
// stages: 플레이어마다 진행중인 스테이지의 단( 1 <= stages.size() <= 200_000, 1 <= stages[n] <= N+1)
// eg) stages[15]: 15스테이지를 진행중인 플레이어의 수
const int number_of_stages = 5;
std::vector<int> stayed_stages{2, 1, 2, 6, 2, 4, 3, 3};

// 실패율이 높은 스테이지부터 내림차순으로 스테이지의 번호가 담겨있는 배열을 리턴, 단 동률이면 스테이지 단계가 낮은것 우선, 진행중인 유저가 0이면 실패율은 0
std::vector<int> solution(int N, const std::vector<int> &stages) {
    std::vector<int> answer;

    // 각 스테이지 마다 실패율 구하기
    // 각 스테이지마다 몇 명이 진행중인가?
    std::unordered_map<int, double> men_in_progress;
    for (const auto &stage: stages) {
        men_in_progress[stage]++;
    } // 각 스테이지마다 몇 명이 진행중인지 파악

    // 이제 해당 스테이지를 완료한 사람들까지 포함한 수를 파악 즉 문제에 따르면 해당 스테이지에 도달한 사람
    std::unordered_map<int, double_t> completed_men; // <스테이지, 도달한 사람>
    auto sum_of_man = (double_t)stages.size();
    for (int i = 1; i <= N; ++i) {
        completed_men[i] = sum_of_man;
        sum_of_man -= men_in_progress[i];
    }

    // 1 스테이지부터 N스테이지까지 실패율 구하기 // N+1 단계-> 다 깼다
    // 실패율 = men_in_progress / completed_men
    std::vector<std::pair<int, double>> failure;

    for (int i = 1; i <= N; i++) {
        if (completed_men[i] == 0) {
            failure.emplace_back(i,0);
            continue;
        }
        failure.emplace_back(i,men_in_progress[i] / completed_men[i]);
    }

    std::sort(failure.begin(), failure.end(),comp);
    for (const auto &item: failure) {
        answer.emplace_back(item.first);
    }
    // 도출한 실패율 바탕으로 answer에 emplace_back
    return answer;
}

int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    for (const auto &item: solution(number_of_stages, stayed_stages)) {
        std::cout << item << " ";
    }
    return 0;
}
