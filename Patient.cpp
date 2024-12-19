#include "Patient.h"
#include <iostream>
using namespace std;
Patient::Patient() :requestTime(0), pickupTime(0), ID(0), nearestHospital(0), distance(0), patientType("NP"), severity(0), picked(0) {}
//Patient::Patient(int request, int pickup, int nearest, int dist, string type, int severity) : requestTime(request), pickupTime(pickup), nearestHospital(nearest), distance(dist), patientType(type), severity(severity) {  }
Patient::Patient(string type, int rt, int ID, int hid, int dst, int svr , bool p): patientType(type), requestTime(rt), ID(ID), nearestHospital(hid), distance(dst), severity(svr), picked(p), pickupTime(0){}
void Patient::setpicked(bool a) { picked = a; }
bool Patient::getpicked() const { return picked; }
void Patient::setRequestTime(int request){ requestTime = request; }
void Patient::setPickupTime(int pickup) { pickupTime = pickup; }
void Patient::setNearestHospital(int nearest) { nearestHospital = nearest; }
void Patient::setDistance(int dist) { distance = dist; }
void Patient::setPatientType(string type) { patientType = type; }
void Patient::setID(int id) { ID = id; }
void Patient::setFinishTime(int f) { finishTime=f; }
void Patient::setWaitTime(int pt, int qt) { waitTime = pt - qt; }
int Patient::getRequestTime() const { return requestTime; }
int Patient::getPickupTime() const { return pickupTime; }
int Patient::getNearestHospital() const { return nearestHospital; }
int Patient::getWaitTime() const { return waitTime; }
int Patient::getFinishTime() const { return finishTime; }
int Patient::getDistance() const { return distance; }
int Patient::getID() const { return ID; }
int Patient::getSeverity() const { return severity; }
void Patient::setSev(int s) { severity = s; }


void Patient::printID() {
	int x = this->getID();
	cout << x<< " ";
}

ostream& operator <<(ostream& out, const Patient& c) {
	out << c.getID() << " ";
	return out;
}


string Patient::getPatientType() const{ return patientType;}
//~Patient() ; el destructor msh 3arfa a3melo
