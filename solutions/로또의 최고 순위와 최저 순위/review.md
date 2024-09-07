# 알고리즘 문제 회고

- **제목(번호): [로또의 최고 순위와 최저 순위](https://school.programmers.co.kr/learn/courses/30/lessons/77484#fn1)**
- **카테고리: 프로그래머스**
- **회고 날짜: 2024. 8. 31.**

## Time Limit

- X

## I/O Examples

| lottos                | win_nums                 | result |
|-----------------------|--------------------------|--------|
| [44, 1, 0, 0, 31, 25] | [31, 10, 45, 1, 6, 19]   | [3, 5] |
| [0, 0, 0, 0, 0, 0]    | [38, 19, 20, 40, 15, 25] | [1, 6] |
| [45, 4, 35, 20, 3, 9] | [20, 9, 3, 45, 4, 35]    | [1, 1] |

## Solution

- [👨‍💻제출 코드](solution.cc)

### 문제 핵심 개념

**로또의 순위 <a id="lotto-rank"></a>**

| 순위    | 당첨 내용        |
|-------|--------------|
| 1     | 6개 번호가 모두 일치 |
| 2     | 5개 번호가 일치    |
| 3     | 4개 번호가 일치    |
| 4     | 3개 번호가 일치    |
| 5     | 2개 번호가 일치    |
| 6(낙첨) | 그 외          |

#### 0의 개수와 당첨된 숫자 개수 구하기

- 0의 개수를 먼저 알아야 한다.
    - `std::count(lottos.begin(), lottos.end(), 0);`
    - **`std::count` 함수를 처음 알았다!**
- match_number; 당첨된 숫자의 개수를 알아야 한다.
    - ```c++
      std::size_t match_number = 0;
      for(const auto& win_num : win_nums){
        if(std::count(lottos.cbegin(), lottos.cend(), win_num){
          match_number++;
        }
      }

- 최고 순위는 보이지 않는 숫자(0)이 모두 당첨될 경우
- 최저 순위는 보이지 않는 숫자(0)이 모두 낙첨될 경우

#### 지워진 숫자도 없고 당첨된 숫자도 없을 때

- 기존의 로또 순위를 정할때 `std::array<int, 6> lotto_rank {6,5,4,3,2,1}` 배열을 이용했다.
- 또한 순위를 정할 때 `answer.emplace(rank[match_numbers+zero_numbers-1]);`로 구했다.
- 하지만 이럴 경우 0도 없고 하나 존재하고 match_number가 0인 상황에서 예외가 발생한다.
- `lottos = {1,2,3,4,5,7}; win_numbs = {11,12,13,14,15,16};`일 때 인덱스가 -1이 된다.
- 따라서 `if(match_number+zero_numbers == 0) answer.emplace_back(6);` 으로 예외 처리를 해주어야 한다! 

## [Claude.ai](https://claude.ai/)에게 부탁한 최적화 코드

```c++
std::vector<int> solution2(std::vector<int> lottos, std::vector<int> win_nums) {
    std::sort(win_nums.begin(), win_nums.end());

    std::size_t zero_count = std::count(lottos.cbegin(), lottos.cend(), 0);
    std::size_t match_count = std::count_if(lottos.cbegin(), lottos.cend(), [&win_nums](int num) {
        return num != 0 && // 동생이 낙서하지 않은 수 중에서
               std::binary_search(win_nums.cbegin(), win_nums.cend(), num); // win_nums 중에 lotto의 원소가 존재하는지 
                                                                            // binary-search
    });

    // 람다식 get_rank, 인자를 unsigned long count로 받고 return은 int로 한다. 
    // 따라서 static_cast<int>로 감싼 std::min(7-count, 6UL)을 리턴한다.
    auto get_rank = [](std::size_t count) -> int { return static_cast<int>(std::min(7 - count, 6UL)); }; 
    // UL = unsigned long
    return {get_rank(match_count + zero_count), get_rank(match_count)};
}
``` 

- 람다식을 사용하여 코드 길이를 파격적으로 줄인것을 확인할 수 있다.
- 특히 `std::size_t match_count = std::count_if(lottos.cbegin(), lottos.cend(), [&lottos](int num) {
        return num != 0 &&
               std::binary_search(lottos.cbegin(), lottos.cend(), num);
    });` 라인이 인상적이었다.
- count함수는 사용했었지만 `std::count_if(InputIt first, InputIt last, UnaryPred p)`는 처음 봤었다.

### C++의 std::for_each
- `<algorithm>`에 포함
- `std::for_each`문은 범위 내 원소들에 대해 함수를 실행시킨다.
- `Function std::for_each(InputIterator first, InputIterator last, Function fn);`
- fn 함수의 리턴값은 무시된다.
- `transform`함수와의 관계
  - `transform`함수는 원본 원소를 수정된다.(함수의 리턴값으로 변경된다.) 또한 순차적으로 진행된다는 보장도 없다.
  - `std::for_each`의 경우 원본 원소를 유지한다. 순차적으로 진행된다.

- 예시 코드
  - ```c++
    #include <algorithm>
    #include <vector>
    #include <iostream>
    
    void myfunction(int i){
      std::cout << ' ' << i;
    }
    
    struct myclass {
      // void operator<<(const auto& a) 와 같이 괄호에 대한 연산자에 대해서 함수 정의
      void operator()(int i) {std::cout << ' ' << i;}
    }myobject; 
    // myobject(5);를 하면 5가 출력된다.
    
    int main(){
      std::vector<int> myvector;
      myvector.emplace_back(10);
      myvector.emplace_back(20);
      myvector.emplace_back(30);
    
      // 일반적인 함수 포인터 전달
      std::cout << "myvector contains:";
      std::for_each(myvector.cbegin(), myvector.cend(), myfunction);
      std::cout << '\n';
    
      // Functor 를 전달
      std::cout << myvector contains:";
      std::for_each(myvector.cbegin(), myvector.cend(), myobject);
      std::cout << '\n';
    
      // 람다 함수를 전달
      std::cout << "myvector contains:";
      std::for_each(myvector.cbegin(), myvector.cend(), [](const int& n) {std::cout << ' ' << '\n';});
      std::cout << '\n';
    
      return 0;
    }

[출처: 모두의 코드](https://modoocode.com/260)

### C++의 람다식($\lambda$)
- 람다식의 구조
  1. captures
  2. tparms
  3. t-requires
  4. front-attr
  5. params
  6. apecs
  7. exception
  8. back-attr
  9. trailing-type
  10. requires
  11. body

- 람다식의 구성
  - `[my_mode] (int v_) -> int { return v_ % my_mod; }`
  - \[]: introducer capture(개시자)
    - 안에 어떤 외부 변수를 써 넣는다면 람다 함수가 이를 캡쳐해서 이 변수를 람다 내부에서 이용할 수 있게 한다. 
  - (): parameters(인자)
    - **인자가 없는 경우 괄호는 생략할 수 있다!**
    - 람다가 실행시 받을 인자들을 넣는다. 여기서는 실제로 함수에서 사용하는 인자 리스트와 동일하게 넣어주면 된다. 
  - -> int: return type(예시에서는 int 타입으로 하였다.)(**void type인 경우 생략 가능**)
  - {}: statement

- 람다식의 예제
  - 모든 벡터 원소의 곱을 구하는 코드
    - 람다를 사용하지 않은 코드
      - ```c++
        vector<int>::const_iterator iter = cardinal.begin();
        vector<int>::const_iterator iter_end = cardinal.end();
        int total_elements = 1;
        while (iter != iter_end) {
          total_elements *= *iter;
          ++iter;
        }
    - 람다를 사용한 코드
      - ```c++
        int total_elements = 1;
        std::for_each(cardinal.cbegin(), cardinal.cend(), [&total_elements](int i) { total_elements *= i; }); 
        // cardianl을 순회하면서 [&total_elements]를 캡쳐, total_elements를 cardinal의 원소들을 하나씩 곱해간다.

- 람다식과 클로저
  -  `[my_mod](int v_) -> int { return v_ % my_mod; }`와 같이 람다식을 수행
  - 런타임에서는 이름은 없지만 메모리 상에 암시적으로 클로저라는 객체가 생성된다.
  - 클로저 객체는 함수 객체 처럼 행동한다.
  - `[]() { cout << "checkIngredient" << endl; }()` 코드를 실행하였다면 어떤 결과가 나올까?
  - 캡처도 없고 인자도 없고 리턴 값도 없어서 그냥 foo가 출력될것이다.
  - `[](int v) { cout << v << "*6=" << v * 6 << endl; }(7);` 이 코드는 어떠한가?
  - 7이라는 인자를 넣었으므로 `7*6=42`가 출력될 것이다.

C++의 람다식은 처음이지만 앞으로 조금 더 깊게 다룰 필요가 있어보인다!