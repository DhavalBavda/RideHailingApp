#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "../include/Users.h"
#include "../include/Vehicles.h"
#include "../include/Rides.h"

class RideSharingSystem
{
private:
    std::vector<std::shared_ptr<Users>> users;
    std::vector<Vehicles> vehicles;
    std::vector<Rides> rides;

    const std::string generateId(int size);

public:
    void registerUser();
    const std::shared_ptr<Users> login();
    void registerVehicle(std::shared_ptr<Users> driver);
    void requestRide(std::shared_ptr<Users> rider);
    void startRide(std::shared_ptr<Users> driver);
    void completeRide(std::shared_ptr<Users> driver);
    void cancelRide(std::shared_ptr<Users> user);
    void rateRide(std::shared_ptr<Users> rider);
    void myRides(std::shared_ptr<Users> user);
    void mainMenu();

};