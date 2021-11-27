#include "../includes/User.h"
#include "../includes/UserBusiness.h"
#include "../libraries/rlutil.h"
#include "../libraries/hasher.hpp"
#include "../libraries/digestpp.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>
#include <regex>
#include <sstream>

#define setBlue rlutil::setColor(1)
#define setGreen rlutil::setColor(2)
#define setRed rlutil::setColor(4)
#define setMagenta rlutil::setColor(5)
#define setLightMagenta rlutil::setColor(13)
#define setWhite rlutil::setColor(15)


User::User(const User &copie) {
    nume_prenume = copie.nume_prenume;
    parola = copie.parola;
    email = copie.email;
    telefon = copie.telefon;
    IBAN = copie.IBAN;
    exp_date = copie.exp_date;
    CIV = copie.CIV;
    suma = copie.suma;
    transaction_history = copie.transaction_history;
}

User &User::operator=(const User &copie) {
    nume_prenume = copie.nume_prenume;
    parola = copie.parola;
    email = copie.email;
    telefon = copie.telefon;
    IBAN = copie.IBAN;
    exp_date = copie.exp_date;
    CIV = copie.CIV;
    suma = copie.suma;
    transaction_history = copie.transaction_history;
    return *this;
}

void User::showInfo(std::ostream &os) const{}

std::ostream &operator<<(std::ostream &os, const std::shared_ptr<User>& user) {
    setLightMagenta;
    os<<"\n\t Info about "<<user->nume_prenume<<"\n\n";
    setGreen;
    os<<"\t First name and last name: "<<user->nume_prenume<<"\n";
    os<<"\t Email: "<<user->email<<"\n";
    os<<"\t Phone number: "<<user->telefon<<"\n";
    os<<"\t IBAN: "<<user->IBAN<<"\n";
    os<<"\t Balance: "<<user->suma<<"lei\n";
    user->showInfo(os);

    setWhite;
    std::cout<<"\n\t Transaction History: ";

    const auto &t = user->loadTransactionsHistory();
    if (t.empty())
        os<<"empty\n\n";
    else{
        os<<"\n\n";
        for (const auto & i : t)
            os<<"\t"<<*i<<"\n";
    }
    return os;
}

void User::writeUserInFile() {
    try{
        std::fstream write;
        write.open("../txt_files/User/users.txt",std::fstream::app);
        write.exceptions(std::ifstream::badbit);
        write<< nume_prenume<<';'<<email<<';'<<parola<<';';
        write<< telefon<<';'<<IBAN<<';'<<exp_date.first<<'/'<<exp_date.second<<';';
        write<< CIV<<';'<<suma<<'\n';
        write.close();
        write.open("../txt_files/User/users.txt",std::fstream::app);
        write.close();
    }
    catch (std::exception& e) {
        setRed;
        std::cout << "\n\t(Error) " << e.what() << "\n";
    }
}

const std::string &User::getNumePrenume() const {
    return nume_prenume;
}

void User::setNumePrenume(const std::string &numePrenume) {
    nume_prenume = numePrenume;
}

void User::setParola(const std::string &parola_copie) {
    User::parola = parola_copie;
}

const std::string &User::getEmail() const {
    return email;
}

void User::setEmail(const std::string &email_copie) {
    User::email = email_copie;
}

const std::string &User::getTelefon() const {
    return telefon;
}

void User::setTelefon(const std::string &telefon_copie) {
    User::telefon = telefon_copie;
}

void User::setIban(const std::string &iban) {
    IBAN = iban;
}

const std::pair<unsigned short, unsigned short> &User::getExpDate() const {
    return exp_date;
}

void User::setExpDate(const std::pair<unsigned short, unsigned short> &expDate) {
    exp_date = expDate;
}

const std::string &User::getIban() const {
    return IBAN;
}

float User::getSuma() const {
    return suma;
}

void User::setSuma(float suma_copie) {
    User::suma = suma_copie;
}

int User::getCiv() const {
    return CIV;
}

void User::setCiv(int civ) {
    CIV = civ;
}

void User::updateBalance(const float &suma_tranzactie) {
    try{
        std::fstream old_file;
        std::ofstream new_file ("../txt_files/User/temporary.txt");
        old_file.open("../txt_files/User/users.txt",std::fstream::in);
        old_file.exceptions(std::ifstream::badbit);
        std::string line;
        while (std::getline(old_file, line)){
            const std::string& copy(line);
            std::istringstream iss(line);
            std::string word, aux_nume;
            std::getline(iss, word, ';');
            aux_nume = word;
            std::getline(iss, word, ';');
            if (word == email){
                new_file<<aux_nume<<";"<<word<<";";
                std::getline(iss, word, ';');

                new_file<<word<<";";
                std::getline(iss, word, ';');

                new_file<<word<<";";
                std::getline(iss, word, ';');

                new_file<<word<<";";
                std::getline(iss, word, ';');

                new_file<<word<<";";
                std::getline(iss, word, ';');

                new_file<<word<<";";
                std::getline(iss, word, ';');

                new_file<<suma_tranzactie<<";";

                User::updateUserInFile(new_file);

                new_file<<"\n";
            }
            else
                new_file<<copy<<'\n';
        }

        old_file.close(); new_file.close();
        updateFileFromTemp();
    }
    catch (std::exception& e) {
        setRed;
        std::cout << "\n\t(Error) " << e.what() << "\n";
    }
}

