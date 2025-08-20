// #include <iostream>
// #include <vector>
// #include <string>
// #include <limits>
// #include <memory>
// #include <stdexcept>

// // ------------------- USER CLASSES -------------------

// class User {
// protected:
//     std::string id;
//     std::string name;
//     std::string email;
//     std::string phone;
//     std::string password;
// public:
//     User(std::string _id, std::string _name, std::string _email, std::string _phone, std::string _password)
//         : id(_id), name(_name), email(_email), phone(_phone), password(_password) {}

//     virtual std::string getType() = 0;
//     std::string getId() const { return id; }
//     std::string getName() const { return name; }

//     bool login(const std::string& em, const std::string& pw) {
//         return email == em && password == pw;
//     }

//     virtual void showMenu() = 0;
// };

// class Rider : public User {
// public:
//     Rider(std::string _id, std::string _name, std::string _email, std::string _phone, std::string _password)
//         : User(_id, _name, _email, _phone, _password) {}
//     std::string getType() override { return "rider"; }
//     void showMenu() override {
//         std::cout << "\nRider Menu:\n1.Request Ride\n2.My Rides\n3.Rate Ride\n4.Logout\n";
//     }
// };

// class Driver : public User {
// public:
//     Driver(std::string _id, std::string _name, std::string _email, std::string _phone, std::string _password)
//         : User(_id, _name, _email, _phone, _password) {}
//     std::string getType() override { return "driver"; }
//     void showMenu() override {
//         std::cout << "\nDriver Menu:\n1.Register Vehicle\n2.My Rides\n3.Start Ride\n4.Cancel Ride\n5.Logout\n";
//     }
// };

// // ------------------- VEHICLE & RIDE -------------------

// class Vehicle {
//     std::string id;
//     std::string driverId;
//     std::string brand, model, year, plate, color;
// public:
//     Vehicle(std::string _id, std::string _driverId, std::string _brand,
//             std::string _model, std::string _year, std::string _plate, std::string _color)
//         : id(_id), driverId(_driverId), brand(_brand), model(_model), year(_year), plate(_plate), color(_color) {}
//     std::string getId() const { return id; }
//     std::string getDriverId() const { return driverId; }
//     void display() {
//         std::cout << "Vehicle ID: " << id << " | " << brand << " " << model << " | Plate: " << plate << "\n";
//     }
// };

// class Ride {
//     std::string id;
//     std::string riderId;
//     std::string driverId;
//     std::string pickup, drop;
//     std::string status;
//     int rating;
// public:
//     Ride(std::string _id, std::string _riderId, std::string _driverId, std::string _pickup, std::string _drop)
//         : id(_id), riderId(_riderId), driverId(_driverId), pickup(_pickup), drop(_drop), status("requested"), rating(0) {}

//     void start() { status = "in_progress"; }
//     void cancel() { status = "cancelled"; }
//     void complete() { status = "completed"; }
//     void rate(int r) { rating = r; }

//     std::string getId() const { return id; }
//     std::string getRiderId() const { return riderId; }
//     std::string getDriverId() const { return driverId; }
//     std::string getStatus() const { return status; }
//     int getRating() const { return rating; }

//     void display() {
//         std::cout << "Ride ID: " << id << " | Pickup: " << pickup << " | Drop: " << drop
//                   << " | Status: " << status << " | Rating: " << rating << "\n";
//     }
// };

// // ------------------- RIDE SHARING SYSTEM -------------------

// class RideSharingSystem {
//     std::vector<std::shared_ptr<User>> users;
//     std::vector<Vehicle> vehicles;
//     std::vector<Ride> rides;

//     std::string generateId(int size) { return std::to_string(size + 1); }

// public:
//     void registerUser() {
//         try {
//             std::string name, email, phone, type, password;
//             std::cout << "Enter Name: "; std::cin.ignore(); std::getline(std::cin, name);
//             std::cout << "Enter Email: "; std::getline(std::cin, email);
//             std::cout << "Enter Phone: "; std::getline(std::cin, phone);
//             std::cout << "Enter Type (rider/driver): "; std::getline(std::cin, type);
//             std::cout << "Enter Password: "; std::getline(std::cin, password);

//             std::string id = generateId(users.size());
//             if(type == "rider")
//                 users.push_back(std::make_shared<Rider>(id, name, email, phone, password));
//             else if(type == "driver")
//                 users.push_back(std::make_shared<Driver>(id, name, email, phone, password));
//             else throw std::invalid_argument("Invalid user type!");

//             std::cout << "User Registered! ID: " << id << "\n";
//         }
//         catch(const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
//     }

//     std::shared_ptr<User> login() {
//         try {
//             std::string email, password;
//             std::cout << "Enter Email: "; std::cin.ignore(); std::getline(std::cin, email);
//             std::cout << "Enter Password: "; std::getline(std::cin, password);

