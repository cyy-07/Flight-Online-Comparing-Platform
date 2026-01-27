#ifndef FLIGHTORDER_H
#define FLIGHTORDER_H
#include <string>
#include "FareType.h"
using namespace std;
class FlightOrder {
private:
    string orderid;
    string providertype;
    string providername;
    string flightnumber;
    string source;
    string dest;
    string deptime;
    string arrtime;
    double baseprice;
    double baggagefee;
    double insurancefee;
    double servicefee;      double refundfee;   

    FareType* chosenFare = nullptr;

public:
    FlightOrder(string id, string type, string provider, string flight,
                string src, string dst, string dep, string arr,
                double base, double bag, double ins, double serv, double ref);
    
    ~FlightOrder();
    double gettotal() const;
    
    void setFareType(FareType* fare);
    void setbaseprice(double price) { baseprice = price; }
    string getorderid() const;
    string getprovidertype() const;
    string getprovidername() const;
    string getflightnumber() const;
    string getsource() const;
    string getdest() const;
    string getdeptime() const;
    string getarrtime() const;
    double getbaseprice() const;
    double getbaggagefee() const;
    double getinsurancefee() const;
    double getservicefee() const;
    double getrefundfee() const;  
    void printdetails() const;
};

#endif