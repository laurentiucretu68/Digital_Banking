#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime>

struct data_str_mess{
    unsigned short zi;
    unsigned short luna;
    unsigned short an;
    unsigned short ora;
};

class Message {
    std::string destinatar{};
    std::string mesaj{};
    unsigned short tip_mesaj{};
    data_str_mess data{};
    data_str_mess getDate();

public:
    Message() = default;

    Message(std::string destinatar, std::string mesaj, unsigned short tipMesaj);

    Message& operator=(const Message& copie);

    ~Message() = default;

    const std::string &getMesaj() const;

    void writeInFile(std::fstream &file);

    friend std::ostream &operator<<(std::ostream &os, const Message &messages);
};

class MessageFactory{
public:
    static Message warning(const std::string& destinatar_, const std::string& mesaj_){
        return Message(destinatar_, mesaj_, 1);
    }

    static Message advice(const std::string& destinatar_, const std::string& mesaj_){
        return Message(destinatar_, mesaj_, 2);
    }

    static Message notification(const std::string& destinatar_, const std::string& mesaj_){
        return Message(destinatar_, mesaj_, 3);
    }
};
