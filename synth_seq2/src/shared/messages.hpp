#pragma once

#include <string>
#include <variant>

struct QuitMessage {};

struct PlayMessage {};

struct StopMessage {};

struct NoteMessage
{
    int note{0};
    NoteMessage() {}
    NoteMessage(int note) : note(note) {}
};

struct IntMessage
{
    std::string key;
    int value;
    IntMessage(std::string key, int value) : key(key), value(value) {}
};

struct BoolMessage
{
    std::string key;
    bool value;
    BoolMessage(std::string key, bool value) : key(key), value(value) {}
};

struct DoubleMessage
{
    std::string key;
    double value;
    DoubleMessage() {}
    DoubleMessage(std::string key, double value) : key(key), value(value) {}
};

struct StringMessage
{
    std::string key{""};
    std::string value{""};
    StringMessage(std::string key) : key(key) {}
    StringMessage(std::string key, std::string value) : key(key), value(value) {}
};

struct EventMapMessage
{
    EventMap eventMap;
    EventMapMessage(EventMap eventMap) : eventMap(eventMap) {}
};

using Message = std::variant<
    QuitMessage,
    PlayMessage,
    StopMessage,
    NoteMessage,
    IntMessage,
    BoolMessage,
    DoubleMessage,
    StringMessage,
    EventMapMessage
>;
