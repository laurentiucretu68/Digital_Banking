#pragma once
#include <iostream>
#include <random>
#include <thread>

struct data_str{
    unsigned short zi;
    unsigned short luna;
    unsigned short an;
    unsigned short ora;
};

class Tranzactie{
    std::string destinatar;
    std::string IBAN_destinatar;
    std::string type;
    unsigned int suma_trimisa;
    data_str data;

public:

    Tranzactie& operator=(const Tranzactie& copie);

    ~Tranzactie()= default;

    void setDestinatar(const std::string &destinatar_copie);

    void setSumaTrimisa(unsigned int sumaTrimisa);

    void setData(const data_str &data);

    void setIbanDestinatar(const std::string &ibanDestinatar_copie);

    void setType(const std::string &type_copie);

    friend std::ostream &operator<<(std::ostream &os, const Tranzactie &tranzactie);

    bool checkPatternIBAN(const std::string &IBAN);

    void writeInFile(std::fstream &file);

};
