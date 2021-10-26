#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <utility>
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

    User(const User& copie);

    User& operator=(const User& copie);

    ~User()= default;

    User(std::string numePrenume, std::string parola, std::string email,
         std::string telefon, std::string iban, std::pair<unsigned short, unsigned short> expDate,
         std::vector<Tranzactie> transactionHistory, int civ, int suma) : nume_prenume(std::move(numePrenume)), parola(std::move(parola)),
                                                                       email(std::move(email)), telefon(std::move(telefon)), IBAN(std::move(iban)),
                                                                       exp_date(std::move(expDate)),
                                                                       transaction_history(std::move(transactionHistory)),
                                                                       CIV(civ), suma(suma) {}

    friend std::ostream &operator<<(std::ostream &os, const User &user);

    static void writeUserInFile(const User& copie);

    const std::string &getNumePrenume() const;

    void setNumePrenume(const std::string &numePrenume);

    const std::string &getParola() const;

    void setParola(const std::string &parola_copie);

    const std::string &getEmail() const;

    void setEmail(const std::string &email_copie);

    const std::string &getTelefon() const;

    void setTelefon(const std::string &telefon_copie);

    const std::string &getIban() const;

    void setIban(const std::string &iban);

    const std::pair<unsigned short, unsigned short> &getExpDate() const;

    void setExpDate(const std::pair<unsigned short, unsigned short> &expDate);

    const std::vector<Tranzactie> &getTransactionHistory() const;

    int getSuma() const;

    void setSuma(int suma_copie);

    int getCiv() const;

    void setCiv(int civ);

    static void changePassword(User& user);

    static void showTransactionsHistory(User& user);

    static std::vector<Tranzactie> loadTransactionsHistory(const std::string&, const std::string&);

    static unsigned int makeTransaction(User&);

    static unsigned int makeTansactionCase1(User&);

    static void updateBalance(const std::string&, const unsigned int&, const User& user);

    static bool checkDuplicateIBAN(const std::string &IBAN);

    static User returnUser(const std::string &IBAN);
};


