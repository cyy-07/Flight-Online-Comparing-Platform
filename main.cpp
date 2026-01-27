#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <set>
#include "FlightOrder.h"
#include "FareType.h"
#include "UserAccount.h"
using namespace std;

vector<FlightOrder> loadflights(string filename) {
vector<FlightOrder> flights;
ifstream file(filename.c_str());

if (!file.is_open()){
    cout<<"Error: Cannot open "<<filename<<endl;
return flights;
}

string line;
getline(file, line);
while (getline(file, line)) {
    stringstream ss(line);
    string id, type, name, num, src, dst, dep, arr;
    string bstr, bgstr, istr, sstr, rstr;

    getline(ss, id, ',');           getline(ss, type, ',');
     getline(ss, name, ',');         getline(ss, num, ',');
    getline(ss, src, ',');          getline(ss, dst, ',');
    getline(ss, dep, ',');          getline(ss, arr, ',');
    getline(ss, bstr, ',');          getline(ss, bgstr, ',');
    getline(ss, istr, ',');         getline(ss, sstr, ',');
    getline(ss, rstr);
    FlightOrder order(id, type, name, num, src, dst, dep, arr,
    atof(bstr.c_str()), atof(bgstr.c_str()),
    atof(istr.c_str()), atof(sstr.c_str()), atof(rstr.c_str()));
    flights.push_back(order);
}

file.close();
return flights;
}
vector<string> getdeparturecities(vector<FlightOrder>& flights) {
set<string> cities;
     for(int i=0; i<flights.size();i++)
     {
    cities.insert(flights[i].getsource());
    }
return vector<string>(cities.begin(), cities.end());}
vector<string> getdestinations(vector<FlightOrder>& flights, string source) {
set<string> dests;
for (int i=0; i<flights.size();i++) {
    if (flights[i].getsource()==source) {
        dests.insert(flights[i].getdest());
}}
return vector<string>(dests.begin(), dests.end());
}
vector<FlightOrder> getflightsforroute(vector<FlightOrder>& flights, string src, string dst) {
vector<FlightOrder> results;
for (int i = 0; i < flights.size(); i++) {
if (flights[i].getsource() == src && flights[i].getdest() == dst) {
       results.push_back(flights[i]);
}}
return results;
}
struct TimeSlot {
    string label;
    string starttime;
    string endtime;
    vector<FlightOrder> flights;
};
vector<TimeSlot> groubybytime(vector<FlightOrder>& flights) {
vector<TimeSlot> slots;
TimeSlot morning, afternoon, evening;
morning.label = "Morning";
morning.starttime ="06:00";
morning.endtime="12:00";
afternoon.label="Afternoon";
afternoon.starttime="12:00";
afternoon.endtime= "18:00";
    evening.label="Evening/Night";
    evening.starttime ="18:00";
    evening.endtime ="06:00";

for(int i=0; i<flights.size();i++){
    string deptime = flights[i].getdeptime();
if(deptime>="06:00"&&deptime<"12:00") {
    morning.flights.push_back(flights[i]);
} 

else if (deptime>="12:00"&&deptime <"18:00") {
    afternoon.flights.push_back(flights[i]);
} 
  else {
    evening.flights.push_back(flights[i]);
}}
if (!morning.flights.empty()) 
                    slots.push_back(morning);
if (!afternoon.flights.empty())
                   slots.push_back(afternoon);
if (!evening.flights.empty())
    slots.push_back(evening);
return slots;}

