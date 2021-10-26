#include "../includes/Tranzactie.h"
#include "../includes/rlutil.h"
#include <iostream>
#include <fstream>
#include <random>
#include <utility>
#include <vector>
#include <chrono>
#include <regex>
#include <thread>

Tranzactie &Tranzactie::operator=(const Tranzactie &copie) {
    this->destinatar = copie.destinatar;
    this->IBAN_destinatar = copie.IBAN_destinatar;
    this->type = copie.type;
    this->suma_trimisa = copie.suma_trimisa;
    this->zi = copie.zi;
    this->luna = copie.luna;
    this->an = copie.an;
    this->ora = copie.ora;
    return *this;
}

void Tranzactie::setDestinatar(const std::string &destinatar_copie) {
    Tranzactie::destinatar = destinatar_copie;
}

void Tranzactie::setSumaTrimisa(unsigned int sumaTrimisa) {
    suma_trimisa = sumaTrimisa;
}

void Tranzactie::setZi(unsigned short zi_copie) {
    Tranzactie::zi = zi_copie;
}

void Tranzactie::setLuna(unsigned short luna_copie) {
    Tranzactie::luna = luna_copie;
}

void Tranzactie::setAn(unsigned short an_copie) {
    Tranzactie::an = an_copie;
}

void Tranzactie::setOra(unsigned short ora_copie) {
    Tranzactie::ora = ora_copie;
}

void Tranzactie::setIbanDestinatar(const std::string &ibanDestinatar_copie) {
    IBAN_destinatar = ibanDestinatar_copie;
}

void Tranzactie::setType(const std::string &type_copie) {
    Tranzactie::type = type_copie;
}

std::ostream &operator<<(std::ostream &os, const Tranzactie &tranzactie) {
    if (tranzactie.type == "sent")
        os <<"\n\t\tDestinatar: ";
    else
        os <<"\n\t\tExpeditor: ";
    os << tranzactie.destinatar;
    os <<"\n\t\tIBAN: " << tranzactie.IBAN_destinatar;
    os <<"\n\t\tSuma: ";
    if (tranzactie.type == "sent")
        os<< "-";
    os<< tranzactie.suma_trimisa;
    os<<"lei";
    os <<"\n\t\tData: " << tranzactie.zi << "." << tranzactie.luna << "."<< tranzactie.an;
    os <<"\n\t\tOra: " << tranzactie.ora <<"\n\n";
    return os;
}

bool Tranzactie::checkPatternIBAN(const std::string &IBAN) {
    if (IBAN.length() != 24)
        return false;

    std::string IBAN_copy = IBAN;
    std::transform(IBAN_copy.begin(), IBAN_copy.end(), IBAN_copy.begin(), ::toupper);
    const std::regex pattern("(RO)[0-9]{2}[A-Z]{4}[0-9]{16}");
    return std::regex_match(IBAN_copy, pattern);
}

void Tranzactie::writeInFile(std::fstream &file, const Tranzactie &tranzactie) {
    file<<tranzactie.destinatar<<";"<<tranzactie.IBAN_destinatar<<";"<<tranzactie.suma_trimisa<<";";
    file<<tranzactie.zi<<";"<<tranzactie.luna<<";"<<tranzactie.an<<";"<<tranzactie.ora<<";"<<tranzactie.type<<"\n";
}
