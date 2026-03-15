#include <iostream> 
#include <conio.h> 
#include <string> 
using namespace std; 
 
class TollBooth 
{ 
private: 
    unsigned int carsPassed; 
    double totalMoney; 
    string location;          // Use string instead of char* 
    static int boothCount;    // Static member 
public: 
    TollBooth();                         // Default constructor 
    TollBooth(const string& loc);        // Parameterized constructor 
    TollBooth(const TollBooth& obj);     // Copy constructor 
    void payingCar(); 
    void nopayCar(); 
    int getcarsPassed() const; 
    double gettotalMoney() const; 
    string getLocation() const;          // Getter for location 
    TollBooth operator+(const TollBooth& other) const; 
    // Friend functions 
 friend int auditBooth(const TollBooth& b); // Friend function to access private members 
 friend double totalReport(TollBooth* booth, int n);// Friend function to calculate total cash from all booths 
    static int showBoothCount(int n);   // Static function 
    ~TollBooth(); 
}; 
 
// Static variable definition 
int TollBooth::boothCount = 0; 
// Default constructor
TollBooth::TollBooth() {
    carsPassed = 0;
    totalMoney = 0;
    location = "xyz";
}

// Parameterized constructor
TollBooth::TollBooth(const string& loc) {
    carsPassed = 0;
    totalMoney = 0;
    location = loc;
}

// Copy constructor
TollBooth::TollBooth(const TollBooth& obj)
    : carsPassed(obj.carsPassed),
    totalMoney(obj.totalMoney),
    location(obj.location) {
}

// Getter functions 
int TollBooth::getcarsPassed() const  { 
    return carsPassed;  
} 
double TollBooth::gettotalMoney() const {  
    return totalMoney; 
} 
string TollBooth::getLocation() const {  
    return location;  
} 
// Record cars 
void TollBooth::payingCar() {  
    carsPassed++; 
    totalMoney += 50;  
} 
void TollBooth::nopayCar() { 
    carsPassed++; 
} 
// Operator + to merge stats 
TollBooth TollBooth::operator+(const TollBooth& other) const 
{ 
    TollBooth result; 
    result.carsPassed = this->carsPassed + other.carsPassed; 
    result.totalMoney = this->totalMoney + other.totalMoney; 
    return result; 
} 
 
// Static function 
int TollBooth::showBoothCount(int n) { 
 boothCount = n; // Set booth count based on user input 
    return boothCount;  
} 
 
// Destructor 
TollBooth::~TollBooth() 
{ // Destructor (not needed in this case, but included for completeness) 
} 
 
// Friend functions 
int auditBooth(const TollBooth& b) { return b.carsPassed; } 
double totalReport(TollBooth* booth, int n) 
{ 
    double totalMoney = 0; 
    for (int i = 0; i < n; i++) totalMoney += booth[i].totalMoney; 
    return totalMoney; 
} 
 
int main()
{
    int n;
    cout << "Enter number of TollBooths: ";
    cin >> n;
    cin.ignore();  // Clear newline from input buffer

    // Create booths with location names
    TollBooth* booth = new TollBooth[n];
    for (int i = 0; i < n; i++)
    {
        string loc;
        cout << "Enter location name for Booth " << i + 1 << ": ";
        getline(cin, loc);
        booth[i] = TollBooth(loc);   // Used parameterized constructor
    }

    char c;
    int location;

    // infinite loop
    while (true)
    {
        cout << "\nEnter TollBooth number (1-" << n << "): ";
        cin >> location;
        if (location < 1 || location > n) {                   // CHECK CONDITION
            cout << "Invalid booth number. Try again.";
            continue;
        }
        cout << "For TollBooth : " << booth[location - 1].getLocation() << "\n";
        cout << "\nPress a for Paying car";
        cout << "\nPress d for Non-paying car";
        cout << "\nPress ESC to Exit\n";
        c = _getch();

        if (c == 'a' || c == 'A') { booth[location - 1].payingCar(); 
        cout << "\nPaying car counted."; }
        else if (c == 'd' || c == 'D') { booth[location - 1].nopayCar(); 
        cout << "\nNon-paying car counted."; }
        else if (c == 27) break;  // ESC
    }

    cout << "\n\n===== Money Collected and Cars Passed =====\n";
    TollBooth total = booth[0];// Start with first booth data
    for (int i = 0; i < n; i++)// Display each booth's report
    {
        cout << "\nTollBooth: " << booth[i].getLocation();
        cout << "\nTotal Cars Passed: " << booth[i].getcarsPassed();
        cout << "\nTotal Money Collected: Rs " << booth[i].gettotalMoney() << " \n";
        if (i > 0) 
            total = total + booth[i];
    }

    // Friend functions
    for (int i = 0; i < n; i++)// Audit each booth
    {
        cout << "\nAudit Cars in " << booth[i].getLocation() << ": " << auditBooth(booth[i]);
    }
    cout << "\nTotal Cash (using private data members in Friend Function): " << totalReport(booth, n);
    // Static function to show booth count
    cout << "\nTotal TollBooth Objects Created: " << TollBooth::showBoothCount(n);
    delete[] booth; //Free dynamic memory
}