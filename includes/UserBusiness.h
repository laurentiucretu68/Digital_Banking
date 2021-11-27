#pragma once
#include <iostream>
#include "User.h"

class UserBusiness : public User{
    std::string numeCompanie{};
    std::string CUI{};
public:
    UserBusiness() = default;

    ~UserBusiness() override = default;

    UserBusiness(const User &copie, std::string numeCompanie, std::string cui);

    void writeUserInFile() override;

    void showInfo(std::ostream &os) const override;

    void updateUserInFile(std::ostream& os) override;
};

