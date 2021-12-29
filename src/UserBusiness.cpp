#include "../includes/UserBusiness.h"
#include <utility>
#include <iostream>
#include <fstream>
#include <thread>
#include <regex>
#include <string>
#include <sstream>
#include "../libraries/rlutil.h"

#define setRed rlutil::setColor(4)

void UserBusiness::writeUserInFile() {
    try{
        User::writeUserInFile();
        std::fstream write;
        write.open("../txt_files/User/users.txt",std::fstream::app);
        write.exceptions(std::ifstream::badbit);
        write<<';'<<numeCompanie<<';'<<CUI;

        write.close();
        write.open("../txt_files/User/users.txt",std::fstream::app);
        write.close();
    }
    catch (std::exception& e) {
        setRed;
        std::cout << "\n\t(Error) " << e.what() << "\n";
    }
}

UserBusiness::UserBusiness(const User &copie, std::string numeCompanie, std::string cui) : User(copie),numeCompanie(std::move(numeCompanie)),CUI(std::move(cui)) {}

void UserBusiness::showInfo(std::ostream &os) const {
    os<<"\t Company name: "<<numeCompanie<<"\n";
    os<<"\t CUI: "<<CUI<<"\n\n";
}

void UserBusiness::updateUserInFile(std::ostream &os) {
    os<<numeCompanie<<";"<<CUI;
}
