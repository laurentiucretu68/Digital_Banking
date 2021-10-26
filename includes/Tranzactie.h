#pragma once
#include <iostream>
#include <random>
#include <thread>

class Tranzactie{
    std::string destinatar;
    std::string IBAN_destinatar;
    std::string type;
    unsigned int suma_trimisa;
    unsigned short zi;
    unsigned short luna;
    unsigned short an;
    unsigned short ora;

public:

    Tranzactie& operator=(const Tranzactie& copie);

    ~Tranzactie()= default;

    void setDestinatar(const std::string &destinatar_copie);

    void setSumaTrimisa(unsigned int sumaTrimisa);

    void setZi(unsigned short zi_copie);

    void setLuna(unsigned short luna_copie);

    void setAn(unsigned short an_copie);

    void setOra(unsigned short ora_copie);

    void setIbanDestinatar(const std::string &ibanDestinatar_copie);

    void setType(const std::string &type_copie);

    friend std::ostream &operator<<(std::ostream &os, const Tranzactie &tranzactie);

    static bool checkPatternIBAN(const std::string &IBAN);

    static void writeInFile(std::fstream &file, const Tranzactie &tranzactie);

};