void User::showTransactionsHistory() const{
    try{
        setMagenta;
        std::cout<<"\n\tTransaction History: ";
        std::string file_name = "../txt_files/User/" + email + "_transactions.txt";
        std::ifstream file;
        file.open(file_name);
        file.exceptions(std::ifstream::badbit);
        if (!file)
            std::cout<<"empty\n\n";
        else{
            std::vector<std::shared_ptr<Tranzactie>> transactions = User::loadTransactionsHistory();
            std::cout<<"\n"; setGreen;
            for (auto & transaction : transactions)
                std::cout<<*transaction;
        }
        file.close();

        setBlue;
        std::cout<<"\n\tGo back to all users panel - type 1\n\n";

        std::cout<<"\tPlease select your choice: ";

        unsigned short option;
        setGreen;

        while (std::cin>>option){
            if (option==1){
                setRed;
                std::cout<<"\n\tWait...\n\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
            }
            else{
                setRed;
                std::cout<<"\n\tIncorrect option!\n";
                setBlue;
                std::cout<<"\n\tPlease select your choice: ";
            }
        }
    }
    catch (std::exception& e) {
        setRed;
        std::cout << "\n\t(Error) " << e.what() << "\n";
    }
}

std::vector<std::shared_ptr<Tranzactie>> User::loadTransactionsHistory() const{
    try{
        std::string file_name = "../txt_files/User/" + email + "_transactions.txt";
        std::vector<std::shared_ptr<Tranzactie>> transactions;
        std::ifstream file;
        file.open(file_name);
        file.exceptions(std::ifstream::badbit);
        std::string line;

        while (std::getline(file, line)){
            Tranzactie tranzactie_curenta;
            std::istringstream iss(line);
            std::string word;

            std::getline(iss, word, ';');
            tranzactie_curenta.setDestinatar(word);

            std::getline(iss, word, ';');
            tranzactie_curenta.setIbanDestinatar(word);

            std::getline(iss, word, ';');
            tranzactie_curenta.setSumaTrimisa(stof(word));

            data_str data_cp{};

            std::getline(iss, word, ';');
            data_cp.zi = (unsigned short)stoi(word);

            std::getline(iss, word, ';');
            data_cp.luna = (unsigned short)stoi(word);

            std::getline(iss, word, ';');
            data_cp.an = (unsigned short)stoi(word);

            std::getline(iss, word, ';');
            data_cp.ora = (unsigned short)stoi(word);

            tranzactie_curenta.setData(data_cp);

            std::getline(iss, word, ';');
            tranzactie_curenta.setType(word);

            transactions.emplace_back(std::make_shared<Tranzactie>(tranzactie_curenta));
        }
        file.close();
        return transactions;
    }
    catch (std::exception& e) {
        setRed;
        std::cout << "\n\t(Error) " << e.what() << "\n";
        return {};
    }
}

float User::makeTransaction() {
    setMagenta;
    std::cout<<"\n\tSend money: ";
    setBlue;
    std::cout<<"\n\t[1] Continue";
    std::cout<<"\n\t[2] Go back";
    std::cout<<"\n\n\tPlease select your choice: ";

    unsigned short option;
    setGreen;
    while (std::cin>>option){
        if (option == 1) {
                float suma_ = makeTansactionCase1();
                setRed;
                std::cout<<"\n\tPlease wait... ";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout<<"Success!\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return suma_;
        }
        else{
            if (option == 2)
                return 0;
            else{
                setRed;
                std::cout<<"\n\tIncorrect option!\n";
                setBlue;
                std::cout<<"\n\tPlease select your choice: ";
            }
        }
    }
    return 0;
}

