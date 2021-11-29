#include "../includes/Tranzactie.h"
#include <iostream>
#include <fstream>
#include <random>
#include <regex>

Tranzactie &Tranzactie::operator=(const Tranzactie &copie) {
    destinatar = copie.destinatar;
    IBAN_destinatar = copie.IBAN_destinatar;
    type = copie.type;
    suma_trimisa = copie.suma_trimisa;
    data = copie.data;
    return *this;
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

Tranzactie::Tranzactie(std::string &destinatar, std::string &ibanDestinatar, std::string type,
                       float sumaTrimisa, const data_str &data) : destinatar(destinatar),
                                                                  IBAN_destinatar(ibanDestinatar), type(type),
                                                                  suma_trimisa(sumaTrimisa), data(data) {}
