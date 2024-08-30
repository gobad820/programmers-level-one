# 알고리즘 문제 회고

- **제목(번호): 실패율**
- **카테고리: 프로그래머스**

## Time Limit

- X

## I/O Examples

| N | stages                   | result      |
|---|--------------------------|-------------|
| 5 | [2, 1, 2, 6, 2, 4, 3, 3] | [3,4,2,1,5] |
| 4 | [4,4,4,4,4]              | [4,1,2,3]   |

## Solution

### 문제 핵심 개념

#### 실패율에 대한 정의

$실패율 = \frac{해당\ 스테이지를\ 진행중인\ 사람}{해당\ 스테이지를\ 진행중인\ 사람 + 해당\ 리스트를\ 클리어한\ 사람}$

stages벡터에서 각 플레이어마다 진행중인 스테이지를 나타내며 해당 값의 범위는 1부터 N+1까지이다. N+1의 경우 모든 스테이지를 클리어한 것으로 간주한다.

----

#### 실패율을 정렬

실패율을 정렬할 때 동등 실패율이면 스테이지 수를 기준으로 정렬시킨다.

```c++
bool comp(const std::pair<int, double>& a, const std::pair<int, double>& b){
    if(a.second == b.second){ // 비교 실패율이 동일하면
        return a.first < b.first; // 스테이지 수가 작은 것부터 우선하여 정렬한다.
    }
    return a.second > b.second; // 실패율이 큰것부터 우선하여 정렬한다.
}
```

----

### 내가 고민 못 했던 부분

**C++에서 멍청하게도 int / int를 하고 왜 0이 나오지 고민하고 있었다.**

또한 men in progress(진행 중인 플레이어) 와 completed men(클리어한 플레이어)를 구현할 때 `std::unordered_map<int, double>`을 사용했는데 그냥 2중 
for문 1~N+1까지 돌면서 해당 stage에 따른 숫자와 동일하면 men in progress 그보다 크거나 같으면 completed men에 추가하면 된다. 무엇이 더 좋은 알고리즘일까?
```c++
for(int i = 1 ; i <= N+1 ; i++){
    double progress_men = 0.0;
    double completed_men = 0.0;
    for(const auto& stage : stages){
        if(stage == i) progress_men++;
        if(stage >= i) completed_men++;
    }
}
```
