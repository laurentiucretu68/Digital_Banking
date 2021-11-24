#include "../includes/Admin.h"
#include "../includes/Interface.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <regex>
#include <sstream>

void Interface::startApp() {
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\t---------------------------------";
    std::cout<<"\n \t| **** Digital Banking App **** |\n";
    std::cout<<"\t---------------------------------\n\n";
    rlutil::setColor(2);
    std::cout<<"\t[1] Login"<<'\n';
    std::cout<<"\t[2] Sign up"<<'\n';
    std::cout<<"\t[3] Exit"<<"\n\n";

    rlutil::setColor(1);
    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    while (std::cin>>option){
        switch (option) {
            case 1:{
                login();
                return;
            }
            case 2:{
                signup();
                return;
            }
            case 3:{
                rlutil::setColor(4);
                std::cout<<"\n\tClosing the app...\n\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
            }
            default:{
                rlutil::setColor(4);
                std::cout<<"\n\tIncorrect option!\n";
                rlutil::setColor(1);
                std::cout<<"\n\tPlease select your choice: ";
            }
        }
    }
}

void Interface::signup() {
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\n\tSign up\n";
    rlutil::setColor(2);
    std::cout<<"\t[1] Continue"<<'\n';
    std::cout<<"\t[2] Back to main panel\n\n";

    rlutil::setColor(1);
    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    rlutil::setColor(2);

    while (std::cin>>option){
        switch(option) {
            case 1: {
                signupProcess();
                return;
            }
            case 2: {
                startApp();
                return;
            }
            default: {
                rlutil::setColor(4);
                std::cout<<"\n\tIncorrect option!\n";
                rlutil::setColor(1);
                std::cout<<"\n\tPlease select your choice: ";
            }
        }
    }
}

