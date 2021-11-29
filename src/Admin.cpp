#include "../includes/Admin.h"
#include "../libraries/rlutil.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <thread>
#include <regex>
#include <string>
#include <sstream>

#define setBlue rlutil::setColor(1)
#define setGreen rlutil::setColor(2)
#define setRed rlutil::setColor(4)
#define setLightMagenta rlutil::setColor(13)


Admin &Admin::operator=(const Admin &copie) {
    username = copie.username;
    email = copie.email;
    parola = copie.parola;
    return *this;
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

void Admin::showAllUsers(unsigned short& val) const {
    try{
        setLightMagenta;
        std::cout<<"\n\tAdmin panel -- all users\n\n";
        setGreen;
        std::fstream login;
        login.open("../txt_files/User/users.txt",std::fstream::in);
        login.exceptions(std::ifstream::badbit);
        std::vector<std::shared_ptr<User>> users;
        std::string line;
        int n = 0;
        std::regex separator("\\;");

        while (std::getline(login, line)){
            std::vector<std::string> out(
                    std::sregex_token_iterator(line.begin(), line.end(), separator, -1),
                    std::sregex_token_iterator()
            );

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
                UserBusiness userBusiness_aux(user, out[8], out[9]);
                users.push_back(std::make_shared<UserBusiness>(userBusiness_aux));
            } else
                users.push_back(std::make_shared<User>(user));

            std::cout << "\t" << n+1 << "\t" << out[0] << "\t"<< out[1] <<"\n";
            n++;
        }
        login.close();

        setBlue;
        std::cout<<"\n\n\tFor a user info type the id"<<'\n';
        std::cout<<"\tFor back, type 0\n\n";
        std::cout<<"\tPlease select your choice: ";
        unsigned short option;
        setGreen;

        while (std::cin>>option){
            if (option==0){
                setRed;
                std::cout<<"\n\tWait...\n\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                val = 1;
                return;
            }
            else
            if (option>=1 && option<=n){
                Admin::showUser(users[option - 1]);
                val = 1;
                return;
            }
            else{
                setRed;
                std::cout<<"\n\tIncorrect option!\n";
                val = 1;
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

void Admin::showUser(const std::shared_ptr<User>& user) const{
    std::cout<<user;
    setBlue;
    std::cout<<"\t[1] Go back to all users panel \n";
    std::cout<<"\t[2] Send a message to this user\n\n";
    std::cout<<"\tPlease select your choice: ";

    unsigned short option;
    setGreen;
    while (std::cin>>option){
        if (option==1){
            setRed;
            std::cout<<"\n\tWait...\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            unsigned short val = 1;
            Admin::showAllUsers(val);
            return;
        }
        else
            if (option==2){
                setRed;
                std::cout<<"\n\tWait...\n\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                Admin::sendMessage(user);
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

void Admin::sendMessage(const std::shared_ptr<User>& user) const{
    setLightMagenta;
    std::cout<<"\t Send message to: "<<user->getNumePrenume()<<"\n\n";
    setBlue;
    std::cout<<"\t[1] Go back to user panel info \n";
    std::cout<<"\t[2] Continue\n\n";
    std::cout<<"\tPlease select your choice: ";
    unsigned short option;
    setGreen;

    while (std::cin>>option){
        if (option==1){
            setRed;
            std::cout<<"\n\tWait...\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            Admin::showUser(user);
            return;
        }
        else
        if (option==2){
            setRed;
            std::cout<<"\n\tWait...\n\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            unsigned short success = 0;
            processingMessage(user,success);
            if (success == 1){
                setRed;
                std::cout<<"\n\tMessage sent!";
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout<<"\n\tLoading main panel! Please wait...\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            else{
                setRed;
                std::cout<<"\n\tError..\n";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
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

void Admin::processingMessage(const std::shared_ptr<User>& user, unsigned short& success) {
    std::string mesaj;
    setBlue;
    std::cout<<"\tSelect type of message:\n";
    std::cout<<"\t[1] Warning\n";
    std::cout<<"\t[2] Advice\n";
    std::cout<<"\t[3] Notification\n\n";
    std::cout<<"\tPlease select your choice: ";
    unsigned short type;
    setGreen;
    while(std::cin>>type){
        if (type != 1 && type != 2 && type != 3){
            setRed;
            std::cout<<"\n\tIncorrect option!\n";
            setBlue;
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
    message.setDestinatar(user->getEmail());
    message.setMesaj(mesaj);
    message.setTipMesaj(type);
    message.setData(data_cp);

    try{
        std::string file_name = "../txt_files/User/" + user->getEmail() + "_messages.txt";
        std::fstream file;
        file.open(file_name,std::fstream::app);
        file.exceptions(std::ifstream::badbit);
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
    catch (std::exception& e) {
        setRed;
        std::cout << "\n\t(Error) " << e.what() << "\n";
    }
}
