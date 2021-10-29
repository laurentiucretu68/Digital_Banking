#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <utility>
#include <vector>
#include "Tranzactie.h"
#include "User.h"

class Admin{
    std::string username;
    std::string email;
    std::string parola;

public:
    Admin()= default;;

    Admin(const Admin& copie);

    Admin& operator=(const Admin& copie);

    friend std::ostream &operator<<(std::ostream &os, const Admin &admin);

    const std::string &getUsername() const;

    void setUsername(const std::string &username_copie);

    void setEmail(const std::string &email_copie);

    void setParola(const std::string &parola_copie);

    static void showAllUsers(const Admin&, unsigned short&);

    static void showUser(const Admin&, const User&);

    static void sendMessage(const Admin&,const User&);

    static void processingMessage(const User&, unsigned short&);

};

