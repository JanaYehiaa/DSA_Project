#include "Car.h"
#include <iostream>
using namespace std;
Car::Car() : carType("Unspecified"), carSpeed(0), carStatus("Stopped"), hospID(0){}
Car::Car(string type, int speed,  int HID, string status): carType(type), carSpeed(speed), hospID(HID), carStatus(status) {}
int Car::getHospID() const { return hospID; }

void Car::setType(string type) 
{
	carType = type;
}
void Car::setSpeed(int speed) 
{
	carSpeed = speed;
}
void Car::setStatus(string status)
{
	carStatus = status;
}
void Car::setPatient(Patient P) { patient = &P; }
Patient* Car::getPatient() { return patient; }
string Car::getType() const { return carType;}
int Car::getSpeed() const { return carSpeed;}
string Car::getStatus() const { return carStatus;}

ostream& operator <<(ostream& out, const Car c) {
	out << c.getStatus() << ",";
	return out;
}