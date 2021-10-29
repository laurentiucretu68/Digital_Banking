#include "../includes/Messages.h"
#include <iostream>
#include <fstream>
#include "../includes/rlutil.h"

const std::string &Messages::getDestinatar() const {
    return destinatar;
}

void Messages::setDestinatar(const std::string &destinatar_copie) {
    Messages::destinatar = destinatar_copie;
}

const std::string &Messages::getMesaj() const {
    return mesaj;
}

void Messages::setMesaj(const std::string &mesaj_copie) {
    Messages::mesaj = mesaj_copie;
}

unsigned short Messages::getZi() const {
    return zi;
}

void Messages::setZi(unsigned short zi_copie) {
    Messages::zi = zi_copie;
}

unsigned short Messages::getLuna() const {
    return luna;
}

void Messages::setLuna(unsigned short luna_copie) {
    Messages::luna = luna_copie;
}

unsigned short Messages::getAn() const {
    return an;
}

void Messages::setAn(unsigned short an_copie) {
    Messages::an = an_copie;
}

unsigned short Messages::getOra() const {
    return ora;
}

void Messages::setOra(unsigned short ora_copie) {
    Messages::ora = ora_copie;
}

Messages &Messages::operator=(const Messages &copie) {
    this->destinatar = copie.destinatar;
    this->mesaj = copie.mesaj;
    this->tip_mesaj = copie.tip_mesaj;
    this->zi = copie.zi;
    this->luna = copie.luna;
    this->an = copie.an;
    this->ora = copie.ora;
    return *this;
}

unsigned short Messages::getTipMesaj() const {
    return tip_mesaj;
}

void Messages::setTipMesaj(unsigned short tipMesaj_copie) {
    tip_mesaj = tipMesaj_copie;
}

void Messages::writeInFile(std::fstream &file, const Messages &mesaj) {
    file<<mesaj.destinatar<<";"<<mesaj.tip_mesaj<<";"<<mesaj.mesaj<<";";
    file<<mesaj.zi<<";"<<mesaj.luna<<";"<<mesaj.an<<";"<<mesaj.ora<<"\n";
}

std::ostream &operator<<(std::ostream &os, const Messages &messages) {
    rlutil::setColor(3);
    os<< "\n\t* Mesaj de tip ";
    if (messages.tip_mesaj == 1)
        os << "warning";
    if (messages.tip_mesaj == 2)
        os << "advice";
    if (messages.tip_mesaj == 3)
        os << "notification";

    os<<" ("<< messages.getZi()<<"."<<messages.getLuna()<<"."<<messages.getAn()<<" ora "<<messages.getOra()<<"):\n";
    rlutil::setColor(6);
    os<<"\t\t"<<messages.getMesaj()<<"\n\n";
    return os;
}
