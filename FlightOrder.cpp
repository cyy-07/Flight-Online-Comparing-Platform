#include "FlightOrder.h"
#include <iostream>
#include <iomanip>
#include "FareType.h"
using namespace std;

FlightOrder::FlightOrder(string id, string type, string provider, string flight,
                         string src, string dst, string dep, string arr,
                         double base, double bag, double ins, double serv, double ref) {
    orderid = id;
    providertype =type;
    providername =provider;    flightnumber=flight;
    source =src; 
    dest= dst;
    deptime= dep;
    arrtime= arr;
    baseprice= base;
    baggagefee= bag;
    insurancefee = ins;
    servicefee =serv;       refundfee =ref;
    chosenFare = nullptr;
}

FlightOrder::~FlightOrder()

{
    if (chosenFare) {
        delete chosenFare;
    }
}
void FlightOrder::setFareType(FareType* fare){
    if (chosenFare) {
        delete chosenFare;
    }
    chosenFare=fare; 
}
double FlightOrder::gettotal() const 
{
    double finalBasePrice = baseprice;
    if (chosenFare) {
        finalBasePrice=chosenFare->calculateFinalPrice(baseprice); 
    }  
    return finalBasePrice+baggagefee+insurancefee+servicefee; 
}
string FlightOrder::getorderid() const{ return orderid; }
string FlightOrder::getprovidertype() const { return providertype; }
string FlightOrder::getprovidername() const { return providername; }
string FlightOrder::getflightnumber() const { return flightnumber; }
string FlightOrder::getsource() const { return source; }
string FlightOrder::getdest() const { return dest; }
string FlightOrder::getdeptime() const{ return deptime; }
string FlightOrder::getarrtime() const{ return arrtime; }
double FlightOrder::getbaseprice() const{ return baseprice; }
double FlightOrder::getbaggagefee() const{ return baggagefee; }
double FlightOrder::getinsurancefee() const{ return insurancefee; }
double FlightOrder::getservicefee() const{ return servicefee; }
double FlightOrder::getrefundfee() const{ return refundfee; }

void FlightOrder::printdetails() const{
    double finalBasePrice = baseprice;
    if(chosenFare)
    {
        finalBasePrice = chosenFare->calculateFinalPrice(baseprice);
    }
    cout<<"\n========== Order Details =========="<<endl;
    cout<<"Order ID: "<< orderid<<endl;
    cout<<"Provider: "<< providername<<" ("<<providertype << ")"<<endl;
    cout<<"Flight: "<< flightnumber<< endl;
    cout<<"Route: "<< source<< " -> "<<dest<<endl;
    cout<<"Time: "<<deptime<< " - "<<arrtime<<endl;
    cout<<"-----------------------------------" <<endl;
    if (chosenFare)
    {
        chosenFare->printFeatures();
        cout<<"-----------------------------------"<<endl;
    }
    cout<<"Base Price:    $"<<fixed<<setprecision(2)<<finalBasePrice<<" (Original: $"<<baseprice<< ")"<<endl;
    cout<<"Baggage Fee:   $"<<baggagefee<<endl;
    cout<<"Insurance Fee: $"<<insurancefee<<endl;
    cout<<"Service Fee:   $"<<servicefee <<endl;
    cout<<"Refund Fee:    $"<<refundfee <<" (if cancelled)"<<endl;
    cout<<"-----------------------------------"<<endl;
    cout<<"TOTAL:         $"<<gettotal()<<endl;
}