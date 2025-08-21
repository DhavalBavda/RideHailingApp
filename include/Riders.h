#pragma once
#include <string>
#include "./Users.h"

class Riders : public Users{
    public:
        Riders(const std::string& _id, const std::string& _name, const std::string& _email, const std::string& _phone, const std::string& _role, const std::string& _createdat, const std::string& _password);
        void showMenu() override;
};