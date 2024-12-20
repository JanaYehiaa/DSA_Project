#pragma once
#include<iostream>
#include <string>
#include "Patient.h"
using namespace std;

class Car
{
	char carType;
	int carSpeed;
	int assignmentTime;
	int busyTime;
	int hospID;
	int carID;
	string carStatus;
	Patient* patient=nullptr;
public:
	Car();
	Car(char type, int speed,  int HID, string status = "Ready");
	void setType(char type);
	void setSpeed(int speed);
	void setID(int id);
	void setAT(int a);
	int getID();
	int getAT() const;
	void setStatus(string status);
	void setBusyTime(int endTime);
	int getBusyTime() const;
	char getType() const;
	int getSpeed() const;
	int getHospID() const;
	friend ostream& operator <<(ostream& out, const Car c);
	string getStatus() const;
	void setPatient(Patient* P);
	Patient* getPatient();
	//void Print();
	//~Car();
};