float User::makeTansactionCase1() {
    std::string destinatar;
    std::string IBAN_dest;
    float suma_;
    unsigned short zi, luna, an, ora;

    setGreen;
    std::cin.get();
    std::cout<<"\n\tEnter full name: "; std::getline(std::cin,destinatar);

    bool cond = false;
    while (!cond){
        setGreen;
        std::cout<<"\n\tEnter the sum of money: "; std::cin>>suma_;
        if (suma_>suma){
            setRed;
            std::cout<<"\n\tYour balance has only "<<suma<<" lei! Try again...\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        else
            cond = true;
    }

    cond = false;
    while (!cond){
        setGreen;
        std::cout<<"\n\tEnter the IBAN: "; std::cin>>IBAN_dest;
        Tranzactie tran;
        if (tran.checkPatternIBAN(IBAN_dest) && IBAN_dest!=IBAN){
            cond = true;
            if (checkDuplicateIBAN(IBAN_dest)){
                User user_aux = returnUser(IBAN_dest);
                user_aux.updateBalance(user_aux.suma + suma_);

                time_t theTime = time(nullptr);
                struct tm *aTime = localtime(&theTime);
                zi = aTime->tm_mday;
                luna = aTime->tm_mon + 1;
                an = aTime->tm_year + 1900;
                ora = aTime->tm_hour;


                tran.setDestinatar(nume_prenume);
                tran.setIbanDestinatar(IBAN);
                tran.setSumaTrimisa(suma_);
                data_str data_cp{};
                data_cp.zi = zi;
                data_cp.luna = luna;
                data_cp.an = an;
                data_cp.ora = ora;
                tran.setData(data_cp);
                tran.setType("recived");

                std::string file_name = "../txt_files/User/" + user_aux.email + "_transactions.txt";
                std::fstream file;
                file.open(file_name,std::fstream::app);
                if (!file) {
                    file.close();
                    file.open(file_name,std::fstream::in);
                    tran.writeInFile(file);
                }
                else{
                    tran.writeInFile(file);
                    file.close();
                }
            }
        }
        else{
            setRed;
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
    tran.setSumaTrimisa(suma_);
    data_str data_cp{};
    data_cp.zi = zi;
    data_cp.luna = luna;
    data_cp.an = an;
    data_cp.ora = ora;
    tran.setData(data_cp);
    tran.setType("sent");

    std::string file_name = "../txt_files/User/" + email + "_transactions.txt";
    std::fstream file;
    file.open(file_name,std::fstream::app);
    if (!file) {
        file.close();
        file.open(file_name,std::fstream::in);
        tran.writeInFile(file);
    }
    else{
        tran.writeInFile(file);
        file.close();
    }
    return suma_;
}

User User::returnUser(const std::string &IBAN_) {
    std::fstream file;
    file.open("../txt_files/User/users.txt",std::fstream::in);
    std::string nume_cp, email_cp, parola_cp, telefon_cp, IBAN_cp;
    std::pair<unsigned short, unsigned short> exp_date_cp;
    int CIV_cp;
    float suma_cp;
    std::string line;
    while (std::getline(file, line)){
        std::istringstream iss(line);
        std::string word;
        std::getline(iss, word, ';'); nume_cp = word;
        std::getline(iss, word, ';'); email_cp = word;
        std::getline(iss, word, ';'); parola_cp = word;
        std::getline(iss, word, ';'); telefon_cp = word;
        std::getline(iss, word, ';'); IBAN_cp = word;

        std::getline(iss, word, ';');
        std::string aux(word);

        std::getline(iss, word, ';'); CIV_cp = stoi(word);
        std::getline(iss, word, ';');  suma_cp = stof(word);

        std::istringstream iss1(aux);
        std::string date;
        std::getline(iss1, date, '/');
        exp_date_cp.first = stoi(date);
        std::getline(iss1, date, '/');
        exp_date_cp.second = stoi(date);

        if (IBAN_cp == IBAN_)
            break;
    }
    file.close();
    User user(nume_cp, parola_cp, email_cp, telefon_cp, IBAN_cp, exp_date_cp, std::vector<std::shared_ptr<Tranzactie>>(), std::vector<std::shared_ptr<Message>>(), CIV_cp,suma_cp);
    return user;
}

bool User::checkDuplicateIBAN(const std::string &IBAN_) {
    std::string IBAN_copy = IBAN_;
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
            return true;
    }
    login.close();
    return false;
}

void User::changePassword() {
    unsigned short option2;
    std::cout<<"\n\tIf you want to continue, type 1, else type 2: ";
    std::cin>>option2;

    if (option2 == 2){
        setRed;
        std::cout<<"\n\n\tPlease wait...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    else{
        std::string parola_curenta, parola_noua, parola_noua_repetare;

        bool cond;
        cond = false;
        while (!cond){
            setGreen;
            std::cout<<"\n\tEnter your password: "; std::cin>>parola_curenta;
            parola_curenta = digestpp::blake2b(256).absorb(parola_curenta).hexdigest();
            if (parola_curenta == parola)
                cond = true;
            else{
                setRed;
                std::cout<<"\n\n\tWrong password! Try again...\n";
            }
        }

        cond = false;
        while (!cond){
            setGreen;
            std::cout<<"\n\tNew password: "; std::cin>>parola_noua;
            if (parola_noua.length()<7){
                setRed;
                std::cout<<"\n\tPassword must contain at least 7 characters!\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            else{
                std::cout<<"\n\tRepeat password: "; std::cin>>parola_noua_repetare;
                if (parola_noua == parola_noua_repetare)
                    cond = true;
                else{
                    setRed;
                    std::cout<<"\n\tPassword and Repeat Password don't match! Try again...\n";
                }
            }
        }
        parola_noua = digestpp::blake2b(256).absorb(parola_noua).hexdigest();
        std::fstream old_file;
        std::ofstream new_file ("../txt_files/User/temporary.txt");
        old_file.open("../txt_files/User/users.txt",std::fstream::in);
        std::string line;
        while (std::getline(old_file, line)){
            const std::string& copy(line);
            std::istringstream iss(line);
            std::string word;
            std::getline(iss, word, ';');

            if (word == getNumePrenume()){
                new_file<<word<<";";
                std::getline(iss, word, ';');
                new_file<<word<<";";
                std::getline(iss, word, ';');
                new_file<<parola_noua<<";";
                std::getline(iss, word, ';');
                new_file<<word<<";";
                std::getline(iss, word, ';');
                new_file<<word<<";";
                std::getline(iss, word, ';');
                new_file<<word<<";";
                std::getline(iss, word, ';');
                new_file<<word<<";";
                std::getline(iss, word, ';');
                new_file<<word<<";";
                User::updateUserInFile(new_file);
                new_file<<"\n";
            }
            else
                new_file<<copy<<'\n';
        }

        old_file.close(); new_file.close();
        User::updateFileFromTemp();
    }
}

void User::showMessages() const {
    try{
        setMagenta;
        std::cout<<"\n\tMessages: ";
        std::string file_name = "../txt_files/User/" + email + "_messages.txt";
        std::ifstream file;
        file.open(file_name);
        file.exceptions(std::ifstream::badbit);
        if (!file)
            std::cout<<"empty\n\n";
        else{
            const auto& mesaje = User::loadMessages();
            std::cout<<"\n"; setGreen;
            for (auto & mesaj_curent : mesaje)
                std::cout<<*mesaj_curent;
        }
        file.close();

        setBlue;
        std::cout<<"\n\tGo back to user panel - type 1\n\n";
        std::cout<<"\tPlease select your choice: ";

        unsigned short option;
        setGreen;

        while (std::cin>>option){
            if (option==1){
                setRed;
                std::cout<<"\n\tWait...\n\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
            }
            else{
                setRed;
                std::cout<<"\n\tIncorrect option!\n";
                setBlue;
                std::cout<<"\n\tPlease select your choice: ";
            }
        }
    }
    catch (std::exception& e) {
        setRed;
        std::cout << "\n\t(Error) " << e.what() << "\n";
    }
}

std::vector<std::shared_ptr<Message>> User::loadMessages() const{
    try{
        std::string file_name = "../txt_files/User/" + email + "_messages.txt";
        std::vector<std::shared_ptr<Message>> mesaje;
        std::ifstream file;
        file.open(file_name);
        file.exceptions(std::ifstream::badbit);
        std::string line;

        while (std::getline(file, line)){
            Message mesaj_auxiliar;
            std::istringstream iss(line);
            std::string word;

            std::getline(iss, word, ';');
            mesaj_auxiliar.setDestinatar(word);

            std::getline(iss, word, ';');
            mesaj_auxiliar.setTipMesaj((unsigned short)stoi(word));

            std::getline(iss, word, ';');
            mesaj_auxiliar.setMesaj(word);

            data_str_mess data_cp{};

            std::getline(iss, word, ';');
            data_cp.zi = (unsigned short)stoi(word);

            std::getline(iss, word, ';');
            data_cp.luna = (unsigned short)stoi(word);

            std::getline(iss, word, ';');
            data_cp.an = (unsigned short)stoi(word);

            std::getline(iss, word, ';');
            data_cp.ora = (unsigned short)stoi(word);

            mesaj_auxiliar.setData(data_cp);
            mesaje.emplace_back(std::make_shared<Message>(mesaj_auxiliar));
        }
        file.close();
        return mesaje;
    }
    catch (std::exception& e) {
        setRed;
        std::cout << "\n\t(Error) " << e.what() << "\n";
        return {};
    }
}

void User::updateFileFromTemp() {
    int result = remove("../txt_files/User/users.txt");
    result = rename("../txt_files/User/temporary.txt","../txt_files/User/users.txt");
    result = remove("../txt_files/User/temporary.txt");

    if (result){
        setRed;
        std::cout<<"\n\tSuccess!\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void User::updateUserInFile(std::ostream &os) {}