#include "../includes/Admin.h"
#include "../includes/rlutil.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <thread>
#include <regex>

Admin::Admin(const Admin &copie) {
    username = copie.username;
    email = copie.email;
    parola = copie.parola;
}

Admin &Admin::operator=(const Admin &copie) {
    username = copie.username;
    email = copie.email;
    parola = copie.parola;
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

void Admin::showAllUsers(unsigned short& val) {
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\n\tAdmin panel -- all users\n\n";

    rlutil::setColor(2);
    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    std::vector<UserBusiness> users;
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
        users[n].setSuma((float)stof(word));

        std::istringstream iss1(aux);
        std::string date;
        std::getline(iss1, date, '/');
        std::pair<unsigned short , unsigned short> temp;
        temp.first = stoi(date);
        std::getline(iss1, date, '/');
        temp.second = stoi(date);
        users[n].setExpDate(temp);

        if (std::getline(iss, word, ';')){
            users[n].setNumeCompanie(word);
            std::getline(iss, word, ';');
            users[n].setCui(word);
        }

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

    while (std::cin>>option){
        if (option==0){
            rlutil::setColor(4);
            std::cout<<"\n\tWait...\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            val = 1;
            return;
        }
        else
        if (option>=1 && option<=n){
            Admin::showUser(users[option-1]);
            val = 1;
            return;
        }
        else{
            rlutil::setColor(4);
            std::cout<<"\n\tIncorrect option!\n";
            val = 1;
            rlutil::setColor(1);
            std::cout<<"\n\tPlease select your choice: ";
        }
    }
}

void Admin::showUser(UserBusiness &user) {
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\n\t Info about "<<user.getNumePrenume()<<"\n\n";

    rlutil::setColor(2);
    std::cout<<"\t First name and last name: "<<user.getNumePrenume()<<"\n";
    std::cout<<"\t Email: "<<user.getEmail()<<"\n";
    std::cout<<"\t Phone number: "<<user.getTelefon()<<"\n";
    std::cout<<"\t IBAN: "<<user.getIban()<<"\n";
    std::cout<<"\t Balance: "<<user.getSuma()<<"lei\n";
    if (!user.getNumeCompanie().empty()){
        std::cout<<"\t Company name: "<<user.getNumeCompanie()<<"\n";
        std::cout<<"\t CUI: "<<user.getCui()<<"\n\n";
    }
    else
        std::cout<<"\n";
    rlutil::setColor(15);
    std::cout<<"\t Transaction History: ";

    std::string file_name = "../txt_files/User/" + user.getEmail() + "_transactions.txt";
    std::vector<std::shared_ptr<Tranzactie>> t = user.loadTransactionsHistory(file_name);
    if (t.empty())
        std::cout<<"empty\n\n";
    else{
        std::cout<<"\n\n";
        for (const auto & i : t)
            std::cout<<"\t"<<*i<<"\n";
    }

    rlutil::setColor(1);
    std::cout<<"\t[1] Go back to all users panel \n";
    std::cout<<"\t[2] Send a message to this user\n\n";

    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    rlutil::setColor(2);

    while (std::cin>>option){
        if (option==1){
            rlutil::setColor(4);
            std::cout<<"\n\tWait...\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            unsigned short val = 1;
            Admin::showAllUsers(val);
            return;
        }
        else
            if (option==2){
                rlutil::setColor(4);
                std::cout<<"\n\tWait...\n\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                Admin::sendMessage(user);
                return;
            }
            else{
                rlutil::setColor(4);
                std::cout<<"\n\tIncorrect option!\n";
                rlutil::setColor(1);
                std::cout<<"\n\tPlease select your choice: ";
            }
    }
}

void Admin::sendMessage(UserBusiness& user) {
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\t Send message to: "<<user.getNumePrenume()<<"\n\n";

    rlutil::setColor(1);
    std::cout<<"\t[1] Go back to user panel info \n";
    std::cout<<"\t[2] Continue\n\n";

    std::cout<<"\tPlease select your choice: ";
    unsigned short option;
    rlutil::setColor(2);

    while (std::cin>>option){
        if (option==1){
            rlutil::setColor(4);
            std::cout<<"\n\tWait...\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            Admin::showUser(user);
            return;
        }
        else
        if (option==2){
            rlutil::setColor(4);
            std::cout<<"\n\tWait...\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            unsigned short success = 0;
            processingMessage(user,success);
            if (success == 1){
                rlutil::setColor(4);
                std::cout<<"\n\tMessage sent!";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout<<"\n\tLoading main panel! Please wait...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            else{
                rlutil::setColor(4);
                std::cout<<"\n\tError..\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            return;
        }
        else{
            rlutil::setColor(4);
            std::cout<<"\n\tIncorrect option!\n";
            rlutil::setColor(1);
            std::cout<<"\n\tPlease select your choice: ";
        }
    }
}

void Admin::processingMessage(const User &user, unsigned short& success) {
    std::string mesaj;
    rlutil::setColor(1);
    std::cout<<"\tSelect type of message:\n";
    std::cout<<"\t[1] Warning\n";
    std::cout<<"\t[2] Advice\n";
    std::cout<<"\t[3] Notification\n\n";

    std::cout<<"\tPlease select your choice: ";
    unsigned short type;
    rlutil::setColor(2);
    while(std::cin>>type){
        if (type != 1 && type != 2 && type != 3){
            rlutil::setColor(4);
            std::cout<<"\n\tIncorrect option!\n";
            rlutil::setColor(1);
            std::cout<<"\n\tPlease select your choice: ";
        }
        else
            break;
    }

    std::cin.get();
    std::cout<<"\n\tMessage: "; std::getline(std::cin,mesaj);

    unsigned short zi, luna, an, ora;
    time_t theTime = time(nullptr);
    struct tm *aTime = localtime(&theTime);
    zi = aTime->tm_mday;
    luna = aTime->tm_mon + 1;
    an = aTime->tm_year + 1900;
    ora = aTime->tm_hour;
    data_str_mess data_cp{};
    data_cp.zi = zi;
    data_cp.luna = luna;
    data_cp.an = an;
    data_cp.ora = ora;


    Message message;
    message.setDestinatar(user.getEmail());
    message.setMesaj(mesaj);
    message.setTipMesaj(type);
    message.setData(data_cp);

    std::string file_name = "../txt_files/User/" + user.getEmail() + "_messages.txt";
    std::fstream file;
    file.open(file_name,std::fstream::app);
    if (!file) {
        file.close();
        file.open(file_name,std::fstream::in);
        message.writeInFile(file);
    }
    else{
        message.writeInFile(file);
        file.close();
    }
    success = 1;
}
