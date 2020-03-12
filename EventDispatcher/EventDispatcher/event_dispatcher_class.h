#ifndef __EVENT_DISPATCHER_CLASS_H__
#define __EVENT_DISPATCHER_CLASS_H__

#include <iostream>
#include <map>
#include <functional>


//监听事件
class EventDispatcher
{
	//成员定义
public:
	using _Callback = std::function<bool(void*)>;

	//函数定义
public:
	virtual~EventDispatcher() {}
	static EventDispatcher* getInstance()
	{
		return instance_ = new EventDispatcher();
	}
	
	//事件监听
public:
	virtual void addCustomEventListener(std::string item_identify, _Callback callback)
	{
		//查找对象
		auto iter = event_items_.find(item_identify);

		//不存在
		if (iter == event_items_.end())
			event_items_.insert(std::make_pair(item_identify, callback));
		else
			iter->second = callback;
	}

	virtual void removeCustomEventListener(std::string remove_identify)
	{
		auto iter = event_items_.find(remove_identify);
		if (iter != event_items_.end())
			event_items_.erase(iter);
	}

	virtual void dispatchCustomEvent(std::string item_identify, void* Arg = nullptr)
	{
		auto iter = event_items_.find(item_identify);
		if (iter == event_items_.end())
		{
			std::logic_error("Cannot find event");
			return;
		}

		iter->second(Arg);
	}

	//函数定义
private:
	EventDispatcher() { event_items_.clear(); }

	//私有成员
private:
	static EventDispatcher*                 instance_;               //单例
	std::map<std::string, _Callback>        event_items_;            //监听对象

};


//界面通知PostMessage
//可以使用condition_variable 阻塞


#endif // !__EVENT_DISPATCHER_CLASS_H__
