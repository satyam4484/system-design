#include <bits/stdc++.h>
using namespace std;

class User{
private:
    unordered_map<string,string> users; // Map to store usernames and passwords.

public:
    // Function to add a new user.
    bool addUser(const string &username, const string &password) {}

    // Function to authenticate a user.
    bool authenticate(const string &username, const string &password) {}

    // Function to remove a user.
    bool removeUser(const string &username) {}

    // Function to change a user's password.
    bool changePassword(const string &username, const string &oldPassword, const string &newPassword) {}

    // Function to check if a user exists.
    bool userExists(const string &username) {}
};
