#pragma once
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <thread>
#include <ctime>
#include <regex>
#include "../src/Admin.cpp"

class Interface{
    Interface() = default;
    ~Interface() = default;
    static Interface* interf;

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
    template <typename T>
    static void panelAdmin(Admin<T>&);
    template <typename T>
    static void showMenuPanelAdmin(const Admin<T>&);

    static void panelUser(const std::shared_ptr<User>&);
    static void showMenuPanelUser(const std::shared_ptr<User>& user);

public:
    /// metoda de Startup
    void startApp();

    Interface(const Interface&) = delete;
    Interface& operator=(const Interface&) = delete;
    static Interface* getInstance();
    static void free();
};
