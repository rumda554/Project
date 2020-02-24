// origin by https://gist.github.com/iikuy/8115191

#include "pch.h"
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <string>
#include <atomic>

// 생산자 - 소비자 모델 

// 스레드 공유 전역 변수들
std::mutex mx;
std::condition_variable cv;	// 조건변수 - 특별한 조건이 만족되었을 경우 스레드가 동작 가능하게 해주는 유저 영역 동기화 객체. 결국 스레드 간 의 동기화를 가능하게 해준다.
std::queue<int> q;

bool finished = false;

// 생산자는 락을 걸고 입력 받은 수n 만큼 큐에 데이터를 넣는다.
void producer(int n)
{
	for (int i = 0; i < n; ++i)
	{
		std::lock_guard<std::mutex> lock(mx);	// 락을 건다
		q.push(i);
		std::cout << "pushing " << i << std::endl;
	}
	cv.notify_all();	// 락을 풀고 신호를 보낸다.

	std::lock_guard<std::mutex> lock(mx);
	finished = true;
	cv.notify_all();
}

// 소비자는 신호를 기다리면서 큐가 빌때까지 데이터를 꺼낸다.
void consumer()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(mx); // 락을 건다.
		cv.wait(lock, [] {return finished || !q.empty(); }); // 신호를 기다면서 신호가 오면 락을 푼다.

		while (!q.empty())
		{
			std::cout << "consuming " << q.front() << std::endl;
			q.pop();
		}

		if (finished)
			break;
	}
}

int main()
{
	std::thread t1(producer, 10);
	std::thread t2(consumer);
	t1.join();	// wait for the t1 thread to finish.
	t2.join();	// wait for the t2 thread to finish.
	std::cout << "finished!" << std::endl;
}