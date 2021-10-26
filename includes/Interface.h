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