//             for(auto &u : users) {
//                 if(u->login(email, password)) {
//                     std::cout << "Login Success! Welcome " << u->getName() << "\n";
//                     return u;
//                 }
//             }
//             std::cout << "Invalid credentials!\n";
//         }
//         catch(const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
//         return nullptr;
//     }

//     void registerVehicle(std::shared_ptr<User> driver) {
//         if(!driver || driver->getType() != "driver") { std::cout << "Only drivers can register vehicles.\n"; return; }
//         std::string brand, model, year, plate, color;
//         std::cout << "Enter Brand: "; std::cin.ignore(); std::getline(std::cin, brand);
//         std::cout << "Enter Model: "; std::getline(std::cin, model);
//         std::cout << "Enter Year: "; std::getline(std::cin, year);
//         std::cout << "Enter Plate: "; std::getline(std::cin, plate);
//         std::cout << "Enter Color: "; std::getline(std::cin, color);
//         std::string id = generateId(vehicles.size());
//         vehicles.emplace_back(id, driver->getId(), brand, model, year, plate, color);
//         std::cout << "Vehicle Registered! ID: " << id << "\n";
//     }

//     void requestRide(std::shared_ptr<User> rider) {
//         if(!rider || rider->getType() != "rider") { std::cout << "Only riders can request rides.\n"; return; }
//         if(vehicles.empty()) { std::cout << "No drivers available!\n"; return; }
//         std::string pickup, drop;
//         std::cout << "Enter Pickup Location: "; std::cin.ignore(); std::getline(std::cin, pickup);
//         std::cout << "Enter Drop Location: "; std::getline(std::cin, drop);
//         auto vehicle = vehicles[0];
//         std::string rideId = generateId(rides.size());
//         rides.emplace_back(rideId, rider->getId(), vehicle.getDriverId(), pickup, drop);
//         std::cout << "Ride Requested! ID: " << rideId << "\n";
//     }

//     void startRide(std::shared_ptr<User> driver) {
//         if(!driver || driver->getType() != "driver") { std::cout << "Only drivers can start rides.\n"; return; }
//         std::cout << "Available Rides:\n";
//         for(auto &r : rides) { if(r.getDriverId() == driver->getId() && r.getStatus() == "requested") r.display(); }
//         std::string rideId; std::cout << "Enter Ride ID to start: "; std::cin >> rideId;
//         for(auto &r : rides) { if(r.getId() == rideId && r.getDriverId() == driver->getId()) { r.start(); std::cout << "Ride Started!\n"; return; } }
//         std::cout << "Ride not found!\n";
//     }

//     void cancelRide(std::shared_ptr<User> user) {
//         std::string rideId; std::cout << "Enter Ride ID to cancel: "; std::cin >> rideId;
//         for(auto &r : rides) {
//             if(r.getId() == rideId && (r.getDriverId() == user->getId() || r.getRiderId() == user->getId())) {
//                 r.cancel(); std::cout << "Ride Cancelled!\n"; return;
//             }
//         }
//         std::cout << "Ride not found or unauthorized!\n";
//     }

//     void rateRide(std::shared_ptr<User> rider) {
//         std::string rideId; int rating;
//         std::cout << "Enter Ride ID to rate: "; std::cin >> rideId;
//         std::cout << "Enter Rating (1-5): "; std::cin >> rating;
//         if(rating < 1 || rating > 5) { std::cout << "Invalid rating!\n"; return; }
//         for(auto &r : rides) {
//             if(r.getId() == rideId && r.getRiderId() == rider->getId() && r.getStatus() == "completed") {
//                 r.rate(rating); std::cout << "Ride Rated!\n"; return;
//             }
//         }
//         std::cout << "Ride not found or cannot rate!\n";
//     }

//     void myRides(std::shared_ptr<User> user) {
//         std::cout << "\n--- My Rides ---\n";
//         for(auto &r : rides) {
//             if(r.getRiderId() == user->getId() || r.getDriverId() == user->getId()) r.display();
//         }
//     }

//     void mainMenu() {
//         std::shared_ptr<User> loggedIn = nullptr;
//         while(true) {
//             if(!loggedIn) {
//                 int choice;
//                 std::cout << "\n1.Register User 2.Login 3.Exit\nEnter Choice: ";
//                 std::cin >> choice;
//                 if(std::cin.fail()) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); continue; }
//                 switch(choice) {
//                     case 1: registerUser(); break;
//                     case 2: loggedIn = login(); break;
//                     case 3: return;
//                     default: std::cout << "Invalid choice!\n"; break;
//                 }
//             } else {
//                 int choice;
//                 loggedIn->showMenu();
//                 std::cout << "Enter Choice: "; std::cin >> choice;
//                 if(std::cin.fail()) { std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); continue; }

