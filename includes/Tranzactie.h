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
    std::string destinatar{};
    std::string IBAN_destinatar{};
    std::string type{};
    float suma_trimisa{};
    data_str data{};

public:
    Tranzactie() = default;

    Tranzactie(std::string &destinatar, std::string &ibanDestinatar, std::string type,
               float sumaTrimisa, const data_str &data);

    Tranzactie& operator=(const Tranzactie& copie);

    ~Tranzactie()= default;

    friend std::ostream &operator<<(std::ostream &os, const Tranzactie &tranzactie);

    static bool checkPatternIBAN(const std::string &IBAN);

    void writeInFile(std::fstream &file);
};
