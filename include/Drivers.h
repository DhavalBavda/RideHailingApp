#pragma once
#include <string>
#include "./Users.h"

class Drivers : public Users{
    public:
        Drivers(const std::string& _id, const std::string& _name, const std::string& _email, const std::string& _phone, const std::string& _role, const std::string& _createdat, const std::string& _password, const std::string& _licenseNumber);
        void showMenu() override;
};