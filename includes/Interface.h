#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <thread>
#include <ctime>
#include <regex>
#include "Admin.h"
#include "rlutil.h"


class Interface{
    /// metodele de Signup
    void signup();
    void signupProcess();

    /// metodele pentru Signup
    static bool checkDuplicateEmail(const std::string&);
    static bool checkPatternEmail(const std::string&);
    static bool checkPatternPhone(const std::string&);
    static bool checkDuplicatePhone(const std::string&);
    static bool checkPatternIBAN(const std::string&);
    static bool checkDuplicateIBAN(const std::string&);

    /// metodele de Login
    void login();
    void loginUser(const std::string&);
    void loginAdmin(const std::string&, const std::string&);

    static bool checkEmailPasswordLogin(const std::string&, const std::string&, unsigned short&);

    /// metodele panel
    void panelAdmin(const Admin&);
    void panelUser(const User&);

public:
    /// metoda de Startup
    void startApp();
};

void Interface::startApp() {
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\t---------------------------------";
    std::cout<<"\n \t| **** Digital Banking App **** |\n";
    std::cout<<"\t---------------------------------\n\n";
    rlutil::setColor(2);
    std::cout<<"\t1. Login"<<'\n';
    std::cout<<"\t2. Sign up"<<'\n';
    std::cout<<"\t3. Exit"<<"\n\n";

    rlutil::setColor(1);
    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    if (std::cin>>option){
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
                startApp();
                return;
            }
        }
    }
}

