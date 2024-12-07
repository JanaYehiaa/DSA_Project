#pragma once
#include <fstream>
#include <time.h>
#include"Hospital.h"
#include"UI.h"

class Organizer
{
	int Reqno;
	int Hospitalnumber;
	int FinishedPat=0;
	int noScar;
	int noNcar;
public:
	LinkedQueue<Patient> allReq;
	LinkedQueue<Patient> cancel;
	Hospital* hospital;
	priQueue<Car> backCars;
	priQueue<Car> outCars;
	LinkedQueue<Patient> finished;
	Organizer();
	void Loadfile(const string& filename);
	void moveNPReqToFinish(LinkedQueue<Patient>& list, Hospital& h);
	void moveEPReqToFinish(priQueue<Patient>& list, Hospital&h);
	void moveSPReqToFinish(LinkedQueue<Patient>& list, Hospital& h);
	void moveSCartoOut(Hospital& h);
	void moveNCartoOut(Hospital& h);
	void moveCarOuttoBack(priQueue<Car>& out);
	void moveCarBacktoFree(priQueue<Car>& backCars);
	void Simulation();
	int getHospitalnum() const;
	int getReqno() const;
	void AssignNPToNC(Patient P, Hospital& h);
	void AssignEPToEC(Patient P, Hospital& h);
	void AssignSPToSC(Patient SP, Hospital& h); 
	~Organizer();
};

