#include "../includes/Message.h"
#include <iostream>
#include "../includes/rlutil.h"


void Message::setDestinatar(const std::string &destinatar_copie) {
    Message::destinatar = destinatar_copie;
}

const std::string &Message::getMesaj() const {
    return mesaj;
}

void Message::setMesaj(const std::string &mesaj_copie) {
    Message::mesaj = mesaj_copie;
}

Message &Message::operator=(const Message &copie) {
    this->destinatar = copie.destinatar;
    this->mesaj = copie.mesaj;
    this->tip_mesaj = copie.tip_mesaj;
    this->data = copie.data;
    return *this;
}

void Message::setTipMesaj(unsigned short tipMesaj_copie) {
    tip_mesaj = tipMesaj_copie;
}

void Message::writeInFile(std::fstream &file) {
    file<<destinatar<<";"<<tip_mesaj<<";"<<mesaj<<";";
    file<<data.zi<<";"<<data.luna<<";"<<data.an<<";"<<data.ora<<"\n";
}

std::ostream &operator<<(std::ostream &os, const Message &messages) {
    rlutil::setColor(3);
    os<< "\n\t* Mesaj de tip ";
    if (messages.tip_mesaj == 1)
        os << "warning";
    if (messages.tip_mesaj == 2)
        os << "advice";
    if (messages.tip_mesaj == 3)
        os << "notification";

    os<<" ("<< messages.getData().zi<<"."<<messages.getData().luna<<"."<<messages.getData().an<<" ora "<<messages.getData().ora<<"):\n";
    rlutil::setColor(6);
    os<<"\t\t"<<messages.getMesaj()<<"\n\n";
    return os;
}

void Message::setData(const data_str_mess &data_cp) {
    Message::data = data_cp;
}

const data_str_mess &Message::getData() const {
    return data;
}
