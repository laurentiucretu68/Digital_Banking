#pragma once
#include <iostream>
#include "User.h"
#include "rlutil.h"

class UserBusiness : public User{
    std::string numeCompanie{};
    std::string CUI{};
public:
    UserBusiness() = default;

    ~UserBusiness() override = default;

    UserBusiness(const User &copie, std::string numeCompanie, std::string cui);

    void writeUserInFile() override;

    const std::string &getNumeCompanie() const;

    const std::string &getCui() const;

    void setNumeCompanie(const std::string &numeCompanie);

    void setCui(const std::string &cui);

    void updateBalance(const float&) override;

    void changePassword() const override;
};

