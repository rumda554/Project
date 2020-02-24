#pragma once
namespace RumdaLib
{
	template<typename T>
	class CSingleton
	{
	private:
		static T* _instance;

	protected:
		CSingleton() {}
		virtual ~CSingleton() {}

		static void Instance()
		{
			if (_instance == nullptr)
			{
				_instance = new T;
			}
		}

		static T* GetInstance()
		{
			return (_instance == nullptr) ? nullptr : _instance;
		}

	private:
		void operator delete(void* p)
		{
			delete _instance;
		}
	};

	template<typename T> T* CSingleton<T>::_instance = nullptr;
}