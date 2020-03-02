// 페킷(mesage)를 담는 큐를 작성
#pragma once
#include <queue>

namespace RumdaLib
{
	template<typename T>
	class CMessageQueue
	{
	public:
		CMessageQueue();
		virtual ~CMessageQueue();

		void Set(int size);
		bool Push(T* message);
		T* Pop();


	private:
		std::queue<T*> _queue; // 메시지를 담을 큐
	};


	template<typename T>
	inline CMessageQueue<T>::CMessageQueue()
	{
	}

	template<typename T>
	inline CMessageQueue<T>::~CMessageQueue()
	{
		while (!_queue.empty())
		{
			T* pQueue;
			pQueue = _queue.front();
			_queue.pop();
			delete pQueue;
		}
	}

	template<typename T>
	inline void CMessageQueue<T>::Set(int size)
	{
		for (int i = 0; i < size; ++i)
		{
			_queue.push(new T);
		}
	}

	template<typename T>
	inline bool CMessageQueue<T>::Push(T* message)
	{
		_queue.push(message);
		return true;
	}

	template<typename T>
	inline T* CMessageQueue<T>::Pop()
	{
		T* pQueue;

		if (_queue.empty())
			return nullptr;

		pQueue = _queue.front();
		_queue.pop();

		return pQueue;
	}
}