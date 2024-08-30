# 알고리즘 문제 회고

- **제목(번호): [대충 만든 자판](https://school.programmers.co.kr/learn/courses/30/lessons/160586)**
- **카테고리: 프로그래머스**
- **회고 날짜: 2024. 8. 30.** 

## Time Limit
- X

## I/O Examples
| keymap | targets | result |
|--------|---------|--------|
| ["ABACD", "BCEFD"] | ["ABCD","AABB"] | [9, 4] |
| ["AA"] | ["B"] | [-1] |
| ["AGZ", "BSSS"] | ["ASA","BGZ"] | [4, 6] |

## Solution

- [👨‍💻제출 코드](solution.cc)

### 문제 핵심 개념

#### targets 중복 알파벳 제거

- targets은 `std::vector<std::string>` 중복 알파벳이 각 문자열마다 존재하여 이를 제거
- 생각한 방법은 2가지 중 제출은 ii.코드로 하였다.
    1.  `std::vector<char> alphabet`
    2.  `std::unorderd_map<char, int> alphabet`
    3.  `std::array<int, 26> alphabet` 
    - ```c++
      std::unordered_map<char, int> alphabet;
      for(const auto& target: targets){
        for(cosnt auto& c: target){
            alphabet[c] = 0;
        }
      }
    - 의문점: 결국 2중 for문을 돌아야 되는것인가? 단일 for문을 해결할 수 없을까?
      
#### 알파벳 마다 최소 누름 회수 구하기

- `std::unordered_map<char, int> alphabet`에 저장되어 있는 단일 알파벳들의 누름 횟수를 `keymap`를 통해 파악
- 또한 `keymap`에 없는 알파벳도 존재할 수 있다.
- `keymap`에서의 index 위치는 `std::find(char)`를 통해 구함.
    - ```c++
      for(const auto& [key, _] : alphabet){
            std::size_t count = 200;
            for(const auto& k: keymap){
                count = std::min(count, s.find(key)+1);
            }
            alphabet[alpha] = static_cast<int>(count);
      }
    - static cast란?
        - C++에서 일반적으로 static_cast를 포함한 다양한 캐스팅 연산자 사용을 권장  
        - `(int) count`는 C 스타일
    - `std::unordered_map`의 경우 iteration할 때
        - `for(const auto& [key, value]: unordered_map)`으로 키와 값에 쉽게 접근할 수 있다.
  

### 내가 고민 못 했던 부분


