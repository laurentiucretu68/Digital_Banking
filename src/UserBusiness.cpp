#include "../includes/UserBusiness.h"
#include <utility>
#include <iostream>
#include <fstream>
#include <thread>
#include <regex>

void UserBusiness::writeUserInFile() {
    std::fstream write;

    write.open("../txt_files/User/users.txt",std::fstream::app);
    write<< nume_prenume<<';'<<email<<';'<<parola<<';';
    write<< telefon<<';'<<IBAN<<';'<<exp_date.first<<'/'<<exp_date.second<<';';
    write<< CIV<<';'<<suma<<';'<<numeCompanie<<';'<<CUI<<'\n';

    write.close();
    write.open("../txt_files/User/users.txt",std::fstream::app);
    write.close();
}

UserBusiness::UserBusiness(const User &copie, std::string numeCompanie, std::string cui) : User(copie),numeCompanie(std::move(numeCompanie)),CUI(std::move(cui)) {}

const std::string &UserBusiness::getNumeCompanie() const {
    return numeCompanie;
}

const std::string &UserBusiness::getCui() const {
    return CUI;
}

void UserBusiness::updateBalance(const float &suma_tranzactie) {
    std::fstream old_file;
    std::ofstream new_file ("../txt_files/User/temporary.txt");
    old_file.open("../txt_files/User/users.txt",std::fstream::in);
    std::string line;
    while (std::getline(old_file, line)){
        const std::string& copy(line);
        std::istringstream iss(line);
        std::string word, aux_nume;
        std::getline(iss, word, ';');
        aux_nume = word;
        std::getline(iss, word, ';');
        if (word == getEmail()){
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
            std::getline(iss, word, ';');

            new_file<<numeCompanie<<";";
            new_file<<CUI<<"\n";
        }
        else
            new_file<<copy<<'\n';
    }

    old_file.close(); new_file.close();
    remove("../txt_files/User/users.txt");
    rename("../txt_files/User/temporary.txt","../txt_files/User/users.txt");
    remove("../txt_files/User/temporary.txt");
}

void UserBusiness::changePassword() const {
    unsigned short option2;
    std::cout<<"\n\tIf you want to continue, type 1, else type 2: ";
    std::cin>>option2;

    if (option2 == 2){
        rlutil::setColor(4);
        std::cout<<"\n\n\tPlease wait...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    else{
        std::string parola_curenta, parola_noua, parola_noua_repetare;

        bool cond;
        cond = false;
        while (!cond){
            rlutil::setColor(2);
            std::cout<<"\n\tEnter your password: "; std::cin>>parola_curenta;
            if (parola_curenta == getParola())
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
                std::getline(iss, word, ';');
                new_file<<word<<";";
                std::getline(iss, word, ';');
                new_file<<word<<"\n";
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

void UserBusiness::setNumeCompanie(const std::string &numeCompanie) {
    UserBusiness::numeCompanie = numeCompanie;
}

void UserBusiness::setCui(const std::string &cui) {
    CUI = cui;
}
