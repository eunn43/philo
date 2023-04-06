# philosophers
<br/>

**  입력이 들어왔을 때 철학자가 최대한 죽지않도록 실행
```
./philo 4 410 200 200
```
<br/>

* 철학자가 하는 행동 Eating / Sleeping / Thinking

* num_of_philo time_to_die time_to_eat time_to_sleep [num_of_times_each_philo_must_eat] (단위 : 밀리초)

* 철학자 수만큼의 포크가 존재 ➡️ 2개의 포크가 있어야 Eating

<br/>

<img width="463" alt="result" src="https://user-images.githubusercontent.com/69659340/230282407-f50c32e1-9b9a-4769-ae13-72274189cbe9.png">

<br/>

---

<br/>

* 멀티스레드 : 하나의 프로세스 안에서 두 개 이상의 스레드를 갖는다

* 스레드끼리 스택영역을 제외한 메모리를 모두 공유하므로 데이터레이스(공유 자원에 동시에 접근)가 발생할 수 있다.

* 동시 접근을 막기 위해 mutex를 사용한다 -> 상호배제

