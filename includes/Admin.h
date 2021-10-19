#include <iostream>
#include "User.h"

class Admin{
    std::string username;
    std::string email;
    std::string parola;

public:
    Admin()= default;;


    Admin(const Admin& copie){
        this->username = copie.username;
        this->email = copie.email;
        this->parola = copie.parola;
    }

    Admin& operator=(const Admin& copie){
        this->username = copie.username;
        this->email = copie.email;
        this->parola = copie.parola;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Admin &admin) {
        os << "username: " << admin.username << " email: " << admin.email << " parola: " << admin.parola;
        return os;
    }

    const std::string &getUsername() const {
        return username;
    }

    void setUsername(const std::string &username_copie) {
        Admin::username = username_copie;
    }

    void setEmail(const std::string &email_copie) {
        Admin::email = email_copie;
    }

    void setParola(const std::string &parola_copie) {
        Admin::parola = parola_copie;
    }

    static void showAllUsers(const Admin&, unsigned short&);

    static void showUser(const Admin&, const User&);

};

