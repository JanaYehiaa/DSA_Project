#include "Car.h"
#include <iostream>
using namespace std;
Car::Car() : carType('U'), carSpeed(0), carStatus("Stopped"), hospID(0) {}
Car::Car(char type, int speed,  int HID, string status): carType(type), carSpeed(speed), hospID(HID), carStatus(status) {}
int Car::getHospID() const { return hospID; }
void Car::setBusyTime(int endTime) {
	busyTime = busyTime + (endTime - assignmentTime);
}
int Car::getBusyTime() const { return busyTime; }
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
int Car::getID()
{
	return carID;
}
void Car::setStatus(string status)
{
	carStatus = status;
}
void Car::setPatient(Patient* P) { patient = P; }
Patient* Car::getPatient() { return patient; }
char Car::getType() const { return carType; }
int Car::getSpeed() const { return carSpeed;}
string Car::getStatus() const { return carStatus;}
int Car::getAT() const { return assignmentTime; }
void Car::setAT(int a) { assignmentTime = a; }

ostream& operator <<(ostream& out, const Car c) {
	out << c.getStatus() << ",";
	return out;
}