#include "../libraries/digestpp.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <regex>
#include <sstream>
#include "../libraries/rlutil.h"
#include "../includes/Admin.h"
#include "../includes/Interface.h"


void Interface::startApp() {
    setLightMagenta;
    std::cout<<"\t---------------------------------";
    std::cout<<"\n\t| **** Digital Banking App **** |\n";
    std::cout<<"\t---------------------------------\n\n";
    setBlue;
    std::cout<<"\t[1] Login"<<'\n';
    std::cout<<"\t[2] Sign up"<<'\n';
    std::cout<<"\t[3] Exit"<<"\n\n";
    setBlue;
    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    while (std::cin>>option){
        switch (option) {
            case 1:{
                login();
                break;
            }
            case 2:{
                signup();
                break;
            }
            case 3:{
                setRed;
                std::cout<<"\n\tClosing the app...\n\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
            }
            default:{
                setRed;
                std::cout<<"\n\tIncorrect option!\n";
                break;
            }
        }
        setLightMagenta;
        std::cout<<"\t---------------------------------";
        std::cout<<"\n\t| **** Digital Banking App **** |\n";
        std::cout<<"\t---------------------------------\n\n";
        setGreen;
        std::cout<<"\t[1] Login"<<'\n';
        std::cout<<"\t[2] Sign up"<<'\n';
        std::cout<<"\t[3] Exit"<<"\n\n";
        setBlue;
        std::cout<<"\tPlease select your choice: ";
    }
}

