#include <iostream>
#include <conio.h>
using namespace std;

class TollBooth {
private:
    unsigned int carsPassed;
    int totalMoney;

public:
    TollBooth();
    void payingCar();
    void nopayCar();
    void display();
};

TollBooth::TollBooth() : carsPassed(0), totalMoney(0) {}

void TollBooth::payingCar() {
    carsPassed++;
    totalMoney += 50.0;
}

void TollBooth::nopayCar() {
    carsPassed++;
}

void TollBooth::display() {
    cout << "Total Cars Passed: " << carsPassed << endl;
    cout << "Total Money Collected: Rs " << totalMoney << endl;
}

int main() {
    TollBooth booth;
    char key;

    cout << "Press 'A' for paying car\n'D' for non-paying car\n'Esc' to exit: ";

    while (true)
    {
        key = _getch();

        if (key == 27) {
            booth.display();
            cout << "exiting: ";
            break;
        }
        else if (key == 'a' || key == 'A') {
            booth.payingCar();
            cout << "A pressed: Car passed money collected.";
        }
        else if (key == 'd' || key == 'D') {
            booth.nopayCar();
            cout << "D pressed: Car passed no money collected.";
        }
        else {
            cout << "Invalid key. Please press 'A', 'D', or Esc.\n";
        }
    }

    return 0;
}