//                 if(loggedIn->getType() == "rider") {
//                     switch(choice) {
//                         case 1: requestRide(loggedIn); break;
//                         case 2: myRides(loggedIn); break;
//                         case 3: rateRide(loggedIn); break;
//                         case 4: loggedIn = nullptr; break; // logout
//                         default: std::cout << "Invalid choice!\n"; break;
//                     }
//                 } else if(loggedIn->getType() == "driver") {
//                     switch(choice) {
//                         case 1: registerVehicle(loggedIn); break;
                
//                         case 2: myRides(loggedIn); break;
//                         case 3: startRide(loggedIn); break;
//                         case 4: cancelRide(loggedIn); break;
//                         case 5: loggedIn = nullptr; break; // logout
//                         default: std::cout << "Invalid choice!\n"; break;
//                     }
//                 }
//             }
//         }
//     }
// };

// // ------------------- MAIN -------------------

// int main() {
//     RideSharingSystem system;
//     system.mainMenu();
//     std::cout << "Exiting Ride Sharing System. Goodbye!\n";
//     return 0;

// }


#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <memory>
#include <stdexcept>

// ------------------- USER CLASSES -------------------

class User {
protected:
    std::string id;
    std::string name;
    std::string email;
    std::string phone;
    std::string password;
public:
    User(std::string _id, std::string _name, std::string _email, std::string _phone, std::string _password)
        : id(_id), name(_name), email(_email), phone(_phone), password(_password) {}

    virtual std::string getType() = 0;
    std::string getId() const { return id; }
    std::string getName() const { return name; }

    bool login(const std::string& em, const std::string& pw) {
        return email == em && password == pw;
    }

    virtual void showMenu() = 0;
};

class Rider : public User {
public:
    Rider(std::string _id, std::string _name, std::string _email, std::string _phone, std::string _password)
        : User(_id, _name, _email, _phone, _password) {}
    std::string getType() override { return "rider"; }
    void showMenu() override {
        std::cout << "\nRider Menu:\n1.Request Ride\n2.My Rides\n3.Rate Ride\n4.Logout\n";
    }
};

class Driver : public User {
public:
    Driver(std::string _id, std::string _name, std::string _email, std::string _phone, std::string _password)
        : User(_id, _name, _email, _phone, _password) {}
    std::string getType() override { return "driver"; }
    void showMenu() override {
        std::cout << "\nDriver Menu:\n1.Register Vehicle\n2.My Rides\n3.Start Ride\n4.Cancel Ride\n5.Complete Ride\n6.Logout\n";
    }
};

// ------------------- VEHICLE & RIDE -------------------

class Vehicle {
    std::string id;
    std::string driverId;
    std::string brand, model, year, plate, color;
public:
    Vehicle(std::string _id, std::string _driverId, std::string _brand,
            std::string _model, std::string _year, std::string _plate, std::string _color)
        : id(_id), driverId(_driverId), brand(_brand), model(_model), year(_year), plate(_plate), color(_color) {}
    std::string getId() const { return id; }
    std::string getDriverId() const { return driverId; }
    void display() {
        std::cout << "Vehicle ID: " << id << " | " << brand << " " << model << " | Plate: " << plate << "\n";
    }
};

class Ride {
    std::string id;
    std::string riderId;
    std::string driverId;
    std::string pickup, drop;
    std::string status;
    int rating;
public:
    Ride(std::string _id, std::string _riderId, std::string _driverId, std::string _pickup, std::string _drop)
        : id(_id), riderId(_riderId), driverId(_driverId), pickup(_pickup), drop(_drop), status("requested"), rating(0) {}

    void start() { status = "in_progress"; }
    void cancel() { status = "cancelled"; }
    void complete() { status = "completed"; }
    void rate(int r) { rating = r; }

    std::string getId() const { return id; }
    std::string getRiderId() const { return riderId; }
    std::string getDriverId() const { return driverId; }
    std::string getStatus() const { return status; }
    int getRating() const { return rating; }

    void display() {
        std::cout << "Ride ID: " << id << " | Pickup: " << pickup << " | Drop: " << drop
                  << " | Status: " << status << " | Rating: " << rating << "\n";
    }
};

// ------------------- RIDE SHARING SYSTEM -------------------

class RideSharingSystem {
    std::vector<std::shared_ptr<User>> users;
    std::vector<Vehicle> vehicles;
    std::vector<Ride> rides;

