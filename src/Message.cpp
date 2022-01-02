#include <iostream>
#include <utility>
#include "../includes/Message.h"
#include "../libraries/rlutil.h"


const std::string &Message::getMesaj() const {
    return mesaj;
}

Message &Message::operator=(const Message &copie) {
    destinatar = copie.destinatar;
    mesaj = copie.mesaj;
    tip_mesaj = copie.tip_mesaj;
    data = copie.data;
    return *this;
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

Message::Message(std::string destinatar, std::string mesaj, unsigned short tipMesaj)
        : destinatar(std::move(destinatar)), mesaj(std::move(mesaj)), tip_mesaj(tipMesaj){
    data = getDate();
}


data_str_mess Message::getDate() {
    unsigned short zi, luna, an, ora;
    time_t theTime = time(nullptr);
    struct tm *aTime = localtime(&theTime);
    zi = aTime->tm_mday;
    luna = aTime->tm_mon + 1;
    an = aTime->tm_year + 1900;
    ora = aTime->tm_hour;

    data_str_mess data_cp{};
    data_cp.zi = zi;
    data_cp.luna = luna;
    data_cp.an = an;
    data_cp.ora = ora;

    return data_cp;
}
