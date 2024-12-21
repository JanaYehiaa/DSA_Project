#pragma once
#include<iostream>
#include <string>
using namespace std;
class Patient
{
	int requestTime;
	int finishTime;
	int pickupTime;
	int waitTime;
	int ID;
	int nearestHospital;
	int distance;
	string patientType;
	int severity;
	bool picked;
public:
	Patient();
	//Patient(int request, int pickup, int nearest, int dist, string type, int severity = 0);
	Patient(string type, int rt, int ID, int hid, int dst, int svr=0, bool p = 0);
	void setRequestTime(int request);
	void setFinishTime(int f);
	void setPickupTime(int pickup);
	void setWaitTime(int pt);
	void setNearestHospital(int nearest);
	void setDistance(int dist);
	void setPatientType(string type);
	void setID(int id);
	void setpicked(bool a);
	void setSev(int s);
	bool getpicked() const;
	int getSeverity() const;
	int getRequestTime() const;
	int getPickupTime() const;
	int getWaitTime() const;
	int getFinishTime() const;
	int getNearestHospital() const;
	int getDistance() const;
	int getID() const;
	string getPatientType() const;
	friend ostream& operator <<(ostream& out, const Patient& c);
	void printID();
	//~Patient();
};

