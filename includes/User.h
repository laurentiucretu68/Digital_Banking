#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <utility>
#include <vector>
#include <memory>
#include "Tranzactie.h"
#include "Message.h"

class User{
protected:
    std::string nume_prenume{};
    std::string parola{};
    std::string email{};
    std::string telefon{};
    std::string IBAN{};
    std::pair<unsigned short, unsigned short> exp_date{};
    std::vector<std::shared_ptr<Tranzactie>> transaction_history{};
    std::vector<std::shared_ptr<Message>> messages{};
    int CIV{};
    float suma{};

public:

    User()= default;

    User(const User& copie);

    User& operator=(const User& copie);

    virtual ~User()= default;

    User(std::string numePrenume, std::string parola, std::string email,
         std::string telefon, std::string iban, std::pair<unsigned short, unsigned short> expDate,
         std::vector<std::shared_ptr<Tranzactie>> transaction_history, std::vector<std::shared_ptr<Message>> messages,
         int civ, float suma) : nume_prenume(std::move(numePrenume)), parola(std::move(parola)),
         email(std::move(email)), telefon(std::move(telefon)), IBAN(std::move(iban)),
         exp_date(std::move(expDate)), transaction_history(std::move(transaction_history)),
         messages(std::move(messages)), CIV(civ), suma(suma) {}

    friend std::ostream &operator<<(std::ostream &os, const std::shared_ptr<User>& user);

    virtual void writeUserInFile();

    const std::string &getNumePrenume() const;

    const std::string &getEmail() const;

    const std::string &getTelefon() const;

    const std::string &getIban() const;

    const std::pair<unsigned short, unsigned short> &getExpDate() const;

    float getSuma() const;

    int getCiv() const;

    void changePassword();

    void showTransactionsHistory() const;

    std::vector<std::shared_ptr<Tranzactie>> loadTransactionsHistory() const;

    void showMessages() const;

    std::vector<std::shared_ptr<Message>> loadMessages() const;

    float makeTransaction();

    float makeTansactionCase1();

    void updateBalance(const float&);

    bool checkDuplicateIBAN(const std::string &IBAN);

    std::shared_ptr<User> returnUser(const std::string &IBAN);

    static void updateFileFromTemp();

    virtual void showInfo(std::ostream&) const{}

    virtual void updateUserInFile(std::ostream&){}

    void setSuma(float suma);
};