void Interface::signup() {
    setLightMagenta;
    std::cout<<"\n\tSign up\n";
    setGreen;
    std::cout<<"\t[1] Continue"<<'\n';
    std::cout<<"\t[2] Back to main panel\n\n";
    setBlue;
    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    setGreen;
    while (std::cin>>option){
        switch(option) {
            case 1: {
                signupProcess();
                return;
            }
            case 2: {
                return;
            }
            default: {
                setRed;
                std::cout<<"\n\tIncorrect option!\n";
                break;
            }
        }
        setLightMagenta;
        std::cout<<"\n\tSign up\n";
        setGreen;
        std::cout<<"\t[1] Continue"<<'\n';
        std::cout<<"\t[2] Back to main panel\n\n";
        setBlue;
        std::cout<<"\tPlease select your choice: ";
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
        setGreen;
        std::cout<<"\n\tEmail: "; std::getline(std::cin,email);
        if (checkPatternEmail(email)){
            if (checkDuplicateEmail(email)){
                cond = true;
            }
            else{
                setRed;
                std::cout<<"\n\tEmail already exist! Try again...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        else{
            setRed;
            std::cout<<"\n\tInvalid email address! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    }

    cond = false;
    while (!cond){
        setGreen;
        std::cout<<"\n\tPassword: "; std::getline(std::cin,password);
        if (password.length()<7){
            setRed;
            std::cout<<"\n\tPassword must contain at least 7 characters!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
            cond = true;
    }

    cond = false;
    while (!cond){
        setGreen;
        std::cout<<"\n\tRepeat password: "; std::getline(std::cin,repeat_password);
        if (password != repeat_password){
            setRed;
            std::cout<<"\n\tPassword and Repeat Password don't match! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
            cond = true;
    }

    cond = false;
    while (!cond){
        setGreen;
        std::cout<<"\n\tPhone Number (Format: 07********): "; std::getline(std::cin,phone);
        if (checkPatternPhone(phone)){
            if (checkDuplicatePhone(phone))
                cond = true;
            else{
                setRed;
                std::cout<<"\n\tPhone number already exist! Try again...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        else{
            setRed;
            std::cout<<"\n\tInvalid phone format! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    cond = false;
    while (!cond){
        setGreen;
        std::cout<<"\n\tIBAN (Example: RO35RZBR4421944568612335): "; std::cin>>IBAN;
        if (checkPatternIBAN(IBAN)){
            if (checkDuplicateIBAN(IBAN))
                cond = true;
            else{
                setRed;
                std::cout<<"\n\tIBAN already exist! Try again...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        else{
            setRed;
            std::cout<<"\n\tInvalid IBAN format! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    setGreen;
    std::cout<<"\n\tExpiration date: ";
    cond = false;
    while (!cond){
        setGreen;
        std::cout<<"\n\t\tMonth: "; std::cin>>exp_date.first;
        if (exp_date.first >=1 && exp_date.first<=12)
            cond = true;
        else{
            setRed;
            std::cout<<"\n\tInvalid month! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    cond = false;
    while (!cond){
        setGreen;
        std::cout<<"\n\t\tYear (two digits): "; std::cin>>exp_date.second;
        if (exp_date.second >=22 && exp_date.second <=30)
            cond = true;
        else{
            setRed;
            std::cout<<"\n\tInvalid year! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    cond = false;
    while (!cond){
        setGreen;
        std::cout<<"\n\tCIV: "; std::cin>>civ;
        if (civ >=100 && civ <=999)
            cond = true;
        else{
            setRed;
            std::cout<<"\n\tInvalid CIV! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    std::string numeCompanie{};
    setGreen;
    std::cin.get();
    std::cout<<"\n\tNume companie (scrie 0 pentru persoana fizica): "; std::getline(std::cin,numeCompanie);

    cond = false;
    std::string cui{};
    while (!cond){
        setGreen;
        std::cout<<"\n\tCUI (scrie 0 pentru persoana fizica): "; std::cin>>cui;
        static const std::regex pattern("([0-9]*)");
        if (std::regex_match(cui, pattern))
            cond = true;
        else{
            setRed;
            std::cout<<"\n\tInvalid CUI format! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    static std::default_random_engine generator;
    static std::uniform_real_distribution<float> distribution(100,5000);
    float suma = distribution(generator);

    password = digestpp::blake2b(256).absorb(password).hexdigest();
    User u(name, password, email, phone, IBAN,
           exp_date, std::vector<std::shared_ptr<Tranzactie>>(),
           std::vector<std::shared_ptr<Message>>(), civ, suma);

    if (numeCompanie!="0" && cui!="0"){
        UserBusiness ub_aux(u,numeCompanie,cui);
        std::shared_ptr<UserBusiness> ub;
        ub = std::make_shared<UserBusiness>(ub_aux);
        ub->writeUserInFile();
    }
    else
        u.writeUserInFile();

    setCyan;
    std::cout<<"\n\tCreating account...";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<<"\n\tDone\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

bool Interface::checkDuplicateEmail(const std::string &email) {
    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    std::string line;
    std::regex separator("\\;");

    while (std::getline(login, line)){
        std::vector<std::string> out(
                std::sregex_token_iterator(line.begin(), line.end(), separator, -1),
                std::sregex_token_iterator()
        );
        if (out[1] == email)
            return false;
    }
    login.close();

    login.open("../txt_files/Admin/admins.txt",std::fstream::in);
    while (std::getline(login, line)){
        std::vector<std::string> out(
                std::sregex_token_iterator(line.begin(), line.end(), separator, -1),
                std::sregex_token_iterator()
        );
        if (out[1] == email)
            return false;
    }
    login.close();
    return true;
}

bool Interface::checkDuplicatePhone(const std::string &phone) {
    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    std::string line;
    std::regex separator("\\;");

    while (std::getline(login, line)){
        std::vector<std::string> out(
                std::sregex_token_iterator(line.begin(), line.end(), separator, -1),
                std::sregex_token_iterator()
        );
        if (out[3] == phone)
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
    std::regex separator("\\;");
    while (std::getline(login, line)){
        std::vector<std::string> out(
                std::sregex_token_iterator(line.begin(), line.end(), separator, -1),
                std::sregex_token_iterator()
        );
        if (out[4] == IBAN_copy)
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
    setLightMagenta;
    std::cout<<"\n\tLogin\n";
    setGreen;
    std::cout<<"\t[1] Continue"<<'\n';
    std::cout<<"\t[2] Back to main panel\n\n";
    setBlue;
    std::cout<<"\tPlease select your choice: ";
    setGreen;

    unsigned short option;
    while (std::cin>>option){
        switch(option) {
            case 1: {
                std::string email;
                std::string password;
                unsigned short tip=0;
                std::cout<<"\n\tEmail/Username (for admins): "; std::cin>>email;
                std::cout<<"\n\tPassword: ";    std::cin>>password;
                password = digestpp::blake2b(256).absorb(password).hexdigest();
                if (checkEmailPasswordLogin(email,password,tip)){
                    setCyan;
                    std::cout<<"\n\tLogin Succesful!\n\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    if (tip==2){
                        loginAdmin(email,password);
                    }
                    else
                        loginUser(email);
                }
                else{
                    setRed;
                    std::cout<<"\n\tWrong email/username(for admins) or password...\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                return;
            }
            case 2: {
                return;
            }
            default: {
                setRed;
                std::cout<<"\n\tIncorrect option!\n";
                break;
            }
        }
        setLightMagenta;
        std::cout<<"\n\tLogin\n";
        setGreen;
        std::cout<<"\t[1] Continue"<<'\n';
        std::cout<<"\t[2] Back to main panel\n\n";
        setBlue;
        std::cout<<"\tPlease select your choice: ";
        setGreen;
    }
}

void Interface::loginUser(const std::string &email) {
    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    std::string line;
    std::regex separator("\\;");

    while (std::getline(login, line)){
        std::vector<std::string> out(
                std::sregex_token_iterator(line.begin(), line.end(), separator, -1),
                std::sregex_token_iterator()
        );
        if (out[1] == email) {
            std::pair<unsigned short, unsigned short> temp;
            std::istringstream iss(out[5]);
            std::string date;
            std::getline(iss, date, '/');
            temp.first = stoi(date);
            std::getline(iss, date, '/');
            temp.second = stoi(date);

            User user(out[0], out[2], out[1], out[3], out[4], temp,
                      std::vector<std::shared_ptr<Tranzactie>>(),
                      std::vector<std::shared_ptr<Message>>(),
                      std::stoi(out[6]), std::stof(out[7]));

            if (out.size() > 8) {
                UserBusiness ub_var(user, out[8], out[9]);
                std::shared_ptr<UserBusiness> us_ptr = std::make_shared<UserBusiness>(ub_var);
                panelUser(us_ptr);
            } else {
                std::shared_ptr<User> us_ptr = std::make_shared<User>(user);
                panelUser(us_ptr);
            }
            login.close();
            break;
        }
    }
}

void Interface::loginAdmin(const std::string &email, const std::string &password) {
    std::fstream login;
    login.open("../txt_files/Admin/admins.txt",std::fstream::in);
    std::string line;
    std::regex separator("\\;");

    while (std::getline(login, line)){
        std::vector<std::string> out(
                std::sregex_token_iterator(line.begin(), line.end(), separator, -1),
                std::sregex_token_iterator()
        );
        if (out[0] == email || out[1]==email){
            Admin<std::string> ad(out[0], out[1], password);
            login.close();
            panelAdmin(ad);
            return;
        }
    }
}

bool Interface::checkEmailPasswordLogin(const std::string& email, const std::string& password,unsigned short& tip){
    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    std::string line;
    std::regex separator("\\;");

    while (std::getline(login, line)){
        std::vector<std::string> out(
                std::sregex_token_iterator(line.begin(), line.end(), separator, -1),
                std::sregex_token_iterator()
        );
        if (email == out[1]){
            if (password == out[2]){
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
        std::vector<std::string> out(
                std::sregex_token_iterator(line.begin(), line.end(), separator, -1),
                std::sregex_token_iterator()
        );
        if (email == out[0] || email == out[1]){
            if (password == out[2]){
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

void Interface::panelUser(const std::shared_ptr<User>& user) {
    Interface::showMenuPanelUser(user);
    unsigned short option;
    while (std::cin>>option){
        switch(option) {
            case 1: {
                user->showTransactionsHistory();
                break;
            }
            case 2: {
                user->showMessages();
                break;
            }
            case 3: {
                float suma_tranzactie = user->makeTransaction();
                user->updateBalance(user->getSuma() - suma_tranzactie);
                user->setSuma(user->getSuma() - suma_tranzactie);
                break;
            }
            case 4: {
                user->changePassword();
                break;
            }
            case 5: {
                setRed;
                std::cout<<"\n\tPlease wait...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
            }
            default: {
                setRed;
                std::cout<<"\n\tIncorrect option!\n";
                setBlue;
                std::cout<<"\n\tPlease select your choice: ";
                break;
            }
        }
        Interface::showMenuPanelUser(user);
    }
}

template <typename T>
void Interface::panelAdmin(Admin<T>& admin) {
    Interface::showMenuPanelAdmin(admin);
    unsigned short option;
    while (std::cin>>option){
        switch(option) {
            case 1: {
                admin.showAllUsers();
                break;
            }
            case 2: {
                setRed;
                std::cout<<"\n\tPlease wait...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
            }
            default: {
                setRed;
                std::cout<<"\n\tIncorrect option!\n";
                setBlue;
                std::cout<<"\n\tPlease select your choice: ";
                break;
            }
        }
        Interface::showMenuPanelAdmin(admin);
    }
}

void Interface::showMenuPanelUser(const std::shared_ptr<User> &user) {
    setLightMagenta;
    std::cout<<"\t---------------------------------";
    std::cout<<"\n\t| **** Digital Banking App **** |\n";
    std::cout<<"\t---------------------------------\n\n";
    std::cout<<"\tWelcome back "<<user->getNumePrenume()<<"!\n";
    std::cout<<"\tYour balance: "<<user->getSuma()<<"lei"<<"\n\n";
    setGreen;
    std::cout<<"\tInfo:\n";
    std::cout<<"\t Email: "<<user->getEmail()<<"\n";
    std::cout<<"\t Phone number: "<<user->getTelefon()<<"\n";
    std::cout<<"\t IBAN: "<<user->getIban()<<"\n";
    std::pair<unsigned short, unsigned short> date_aux = user->getExpDate();
    std::cout<<"\t Date exp: "<<date_aux.first<<"/"<<date_aux.second<<"\n";
    std::cout<<"\t CIV: "<<user->getCiv()<<"\n";
    user->showInfo(std::cout);
    setWhite;
    std::cout<<"\n\tMeniu:\n";
    std::cout<<"\t [1] Show transactions history\n";
    std::cout<<"\t [2] Show messages\n";
    std::cout<<"\t [3] Send money\n";
    std::cout<<"\t [4] Change password\n";
    std::cout<<"\t [5] Logout\n";
    setBlue;
    std::cout<<"\n\tPlease select your choice: ";
    setGreen;
    setWhite;
}

template <typename T>
void Interface::showMenuPanelAdmin(const Admin<T>& admin) {
    setLightMagenta;
    std::cout<<"\t---------------------------------";
    std::cout<<"\n\t| **** Digital Banking App **** |\n";
    std::cout<<"\t---------------------------------\n\n";
    std::cout<<"\tWelcome back "<<admin.getUsername()<<"!\n\n";
    setGreen;
    std::cout<<"\t[1] Show all users"<<'\n';
    std::cout<<"\t[2] Logout\n\n";

    setBlue;
    std::cout<<"\tPlease select your choice: ";
    setGreen;
}

Interface* Interface::interf = nullptr;

Interface *Interface::getInstance() {
    if(interf == nullptr)
        interf = new Interface();

    return interf;
}

void Interface::free() {
    delete interf;
}
