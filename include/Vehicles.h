#pragma once
#include <string>
#include "./Vehicles.h"

class Vehicles{
    private:
        std::string id;
        std::string driverId;
        std::string brand, model, year, plate, color;
    public:

        Vehicles(const std::string& _id, const std::string& _driverId, const std::string& _brand,
            const std::string& _model, const std::string& _year, const std::string& _plate, const std::string& _color);

        const std::string& getId() const;
        const std::string& getDriverId() const;
        void display();
};