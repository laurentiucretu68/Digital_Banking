#pragma once
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
    bool checkDuplicateEmail(const std::string&);
    bool checkPatternEmail(const std::string&);
    bool checkPatternPhone(const std::string&);
    bool checkDuplicatePhone(const std::string&);
    bool checkPatternIBAN(const std::string&);
    bool checkDuplicateIBAN(const std::string&);

    /// metodele de Login
    void login();
    void loginUser(const std::string&);
    void loginAdmin(const std::string&, const std::string&);

    bool checkEmailPasswordLogin(const std::string&, const std::string&, unsigned short&);

    /// metodele panel
    void panelAdmin(Admin&);
    void panelUser(User&);

public:
    /// metoda de Startup
    void startApp();
};