void Interface::signupProcess() {
    std::string name;
    std::string email;
    std::string password;
    std::string repeat_password;
    std::string phone;
    std::string IBAN;
    std::pair<unsigned short, unsigned short > exp_date;
    int civ;
    std::cin.get();
    std::cout<<"\n\tNume si prenume: "; std::getline(std::cin,name);

    bool cond = false;
    while (!cond){
        rlutil::setColor(2);
        std::cout<<"\n\tEmail: "; std::getline(std::cin,email);
        if (checkPatternEmail(email)){
            if (checkDuplicateEmail(email)){
                cond = true;
            }
            else{
                rlutil::setColor(4);
                std::cout<<"\n\tEmail already exist! Try again...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        else{
            rlutil::setColor(4);
            std::cout<<"\n\tInvalid email address! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    }

    cond = false;
    while (!cond){
        rlutil::setColor(2);
        std::cout<<"\n\tPassword: "; std::getline(std::cin,password);
        if (password.length()<7){
            rlutil::setColor(4);
            std::cout<<"\n\tPassword must contain at least 7 characters!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
            cond = true;
    }

    cond = false;
    while (!cond){
        rlutil::setColor(2);
        std::cout<<"\n\tRepeat password: "; std::getline(std::cin,repeat_password);
        if (password != repeat_password){
            rlutil::setColor(4);
            std::cout<<"\n\tPassword and Repeat Password don't match! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
            cond = true;
    }

    cond = false;
    while (!cond){
        rlutil::setColor(2);
        std::cout<<"\n\tPhone Number (Format: 07********): "; std::getline(std::cin,phone);
        if (checkPatternPhone(phone)){
            if (checkDuplicatePhone(phone))
                cond = true;
            else{
                rlutil::setColor(4);
                std::cout<<"\n\tPhone number already exist! Try again...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        else{
            rlutil::setColor(4);
            std::cout<<"\n\tInvalid phone format! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    cond = false;
    while (!cond){
        rlutil::setColor(2);
        std::cout<<"\n\tIBAN (Example: RO35RZBR4421944568612335): "; std::cin>>IBAN;
        if (checkPatternIBAN(IBAN)){
            if (checkDuplicateIBAN(IBAN))
                cond = true;
            else{
                rlutil::setColor(4);
                std::cout<<"\n\tIBAN already exist! Try again...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        else{
            rlutil::setColor(4);
            std::cout<<"\n\tInvalid IBAN format! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    rlutil::setColor(2);
    std::cout<<"\n\tExpiration date: ";
    cond = false;
    while (!cond){
        rlutil::setColor(2);
        std::cout<<"\n\t\tMonth: "; std::cin>>exp_date.first;
        if (exp_date.first >=1 && exp_date.first<=12)
            cond = true;
        else{
            rlutil::setColor(4);
            std::cout<<"\n\tInvalid month! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    cond = false;
    while (!cond){
        rlutil::setColor(2);
        std::cout<<"\n\t\tYear (two digits): "; std::cin>>exp_date.second;
        if (exp_date.second >=22 && exp_date.second <=30)
            cond = true;
        else{
            rlutil::setColor(4);
            std::cout<<"\n\tInvalid year! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    cond = false;
    while (!cond){
        rlutil::setColor(2);
        std::cout<<"\n\tCIV: "; std::cin>>civ;
        if (civ >=100 && civ <=999)
            cond = true;
        else{
            rlutil::setColor(4);
            std::cout<<"\n\tInvalid CIV! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    std::string numeCompanie{};
    rlutil::setColor(2);
    std::cin.get();
    std::cout<<"\n\tNume companie (scrie 0 pentru persoana fizica): "; std::getline(std::cin,numeCompanie);

    cond = false;
    std::string cui{};
    while (!cond){
        rlutil::setColor(2);
        std::cout<<"\n\tCUI (scrie 0 pentru persoana fizica): "; std::cin>>cui;
        static const std::regex pattern("([0-9]*)");
        if (std::regex_match(cui, pattern))
            cond = true;
        else{
            rlutil::setColor(4);
            std::cout<<"\n\tInvalid CUI format! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(100,5000);
    float suma = distribution(generator);

    std::hash<std::string> hash_pass;
    password = std::to_string(hash_pass(password));
    User u(name, password, email, phone, IBAN, exp_date, std::vector<std::shared_ptr<Tranzactie>>(),std::vector<std::shared_ptr<Message>>(),civ,suma);

    if (numeCompanie!="0" && cui!="0"){
        UserBusiness ub_aux(u,numeCompanie,cui);
        std::shared_ptr<UserBusiness> ub;
        ub = std::make_shared<UserBusiness>(ub_aux);
        ub->writeUserInFile();
    }
    else
        u.writeUserInFile();

    rlutil::setColor(3);
    std::cout<<"\n\tCreating account...";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"\n\tDone\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    startApp();
}

bool Interface::checkDuplicateEmail(const std::string &email) {
    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    std::string line;

    while (std::getline(login, line)){
        std::istringstream iss(line);
        std::string word;
        std::getline(iss, word, ';');
        std::getline(iss, word, ';');
        if (email == word)
            return false;
    }
    login.close();

    login.open("../txt_files/Admin/admins.txt",std::fstream::in);
    while (std::getline(login, line)){
        std::istringstream iss(line);
        std::string word;
        std::getline(iss, word, ';');
        std::getline(iss, word, ';');
        if (email == word)
            return false;
    }
    login.close();
    return true;
}

bool Interface::checkDuplicatePhone(const std::string &phone) {
    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    std::string line;
    while (std::getline(login, line)){
        std::istringstream iss(line);
        std::string word;
        std::getline(iss, word, ';');
        std::getline(iss, word, ';');
        std::getline(iss, word, ';');
        std::getline(iss, word, ';');
        if (phone==word)
            return false;
    }
    login.close();
    return true;
}

bool Interface::checkDuplicateIBAN(const std::string &IBAN) {
    std::string IBAN_copy = IBAN;
    std::transform(IBAN_copy.begin(), IBAN_copy.end(), IBAN_copy.begin(), ::toupper);
    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    std::string line;
    while (std::getline(login, line)){
        std::istringstream iss(line);
        std::string word;
        std::getline(iss, word, ';');
        std::getline(iss, word, ';');
        std::getline(iss, word, ';');
        std::getline(iss, word, ';');
        std::getline(iss, word, ';');
        if (IBAN_copy==word)
            return false;
    }
    login.close();
    return true;
}

bool Interface::checkPatternEmail(const std::string &email) {
    static const std::regex pattern("([a-z]+)([_.a-z0-9]*)([a-z0-9]+)(@)([a-z]+)([.a-z]+)([a-z]+)");
    return std::regex_match(email, pattern);
}

bool Interface::checkPatternPhone(const std::string &phone) {
    if (phone.length() != 10)
        return true;

    static const std::regex pattern("(07)([0-9]{8})");
    return std::regex_match(phone, pattern);
}

bool Interface::checkPatternIBAN(const std::string &IBAN) {
    if (IBAN.length() != 24)
        return true;

    std::string IBAN_copy = IBAN;
    std::transform(IBAN_copy.begin(), IBAN_copy.end(), IBAN_copy.begin(), ::toupper);
    static const std::regex pattern("(RO)[0-9]{2}[A-Z]{4}[0-9]{16}");
    return std::regex_match(IBAN_copy, pattern);
}

void Interface::login() {
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\n\tLogin\n";
    rlutil::setColor(2);

    std::cout<<"\t[1] Continue"<<'\n';
    std::cout<<"\t[2] Back to main panel\n\n";

    rlutil::setColor(1);
    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    rlutil::setColor(2);

    while (std::cin>>option){
        switch(option) {
            case 1: {
                std::string email;
                std::string password;
                unsigned short tip=0;
                std::cout<<"\n\tEmail/Username (for admins): "; std::cin>>email;
                std::cout<<"\n\tPassword: ";    std::cin>>password;
                std::hash<std::string> hash_pass;
                password = std::to_string(hash_pass(password));
                if (checkEmailPasswordLogin(email,password,tip)){
                    rlutil::setColor(3);
                    std::cout<<"\n\tLogin Succesful!\n\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    if (tip==2)
                        loginAdmin(email,password);
                    else
                        loginUser(email);
                }
                else{
                    rlutil::setColor(4);
                    std::cout<<"\n\tWrong email/username(for admins) or password...\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    login();
                }
                return;
            }
            case 2: {
                startApp();
                return;
            }
            default: {
                rlutil::setColor(4);
                std::cout<<"\n\tIncorrect option!\n";
                rlutil::setColor(1);
                std::cout<<"\n\tPlease select your choice: ";
            }
        }
    }
}

void Interface::loginUser(const std::string &email) {
    User user;
    std::fstream write;
    write.open("../txt_files/User/users.txt",std::fstream::in);
    std::string line;
    while (std::getline(write, line)){
        std::istringstream iss(line);
        std::string word;
        std::getline(iss, word, ';');

        std::string nume(word);
        std::getline(iss, word, ';');
        if (word == email){
            user.setNumePrenume(nume);
            user.setEmail(email);

            std::getline(iss, word, ';');
            user.setParola(word);

            std::getline(iss, word, ';');
            user.setTelefon(word);

            std::getline(iss, word, ';');
            user.setIban(word);

            std::getline(iss, word, ';');
            std::string aux(word);


            std::getline(iss, word, ';');
            user.setCiv(stoi(word));

            std::getline(iss, word, ';');
            user.setSuma((float)stof(word));

            std::pair<unsigned short , unsigned short> temp;
            std::istringstream iss1(aux);
            std::string date;
            std::getline(iss1, date, '/');
            temp.first = stoi(date);
            std::getline(iss1, date, '/');
            temp.second = stoi(date);
            user.setExpDate(temp);

            std::string numeCompanie, cui;
            if(std::getline(iss, word, ';')){
                numeCompanie = word;
                std::getline(iss, word, ';');
                cui = word;
            }
            UserBusiness ub(user,numeCompanie,cui);

            write.close();
            panelUser(ub);
            break;
        }
    }
}

void Interface::loginAdmin(const std::string &email,const std::string &password) {
    Admin ad;
    std::fstream write;
    write.open("../txt_files/Admin/admins.txt",std::fstream::in);
    std::string line;
    while (std::getline(write, line)){
        std::istringstream iss(line);
        std::string word;
        std::getline(iss, word, ';');
        std::string username(word);
        std::getline(iss, word, ';');
        if (word == email || username==email){
            ad.setParola(password);
            ad.setUsername(username);
            ad.setEmail(word);
            write.close();
            panelAdmin(ad);
            break;
        }
    }
}

bool Interface::checkEmailPasswordLogin(const std::string& email, const std::string& password,unsigned short& tip){
    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    std::string line;
    while (std::getline(login, line)){
        std::istringstream iss(line);
        std::string word;
        std::getline(iss, word, ';');
        std::getline(iss, word, ';');
        if (email == word){
            std::getline(iss, word, ';');
            if (password == word){
                tip = 1;
                return true;
            }
            else
                return false;
        }
    }
    login.close();

    login.open("../txt_files/Admin/admins.txt",std::fstream::in);
    while (std::getline(login, line)){
        std::istringstream iss(line);
        std::string word;
        std::getline(iss, word, ';');
        if (email == word){
            std::getline(iss, word, ';');
            std::getline(iss, word, ';');
            if (password == word){
                tip = 2;
                return true;
            }
            else
                return false;
        }
        std::getline(iss, word, ';');
        if (email == word){
            std::getline(iss, word, ';');
            if (password == word){
                tip = 2;
                return true;
            }
            else
                return false;
        }
    }
    login.close();
    return false;
}

void Interface::panelUser(UserBusiness &user) {
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\t---------------------------------";
    std::cout<<"\n\t| **** Digital Banking App **** |\n";
    std::cout<<"\t---------------------------------\n\n";
    std::cout<<"\tWelcome back "<<user.getNumePrenume()<<"!\n";
    std::cout<<"\tYour balance: "<<user.getSuma()<<"lei"<<"\n\n";
    rlutil::setColor(2);
    std::cout<<"\tInfo:\n";
    std::cout<<"\t Email: "<<user.getEmail()<<"\n";
    std::cout<<"\t Phone number: "<<user.getTelefon()<<"\n";
    std::cout<<"\t IBAN: "<<user.getIban()<<"\n";
    std::pair<unsigned short, unsigned short> date_aux = user.getExpDate();
    std::cout<<"\t Date exp: "<<date_aux.first<<"/"<<date_aux.second<<"\n";
    std::cout<<"\t CIV: "<<user.getCiv()<<"\n";
    if (!user.getNumeCompanie().empty()){
        std::cout<<"\t Nume companie: "<<user.getNumeCompanie()<<"\n";
        std::cout<<"\t CUI: "<<user.getCui()<<"\n\n";
    }
    else
        std::cout<<"\n";

    rlutil::setColor(15);
    std::cout<<"\tMeniu:\n";
    std::cout<<"\t [1] Show transactions history\n";
    std::cout<<"\t [2] Show messages\n";
    std::cout<<"\t [3] Send money\n";
    std::cout<<"\t [4] Change password\n";
    std::cout<<"\t [5] Logout\n";

    rlutil::setColor(1);
    std::cout<<"\n\tPlease select your choice: ";

    unsigned short option;
    rlutil::setColor(2);

    while (std::cin>>option){
        switch(option) {
            case 1: {
                user.showTransactionsHistory();
                Interface::panelUser(user);
                return;
            }
            case 2: {
                user.showMessages();
                Interface::panelUser(user);
                return;
            }
            case 3: {
                float suma_tranzactie = user.makeTransaction();
                if (!user.getNumeCompanie().empty()){
                    std::shared_ptr<UserBusiness> ub_aux;
                    ub_aux = std::make_shared<UserBusiness>(user);
                    ub_aux->updateBalance(ub_aux->getSuma() - suma_tranzactie);
                }
                else
                    user.updateBalance(user.getSuma() - suma_tranzactie);
                Interface::loginUser(user.getEmail());
                return;
            }
            case 4: {
                if (!user.getNumeCompanie().empty()){
                    std::shared_ptr<UserBusiness> ub_aux;
                    ub_aux = std::make_shared<UserBusiness>(user);
                    ub_aux->changePassword();
                }
                else
                    user.changePassword();
                panelUser(user);
                return;
            }
            case 5: {
                rlutil::setColor(4);
                std::cout<<"\n\tPlease wait...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                startApp();
                return;
            }
            default: {
                rlutil::setColor(4);
                std::cout<<"\n\tIncorrect option!\n";
                rlutil::setColor(1);
                std::cout<<"\n\tPlease select your choice: ";
            }
        }
    }
}

void Interface::panelAdmin(Admin& admin) {
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\t---------------------------------";
    std::cout<<"\n\t| **** Digital Banking App **** |\n";
    std::cout<<"\t---------------------------------\n\n";
    std::cout<<"\tWelcome back "<<admin.getUsername()<<"!\n\n";
    rlutil::setColor(2);
    std::cout<<"\t[1] Show all users"<<'\n';
    std::cout<<"\t[2] Logout\n\n";

    rlutil::setColor(1);
    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    rlutil::setColor(2);

    while (std::cin>>option){
        switch(option) {
            case 1: {
                unsigned short val = 0;
                admin.showAllUsers(val);
                if (val == 1)
                    panelAdmin(admin);
                return;
            }
            case 2: {
                rlutil::setColor(4);
                std::cout<<"\n\tPlease wait...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                startApp();
                return;
            }
            default: {
                rlutil::setColor(4);
                std::cout<<"\n\tIncorrect option!\n";
                rlutil::setColor(1);
                std::cout<<"\n\tPlease select your choice: ";
            }
        }
    }
}
