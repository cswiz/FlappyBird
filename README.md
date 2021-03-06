# FlappyBird

## 제작 동기 및 배경

게임 서버 인턴을 하면서 게임 클라이언트와 엔진에도 관심을 가지게 되었다. 유명한 2D 캐주얼 게임인 FlappyBird의 리소스를 구하여 처음부터 끝까지 직접 개발해 봄으로써 게임 클라이언트 및 엔진 개발의 첫 발을 내딛고자 하였다.

## 설치

### Simple DirectMedia Layer

본 프로그램은 멀티미디어 라이브러리로 SDL을 사용한다. SDL이 설치되어 있지 않다면 [여기](https://wiki.libsdl.org/Installation)에서 안내된 대로 설치해주도록 하자.

### 다운로드

SDL이 설치되었다면 본 프로그램의 소스코드를 다운로드 받고 게임 디렉토리로 이동한다.

    $ git clone https://github.com/cswiz/FlappyBird.git
    $ cd FlappyBird

### 빌드 및 실행

게임을 빌드하고 실행한다.

    $ make
    $ ./FlappyBird

## 프로젝트 제약 조건 및 달성 목표

본 프로젝트를 진행하며 이루고자 하는 목표가 몇가지 있다. 또한 학습 효과의 최대화를 위해 스스로 내건 제약 조건도 몇가지 있는데 하나씩 살펴보자.

- 별도의 게임 엔진을 사용하지 않는다.
- 게임 클라이언트 내부 동작 원리를 익혀본다.

FlappyBird는 매우 유명한 게임이라, 게임 개발 입문자를 위한 강좌가 꽤 많은 편이다. 자료조사 도중 보게 된 대부분의 강좌에서는 2D 게임 개발에 많이 쓰이는 Unity 게임 엔진을 이용하였는데, 엔진을 활용하여 단 몇시간 만에 기본적인 기능 개발을 완료하는 모습을 볼 수 있었다. 그러나 본 프로젝트에서는 필요한 것들을 일일이 직접 구현해보고, 일반적인 게임 클라이언트의 내부 동작 원리를 깨닫는 데에 초점을 맞춘다. 따라서 게임 엔진의 도움을 받지 않는다.

- Simple DirectMedia Layer를 익혀본다.
- 순수 C언어로만 개발한다. (C99 표준)
- 객체지향 패러다임을 익혀본다.

게임 업계의 표준어가 C/C++이라는 것을 부인하기는 힘들 것이다. 따라서 본 프로젝트에서는 멀티미디어 라이브러리로 C언어로 작성된 Simple DirectMedia Layer(이하 SDL)를 채택하였다. SDL이 크로스 플랫폼 라이브러리이기 때문에 주요 플랫폼으로의 이식이 쉽다는 것도 큰 장점으로 작용했다.

SDL을 사용하는 대부분의 오픈소스 프로젝트는 C++를 사용한다. 그럼에도 불구하고 순수 C언어 사용을 제약조건으로 정한 이유는 다음과 같다. 우선 GitHub에 있는 수많은 FlappyBird 클론 중 순수 C언어로 작성된 클론이 많지 않았다. 그리고 C언어에 대한 이해를 좀 더 깊이있게 만들고 싶었다.

마지막 이유가 가장 중요한데, 순수 C언어로 객체지향 프로그래밍을 시도해보고 싶었다. 최근에 "객체지향의 사실과 오해"라는 책을 읽었는데, 객체지향은 프로그래밍 언어에 종속되는 것이 아닌 하나의 사고 방식, 어떤 패러다임을 의미한다는 내용이 굉장히 인상 깊었다. 그래서 역발상으로 객체지향에 대한 문법적 설탕을 제공하지 않는 순수 C언어로 객체지향 프로그래밍을 시도하게 된 것이다. 일부러 객체지향의 주요 요소에 대한 직접적인 지원이 없는 언어로 객체지향을 시도해 봄으로써 역으로 진정한 객체지향이 무엇인가를 드러내려는 일종의 내 나름의 시도라고 할 수 있다.

- 별도의 물리 엔진을 사용하지 않는다.
- 게임에 필요한 수학과 물리를 익혀본다.

겉으로 드러나는 게임 서버와 클라이언트 개발의 가장 큰 차이점 중 하나는 가시성, 즉 눈에 보이는지의 여부인 것 같다. 게임 클라이언트 내 월드에는 수많은 오브젝트들이 움직이며 서로 상호작용한다. 따라서 필연적으로 수학과 물리 지식이 필요할 것으로 예상된다. FlappyBird는 오브젝트의 개수가 많지도 않고, 복잡한 운동이 개입하지도 않는다. 따라서 별도의 물리 엔진을 사용하지 않고, 필요한 수학과 물리를 직접 구현해보고 익히도록 한다.

## 설계

프로그램의 전체적인 구조와 설계를 다이어그램으로 나타내보았다.

![Diagram](https://user-images.githubusercontent.com/43113225/173884494-788ff55a-4886-4c34-b204-58a338dd4a7a.png)

## 주요 로직

### 객체지향

#### 추상화

#### 캡슐화

#### 상속

#### 다형성

### 수학 및 물리

#### 오브젝트 이동

#### 자유 낙하

#### 충돌 감지
