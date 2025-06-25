#pragma once
#include <string>
#include <vector>


class Console
{
public:
    enum class MessageType
    {
        Info,
        Warning,
        Error
    };

    typedef struct
    {
        MessageType type;
        std::string title;
        std::string content;
        std::string time;
    } Message;

    static std::vector<Message> messages;

public:
    static void AddMessage(Message message);
    static void Update();
};

