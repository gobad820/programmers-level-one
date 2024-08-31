//
// Created by pelikan on 2024. 8. 29.
// https://school.programmers.co.kr/learn/courses/30/lessons/17682
//

/*
 * 다트는 총 3번 던진다.
 *
 * 점수 영역
 * 점수는 0~10점으로 분포됨
 *
 * 제곱배 영역(점수마다 하나씩 존재) -> 1/3 확률로 반드시 선택됨
 * S: single => 점수의 1제곱 득점
 * D: double => 점수의 2제곱 득점
 * T: triple => 점수의 3제곱 득점
 *
 * 옵션 영역(점수마다 둘 중 하나만 존재하거나 존재하지 않을 수도 있다)
 * *: 스타상 => 현재 점수와 직전 점수 2배 득점 처리(스타상은 스타상과 아차상 모두 중복 득점가능)
 * #: 아차상 => 해당 점수를 -점수로 득점한다.
 *
 * 옵션의 중첩
 * 스타상 x 스타상 => 중첩된 스타상의 점수 4배
 *                 ( 1, 2, 3 번 던졌을 때 2, 3 에서 모두 스타상 -> 2번째 던진 다트는 4배점수)
 * 스타상 x 아차상 => 아차상 점수는 -2배
 *                 ( 1, 2, 3 번 던지고 1, 2 에서 아차상, 스타상 -> 1번째 점수는 -2배 득점 처리)
 *
 *
 * 입력 형식
 * "점수 | 보너스 | [옵션]"
 * 1S2D*3T => 첫번째는 1점 싱글 옵션 없음, 두번째는 2점 더블 스타상, 3번째는 3점 트리플 옵션 없음
 * 1D2S#10S => 첫번째는 1점 더블 옵셥 없음, 두번째는 2점 싱글 아차상, 3번재는 10점 싱글 옵션 없음
 * */
#include <bits/stdc++.h>

std::string d = "1D2S3T*";
const std::string bonus_string = "SDT";
const std::string options_string = "*#";

int solution(std::string dartResult) {
    int count = 0;
    int answer = 0;

    std::vector<int> score;
    // 3번 반복
    for (int i = 0; i < dartResult.length(); ++i) {
        if (count > 3) {
            break; // 기회는 3번
        }

        // 점수부 구분하여 점수부 추가
        if (isdigit(dartResult[i])) {
            // 10의 경우는 어떻게?
            std::size_t n = 1;
            if (isdigit(dartResult[i + 1])) {
                n++;
            }
            score.emplace_back(std::stoi(dartResult.substr(i, n)));
            if (n == 2) {
                i++;
            }
            std::cout << "SCORE: " << score[count] << "\n";
            count++;
        }// 제곱부 구분하여 socre 연산 득점 처리
        else if (bonus_string.find(dartResult[i]) != std::string::npos) {
            int temp_score = score[count - 1];
            if (dartResult[i] == bonus_string.at(1)) { // DOUBLE
                score[count - 1] = temp_score * temp_score;
            } else if (dartResult[i] == bonus_string.at(2)) { // TRIPLE
                score[count - 1] = temp_score * temp_score * temp_score;
            } else;
        }  // 옵션부 score 연산 시도
        else if (options_string.find(dartResult[i]) != std::string::npos) {
            if (dartResult[i] == options_string.at(0)) { // 스타상 이전 score와 현재 score 모두 2배
                // 첫번쨰 시도가 아니라면
                if (count != 0) {
                    score[count - 2] *= 2;
                    score[count - 1] *= 2;
                }
            } else { // 아차상 이번 score 점수를 음수화 시킴
                score[count - 1] *= -1;
            }
        } else { ; }

    }
    for (const auto &item: score) {
        std::cout << item << "\n";
        answer += item;
    }
    return answer;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cout << solution(d);
    return 0;
}
