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

    virtual void updateUserInFile(std::ostream& os);

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
                                                                       exp_date(std::move(expDate)),
                                                                       transaction_history(std::move(transaction_history)),
                                                                       messages(std::move(messages)),
                                                                       CIV(civ), suma(suma) {}

    friend std::ostream &operator<<(std::ostream &os, const std::shared_ptr<User>& user);

    virtual void writeUserInFile();

    const std::string &getNumePrenume() const;

    void setNumePrenume(const std::string &numePrenume);

    void setParola(const std::string &parola_copie);

    const std::string &getEmail() const;

    void setEmail(const std::string &email_copie);

    const std::string &getTelefon() const;

    void setTelefon(const std::string &telefon_copie);

    const std::string &getIban() const;

    void setIban(const std::string &iban);

    const std::pair<unsigned short, unsigned short> &getExpDate() const;

    void setExpDate(const std::pair<unsigned short, unsigned short> &expDate);

    float getSuma() const;

    void setSuma(float suma_copie);

    int getCiv() const;

    void setCiv(int civ);

    void changePassword();

    void showTransactionsHistory() const;

    std::vector<std::shared_ptr<Tranzactie>> loadTransactionsHistory() const;

    void showMessages() const;

    std::vector<std::shared_ptr<Message>> loadMessages() const;

    float makeTransaction();

    float makeTansactionCase1();

    void updateBalance(const float&);

    bool checkDuplicateIBAN(const std::string &IBAN);

    User returnUser(const std::string &IBAN);

    static void updateFileFromTemp();

    virtual void showInfo(std::ostream &os) const;
};


