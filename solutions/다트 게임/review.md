# 알고리즘 문제 회고

- **제목(번호): [다트 게임](https://school.programmers.co.kr/learn/courses/30/lessons/17682)**
- **카테고리: 프로그래머스**
- **회고 날짜: 2024. 8. 30.**

## Time Limit
- X
## I/O Examples
| 예제 | dartResult | answer | 설명 |
|-----|------------|--------|------|
| 1   | 1S2D*3T    | 37     | 1^1 * 2 + 2^2 * 2 + 3^3 |
| 2   | 1D2S#10S   | 9      | 1^2 + 2^1 * (-1) + 10^1 |
| 3   | 1D2S0T     | 3      | 1^2 + 2^1 + 0^3 |
| 4   | 1S*2T*3S   | 23     | 1^1 * 2 * 2 + 2^3 * 2 + 3^1 |
| 5   | 1D#2S*3S   | 5      | 1^2 * (-1) * 2 + 2^1 * 2 + 3^1 |
| 6   | 1T2D3D#    | -4     | 1^3 + 2^2 + 3^2 * (-1) |
| 7   | 1D2S3T*    | 59     | 1^2 + 2^1 * 2 + 3^3 * 2 |
## Solution

- [👨‍💻제출 코드](solution.cc)

### 문제 핵심 개념

#### 다트 점수 저장

- 다트는 총 3번 던짐
    - count 변수를 통해 3번 이상은 더 이상 반복문이 돌아가지 않게 함.
- 점수는 0점에서 10점까지 가능
    - 10점일 경우 처리 방법이 귀찮았음
    - 전체 dartResult 문자열을 문자 하나씩 순회하면서`isidigt`가 `true`이면(문자가 숫자이면) count를 올린다.
    - 10의 경우 다음 문자까지 `isdigit`의 값이 `true`이면(숫자가 10) 다음 문자까지 순회하여 count를 올린다.
- 점수 저장은 `std::vector<int> score`에 함

#### 제곱배 연산

- `std::string bonus_string = "SDT";`를 생성
- dartResult 문자열을 문자 한 글자씩 순회하면서 `bonus_string.find(dartResult[i]) != std::string::npos`가 참일 때
    - `dartResult[i] == 'T'`이면 score[count-1] = 기존 값의 3제곱배
    - `dartResult[i] == 'D'`이면 score[count-1] = 기존 값의 2제곱배
    - `dartResult[i] == 'S'`이면 score[count-1] = 기존 값 그대로

#### 스타상 및 아차상 처리

- `std::string option_string = "*#";`를 생성
- dartResult 문자열을 문자 할 글자씩 순회하면서 `option_string.find(dartResult[i]) != std::string::npos`가 참일 때
    - `dartResult[i] == '*'`일 때
        - 첫 번째 시도가 아니라면, 즉 이전 시도가 존재할 때는
            - `score[count-2] = score[count-2]*2;` $\rightarrow$ 이전 시도 점수 2배
            - `score[count-1] = score[count-1]*2;` $\rightarrow$ 현재 시도 점수 2배
        - 첫 번째 시도라면
            - `score[count-1] = score[count-1]*2;` $\rightarrow$ 현재 시도 점수 2배
    - `dartResult[i] == '#'`일 때
        - `score[count-1] = -score[count-1]*2` $\rightarrow$ 현재 시도 점수 음수화 

