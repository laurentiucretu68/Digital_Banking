#pragma once
#include <iostream>
#include <fstream>
#include <vector>

class Messages {
    std::string destinatar;
    std::string mesaj;
    unsigned short tip_mesaj;
    unsigned short zi;
    unsigned short luna;
    unsigned short an;
    unsigned short ora;

public:

    Messages& operator=(const Messages& copie);

    ~Messages() = default;

    const std::string &getDestinatar() const;

    void setDestinatar(const std::string &destinatar_copie);

    const std::string &getMesaj() const;

    void setMesaj(const std::string &mesaj_copie);

    unsigned short getZi() const;

    void setZi(unsigned short zi_copie);

    unsigned short getLuna() const;

    void setLuna(unsigned short luna_copie);

    unsigned short getAn() const;

    void setAn(unsigned short an_copie);

    unsigned short getOra() const;

    void setOra(unsigned short ora_copie);

    unsigned short getTipMesaj() const;

    void setTipMesaj(unsigned short tipMesaj);

    static void writeInFile(std::fstream &file, const Messages &mesaj);

    friend std::ostream &operator<<(std::ostream &os, const Messages &messages);
};