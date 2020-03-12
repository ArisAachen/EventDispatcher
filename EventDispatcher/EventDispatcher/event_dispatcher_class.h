#ifndef __EVENT_DISPATCHER_CLASS_H__
#define __EVENT_DISPATCHER_CLASS_H__

#include <iostream>
#include <map>
#include <functional>


//�����¼�
class EventDispatcher
{
	//��Ա����
public:
	using _Callback = std::function<bool(void*)>;

	//��������
public:
	virtual~EventDispatcher() {}
	static EventDispatcher* getInstance()
	{
		return instance_ = new EventDispatcher();
	}
	
	//�¼�����
public:
	virtual void addCustomEventListener(std::string item_identify, _Callback callback)
	{
		//���Ҷ���
		auto iter = event_items_.find(item_identify);

		//������
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

	//��������
private:
	EventDispatcher() { event_items_.clear(); }

	//˽�г�Ա
private:
	static EventDispatcher*                 instance_;               //����
	std::map<std::string, _Callback>        event_items_;            //��������

};


//����֪ͨPostMessage
//����ʹ��condition_variable ����


#endif // !__EVENT_DISPATCHER_CLASS_H__
