# 알고리즘 문제 회고

- **제목(번호): [둘만의 암호](https://school.programmers.co.kr/learn/courses/30/lessons/155652)**
- **카테고리: 프로그래머스**
- **회고 날짜: 2024. 9. 1.**

## Time Limit

- X

## I/O Examples

| S       | skip   | index | result  |
|---------|--------|-------|---------|
| "aukks" | "wbqd" | 5     | "happy" |

## Solution

- [👨‍💻제출 코드](solution.cc)

### 문제 핵심 개념

- 시저 암호 문제라고 쉽게 접근했지만 생각보다 허를 찔린 느낌이었다.
- skip을 처리하는 것이 생각보다 까다로웠다.

#### skip 알파벳의 처리 & 인덱스 넘어갈때 예외 처리

- skip 문자열에 해당하는 알파벳은 생략하고 다음 알파벳으로 넘기면서 암호를 만든다.
- 먼저 skip 문자열을 생략하고 새로운 alphabet 벡터를 생성한다.
- ```c++
    std::vector<char> alphabet;
    char c = 'a';
    while(c <= 'z'){
       alphabet.emplace_back(c);
       c = static_cast<char>(c++); 
    }
- 그 후 주어진 입력 문자열 s를 순회하면서 index만큼 알파벳을 돌렸을 때 결과로 바꾸어 준다.
- 이 때 마지막 알파벳(z가 스킵에 포함이 될 수 있으므로)을 넘어가는 경우를 처리해 주어야 한다.
- ```c++
   for (auto &item: s) {
        item = alphabet_vector[(std::find(alphabet_vector.begin(), alphabet_vector.end(), item) 
                                - std::begin(alphabet_vector) + index) % alphabet_vector.size()];
    } 
  

### 코드 복습
- 찾는 요소의 인덱스를 얻기 위해서 아래와 같이 코드를 작성할 수 있다.
- `auto it = std::find(vec.begin(), vec.end(), find_item) - vec.begin();`
- `find`함수도 `iterator`를 리턴하므로 인덱스를 구할 수 있다.





