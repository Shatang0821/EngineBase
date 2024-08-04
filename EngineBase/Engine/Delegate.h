#ifndef _DELEGATE_H_
#define _DELEGATE_H_

#include "../stdafx.h"

template<typename R = void,typename... Args>
class UnicastDelegate
{
private:
	std::function<R(Args...)> callback;
public:
	void Bind(std::function<R(Args...)> callback)
	{
		this->callback = callback;
	}

	template<typename T>
	void Bind(T* obj, void(T::* func)(Args...))
	{
		std::function<R(Args...)> f = [=](Args... args) { (obj->*func)(args...); };
		Bind(f);
	}

	void UnBind()
	{
		callback = nullptr;
	}

	R Execute(Args... args)
	{
		if (callback)
		{
			return callback(args...);
		}
		return R();
	}

	R operator()(Args... args)
	{
		return Execute(args...);
	}
};


template<typename... Args>
class MulticastDelegate
{
private:
	std::vector<std::function<void(Args...)>> callbacks;

public:
	void Add(std::function<void(Args...)> callback)
	{
		for(auto it = callbacks.begin(); it != callbacks.end(); ++it)
		{
			if (it -> target<void(Args...)>() == callback.target<void(Args...)>())
			{
				return;
			}
		}
		callbacks.push_back(callback);
	}

	template<typename T>
	void Add(T* obj, void(T::* func)(Args...))
	{
		std::function<void(Args...)> callback = [=](Args... args) { (obj->*func)(args...); };
		Add(callback);
	}

	void Remove(std::function<void(Args...)> callback)
	{
		for(auto it = callbacks.begin(); it != callbacks.end(); ++it)
		{
			if (it -> target<void(Args...)>() == callback.target<void(Args...)>())
			{
				callbacks.erase(it);
				break;
			}
		}
	}

	template<typename T>
	void Remove(T* obj, void (T::* func)(Args...)) {
		std::function<void(Args...)> callback = [=](Args... args) { (obj->*func)(args...); };
		Remove(callback);
	}

	void BroadCast(Args... args) {
		for (auto& callback : callbacks)
		{
			callback(args...);
		}
	}

	void operator()(Args... args){
		BroadCast(args...);
	}

#define AddDynamic(obj,func) Add(obj,func)
#define RemoveDynamic(obj,func) Remove(obj,func)
#define AddLambda(lambda) Add(lambda)
#define RemoveLambda(lambda) Remove(lambda)
};

//�}�N�����g���ăf���Q�[�g�N���X��錾����

/*----------- ���j�L���X�g�f���Q�[�g -----------*/
//����������A�߂�l�̂���ꍇ
#define DECLARE_MULTI_PARAM_WITH_RETURN_UNICAST_DELEGATE_CLASS(Name, R, ...) class Name : public UnicastDelegate<R,__VA_ARGS__> {};
//�������Ȃ��C�߂�l�̂���ꍇ
#define DECLARE_NO_PARAM_WITH_RETURN_UNICAST_DELEGATE_CLASS(Name, R) class Name : public UnicastDelegate<R> {};

//����������C�߂�l���Ȃ��ꍇ
#define DECLARE_MULTI_PARAM_UNICAST_DELEGATE_CLASS(Name, ...) class Name : public UnicastDelegate<void,__VA_ARGS__> {};
//�������Ȃ��C�߂�l���Ȃ��ꍇ
#define DECLARE_NO_PARAM_UNICAST_DELEGATE_CLASS(Name) class Name : public UnicastDelegate<void> {};

/*----------- �}���`�L���X�g�f���Q�[�g -----------*/
//����������ꍇ
#define DECLARE_MULTI_PARAM_MULTICAST_DELEGATE_CLASS(Name, ...) class Name : public MulticastDelegate<__VA_ARGS__> {};
//�������Ȃ��ꍇ
#define DECLARE_NO_PARAM_MULTICAST_DELEGATE_CLASS(Name) class Name : public MulticastDelegate<> {};

#endif // !_DELEGATE_H_
