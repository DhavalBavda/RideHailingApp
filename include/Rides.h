#pragma once
#include <string>

class Rides{
    private:
        std::string id;
        std::string riderId;
        std::string driverId;
        std::string pickup;
        std::string drop;
        std::string status; // requested, in_progress, completed, cancelled
        // std::string fare;
        // std::string dateTime;
        // std::string vehicleId;
        int rating; // rating given by rider after ride

    public:
        // Constructor
        // Rides(const std::string& id, const std::string& riderId, 
        //     const std::string& pickup, const std::string& drop);

        Rides(const std::string& _id, const std::string& _riderId, const std::string& _driverId, const std::string& _pickup, const std::string& _drop, const std::string& _status);

        // Alternative constructor with more details
        // Rides(const std::string& id, const std::string& riderId, 
        //     const std::string& driverId, const std::string& pickup, 
        //     const std::string& drop, double fare, const std::string& vehicleId);

        void start();
        void cancel();
        void complete();
        void rate(int& r);

        const std::string& getId() const;
        const std::string& getRiderId() const;
        const std::string& getDriverId() const;
        const std::string& getStatus() const;
        const int& getRating() const;
        void display();
        
};