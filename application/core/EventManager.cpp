#include "EventManager.hpp"
#include <vector> 
#include <stdio.h>
#include <unordered_map>

std::unordered_map<EventType, std::vector<EventSubscriber>> EventManager::subscribers;

void EventManager::Notify(EventType type)
{
    for(const EventSubscriber& subscriber : subscribers[type])
    {
        subscriber();
    }
}

void EventManager::Subscribe(EventType type, EventSubscriber func)
{
    subscribers[type].push_back(func);
}

void EventManager::Unsubscribe(EventType type, EventSubscriber func)
{
    for(int i = 0; i < subscribers[type].size(); i++)
    {
        if(subscribers[type][i] == func)
        {
            subscribers[type].erase(subscribers[type].begin() + i);
        }
    }
}
