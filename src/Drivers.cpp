#include <iostream>
#include "../include/Drivers.h"

Drivers::Drivers(const std::string& _id, const std::string& _name, const std::string& _email, const std::string& _phone, const std::string& _role, const std::string& _createdat, const std::string& _password, const std::string& _licenseNumber)
            : Users(_id, _name, _email, _phone, _role, _createdat, _licenseNumber, _password ) {}

void Drivers::showMenu(){
    std::cout << "\nDriver Menu:\n1.Register Vehicle\n2.My Rides\n3.Start Ride\n4.Cancel Ride\n5.Complete Ride\n6.Logout\n";
}