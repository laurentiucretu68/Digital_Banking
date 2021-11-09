#pragma once
#include <iostream>
#include <fstream>
#include <vector>

struct data_str_mess{
    unsigned short zi;
    unsigned short luna;
    unsigned short an;
    unsigned short ora;
};

class Message {
    std::string destinatar;
    std::string mesaj;
    unsigned short tip_mesaj;
    data_str_mess data;

public:

    Message& operator=(const Message& copie);

    ~Message() = default;

    void setDestinatar(const std::string &destinatar_copie);

    const std::string &getMesaj() const;

    void setMesaj(const std::string &mesaj_copie);

    const data_str_mess &getData() const;

    void setData(const data_str_mess &data_cp);

    void setTipMesaj(unsigned short tipMesaj);

    void writeInFile(std::fstream &file);

    friend std::ostream &operator<<(std::ostream &os, const Message &messages);
};