    std::string generateId(int size) { return std::to_string(size + 1); }

public:
    void registerUser() {
        try {
            std::string name, email, phone, type, password;
            std::cout << "Enter Name: "; std::cin.ignore(); std::getline(std::cin, name);
            std::cout << "Enter Email: "; std::getline(std::cin, email);
            std::cout << "Enter Phone: "; std::getline(std::cin, phone);
            std::cout << "Enter Type (rider/driver): "; std::getline(std::cin, type);
            std::cout << "Enter Password: "; std::getline(std::cin, password);

            std::string id = generateId(users.size());
            if(type == "rider")
                users.push_back(std::make_shared<Rider>(id, name, email, phone, password));
            else if(type == "driver")
                users.push_back(std::make_shared<Driver>(id, name, email, phone, password));
            else throw std::invalid_argument("Invalid user type!");

            std::cout << "User Registered! ID: " << id << "\n";
        }
        catch(const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
    }

    std::shared_ptr<User> login() {
        try {
            std::string email, password;
            std::cout << "Enter Email: "; std::cin.ignore(); std::getline(std::cin, email);
            std::cout << "Enter Password: "; std::getline(std::cin, password);

            for(auto &u : users) {
                if(u->login(email, password)) {
                    std::cout << "Login Success! Welcome " << u->getName() << "\n";
                    return u;
                }
            }
            std::cout << "Invalid credentials!\n";
        }
        catch(const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
        return nullptr;
    }

    void registerVehicle(std::shared_ptr<User> driver) {
        if(!driver || driver->getType() != "driver") { std::cout << "Only drivers can register vehicles.\n"; return; }
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

    void requestRide(std::shared_ptr<User> rider) {
        if(!rider || rider->getType() != "rider") { std::cout << "Only riders can request rides.\n"; return; }
        if(vehicles.empty()) { std::cout << "No drivers available!\n"; return; }
        std::string pickup, drop;
        std::cout << "Enter Pickup Location: "; std::cin.ignore(); std::getline(std::cin, pickup);
        std::cout << "Enter Drop Location: "; std::getline(std::cin, drop);
        auto vehicle = vehicles[0];
        std::string rideId = generateId(rides.size());
        rides.emplace_back(rideId, rider->getId(), vehicle.getDriverId(), pickup, drop);
        std::cout << "Ride Requested! ID: " << rideId << "\n";
    }

    void startRide(std::shared_ptr<User> driver) {
        if(!driver || driver->getType() != "driver") { std::cout << "Only drivers can start rides.\n"; return; }
        std::cout << "Available Rides:\n";
        for(auto &r : rides) { if(r.getDriverId() == driver->getId() && r.getStatus() == "requested") r.display(); }
        std::string rideId; std::cout << "Enter Ride ID to start: "; std::cin >> rideId;
        for(auto &r : rides) { if(r.getId() == rideId && r.getDriverId() == driver->getId()) { r.start(); std::cout << "Ride Started!\n"; return; } }
        std::cout << "Ride not found!\n";
    }

    void completeRide(std::shared_ptr<User> driver) {
        std::string rideId; std::cout << "Enter Ride ID to complete: "; std::cin >> rideId;
        for(auto &r : rides) {
            if(r.getId() == rideId && (r.getDriverId() == driver->getId()) && r.getStatus() == "in_progress") {
                r.complete(); std::cout << "Ride Completed!\n"; return;
            }
        }
        std::cout << "Ride not found or unauthorized!\n";
    }

    void cancelRide(std::shared_ptr<User> user) {
        std::string rideId; std::cout << "Enter Ride ID to cancel: "; std::cin >> rideId;
        for(auto &r : rides) {
            if(r.getId() == rideId && (r.getDriverId() == user->getId() || r.getRiderId() == user->getId())) {
                r.cancel(); std::cout << "Ride Cancelled!\n"; return;
            }
        }
        std::cout << "Ride not found or unauthorized!\n";
    }

    void rateRide(std::shared_ptr<User> rider) {
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

    void myRides(std::shared_ptr<User> user) {
        std::cout << "\n--- My Rides ---\n";
        for(auto &r : rides) {
            if(r.getRiderId() == user->getId() || r.getDriverId() == user->getId()) r.display();
        }
    }

    void mainMenu() {
        std::shared_ptr<User> loggedIn = nullptr;
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

                if(loggedIn->getType() == "rider") {
                    switch(choice) {
                        case 1: requestRide(loggedIn); break;
                        case 2: myRides(loggedIn); break;
                        case 3: rateRide(loggedIn); break;
                        case 4: loggedIn = nullptr; break; // logout
                        default: std::cout << "Invalid choice!\n"; break;
                    }
                } else if(loggedIn->getType() == "driver") {
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
};

// ------------------- MAIN -------------------

int main() {
    RideSharingSystem system;
    system.mainMenu();
    std::cout << "Exiting Ride Sharing System. Goodbye!\n";
    return 0;
}
