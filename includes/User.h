#include <iostream>
#include <random>
#include <vector>
#include "Tranzactie.h"

class User{
    std::string nume_prenume;
    std::string parola;
    std::string email;
    std::string telefon;
    std::string IBAN;
    std::pair<unsigned short, unsigned short > exp_date;
    std::vector<Tranzactie> transaction_history;
    int CIV{};
    int suma{};

public:

    User()= default;;

    User(const User& copie){
        this->nume_prenume = copie.nume_prenume;
        this->parola = copie.parola;
        this->email = copie.email;
        this->telefon = copie.telefon;
        this->IBAN = copie.IBAN;
        this->exp_date = copie.exp_date;
        this->CIV = copie.CIV;
        this->suma = copie.suma;
        this->transaction_history = copie.transaction_history;
    }

    User& operator=(const User& copie){
        this->nume_prenume = copie.nume_prenume;
        this->parola = copie.parola;
        this->email = copie.email;
        this->telefon = copie.telefon;
        this->IBAN = copie.IBAN;
        this->exp_date = copie.exp_date;
        this->CIV = copie.CIV;
        this->suma = copie.suma;
        this->transaction_history = copie.transaction_history;
        return *this;
    }

    ~User(){  }

    User(const std::string &numePrenume, const std::string &parola, const std::string &email,
         const std::string &telefon, const std::string &iban, const std::pair<unsigned short, unsigned short> &expDate,
         const std::vector<Tranzactie> &transactionHistory, int civ, int suma) : nume_prenume(numePrenume), parola(parola),
                                                                       email(email), telefon(telefon), IBAN(iban),
                                                                       exp_date(expDate),
                                                                       transaction_history(transactionHistory),
                                                                       CIV(civ), suma(suma) {}

    friend std::ostream &operator<<(std::ostream &os, const User &user) {
        os << "nume_prenume: " << user.nume_prenume << " parola: " << user.parola << " email: " << user.email
           << " telefon: " << user.telefon << " IBAN: " << user.IBAN << " exp_date: " << user.exp_date.first<<"/"<<user.exp_date.second
           << " CIV: " << user.CIV <<" suma: "<<user.suma;
        return os;
    }

    static void writeUserInFile(const User& copie){
        std::fstream write;

        write.open("../txt_files/User/users.txt",std::fstream::app);
        write<<copie.nume_prenume<<';'<<copie.email<<';'<<copie.parola<<';';
        write<<copie.telefon<<';'<<copie.IBAN<<';'<<copie.exp_date.first<<'/'<<copie.exp_date.second<<';';
        write<<copie.CIV<<';'<<copie.suma<<'\n';

        write.close();
        write.open("../txt_files/User/users.txt",std::fstream::app);
        write.close();
    }

    const std::string &getNumePrenume() const {
        return nume_prenume;
    }

    void setNumePrenume(const std::string &numePrenume) {
        nume_prenume = numePrenume;
    }

    const std::string &getParola() const {
        return parola;
    }

    void setParola(const std::string &parola_copie) {
        User::parola = parola_copie;
    }

    const std::string &getEmail() const {
        return email;
    }

    void setEmail(const std::string &email_copie) {
        User::email = email_copie;
    }

    const std::string &getTelefon() const {
        return telefon;
    }

    void setTelefon(const std::string &telefon_copie) {
        User::telefon = telefon_copie;
    }

    const std::string &getIban() const {
        return IBAN;
    }

    void setIban(const std::string &iban) {
        IBAN = iban;
    }

    const std::pair<unsigned short, unsigned short> &getExpDate() const {
        return exp_date;
    }

    void setExpDate(const std::pair<unsigned short, unsigned short> &expDate) {
        exp_date = expDate;
    }

    const std::vector<Tranzactie> &getTransactionHistory() const {
        return transaction_history;
    }


    int getSuma() const {
        return suma;
    }

    void setSuma(int suma_copie) {
        User::suma = suma_copie;
    }

    int getCiv() const {
        return CIV;
    }

    void setCiv(int civ) {
        CIV = civ;
    }

    static void changePassword(User& user);

    static void showTransactionsHistory(User& user);

    static std::vector<Tranzactie> loadTransactionsHistory(const std::string&, const std::string&);

    static unsigned int makeTransaction(User&);

    static unsigned int makeTansactionCase1(User&);

    static void updateBalance(const std::string&, const unsigned int&, const User& user);

    static bool checkDuplicateIBAN(const std::string &IBAN);

    static User returnUser(const std::string &IBAN);
};


