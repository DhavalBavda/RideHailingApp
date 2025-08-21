#include <iostream>
#include "../include/Vehicles.h"

Vehicles::Vehicles(const std::string& _id, const std::string& _driverId, const std::string& _brand,
            const std::string& _model, const std::string& _year, const std::string& _plate, const std::string& _color)
            : id(_id), driverId(_driverId), brand(_brand), model(_model), year(_year), plate(_plate), color(_color) {};

const std::string& Vehicles::getDriverId() const{
    return driverId;
}

const std::string& Vehicles::getId() const{
    return id;
}

void Vehicles::display() {
    std::cout << "Vehicle ID: " << id << " | " << brand << " " << model << " | Plate: " << plate << "\n";
}