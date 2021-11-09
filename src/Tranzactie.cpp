#include "../includes/Tranzactie.h"
#include <iostream>
#include <fstream>
#include <random>
#include <regex>

Tranzactie &Tranzactie::operator=(const Tranzactie &copie) {
    this->destinatar = copie.destinatar;
    this->IBAN_destinatar = copie.IBAN_destinatar;
    this->type = copie.type;
    this->suma_trimisa = copie.suma_trimisa;
    this->data = copie.data;
    return *this;
}

void Tranzactie::setDestinatar(const std::string &destinatar_copie) {
    Tranzactie::destinatar = destinatar_copie;
}

void Tranzactie::setSumaTrimisa(unsigned int sumaTrimisa) {
    suma_trimisa = sumaTrimisa;
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
    os <<"\n\t\tData: " << tranzactie.data.zi << "." << tranzactie.data.luna << "."<< tranzactie.data.an;
    os <<"\n\t\tOra: " << tranzactie.data.ora <<"\n\n";
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

void Tranzactie::writeInFile(std::fstream &file) {
    file<<destinatar<<";"<<IBAN_destinatar<<";"<<suma_trimisa<<";";
    file<<data.zi<<";"<<data.luna<<";"<<data.an<<";"<<data.ora<<";"<<type<<"\n";
}

void Tranzactie::setData(const data_str &data_cp) {
    Tranzactie::data = data_cp;
}
