#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <utility>
#include <vector>
#include "Tranzactie.h"
#include "Message.h"
#include "User.h"
#include "UserBusiness.h"

class Admin{
    std::string username{};
    std::string email{};
    std::string parola{};
    static void processingMessage(const std::shared_ptr<User>&, unsigned short&) ;

public:
    Admin()= default;

    Admin& operator=(const Admin& copie);

    const std::string &getUsername() const;

    void setUsername(const std::string &username_copie);

    void setEmail(const std::string &email_copie);

    void setParola(const std::string &parola_copie);

    void showAllUsers(unsigned short&) const;

    void showUser(const std::shared_ptr<User>& user) const;

    void sendMessage(const std::shared_ptr<User>& user) const;

};

