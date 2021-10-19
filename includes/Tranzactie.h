#include <iostream>

class Tranzactie{
    std::string expeditor;
    std::string destinatar;
    unsigned int suma_trimisa;
    unsigned short zi;
    unsigned short luna;
    unsigned short an;
    unsigned short ora;

public:

    Tranzactie& operator=(const Tranzactie& copie){
        this->expeditor = copie.expeditor;
        this->destinatar = copie.destinatar;
        this->suma_trimisa = copie.suma_trimisa;
        this->zi = copie.zi;
        this->luna = copie.luna;
        this->an = copie.an;
        this->ora = copie.ora;
        return *this;
    }

    ~Tranzactie(){}

    void setExpeditor(const std::string &expeditor) {
        Tranzactie::expeditor = expeditor;
    }

    void setDestinatar(const std::string &destinatar) {
        Tranzactie::destinatar = destinatar;
    }

    void setSumaTrimisa(unsigned int sumaTrimisa) {
        suma_trimisa = sumaTrimisa;
    }

    void setZi(unsigned short zi) {
        Tranzactie::zi = zi;
    }

    void setLuna(unsigned short luna) {
        Tranzactie::luna = luna;
    }

    void setAn(unsigned short an) {
        Tranzactie::an = an;
    }

    void setOra(unsigned short ora) {
        Tranzactie::ora = ora;
    }

    friend std::ostream &operator<<(std::ostream &os, const Tranzactie &tranzactie) {
        os <<"\n\t\tDestinatar: " << tranzactie.destinatar;
        os <<"\n\t\tSuma_trimisa: " << tranzactie.suma_trimisa <<"lei";
        os <<"\n\t\tData: " << tranzactie.zi << "." << tranzactie.luna << "."<< tranzactie.an;
        os <<"\n\t\tOra: " << tranzactie.ora <<"\n\n";
        return os;
    }


};