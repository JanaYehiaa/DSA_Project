#pragma once
#include<iostream>
#include <string>
#include "Car.h"
#include "Patient.h"
#include"LinkedQueue.h"
#include"PriQueue.h"
using namespace std;
class Hospital
{
	int ID;
	Car* cars;
	int noNP;
	int noSP;
	int noEP;
	int noScars;
	int noNcars;
	static const int MAX_HOSPITALS = 100;
	int Dmatrix[MAX_HOSPITALS][MAX_HOSPITALS];
	LinkedQueue<Patient*> SPlist;
	CancelQueue<Patient*> NPlist;
	priQueue<Patient*> EPlist;
	LinkedQueue<Car*> SCarslist;
	LinkedQueue<Car*> NCarslist;
//	LinkedQueue<Patient*> AssignedP;
	LinkedQueue<Car*> AssignedCars;
	
public:
	Hospital();
	Hospital(int id, Car* Cars);
	void setID(int id);
	void setCars(Car* Cars, int newsize);
	void setnoNP(int a);
	void setnoSP(int a);
	void setnoEP(int a);
	int getnoNP() const;
	int getnoEP() const;
	int getnoSP() const;
	int getnoScar() const;
	int getnoNcar() const;
	priQueue<Patient*>& getEPQueue() ;
	LinkedQueue<Patient*>& getSPQueue() ;
	LinkedQueue<Patient*>& getNPQueue();
	LinkedQueue<Car*>& getNCQueue();
	LinkedQueue<Car*>& getSCQueue();
	LinkedQueue<Car*>& getACQueue();



	void enqueueNp(Patient *p);
	void enqueueSp(Patient* p);
	void enqueueEp(Patient* p, int s);
	void setnoScar(int a);
	void setnoNcar(int a);
	void printFreeCars();
	void printSPrequest();
	void printNPrequest();
	void printEPrequest();
	int getID() const;
	Car* getCars() const;
	void setPatFinishTime(Patient* p, Car* c);
	void setPatPickupTime(Patient* p, Car* c);
	void enqueueScar(Car &car, int n=1);
	void enqueueNcar(Car& car, int n =1);
	Car& dequeueNcar();
	Car& dequeueScar();
	void setDistance(int i, int j, int d);
	//friend ostream& operator <<(ostream& out, const Hospital c);
	void handleReq(LinkedQueue<Patient*> QP, int timestep);
	void AssignEp(int timestep);
	void AssignNPtoNc(int timestep);
	void AssignSPtoSC(int timestep);
	//Car* AssignNPToNC( int TS);
	//Car* AssignEPToEC( int TS);
	//Car* AssignSPToSC(int TS);
	~Hospital();
};

