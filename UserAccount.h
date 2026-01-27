#ifndef USERACCOUNT_H
#define USERACCOUNT_H
#include <string>
using namespace std;
class UserAccount {
private:
    string username;
    string password;
    string passportID;   
public:
    UserAccount(string u, string p, string id) : username(u), password(p), passportID(id) {}
        
        string getUsername() const { return username; }
        string getPassportID() const { return passportID; }
        
    bool verify(string u, string p) const {
        return (username == u && password == p);
    }
};
#endif