void Interface::signup() {
    rlutil::cls();
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\n\t***** Digital Banking App *****\n\n";
    std::cout<<"\tSign up\n";
    rlutil::setColor(2);
    std::cout<<"\t1. Continue"<<'\n';
    std::cout<<"\t2. Back to main panel\n\n";

    rlutil::setColor(1);
    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    rlutil::setColor(2);

    if (std::cin>>option){
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
                std::this_thread::sleep_for(std::chrono::seconds(2));
                startApp();
                return;
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

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(100,5000);
    int suma = distribution(generator);

    User u(name, password, email, phone, IBAN, exp_date, {std::vector<Tranzactie>()},civ,suma);
    User::writeUserInFile(u);

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
    char line[500];
    while (login.getline(line,500)){
        char *p = std::strtok(line,";");
        p = std::strtok(nullptr,";");
        if (email==p)
            return false;
    }
    login.close();

    login.open("../txt_files/Admin/admins.txt",std::fstream::in);
    while (login.getline(line,500)){
        char *p = std::strtok(line,";");
        p = std::strtok(nullptr,";");
        if (email==p)
            return false;
    }
    login.close();
    return true;
}

bool Interface::checkDuplicatePhone(const std::string &phone) {
    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    char line[500];
    while (login.getline(line,500)){
        char *p = std::strtok(line,";");
        p = std::strtok(nullptr,";");
        p = std::strtok(nullptr,";");
        p = std::strtok(nullptr,";");
        if (phone==p)
            return false;
    }
    login.close();
    return true;
}

bool Interface::checkDuplicateIBAN(const std::string &IBAN) {
    std::string IBAN_copy = IBAN;
    std::transform(IBAN_copy.begin(), IBAN_copy.end(), IBAN_copy.begin(), ::toupper);    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    char line[500];
    while (login.getline(line,500)){
        char *p = std::strtok(line,";");
        p = std::strtok(nullptr,";");
        p = std::strtok(nullptr,";");
        p = std::strtok(nullptr,";");
        p = std::strtok(nullptr,";");
        if (IBAN_copy==p)
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
    rlutil::cls();
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\n\t***** Digital Banking App *****\n\n";
    std::cout<<"\tLogin\n";
    rlutil::setColor(2);

    std::cout<<"\t1. Continue"<<'\n';
    std::cout<<"\t2. Back to main panel\n\n";

    rlutil::setColor(1);
    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    rlutil::setColor(2);

    if (std::cin>>option){
        switch(option) {
            case 1: {
                std::string email;
                std::string password;
                unsigned short tip=0;
                std::cout<<"\n\tEmail/Username (for admins): "; std::cin>>email;
                std::cout<<"\n\tPassword: ";    std::cin>>password;
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
                startApp();
                return;
            }
        }
    }
}

void Interface::loginUser(const std::string &email) {
    User user;
    std::fstream write;
    write.open("../txt_files/User/users.txt",std::fstream::in);
    char line[500];
    while (write.getline(line,500)){
        char *p = std::strtok(line,";");
        std::string nume(p);
        p = std::strtok(nullptr,";");
        if (p == email){
            user.setNumePrenume(nume);
            user.setEmail(email);

            p = std::strtok(nullptr,";");
            user.setParola(p);

            p = std::strtok(nullptr,";");
            user.setTelefon(p);

            p = std::strtok(nullptr,";");
            user.setIban(p);

            p = std::strtok(nullptr,";");
            char aux[6];
            strcpy(aux,p);

            p = std::strtok(nullptr,";");
            user.setCiv(atoi(p));

            p = std::strtok(nullptr,";");
            user.setSuma(atoi(p));

            char *ptr = strtok(aux,"/");
            auto n1 = (unsigned short) atoi(ptr);
            ptr = strtok(nullptr," /");
            auto n2 = (unsigned short) atoi(ptr);
            std::pair<unsigned short , unsigned short> temp;
            temp.first = n1;
            temp.second = n2;
            user.setExpDate(temp);

            write.close();
            panelUser(user);
            break;
        }
    }
}

void Interface::loginAdmin(const std::string &email,const std::string &password) {
    Admin ad;
    std::fstream write;
    write.open("../txt_files/Admin/admins.txt",std::fstream::in);
    char line[500];
    while (write.getline(line,500)){
        char *p = std::strtok(line,";");
        std::string username(p);
        p = std::strtok(nullptr,";");
        if (p == email || username==email){
            ad.setParola(password);
            ad.setUsername(username);
            ad.setEmail(p);
            write.close();
            panelAdmin(ad);
            break;
        }
    }
}

bool Interface::checkEmailPasswordLogin(const std::string& email, const std::string& password,unsigned short& tip){
    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    char line[500];
    while (login.getline(line,500)){
        char *p = std::strtok(line,";");
        p = std::strtok(nullptr,";");
        if (email == p){
            p = std::strtok(nullptr,";");
            if (password == p){
                tip = 1;
                return true;
            }
            else
                return false;
        }
    }
    login.close();

    login.open("../txt_files/Admin/admins.txt",std::fstream::in);
    while (login.getline(line,500)){
        char *p = std::strtok(line,";");
        if (email == p){
            p = std::strtok(nullptr,";");
            p = std::strtok(nullptr,";");
            if (password == p){
                tip = 2;
                return true;
            }
            else
                return false;
        }
        p = std::strtok(nullptr,";");
        if (email == p){
            p = std::strtok(nullptr,";");
            if (password == p){
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

void Interface::panelUser(const User &user) {
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\t---------------------------------";
    std::cout<<"\n \t| **** Digital Banking App **** |\n";
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
    std::cout<<"\t CIV: "<<user.getCiv()<<"\n\n";

    rlutil::setColor(15);
    std::cout<<"\tMeniu:\n";
    std::cout<<"\t 1. Show transactions history\n";
    std::cout<<"\t 2. Send money\n";
    std::cout<<"\t 3. Change password\n";
    std::cout<<"\t 4. Logout\n";

    rlutil::setColor(1);
    std::cout<<"\n\tPlease select your choice: ";

    unsigned short option;
    rlutil::setColor(2);

    if (std::cin>>option){
        switch(option) {
            case 1: {
                User::showTransactionsHistory(const_cast<User &>(user));
                Interface::panelUser(user);
                return;
            }
            case 2: {
                unsigned int suma_tranzactie = User::makeTransaction(const_cast<User &>(user));
                User::updateBalance("../txt_files/User/users.txt", user.getSuma() - suma_tranzactie, const_cast<User &>(user));
                Interface::loginUser(user.getEmail());
                return;
            }
            case 3: {
                User::changePassword(const_cast<User &>(user));
                panelUser(user);
                return;
            }
            case 4: {
                rlutil::setColor(4);
                std::cout<<"\n\tPlease wait...\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                startApp();
                return;
            }
            default: {
                rlutil::setColor(4);
                std::cout<<"\n\tIncorrect option!\n";
                panelUser(user);
                return;
            }
        }
    }
}

void User::updateBalance(const std::string &file_name, const unsigned int &suma_tranzactie, const User& user) {
    std::fstream old_file;
    std::ofstream new_file ("../txt_files/User/temporary.txt");
    old_file.open("../txt_files/User/users.txt",std::fstream::in);
    char line[500];
    while (old_file.getline(line,500)){
        std::string copy = line;
        char *p = strtok(line,";");
        if (p == user.getNumePrenume()){
            new_file<<p<<";";
            p = strtok(nullptr,";");

            new_file<<p<<";";
            p = strtok(nullptr,";");

            new_file<<p<<";";
            p = strtok(nullptr,";");

            new_file<<p<<";";
            p = strtok(nullptr,";");

            new_file<<p<<";";
            p = strtok(nullptr,";");

            new_file<<p<<";";
            p = strtok(nullptr,";");

            new_file<<p<<";";
            p = strtok(nullptr,";");

            new_file<<suma_tranzactie<<"\n";
        }
        else
            new_file<<copy<<'\n';
    }

    old_file.close(); new_file.close();
    int result = remove("../txt_files/User/users.txt");
    result = rename("../txt_files/User/temporary.txt","../txt_files/User/users.txt");
    result = remove("../txt_files/User/temporary.txt");
}

void User::showTransactionsHistory(User &user) {
    rlutil::setColor(5);
    std::cout<<"\n\tTransaction History: ";

    std::string file_name = "../txt_files/User/" + user.getEmail() + "_transactions.txt";
    std::ifstream file;
    file.open(file_name);
    if (!file)
        std::cout<<"empty\n\n";
    else{
        std::vector<Tranzactie> transactions = User::loadTransactionsHistory(user.getEmail(),file_name);
        std::cout<<"\n"; rlutil::setColor(2);
        for (auto & transaction : transactions)
            std::cout<<transaction;
    }
    file.close();

    rlutil::setColor(1);
    std::cout<<"\n\tGo back to all users panel - type 1\n\n";

    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    rlutil::setColor(2);

    if (std::cin>>option){
        if (option==1){
            rlutil::setColor(4);
            std::cout<<"\n\tWait...\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else{
            rlutil::setColor(4);
            std::cout<<"\n\tIncorrect option!\n";
            User::showTransactionsHistory(user);
        }
    }
}

std::vector<Tranzactie> User::loadTransactionsHistory(const std::string &user, const std::string& file_name) {
    std::vector<Tranzactie> transactions;
    std::ifstream file;
    file.open(file_name);
    char line[500];
    int n = 0;
    while (file.getline(line,500)){
        transactions.resize(n+1);

        char *p = strtok(line,";");
        transactions[n].setDestinatar(p);

        p = strtok(nullptr,";");
        transactions[n].setIbanDestinatar(p);

        p = strtok(nullptr,";");
        transactions[n].setSumaTrimisa((unsigned int)atoi(p));

        p = strtok(nullptr,";");
        transactions[n].setZi((unsigned short)atoi(p));

        p = strtok(nullptr,";");
        transactions[n].setLuna((unsigned short)atoi(p));

        p = strtok(nullptr,";");
        transactions[n].setAn((unsigned short)atoi(p));

        p = strtok(nullptr,";");
        transactions[n].setOra((unsigned short)atoi(p));

        p = strtok(nullptr,";");
        transactions[n].setType(p);

        n++;
    }
    file.close();
    return transactions;
}

unsigned int User::makeTransaction(User &user) {
    rlutil::setColor(5);
    std::cout<<"\n\tSend money: ";

    rlutil::setColor(1);
    std::cout<<"\n\t1. Continue";
    std::cout<<"\n\t2. Go back";

    std::cout<<"\n\n\tPlease select your choice: ";

    unsigned short option;
    rlutil::setColor(2);
    if (std::cin>>option){
        switch (option) {
            case 1:{
                unsigned int suma = User::makeTansactionCase1(user);
                rlutil::setColor(4);
                std::cout<<"\n\tPlease wait... ";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout<<"Success!\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return suma;
            }
            case 2:{
                return 0;
            }
            default:{
                rlutil::setColor(4);
                std::cout<<"\n\tIncorrect option!\n";
                makeTransaction(user);
                return 0;
            }
        }
    }
    return 0;
}

unsigned int User::makeTansactionCase1(User &user) {
    std::string destinatar;
    std::string IBAN_dest;
    unsigned int suma;
    unsigned short zi, luna, an, ora;

    rlutil::setColor(2);
    std::cin.get();
    std::cout<<"\n\tEnter full name: "; std::getline(std::cin,destinatar);

    bool cond = false;
    while (!cond){
        rlutil::setColor(2);
        std::cout<<"\n\tEnter the sum of money: "; std::cin>>suma;
        if (suma>user.getSuma()){
            rlutil::setColor(4);
            std::cout<<"\n\tYour balance has only "<<user.getSuma()<<" lei! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
            cond = true;
    }

    cond = false;
    while (!cond){
        rlutil::setColor(2);
        std::cout<<"\n\tEnter the IBAN: "; std::cin>>IBAN_dest;
        if (Tranzactie::checkPatternIBAN(IBAN_dest) && IBAN_dest!=user.getIban()){
            cond = true;
            if (User::checkDuplicateIBAN(IBAN_dest)){
                User user_aux = returnUser(IBAN_dest);
                User::updateBalance("../txt_files/User/users.txt", user_aux.getSuma() + suma, user_aux);

                time_t theTime = time(nullptr);
                struct tm *aTime = localtime(&theTime);
                zi = aTime->tm_mday;
                luna = aTime->tm_mon + 1;
                an = aTime->tm_year + 1900;
                ora = aTime->tm_hour;

                Tranzactie tran;
                tran.setDestinatar(user.getNumePrenume());
                tran.setIbanDestinatar(user.getIban());
                tran.setSumaTrimisa(suma);
                tran.setZi(zi);
                tran.setLuna(luna);
                tran.setAn(an);
                tran.setOra(ora);
                tran.setType("recived");

                std::string file_name = "../txt_files/User/" + user_aux.getEmail() + "_transactions.txt";
                std::fstream file;
                file.open(file_name,std::fstream::app);
                if (!file) {
                    file.close();
                    file.open(file_name,std::fstream::in);
                    Tranzactie::writeInFile(file,tran);
                }
                else{
                    Tranzactie::writeInFile(file,tran);
                    file.close();
                }
            }
        }
        else{
            rlutil::setColor(4);
            std::cout<<"\n\tInvalid IBAN format! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    time_t theTime = time(nullptr);
    struct tm *aTime = localtime(&theTime);
    zi = aTime->tm_mday;
    luna = aTime->tm_mon + 1;
    an = aTime->tm_year + 1900;
    ora = aTime->tm_hour;

    Tranzactie tran;
    tran.setDestinatar(destinatar);
    tran.setIbanDestinatar(IBAN_dest);
    tran.setSumaTrimisa(suma);
    tran.setZi(zi);
    tran.setLuna(luna);
    tran.setAn(an);
    tran.setOra(ora);
    tran.setType("sent");

    std::string file_name = "../txt_files/User/" + user.getEmail() + "_transactions.txt";
    std::fstream file;
    file.open(file_name,std::fstream::app);
    if (!file) {
        file.close();
        file.open(file_name,std::fstream::in);
        Tranzactie::writeInFile(file,tran);
    }
    else{
        Tranzactie::writeInFile(file,tran);
        file.close();
    }
    return suma;
}

User User::returnUser(const std::string &IBAN) {
    std::fstream file;
    file.open("../txt_files/User/users.txt",std::fstream::in);
    char line[500];
    std::string nume_cp, email_cp, parola_cp, telefon_cp, IBAN_cp;
    std::pair<unsigned short, unsigned short> exp_date_cp;
    int CIV_cp;
    int suma_cp;
    while (file.getline(line,500)){
        char *p = std::strtok(line,";"); nume_cp = p;
        p = std::strtok(nullptr,";"); email_cp = p;
        p = std::strtok(nullptr,";"); parola_cp = p;
        p = std::strtok(nullptr,";"); telefon_cp = p;
        p = std::strtok(nullptr,";"); IBAN_cp = p;

        p = std::strtok(nullptr,";");
        char cp[6];
        strcpy(cp,p);

        p = std::strtok(nullptr,";"); CIV_cp = atoi(p);
        p = std::strtok(nullptr,";"); suma_cp = atoi(p);

        char *ptr = strtok(cp,"/"); exp_date_cp.first = atoi(ptr);
        ptr = strtok(nullptr," /"); exp_date_cp.second = atoi(ptr);

    }
    file.close();
    User user(nume_cp, parola_cp, email_cp, telefon_cp, IBAN_cp, exp_date_cp, {std::vector<Tranzactie>()},CIV_cp,suma_cp);
    return user;
}

bool User::checkDuplicateIBAN(const std::string &IBAN) {
    std::string IBAN_copy = IBAN;
    std::transform(IBAN_copy.begin(), IBAN_copy.end(), IBAN_copy.begin(), ::toupper);
    std::fstream login;
    login.open("../txt_files/User/users.txt",std::fstream::in);
    char line[500];
    while (login.getline(line,500)){
        char *p = std::strtok(line,";");
        p = std::strtok(nullptr,";");
        p = std::strtok(nullptr,";");
        p = std::strtok(nullptr,";");
        p = std::strtok(nullptr,";");
        if (IBAN_copy==p)
            return true;
    }
    login.close();
    std::cout<<"1\n";
    return false;
}

void User::changePassword(User &user) {
    unsigned short option2;
    std::cout<<"\n\tIf you want to continue, type 1, else type 2: ";
    std::cin>>option2;

    if (option2 == 2){
        rlutil::setColor(4);
        std::cout<<"\n\n\tPlease wait...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    else{
        rlutil::cls();
        std::string parola_curenta, parola_noua, parola_noua_repetare;

        bool cond;
        cond = false;
        while (!cond){
            rlutil::setColor(2);
            std::cout<<"\n\tEnter your password: "; std::cin>>parola_curenta;
            if (parola_curenta == user.getParola())
                cond = true;
            else{
                rlutil::setColor(4);
                std::cout<<"\n\n\tWrong password! Try again...\n";
            }
        }

        cond = false;
        while (!cond){
            rlutil::setColor(2);
            std::cout<<"\n\tNew password: "; std::cin>>parola_noua;

            if (parola_noua.length()<7){
                rlutil::setColor(4);
                std::cout<<"\n\tPassword must contain at least 7 characters!\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            else{
                std::cout<<"\n\tRepeat password: "; std::cin>>parola_noua_repetare;
                if (parola_noua == parola_noua_repetare)
                    cond = true;
                else{
                    rlutil::setColor(4);
                    std::cout<<"\n\tPassword and Repeat Password don't match! Try again...\n";
                }
            }
        }

        std::fstream old_file;
        std::ofstream new_file ("../txt_files/User/temporary.txt");
        old_file.open("../txt_files/User/users.txt",std::fstream::in);
        char line[500];
        while (old_file.getline(line,500)){
            std::string copy = line;
            char *p = strtok(line,";");
            if (p == user.getNumePrenume()){
                new_file<<p<<";";
                p = strtok(nullptr,";");
                new_file<<p<<";";
                p = strtok(nullptr,";");
                new_file<<parola_noua<<";";
                p = strtok(nullptr,";");
                new_file<<p<<";";
                p = strtok(nullptr,";");
                new_file<<p<<";";
                p = strtok(nullptr,";");
                new_file<<p<<";";
                p = strtok(nullptr,";");
                new_file<<p<<";";
                p = strtok(nullptr,";");
                new_file<<p<<"\n";
            }
            else
                new_file<<copy<<'\n';
        }

        old_file.close(); new_file.close();
        int result = remove("../txt_files/User/users.txt");
        result = rename("../txt_files/User/temporary.txt","../txt_files/User/users.txt");
        result = remove("../txt_files/User/temporary.txt");

        if (result){
            rlutil::setColor(4);
            std::cout<<"\n\tPassword changed!\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

    }
}

void Interface::panelAdmin(const Admin& admin) {
    rlutil::setColor(13);
    rlutil::setBackgroundColor(0);
    std::cout<<"\t---------------------------------";
    std::cout<<"\n \t| **** Digital Banking App **** |\n";
    std::cout<<"\t---------------------------------\n\n";
    std::cout<<"\tWelcome back "<<admin.getUsername()<<"!\n\n";
    rlutil::setColor(2);
    std::cout<<"\t1. Show all users"<<'\n';
    std::cout<<"\t2. Logout\n\n";

    rlutil::setColor(1);
    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    rlutil::setColor(2);

    if (std::cin>>option){
        switch(option) {
            case 1: {
                unsigned short val = 0;
                Admin::showAllUsers(admin,val);
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
                panelAdmin(admin);
                return;
            }
        }
    }
    else
        return;
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
    char line[500];
    int n = 0;
    while (login.getline(line,500)){
        std::cout<<"\t"<<n+1<<" ";
        char *p = std::strtok(line,";");
        std::cout<<"\t"<<p<<" ";
        users[n].setNumePrenume(p);
        p = std::strtok(nullptr,";");
        std::cout<<"\t"<<p<<"\n";
        users[n].setEmail(p);
        p = std::strtok(nullptr,";");

        users[n].setParola(p);
        p = std::strtok(nullptr,";");

        users[n].setTelefon(p);
        p = std::strtok(nullptr,";");

        users[n].setIban(p);
        p = std::strtok(nullptr,";");

        char aux[6];
        strcpy(aux,p);

        p = std::strtok(nullptr,";");
        users[n].setCiv(atoi(p));

        p = std::strtok(nullptr,";");
        users[n].setSuma(atoi(p));

        char *ptr = strtok(aux,"/");
        auto n1 = (unsigned short) atoi(ptr);
        ptr = strtok(nullptr," /");
        auto n2 = (unsigned short) atoi(ptr);
        std::pair<unsigned short , unsigned short> temp;
        temp.first = n1;
        temp.second = n2;
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