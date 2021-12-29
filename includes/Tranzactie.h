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
    friend class TranzactieBuilder;

public:
    Tranzactie() = default;

    Tranzactie(std::string &destinatar, std::string &ibanDestinatar, std::string type,
               float sumaTrimisa, const data_str &data);

    Tranzactie& operator=(const Tranzactie&) = default;

    ~Tranzactie()= default;

    friend std::ostream &operator<<(std::ostream &os, const Tranzactie &tranzactie);

    static bool checkPatternIBAN(const std::string &IBAN);

    void writeInFile(std::fstream &file);
};

class TranzactieBuilder{
    Tranzactie tran;

public:
    TranzactieBuilder() = default;

    TranzactieBuilder& destinatar(const std::string& destinatar_){
        tran.destinatar = destinatar_;
        return  *this;
    }

    TranzactieBuilder& IBAN(const std::string& IBAN_){
        tran.IBAN_destinatar = IBAN_;
        return *this;
    }

    TranzactieBuilder& type(const std::string& type_){
        tran.type = type_;
        return *this;
    }

    TranzactieBuilder& suma(float suma_){
        tran.suma_trimisa = suma_;
        return *this;
    }

    TranzactieBuilder& data(data_str& data_){
        tran.data = data_;
        return *this;
    }

    Tranzactie build(){
        return tran;
    }
};