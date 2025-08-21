#include <iostream>
#include "../include/Rides.h"

Rides::Rides(const std::string& _id, const std::string& _riderId, const std::string& _driverId, const std::string& _pickup, const std::string& _drop, const std::string& _status)
            : id(_id), riderId(_riderId), driverId(_driverId), pickup(_pickup), drop(_drop), status(_status) {};

void Rides::start(){
    status = "in_progress";
}

void Rides::cancel(){
    status = "cancelled";
}

void Rides::complete(){
    status = "completed";
}

void Rides::rate(int& r){
    rating = r;
}

const std::string& Rides::getId() const{
    return id;
}

const std::string& Rides::getRiderId() const{
    return riderId;
}

const std::string& Rides::getDriverId() const{
    return driverId;
}

const std::string& Rides::getStatus() const{
    return status;
}

const int& Rides::getRating() const{
    return rating;
}

void Rides::display() {
    std::cout << "Ride ID: " << id << " | Pickup: " << pickup << " | Drop: " << drop
                  << " | Status: " << status << " | Rating: " << rating << " | RiderId: " << riderId << " | DriverId: " << driverId <<   "\n";
}