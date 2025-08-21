#include <iostream>
#include "../include/Riders.h"

Riders::Riders(const std::string& _id, const std::string& _name, const std::string& _email, const std::string& _phone, const std::string& _role, const std::string& _createdat, const std::string& _password)
            : Users(_id, _name, _email, _phone, _role, _createdat, _password) {}

void Riders::showMenu(){
    std::cout << "\nRider Menu:\n1.Request Ride\n2.My Rides\n3.Rate Ride\n4.Logout\n";
}