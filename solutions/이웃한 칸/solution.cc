//
// Created by pelikan on 2024. 9. 7.
// https://school.programmers.co.kr/learn/courses/30/lessons/250125
// BFS 문제
//


#include <bits/stdc++.h>

int solution(std::vector<std::vector<std::string>> board, int h, int w);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}

int dh[] = {0, 1, 0, -1}; // row: 1차원
int dw[] = {1, 0, -1, 0}; // column: 2차원
int solution(std::vector<std::vector<std::string>> board, int h, int w) {
    auto board_size = board.size();
    auto count = 0;

    for (int i = 0; i < 4; ++i) {
        int nw = dw[i] + w;
        int nh = dh[i] + h;
        if (nw < 0 || nw >= board_size || nh < 0 || nh >= board_size) {
            continue;
        }
        if(board[nh][nw] == board[h][w]){
            count++;
        }
    }
    return count;
}