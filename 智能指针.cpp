#include<iostream>
#include<mutex>
#include<thread>
#include<memory>
using namespace std;
//auto_ptr智能指针实现
template<class T>
class autoptr
{
public:
	autoptr(T *ptr)
		:_ptr(ptr)
	{}
	~autoptr()
	{
		if (_ptr)
		{
			delete _ptr;
			cout << "~autoptr delete" << endl;
		}
	}
	//管理权转移问题
	autoptr(autoptr<T>& sp)//拷贝构造
		:_ptr(sp._ptr)
	{
		sp._ptr = nullptr;
	}
	autoptr<T>& operator=(autoptr<T>& sp)//赋值
	{
		if (this != &sp)
		{
			//释放原有资源
			if (_ptr)
			{
				delete _ptr;
			}
			//管理权转移
			_ptr = sp._ptr;
			sp._ptr = nullptr;
		}
		return *this;
	}
	T& operator*()
	{
		return *_ptr;
	}
	T *operator->()
	{
		return _ptr;
	}
private:
	T *_ptr;
};
void test()
{
	int *sp = new int(10);
	autoptr<int> ptr(sp);
	cout << *ptr << endl;
}
//unique_ptr智能指针的实现
template<class T>
class uniqueptr
{
public:
	uniqueptr(T *ptr)
		:_ptr(ptr)
	{}
	~uniqueptr()
	{
		if (_ptr)
		{
			delete _ptr;
		}
	}
	T& operator*()
	{
		return *_ptr;
	}
	T* operator->()
	{
		return _ptr;
	}
	//防拷贝和赋值，所以把拷贝和赋值操作置为delete
	uniqueptr(const uniqueptr<T>& up) = delete;
	uniqueptr& operator=(const uniqueptr<T>& up) = delete;
private:
	T *_ptr;
};
//shared_ptr智能指针实现
template<class T>
class sharedptr
{
public:
	sharedptr(T *ptr,deletor del)
		:_ptr(ptr)
		, _usecount(new int(1))
		, _mtx(new mutex)
		, _del(del)
	{}
	~sharedptr()
	{
		//引用计数自减
		if (sunref() == 0)
		{
			del(_ptr);
			delete _usecount;
			delete _mtx;
		}
	}
	sharedptr(const sharedptr<T> &sp)//拷贝
		:_ptr(sp._ptr)
		, _usecount(sp._usecount)
		, _mtx(sp._mtx)
	{
		addref();
	}
	sharedptr& operator=(const sharedptr<T>& sp)
	{
		if (_ptr != sp._ptr)
		{
			if (sunref() == 0)
			{
				delete _ptr;
				delete _usecount;
				delete _mtx;
			}
			//赋值
			_ptr = sp._ptr;
			_usecount = sp._usecount;
			_mtx = sp._mtx;
			addref();
		}
		return *this;
	}
	int getusecount()
	{
		return *_usecount;
	}
	int addref()
	{
		_mtx->lock();
		++(*_usecount);
		_mtx->unlock();
		return *_usecount;
	}
	int sunref()
	{
		_mtx->lock();
		--(*_usecount);
		_mtx->unlock();
		return *_usecount;
	}
private:
	T* _ptr;
	int *_usecount;//引用计数
	mutex *_mtx;
	deletor _del;
};
int main()
{
	test();
	system("pause");
	return 0;
}