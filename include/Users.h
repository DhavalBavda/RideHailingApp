#pragma once
#include <string>

class Users{

    private:
        std::string id;
        std::string name;
        std::string email;
        std::string phone;
        std::string role;
        std::string createdat;
        std::string password;
        std::string licenseNumber;

    public:

        // Constructor
        Users(const std::string& id, const std::string& name, const std::string& email, const std::string& phone, const std::string& role, const std::string& createdat, const std::string& licenseNumber, const std::string& password);

        // Constructor
        Users(const std::string& id, const std::string& name, const std::string& email, const std::string& phone, const std::string& role, const std::string& createdat, const std::string& password);
          
        // Getters
        const std::string& getId() const;
        const std::string& getRole() const;
        const std::string& getName() const;
        const std::string& getEmail() const;
        const std::string& getPhone() const;
        const std::string& getCreatedAt() const; 
        

        // Funtions
        bool checkValidUser(const std::string& em, const std::string& pw);
        virtual void showMenu() = 0;
};