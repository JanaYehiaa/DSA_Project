#include "Hospital.h"
#include <iostream>
using namespace std;
Hospital::Hospital() : ID(0), cars(nullptr), noNP(0), noSP(0), noEP(0), noScars(0), noNcars(0) {
	for (int i = 0; i < MAX_HOSPITALS; ++i) {
		for (int j = 0; j < MAX_HOSPITALS; ++j) {
			Dmatrix[i][j] = 0;  
		}
	}
}

Hospital::Hospital(int id, Car* Cars):ID(id), cars(Cars), noNP(0), noSP(0), noEP(0), noScars(0), noNcars(0) {
	for (int i = 0; i < MAX_HOSPITALS; ++i) {
		for (int j = 0; j < MAX_HOSPITALS; ++j) {
			Dmatrix[i][j] = 0;
		}
	}
}
void Hospital::setID(int id) { ID = id; }
void Hospital:: setCars(Car* Cars,int newsize) {
	//delete[] this->cars; should I delete to avoid memory leaks?
	/*if (Cars)
	{
		this->cars = new Car[newsize];
		for (int i = 0; i < newsize; i++)
		{
			this->cars[i] = Cars[i];
		}
	}
	else
		this->cars = nullptr;*/ //will be done similarly but it takes NC then special cars or vice versa cant remember
}
int Hospital::getID() const { return ID; }
//int Hospital::getNBofHospitals() const { return nbOfHospitals;} 
Car* Hospital::getCars() const { return cars; }

void Hospital::enqueueScar(Car& car,int n ) {
	for (int i = 0; i < n; i++)
		SCarslist.enqueue(car);
}
void Hospital::enqueueNcar(Car& car, int n ) {
	for (int i = 0; i < n; i++)
		NCarslist.enqueue(car);
	
}


void Hospital::setnoNP(int a) { noNP = a; }
void Hospital::setnoSP(int a){ noSP = a; }
void Hospital::setnoEP(int a){ noEP = a; }
int Hospital::getnoNP() const { return noNP; }
int Hospital::getnoEP() const{ return noEP; }
int Hospital::getnoSP() const{ return noSP; }


void Hospital::enqueueNp(Patient& p) {
	NPlist.enqueue(p);
}
void Hospital::enqueueSp(Patient& p) {
	SPlist.enqueue(p);
}
void Hospital::enqueueEp(Patient& p, int s) {
	EPlist.enqueue(p, s);
}

void Hospital::setnoScar(int a) { noNcars = a; }
void Hospital::setnoNcar(int a) { noScars = a; }

void Hospital::setDistance(int i, int j, int d) {
	Dmatrix[i][j] = d;
	Dmatrix[j][i] = d;  
}

Car* Hospital::dequeueNcar() {
	Car* car = new Car(); 
	NCarslist.dequeue(*car); 
	return car; 
}

Car* Hospital::dequeueScar() {
	Car* car = new Car(); 
	SCarslist.dequeue(*car); 
	return car; 
}

priQueue<Patient>& Hospital::getEPQueue() {
	return EPlist;
}

LinkedQueue<Patient>& Hospital::getSPQueue() {
	return SPlist;
}

LinkedQueue<Patient>& Hospital::getNPQueue() {
	return NPlist;
}

int Hospital::getnoScar() const { return noScars; }
int Hospital::getnoNcar() const { return noNcars; }



void Hospital::printSPrequest()
{
	LinkedQueue<Patient> tempQueue = SPlist;
	cout << "sp request: ";
	while (!tempQueue.isEmpty()) {
		Patient x;
		tempQueue.dequeue(x);
		x.printID();
	}
}

void Hospital::printEPrequest()
{
	priQueue<Patient> tempQueue = EPlist;
	cout << "ep request: ";
	while (!tempQueue.isEmpty()) {
		Patient x;

		int y = x.getSeverity();
		tempQueue.dequeue(x, y);
		x.printID();
	}
}


void Hospital::printNPrequest()
{
	CancelQueue<Patient> tempQueue = NPlist;
	cout << "np request: ";
	while (!tempQueue.isEmpty()) {
		Patient x;
		tempQueue.dequeue(x);
		x.printID();

	}
}


void Hospital::printFreeCars()
{
	LinkedQueue<Car> temp1 = SCarslist;
	LinkedQueue<Car> temp2 = NCarslist;
	int c1 = 0, c2 = 0;
	while (!temp1.isEmpty()) {
		Car x;
		temp1.dequeue(x);
		c1++;

	}
	while (!temp2.isEmpty()) {
		Car x;
		temp2.dequeue(x);
		c2++;

	}
	cout << "Free cars: " << c1 << " SCars, " << c2 << " NCars" << endl;
}




void Hospital::handleReq(LinkedQueue<Patient> QP, int timestep) {
	
	while (!QP.isEmpty()) {
		Patient currentP;
		QP.dequeue(currentP);
		if(currentP.getRequestTime() <= timestep){
			if (currentP.getPatientType() == "EP") {
				EPlist.enqueue(currentP, currentP.getSeverity());
			}
			else if (currentP.getPatientType() == "SP") {
				SPlist.enqueue(currentP);
			}
			else if (currentP.getPatientType() == "NP") {
				NPlist.enqueue(currentP);
			}
		}
		
	}
}


Hospital::~Hospital() { delete[]cars; }
