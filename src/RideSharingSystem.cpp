#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <stdexcept>
#include "../include/RideSharingSystem.h"
#include "../include/Users.h"
#include "../include/Riders.h"
#include "../include/Drivers.h"
#include "../include/Rides.h"

const std::string RideSharingSystem::generateId(int size){
    return std::to_string(size + 1);
}

void RideSharingSystem::registerUser()
{
    try
    {
        std::string name, email, phone, role, password, licenseNumber;
        std::cout << "Enter Name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "Enter Email: ";
        std::getline(std::cin, email);
        std::cout << "Enter Phone: ";
        std::getline(std::cin, phone);
        std::cout << "Enter Type (rider/driver): ";
        std::getline(std::cin, role);
        std::cout << "Enter Password: ";
        std::getline(std::cin, password);

        std::string id = generateId(users.size());
        if (role == "rider"){
            users.push_back(std::make_shared<Riders>(id, name, email, phone, role, "", password));
        }
        else if (role == "driver"){
            std::cout << "Enter License Number: ";
            std::getline(std::cin, licenseNumber);
            users.push_back(std::make_shared<Drivers>(id, name, email, phone, role, "", password, licenseNumber));
        }
        else{
            throw std::invalid_argument("Invalid user role!");
        }
        std::cout << "User Registered! ID: " << id << "\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }
}

const std::shared_ptr<Users> RideSharingSystem::login(){
    try {
        std::string email, password;
        std::cout << "Enter Email: "; std::cin.ignore(); std::getline(std::cin, email);
        std::cout << "Enter Password: "; std::getline(std::cin, password);

        for(auto &u : users) {
            if(u->checkValidUser(email, password)) {
                std::cout << "Login Success! Welcome " << u->getName() << "\n";
                return u;
            }
        }
        std::cout << "Invalid credentials!\n";
    }
    catch(const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
    return nullptr;   
}

void RideSharingSystem::registerVehicle(std::shared_ptr<Users> driver){
    if(!driver || driver->getRole() != "driver") { std::cout << "Only drivers can register vehicles.\n"; return; }
    std::string brand, model, year, plate, color;
    std::cout << "Enter Brand: "; std::cin.ignore(); std::getline(std::cin, brand);
    std::cout << "Enter Model: "; std::getline(std::cin, model);
    std::cout << "Enter Year: "; std::getline(std::cin, year);
    std::cout << "Enter Plate: "; std::getline(std::cin, plate);
    std::cout << "Enter Color: "; std::getline(std::cin, color);
    std::string id = generateId(vehicles.size());
    vehicles.emplace_back(id, driver->getId(), brand, model, year, plate, color);
    std::cout << "Vehicle Registered! ID: " << id << "\n";   
}

void RideSharingSystem::requestRide(std::shared_ptr<Users> rider){
    if(!rider || rider->getRole() != "rider") { std::cout << "Only riders can request rides.\n"; return; }
    if(vehicles.empty()) { std::cout << "No drivers available!\n"; return; }
    std::string pickup, drop;
    std::cout << "Enter Pickup Location: "; std::cin.ignore(); std::getline(std::cin, pickup);
    std::cout << "Enter Drop Location: "; std::getline(std::cin, drop);
    auto vehicle = vehicles[0];
    std::string rideId = generateId(rides.size());
    rides.emplace_back(rideId, rider->getId(), vehicle.getDriverId(), pickup, drop, "requested");
    std::cout << "Ride Requested! ID: " << rideId << "\n";
}

void RideSharingSystem::startRide(std::shared_ptr<Users> driver){
    if(!driver || driver->getRole() != "driver") { std::cout << "Only drivers can start rides.\n"; return; }
    std::cout << "Available Rides:\n";
    for(auto &r : rides) { if(r.getDriverId() == driver->getId() && r.getStatus() == "requested") r.display(); }
    std::string rideId; std::cout << "Enter Ride ID to start: "; std::cin >> rideId;
    for(auto &r : rides) { if(r.getId() == rideId && r.getDriverId() == driver->getId()) { r.start(); std::cout << "Ride Started!\n"; return; } }
    std::cout << "Ride not found!\n";
}

void RideSharingSystem::completeRide(std::shared_ptr<Users> driver) {
    std::string rideId; std::cout << "Enter Ride ID to complete: "; std::cin >> rideId;
    for(auto &r : rides) {
        if(r.getId() == rideId && r.getDriverId() == driver->getId() && r.getStatus() == "in_progress") {
            r.complete(); std::cout << "Ride Completed!\n"; return;
        }
    }
    std::cout << "Ride not found or unauthorized!\n";
}

void RideSharingSystem::cancelRide(std::shared_ptr<Users> user) {
    std::string rideId; std::cout << "Enter Ride ID to cancel: "; std::cin >> rideId;
    for(auto &r : rides) {
        if(r.getId() == rideId && (r.getDriverId() == user->getId() || r.getRiderId() == user->getId())) {
            r.cancel(); std::cout << "Ride Cancelled!\n"; return;
        }
    }
    std::cout << "Ride not found or unauthorized!\n";
}

void RideSharingSystem::rateRide(std::shared_ptr<Users> rider) {
    std::string rideId; int rating;
    std::cout << "Enter Ride ID to rate: "; std::cin >> rideId;
    std::cout << "Enter Rating (1-5): "; std::cin >> rating;
    if(rating < 1 || rating > 5) { std::cout << "Invalid rating!\n"; return; }
    for(auto &r : rides) {
        if(r.getId() == rideId && r.getRiderId() == rider->getId() && r.getStatus() == "completed") {
            r.rate(rating); std::cout << "Ride Rated!\n"; return;
        }
    }
    std::cout << "Ride not found or cannot rate!\n";
}

void RideSharingSystem::myRides(std::shared_ptr<Users> user) {
    std::cout << "\n--- My Rides ---\n";
    for(auto &r : rides) {
        if(r.getRiderId() == user->getId() || r.getDriverId() == user->getId()) r.display();
    }
}
void RideSharingSystem::mainMenu() {
    std::shared_ptr<Users> loggedIn = nullptr;
    while(true) {
        if(!loggedIn) {
            int choice;
            std::cout << "\n1.Register User 2.Login 3.Exit\nEnter Choice: ";
            std::cin >> choice;
            if(std::cin.fail()) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); continue; }
            switch(choice) {
                case 1: registerUser(); break;
                case 2: loggedIn = login(); break;
                case 3: return;
                default: std::cout << "Invalid choice!\n"; break;
            }
        } else {
            int choice;
            loggedIn->showMenu();
            std::cout << "Enter Choice: "; std::cin >> choice;
            if(std::cin.fail()) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); continue; }

            if(loggedIn->getRole() == "rider") {
                switch(choice) {
                    case 1: requestRide(loggedIn); break;
                    case 2: myRides(loggedIn); break;
                    case 3: rateRide(loggedIn); break;
                    case 4: loggedIn = nullptr; break; // logout
                    default: std::cout << "Invalid choice!\n"; break;
                }
            } else if(loggedIn->getRole() == "driver") {
                switch(choice) {
                    case 1: registerVehicle(loggedIn); break;
            
                    case 2: myRides(loggedIn); break;
                    case 3: startRide(loggedIn); break;
                    case 4: cancelRide(loggedIn); break;
                    case 5: completeRide(loggedIn); break;
                    case 6: loggedIn = nullptr; break; // logout
                    default: std::cout << "Invalid choice!\n"; break;
                }
            }
        }
    }
}
