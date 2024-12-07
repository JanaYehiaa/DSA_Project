#pragma once
#include<iostream>
#include <string>
#include "Patient.h"
using namespace std;

class Car
{
	string carType;
	int carSpeed;
	int hospID;
	string carStatus;
	Patient* patient=nullptr;
public:
	Car();
	Car(string type, int speed,  int HID, string status = "Ready");
	void setType(string type);
	void setSpeed(int speed);
	void setStatus(string status);
	string getType() const;
	int getSpeed() const;
	int getHospID() const;
	friend ostream& operator <<(ostream& out, const Car c);
	string getStatus() const;
	void setPatient(Patient P);
	Patient* getPatient();
	//void Print();
	//~Car();
};

