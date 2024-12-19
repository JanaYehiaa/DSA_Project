#include "Car.h"
#include <iostream>
using namespace std;
Car::Car() : carType('U'), carSpeed(0), carStatus("Stopped"), carID(0), failed(false), hospID(0) {}
Car::Car(char type, int speed, int HID, string status) : carType(type), carSpeed(speed), failed(false), carID(0), hospID(HID), carStatus(status) {}
int Car::getHospID() const { return hospID; }

void Car::setType(char type) 
{
	carType = type;
}
void Car::setSpeed(int speed) 
{
	carSpeed = speed;
}
void Car::setID(int id)
{
	carID = id;
}
int Car::getID() const
{
	return carID;
}
void Car::setStatus(string status)
{
	carStatus = status;
}
void Car::setFail(bool f)
{
	failed = f;
}
bool Car::getFailed() const
{
	return failed;
}

void Car::setPatient(Patient P) { patient = &P; }
Patient* Car::getPatient() { return patient; }
char Car::getType() const { return carType; }
int Car::getSpeed() const { return carSpeed;}
string Car::getStatus() const { return carStatus;}
int Car::getAT() const { return assignmentTime; }
ostream& operator <<(ostream& out, const Car c) {
	out << c.getID() << ",";
	return out;
}
