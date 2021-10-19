#include <iostream>

class Tranzactie{
    std::string destinatar;
    std::string IBAN_destinatar;
    unsigned int suma_trimisa;
    unsigned short zi;
    unsigned short luna;
    unsigned short an;
    unsigned short ora;

public:


    Tranzactie& operator=(const Tranzactie& copie){
        this->destinatar = copie.destinatar;
        this->suma_trimisa = copie.suma_trimisa;
        this->zi = copie.zi;
        this->luna = copie.luna;
        this->an = copie.an;
        this->ora = copie.ora;
        return *this;
    }

    ~Tranzactie(){}

    void setDestinatar(const std::string &destinatar_copie) {
        Tranzactie::destinatar = destinatar_copie;
    }

    void setSumaTrimisa(unsigned int sumaTrimisa) {
        suma_trimisa = sumaTrimisa;
    }

    void setZi(unsigned short zi_copie) {
        Tranzactie::zi = zi_copie;
    }

    void setLuna(unsigned short luna_copie) {
        Tranzactie::luna = luna_copie;
    }

    void setAn(unsigned short an_copie) {
        Tranzactie::an = an_copie;
    }

    void setOra(unsigned short ora_copie) {
        Tranzactie::ora = ora_copie;
    }

    void setIbanDestinatar(const std::string &ibanDestinatar_copie) {
        IBAN_destinatar = ibanDestinatar_copie;
    }

    friend std::ostream &operator<<(std::ostream &os, const Tranzactie &tranzactie) {
        os <<"\n\t\tDestinatar: " << tranzactie.destinatar;
        os <<"\n\t\tIBAN: " << tranzactie.IBAN_destinatar;
        os <<"\n\t\tSuma_trimisa: " << tranzactie.suma_trimisa <<"lei";
        os <<"\n\t\tData: " << tranzactie.zi << "." << tranzactie.luna << "."<< tranzactie.an;
        os <<"\n\t\tOra: " << tranzactie.ora <<"\n\n";
        return os;
    }

    static bool checkPatternIBAN(const std::string &IBAN) {
        if (IBAN.length() != 24)
            return false;

        std::string IBAN_copy = IBAN;
        std::transform(IBAN_copy.begin(), IBAN_copy.end(), IBAN_copy.begin(), ::toupper);
        const std::regex pattern("(RO)[0-9]{2}[A-Z]{4}[0-9]{16}");
        return std::regex_match(IBAN_copy, pattern);
    }

    static void writeInFile(std::fstream &file, const Tranzactie &tranzactie){
        file<<tranzactie.destinatar<<";"<<tranzactie.IBAN_destinatar<<";"<<tranzactie.suma_trimisa<<";";
        file<<tranzactie.zi<<";"<<tranzactie.luna<<";"<<tranzactie.an<<";"<<tranzactie.ora<<"\n";
    }


};