void displayoptions(vector<FlightOrder>& flights)
{
if (flights.empty()){
    cout<<"No flights available."<<endl;
    return;
}

cout<<"\n--- Flight Options ("<<flights.size()<<" options) ---\n"<< endl; 
FlightOrder* airline_ref=NULL;
FlightOrder* thirdparty_ref =NULL;

for (int i=0; i<flights.size();i++) {
const FlightOrder& currentFlight = flights[i];
char optionLetter = 'A' + i;

cout<<"Option "<<optionLetter<<": "<<currentFlight.getprovidername()<<" ("<<currentFlight.getprovidertype()<<")"<<endl;
if (currentFlight.getprovidertype()=="Airline" && airline_ref==NULL) {
    airline_ref = &flights[i];
} else if(currentFlight.getprovidertype() =="ThirdParty" &&thirdparty_ref==NULL) {
    thirdparty_ref = &flights[i];
}

        cout<<"  Flight: "<<currentFlight.getflightnumber()
            <<" | Dep: "<<currentFlight.getdeptime()
            <<" | Arr: "<<currentFlight.getarrtime()<<endl;

        cout<<"  Base Price:   $"<<fixed<<setprecision(2)<<currentFlight.getbaseprice()<<endl;
        cout<<"  Baggage:    $"<<currentFlight.getbaggagefee();
if (currentFlight.getprovidertype() == "Airline") {
    cout<<" (included)";
}
    cout<<endl;

cout<<"  Insurance:    $"<<currentFlight.getinsurancefee();
if (currentFlight.getprovidertype()=="Airline") {
    cout<<" (included)";
}
        cout<<endl;

    cout<<"  Service Fee:  $"<<currentFlight.getservicefee()<<endl;
    cout<<"  Total:        $"<<currentFlight.gettotal()<<" <--- Compare this!"<<endl;
    cout<<"  Refund Fee:   $"<<currentFlight.getrefundfee()<<endl;
    cout<<endl;
    }

if(airline_ref != NULL && thirdparty_ref != NULL) {
double diff =airline_ref->gettotal()-thirdparty_ref->gettotal();
double refunddiff =thirdparty_ref->getrefundfee()-airline_ref->getrefundfee();

if(diff>0){
    cout<<"Tip: ThirdParty ("<<thirdparty_ref->getprovidername()<<") is $"<<diff<<" cheaper";
} else if (diff<0) {
    cout<<"Tip: Airline ("<<airline_ref->getprovidername()<<") is $"<<-diff<<" cheaper";
}
if (refunddiff>0) {
        cout<<", but refund fee is $"<<refunddiff<<" more!"<<endl;
} else{
    cout<<"!"<<endl;
}}}
UserAccount* attemptLogin(vector<UserAccount>& registeredUsers) {
    string inputUsername, inputPassword;
    cout<<"\n--- Login ---"<<endl;
    cout<<"Enter Username: ";
    cin >>inputUsername;
    cout <<"Enter Password: ";
    cin>> inputPassword;
    for (UserAccount& user:registeredUsers) {
        if (user.verify(inputUsername, inputPassword)) {
            cout<<"\nLogin Successful! Welcome, "<<user.getUsername() << "!"<<endl;
            cout<<"Current User: "<<user.getUsername()<<" (Passport ID: "<<user.getPassportID()<<")\n" <<endl;
            return &user;
        }
    }
    cout<< "\nLogin Failed. Invalid username or password."<<endl;
    return nullptr;
}
void registerAccount(vector<UserAccount>&registeredUsers) {
    string newUsername, newPassword, newPassportID;
    bool unique = false;
    cout <<"\n--- New Account Registration ---"<<endl;
    while(!unique) {
        cout<<"Enter new Username: ";
        cin>>newUsername;
        
        unique=true;
        for(const UserAccount& user :registeredUsers) {
            if(user.getUsername()==newUsername)
            {
                 cout<<"Username already exists. Try a different one."<<endl;
                unique=false;
                break;
            }
        }
    }
    cout<<"Enter new Password: ";        cin>>newPassword;
    cout<<"Enter Passport ID: ";          cin>>newPassportID;   
    registeredUsers.push_back(UserAccount(newUsername, newPassword, newPassportID));
    cout<<"\nRegistration Successful! You can now log in." <<endl;
}
int main() {
cout<<"\n========== Flight Booking System =========="<<endl;
vector<FlightOrder> allflights = loadflights("mock_flight_data.csv");
if(allflights.empty()) {
    cout<<"Failed to load flights. Exiting."<<endl;
    return 1;
}
cout<<"Loaded "<<allflights.size()<<" flights successfully!\n"<<endl;
vector<UserAccount> registeredUsers;
registeredUsers.push_back(UserAccount("CYY", "12345", "P87654321"));
registeredUsers.push_back(UserAccount("Traveller", "123456", "A12345678"));
  UserAccount* loggedInUser=nullptr;
char authChoice;
bool authLoop=true;

while (authLoop&&loggedInUser==nullptr) {
    cout<< "\n========== User Authentication =========="<<endl;
    cout<< "1. Login to Existing Account (We already have existing accounts, and"<<endl;
     cout<<" please check the password book located in account_and_password.txt within the zip file.)"<<endl;
    cout<<"2. Register New Account"<<endl;
    cout<<"3. Exit Program"<< endl;
         cout<<"Enter choice (1-3): ";
    if (!(cin >> authChoice)) {
        cout << "Invalid input. Please enter 1, 2, or 3."<<endl;
        cin.clear();
        cin.ignore(10000,'\n');
        continue;
    }
    if (authChoice=='1')
    {
        loggedInUser = attemptLogin(registeredUsers);
    } else if (authChoice=='2')
    {
        registerAccount(registeredUsers);
    } else if (authChoice=='3')
    {
        cout<<"\nExiting Program."<<endl;
        authLoop = false;
    } else {
        cout<<"Invalid choice. Please enter 1, 2, or 3."<<endl;
    }
}

if (loggedInUser==nullptr) {
        return 0;
}
vector<FlightOrder> cart;
bool shopping = true;

while (shopping) {
        cout<<"\nAvailable Departure Cities:"<< endl;
        vector<string> departures=getdeparturecities(allflights);
for (int i=0; i<departures.size(); i++) {
    cout<<(i+1)<<". "<<departures[i]<<endl;
}
    cout<<"0. Exit"<<endl;

    cout<<"\nSelect departure city (0-"<<departures.size()<<"): ";
int depchoice;
while (!(cin>>depchoice) ||depchoice<0|| depchoice>departures.size())
{
    if (cin.fail()) {
        cout<< "Invalid input type. Please enter a number: ";
    } else {
        cout<<"Invalid choice! Select departure city (0-" <<departures.size()<<"): ";
    }
    cin.clear();
    cin.ignore(10000,'\n');
}

if (depchoice==0)
{
        cout<<"Exiting..."<<endl;
        break;
}
string source=departures[depchoice-1];
dest_selection:
    cout<<"\nAvailable Destinations from "<<source<<":"<< endl;
vector<string> destinations =getdestinations(allflights, source);

if (destinations.empty())
{
  cout<<"No destinations available from "<<source<<endl;
continue;
}
for (int i=0; i<destinations.size();i++) {
  cout<<(i+1)<<". "<<destinations[i]<<endl;
}
cout<<"0. Back to departure selection"<<endl;

    cout<<"\nSelect destination (0-"<<destinations.size()<<"): ";
int destchoice;

while (!(cin >>destchoice)||destchoice<0||destchoice>destinations.size()) {
    if (cin.fail()) {
        cout<<"Invalid input type. Please enter a number: ";
    } else {
        cout<<"Invalid choice! Select destination (0-"<<destinations.size()<<"): ";}
    cin.clear();
    cin.ignore(10000,'\n');          }

if (destchoice==0)
{
    continue;
}

if (destchoice<1||destchoice>destinations.size()) {
        goto dest_selection;
}
string dest = destinations[destchoice-1];
vector<FlightOrder> routeflights=getflightsforroute(allflights, source, dest);

if (routeflights.empty())
{
        cout<<"No flights found for this route."<<endl;
        goto dest_selection;
}
time_selection:
cout<<"\n--- Flights from "<<source<<" to "<<dest<<" ---"<<endl;
vector<TimeSlot> timeslots=groubybytime(routeflights);

for (int i=0; i<timeslots.size(); i++)
{
        cout<<"\n"<<(i+1)<<". "<<timeslots[i].label<<" ("
        <<timeslots[i].starttime<<"-"<<timeslots[i].endtime<<")"<<endl;
        cout<<" "<<timeslots[i].flights.size()<<" options available"<<endl;
}
    cout<<"0. Back to destination selection"<<endl;
    cout<<"\nSelect time slot (0-"<<timeslots.size()<<"): ";
    int timechoice;
while (!(cin>>timechoice)||timechoice<0|| timechoice >timeslots.size()) {
    if(cin.fail()) {
        cout<< "Invalid input type. Please enter a number: ";
    } else
     {
        cout<<"Invalid choice! Select time slot (0-" << timeslots.size() << "): ";
    }
    cin.clear();
    cin.ignore(10000,'\n');
}
if(timechoice==0) 
{
    continue;
    }
if(timechoice<1 || timechoice>timeslots.size())
{
    goto time_selection;
    }

vector<FlightOrder> selectedflights = timeslots[timechoice-1].flights;
    option_selection:
displayoptions(selectedflights);
    cout<<"\nChoose option (e.g., A, B, C, D, or 0 to go back): ";
char option;
cin>>option;

    if(option=='0')
{
        goto time_selection;
}

FlightOrder* chosen =NULL;
     int index=-1;
if(option >='A'&& option<=('A'+selectedflights.size()-1)) {
    index = option -'A';
} else if (option>='a' && option <=('a'+selectedflights.size()-1)) {
    index =option-'a';
}

if (index !=-1)
{
    chosen=&selectedflights[index];
}
if (chosen != NULL) {
    char fareChoice;
    cout<<"\nChoose your fare type:"<<endl;
    cout<< "  [E] Economy Class (Base Price)"<<endl;
    cout<< "  [F] First Class (ONLY Base Price x 3, Free Meals, Spacious Seating and early boarding)" <<endl;
    cout<< "Enter E or F: ";
    
    cin >> fareChoice;

while(cin.fail() || (fareChoice !='E'&& fareChoice != 'e' &&fareChoice !='F'&&fareChoice !='f')) {
    cin.clear();                   cin.ignore(10000,'\n');
    cout<<"Invalid choice. Please enter E or F: ";
    cin>>fareChoice;
        }
if(fareChoice=='F'||fareChoice=='f') {
    double oldPrice=chosen->getbaseprice();
    chosen->setbaseprice(oldPrice * 3);
    cout <<"\nFirst Class selected! Price updated to $" 
         <<fixed<<setprecision(2)<<chosen->gettotal()<<endl;
} else {
    cout << "\nEconomy Class selected."<<endl;
}

cart.push_back(*chosen);
    cout<<"\nFlight added to your cart!" <<endl;

} else {
    cout<<"\nInvalid option! Please select again.\n";
    goto option_selection;
}
            cout<<"\nContinue shopping? (Y/N): ";
char cont;
cin >> cont;

if (cont=='N'||cont=='n') {
    shopping=false;
}}
if (cart.empty()) {
    cout<<"\nYour cart is empty. Goodbye!"<<endl;
    return 0;
}

cout<<"\n========== Shopping Cart =========="<<endl;
double total = 0;
for (int i=0; i<cart.size();i++) {
    cout<<(i+1)<<". "<<cart[i].getprovidername()<<" "
        <<cart[i].getflightnumber()<<" | "
        <<cart[i].getsource()<<" -> "<< cart[i].getdest()
        <<" | Dep: "<<cart[i].getdeptime()
        <<" | Arr: "<<cart[i].getarrtime()<<endl;
    cout<<"   Total Price: $"<<fixed<<setprecision(2)<<cart[i].gettotal()<<endl<<endl;
    total += cart[i].gettotal();
    }

cout<<"Grand Total: $"<<fixed<<setprecision(2)<<total<<endl;

cout<<"\nProceed to payment? (Y/N):";
char pay;
cin>>pay;

if(pay=='Y'||pay=='y') 
{
    cout<<"\nProcessing payment..."<<endl;
    cout<<"Payment successful! Booking confirmed under Passport ID: "
        <<loggedInUser->getPassportID()<<endl;
} else
{
    cout<<"\nPayment cancelled. Your cart will be cleared."<<endl;
}
    cout<<"\nThank you for using the Flight Booking System!"<<endl;
    cout<<"Press Enter to exit...";
    cin.ignore();
    cin.get();
    return 0;
}