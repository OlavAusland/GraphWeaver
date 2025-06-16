#pragma once
#include <unordered_map>
#include <vector>

typedef void (*EventSubscriber)();

enum class EventType
{
    NewFrame,
    OnDragBegin,
    OnDragStop
};

class EventManager
{
private:
    static std::unordered_map<EventType, std::vector<EventSubscriber>> subscribers;
public:
    EventManager() = delete;

    static void Notify(EventType type);
    static void Subscribe(EventType type, EventSubscriber func);
    static void Unsubscribe(EventType type, EventSubscriber func);
};
