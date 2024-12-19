#pragma once
#include <fstream>
#include <time.h>
#include"Hospital.h"
#include"UI.h"

class Organizer
{
	int Reqno;
	int CancelReq;
	int TotalEPNo;
	int TotalNpNo;
	int TotalSpNo;
	int Hospitalnumber;
	int FinishedPat=0;
	int noScar;
	int noNcar;
	int Totalcars;
	int FailProb;
	string filename;
public:
	LinkedQueue<Patient> allReq;
	LinkedQueue<Patient> cancel;
	Hospital* hospital;
	priQueue<Car> backCars;
	priQueue<Car> outCars;
	LinkedQueue<Patient> finished;
	Organizer();
	void Loadfile(const string& filename);
	bool Writefile(LinkedQueue<Patient>& p);
	void moveNPReqToFinish(LinkedQueue<Patient>& list, Hospital& h);
	void moveEPReqToFinish(priQueue<Patient>& list, Hospital&h);
	void moveSPReqToFinish(LinkedQueue<Patient>& list, Hospital& h);
	void moveSCartoOut(Hospital& h);
	void moveNCartoOut(Hospital& h);
	void moveCarOuttoBack(priQueue<Car>& out);
	void moveCarBacktoFree(priQueue<Car>& backCars);
	void setPatFinishTime(Patient p, Car c);
	void setPatPickupTime(Patient p, Car c);
	void Simulation();
	bool mainSimulation();
	int getHospitalnum() const;
	int getReqno() const;
	int avgWaitTime(LinkedQueue<Patient>& p, int f) const;
	void AssignNPToNC(Patient P, Hospital& h);
	void AssignEPToEC(Patient P, Hospital& h);
	void AssignSPToSC(Patient SP, Hospital& h); 
	void SilentMode();
	void InteractiveMode();
	~Organizer();
};

