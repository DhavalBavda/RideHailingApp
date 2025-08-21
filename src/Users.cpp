#include <iostream>
#include "../include/Users.h"

Users::Users(const std::string& id, const std::string& name, const std::string& email, const std::string& phone, const std::string& role, const std::string& createdat, const std::string& licenseNumber, const std::string& password)
        : id(id), name(name), email(email), phone(phone), role(role), createdat(createdat), licenseNumber(licenseNumber), password(password) {}

Users::Users(const std::string& id, const std::string& name, const std::string& email, const std::string& phone, const std::string& role, const std::string& createdat, const std::string& password)
        : id(id), name(name), email(email), phone(phone), role(role), createdat(createdat), password(password) {}

const std::string& Users::getId() const{
    return id;
}

const std::string& Users::getRole() const{
    return role;
}

const std::string& Users::getName() const{
    return name;
}

const std::string& Users::getEmail() const{
    return email;
}

const std::string& Users::getPhone() const{
    return phone;
}

const std::string& Users::getCreatedAt() const{
    return createdat;
}

bool Users::checkValidUser(const std::string& em, const std::string& pw){
    return email == em && password == pw;
}