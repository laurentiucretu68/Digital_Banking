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

template <typename T>
class Admin{
    T username;
    T email;
    T parola;
    static void processingMessage(const std::shared_ptr<User>&, unsigned short&);

public:
    Admin()= default;

    Admin(const T& username_, const T& email_, const T& parola_);

    Admin& operator=(const Admin&) = default;

    const T& getUsername() const;

    void showAllUsers() const;

    void showUser(const std::shared_ptr<User>& user) const;

    void sendMessage(const std::shared_ptr<User>& user) const;

};

