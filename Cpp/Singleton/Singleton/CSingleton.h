#pragma once
#include "pch.h"

template<typename T>
class CSingleton
{
protected:
	CSingleton() = default;
	~CSingleton() = default;

public:
	static inline T& Instance()
	{
		return *(GetInstance()); // 깔끔한 인터페이스를 위해 제공
	}

public:

	int GetData()
	{
		return m_Data;
	}

	int SetData(int data)
	{
		m_Data = data;
	}

	static T *GetInstance()
	{
		if (nullptr == m_Instance)
		{
			m_Instance = std::make_shared<T>();
		}
		return m_Instance.get();
	}

private:
	static std::shared_ptr<T> m_Instance;
	int m_Data = 0;
};

template<typename T> std::shared_ptr<T> CSingleton<T>::m_Instance;