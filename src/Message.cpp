#include "../includes/Message.h"
#include <iostream>
#include "../libraries/rlutil.h"

#define setCyan rlutil::setColor(3)
#define setBrown rlutil::setColor(6)


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
    destinatar = copie.destinatar;
    mesaj = copie.mesaj;
    tip_mesaj = copie.tip_mesaj;
    data = copie.data;
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
    setCyan;
    os<< "\n\t* Mesaj de tip ";
    if (messages.tip_mesaj == 1)
        os << "warning";
    if (messages.tip_mesaj == 2)
        os << "advice";
    if (messages.tip_mesaj == 3)
        os << "notification";

    os<<" ("<< messages.data.zi<<"."<<messages.data.luna<<"."<<messages.data.an<<" ora "<<messages.data.ora<<"):\n";
    setBrown;
    os<<"\t\t"<<messages.getMesaj()<<"\n\n";
    return os;
}

void Message::setData(const data_str_mess &data_cp) {
    Message::data = data_cp;
}

Message::Message(std::string &destinatar, std::string &mesaj, unsigned short tipMesaj,
                 const data_str_mess &data) : destinatar(destinatar), mesaj(mesaj), tip_mesaj(tipMesaj), data(data) {}
