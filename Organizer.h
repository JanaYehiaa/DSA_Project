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
	float FailProb;
	int CheckUpTime;
	string filename;
public:
	LinkedQueue<Patient*> allReq;
	LinkedQueue<Patient*> cancel;
	Hospital* hospital;
	priQueue<Car*> backCars;
	priQueue<Car*> outCars;
	priQueue<Car> checkUp;
	LinkedQueue<Patient*> finished;
	Organizer();
	void Loadfile(const string& filename);
	bool Writefile(LinkedQueue<Patient*>& p);
	void moveNPReqToFinish(LinkedQueue<Patient*>& list, Hospital& h);
	void moveEPReqToFinish(priQueue<Patient*>& list, Hospital&h);
	void moveSPReqToFinish(LinkedQueue<Patient*>& list, Hospital& h);
	//void moveSCartoOut(Hospital& h);
	//void moveNCartoOut(Hospital& h);
	//void moveCarOuttoBack(priQueue<Car*>& out);
	//void moveCarBacktoFree(priQueue<Car*>& backCars);
	void moveCarBacktoCheckup(Car c, int T);
	void failureAction(Car s, int T);
	void addToFinished(Car c, int T);
	void reEnqueuePatient(Patient* p);
	void Simulation();
	void mainSimulation();
	int getHospitalnum() const;
	int getReqno() const;
	int avgWaitTime(LinkedQueue<Patient*>& p, int f) const;
	//int avgBusyTime() const;
	/*void AssignNPToNC(Patient P, Hospital& h);
	void AssignEPToEC(Patient P, Hospital& h);
	void AssignSPToSC(Patient SP, Hospital& h);*/
	//void freeToOut();
	void InteractiveMode(int timestep, Hospital& current, int Hon);
	void SilentMode();
	void HandleTimeStep(int timestep);
	void FreetoOut(int timestep, Hospital& current);
	void OuttoBack(int timestep);
	void BacktoFree(int timestep, Hospital& current);
	~Organizer();
};

