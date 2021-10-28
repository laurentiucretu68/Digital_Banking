#include "../includes/Admin.h"
#include "../includes/rlutil.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <thread>
#include <regex>

Admin::Admin(const Admin &copie) {
    this->username = copie.username;
    this->email = copie.email;
    this->parola = copie.parola;
}

Admin &Admin::operator=(const Admin &copie) {
    this->username = copie.username;
    this->email = copie.email;
    this->parola = copie.parola;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Admin &admin) {
    os << "username: " << admin.username << " email: " << admin.email << " parola: " << admin.parola;
    return os;
}

const std::string &Admin::getUsername() const {
    return username;
}

void Admin::setUsername(const std::string &username_copie) {
    Admin::username = username_copie;
}

void Admin::setEmail(const std::string &email_copie) {
    Admin::email = email_copie;
}

void Admin::setParola(const std::string &parola_copie) {
    Admin::parola = parola_copie;
}

void Admin::showAllUsers(const Admin& admin, unsigned short& val) {
    rlutil::cls();
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\t---------------------------------";
    std::cout<<"\n \t| **** Digital Banking App **** |\n";
    std::cout<<"\t---------------------------------\n\n";
    std::cout<<"\tAdmin panel -- all users\n\n";

    rlutil::setColor(2);
    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    std::vector<User> users;
    users.resize(1);

    std::string line;
    int n = 0;
    while (std::getline(login, line)){
        std::cout<<"\t"<<n+1<<" ";
        std::istringstream iss(line);
        std::string word;
        std::getline(iss, word, ';');
        std::cout<<"\t"<<word<<" ";
        users[n].setNumePrenume(word);
        std::getline(iss, word, ';');
        std::cout<<"\t"<<word<<"\n";
        users[n].setEmail(word);
        std::getline(iss, word, ';');

        users[n].setParola(word);
        std::getline(iss, word, ';');

        users[n].setTelefon(word);
        std::getline(iss, word, ';');

        users[n].setIban(word);
        std::getline(iss, word, ';');

        std::string aux(word);

        std::getline(iss, word, ';');
        users[n].setCiv(stoi(word));

        std::getline(iss, word, ';');
        users[n].setSuma(stoi(word));

        std::istringstream iss1(aux);
        std::string date;
        std::getline(iss1, date, '/');
        std::pair<unsigned short , unsigned short> temp;
        temp.first = stoi(date);
        std::getline(iss1, date, '/');
        temp.second = stoi(date);
        users[n].setExpDate(temp);

        n++;
        users.resize(n+1);
    }
    login.close();
    users.resize(n);

    rlutil::setColor(1);
    std::cout<<"\n\n\tFor a user info type the id"<<'\n';
    std::cout<<"\tFor back, type 0\n\n";

    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    rlutil::setColor(2);

    if (std::cin>>option){
        if (option==0){
            rlutil::setColor(4);
            std::cout<<"\n\tWait...\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            val = 1;
            return;
        }
        else
        if (option>=1 && option<=n){
            Admin::showUser(admin,users[option-1]);
            val = 1;
        }
        else{
            rlutil::setColor(4);
            std::cout<<"\n\tIncorrect option!\n";
            val = 1;
            showAllUsers(admin,val);
            return;
        }
    }
}

void Admin::showUser(const Admin& admin,const User &user) {
    rlutil::cls();
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\t---------------------------------";
    std::cout<<"\n \t| **** Digital Banking App **** |\n";
    std::cout<<"\t---------------------------------\n\n";
    std::cout<<"\t Info about "<<user.getNumePrenume()<<"\n\n";

    rlutil::setColor(2);
    std::cout<<"\t First name and last name: "<<user.getNumePrenume()<<"\n";
    std::cout<<"\t Email: "<<user.getEmail()<<"\n";
    std::cout<<"\t Phone number: "<<user.getTelefon()<<"\n";
    std::cout<<"\t IBAN: "<<user.getIban()<<"\n";
    std::cout<<"\t Balance: "<<user.getSuma()<<"lei"<<"\n\n";
    rlutil::setColor(15);
    std::cout<<"\t Transaction History: ";

    const std::vector<Tranzactie>& t = user.getTransactionHistory();
    if (t.empty())
        std::cout<<"empty\n\n";
    else{
        std::cout<<"\n\n";
        for (const auto & i : t)
            std::cout<<i<<"\n";
    }

    rlutil::setColor(1);
    std::cout<<"\tGo back to all users panel - type 1\n\n";

    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    rlutil::setColor(2);

    if (std::cin>>option){
        if (option==1){
            rlutil::setColor(4);
            std::cout<<"\n\tWait...\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            unsigned short val = 1;
            Admin::showAllUsers(admin,val);
            return;
        }
        else{
            rlutil::setColor(4);
            std::cout<<"\n\tIncorrect option!\n";
            showUser(admin,user);
            return;
        }
    }
}