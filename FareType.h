#ifndef FARETYPE_H
#define FARETYPE_H
#include <string>
#include <iostream>
using namespace std;
class FareType {
public:
    virtual ~FareType() {}
    virtual double calculateFinalPrice(double basePrice) const = 0;
    virtual void printFeatures() const = 0;
    virtual string getName() const = 0;
};
class EconomyClass : public FareType {
public:
    double calculateFinalPrice(double basePrice) const override {
        return basePrice;
    } 
    void printFeatures() const override{
        cout<< "  - Fare Type: Economy Class"<<endl;
        cout<<"  - Features: Standard Seating, Pay for meals/drinks."<<endl;
    }
    string getName() const override{
        return "Economy Class";
    }};

class FirstClass : public FareType{
public:
    double calculateFinalPrice(double basePrice) const override
    {
        return basePrice * 3.0;
    }
    
    void printFeatures() const override
    {
        cout<<"  - Fare Type: First Class" << endl;
        cout<<"  - Features: Priority Boarding, Free Gourmet Meals, Extra Legroom."<<endl;          }
    
    string getName() const override
    {
        return "First Class";
    }
};
#endif