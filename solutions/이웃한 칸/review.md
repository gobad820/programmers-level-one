# 알고리즘 문제 회고

- **제목(번호): [이웃한 칸](https://school.programmers.co.kr/learn/courses/30/lessons/250125)**
- **카테고리: 프로그래머스**
- **회고 날짜: 2024. 9. 7.** 

## Time Limit

- 1초

## I/O Examples

| board                                                                                               | h | w | result |
|-----------------------------------------------------------------------------------------------------|---|---|--------|
| [["blue", "red", "orange", "red"], ["red", "red", "blue", "orange"], ["blue", "orange", "red", "red"], ["orange", "orange", "red", "blue"]] | 1 | 1 | 2      |
| [["yellow", "green", "blue"], ["blue", "green", "yellow"], ["yellow", "blue", "blue"]]              | 0 | 1 | 1      |


## Solution

- [👨‍💻제출 코드](solution.cc)

### 문제 핵심 개념

#### BFS/DFS의 준비 문제

- 해당 문제는 BFS/DFS 문제 유형을 안다면 아주 쉽게 풀이할 수 있다.
- 결국 주어진 w,h 좌표값을 가지는 칸 주위 상하좌우 4칸을 탐색하고 같은 색이 몇개인지 판단하는 문제이다.

