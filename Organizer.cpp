#include "Organizer.h"




Organizer::Organizer() {
	Simulation();
}
/*
Organizer::Organizer() {
	srand((int)time(NULL));
	UI ui;
	ui.readmode();
	filename = ui.getFilename();

}
*/

int Organizer::avgWaitTime(LinkedQueue<Patient*>& p, int f) const {
	int wt = 0;
	LinkedQueue<Patient*> temp1 = p;
	Patient* P=new Patient;
	while (!temp1.isEmpty()) {
		temp1.dequeue(P);
		wt += P->getWaitTime();
	}
	return (wt / f);
}
void Organizer::moveCarBacktoCheckup(Car c, int T)
{
	int x = -T;
	if (c.getPatient()->getFinishTime() == T)
		checkUp.enqueue(c, x);
}
void Organizer::failureAction(Car m, int T)
{
	//put from out to back here
	moveCarBacktoCheckup(m, T);
	//Patient s = *m.getPatient();
	Patient *s=m.getPatient();
	reEnqueuePatient(s);
}

void Organizer::addToFinished(Car c, int T)
{
	Patient* p = c.getPatient();//8ayarna hena
	if (p->getFinishTime() == T)
		finished.enqueue(p);
}
void Organizer::reEnqueuePatient(Patient* p)
{
	LinkedQueue<Patient*> temp = allReq;
	LinkedQueue<Patient*> temp1;
	while (!temp.isEmpty()) {
		Patient *t=new Patient;
		temp.dequeue(t);
		temp1.enqueue(p); 
		temp1.enqueue(t);
	}
	allReq = temp1;
}
void Organizer::Simulation( ) {
	srand((int)time(NULL));
	int timestep=0;
	UI ui;
	ui.readmode();
	if (ui.getmode() == 2)
		return;
	filename = (ui.getFilename()); 

	Loadfile(filename);
	bool flag = (FinishedPat == Reqno);
	while (!flag) {
		ui.display_same_line("Current Timestep:");
		ui.display(timestep);

		for (int i = 0; i < Hospitalnumber; i++) {
			Hospital& currentHospital = hospital[i];  
			int randomNum = rand() % 101;
			//ui.printPriPatient(currentHospital.getEPQueue(), timestep);
			//moveEPReqToFinish(currentHospital.getEPQueue(), currentHospital);
			if (randomNum >= 10 && randomNum < 20) {
				moveSPReqToFinish(currentHospital.getSPQueue(), currentHospital);
			}
			else if (randomNum >= 20 && randomNum < 25) {
				//ui.printPriPatient(currentHospital.getEPQueue(), timestep);

				moveEPReqToFinish(currentHospital.getEPQueue(), currentHospital);
			}
			else if (randomNum >= 30 && randomNum < 40) {
				moveNPReqToFinish(currentHospital.getNPQueue(), currentHospital);
			}
			else if (randomNum >= 40 && randomNum < 45) {
				//moveSCartoOut(currentHospital);
			}
			else if (randomNum >= 70 && randomNum < 75) {
				//moveNCartoOut(currentHospital);
			}
			else if (randomNum >= 80 && randomNum < 90) {
				//moveCarOuttoBack(outCars);
			}
			else if (randomNum >= 91 && randomNum < 95) {
				//moveCarBacktoFree(backCars);
			}
			flag = (FinishedPat == Reqno);



			//printing patients lists 

			ui.display_same_line("================  HOSPITAL #");
			ui.display_same_line(i + 1);
			ui.display("data  =================");
			
			ui.display_same_line("NP Requests: ");
			ui.printPatient(currentHospital.getNPQueue(), timestep);
			ui.display(" "); //to leave a line between patients

			ui.display_same_line("SP Requests: ");
			ui.printPatient(currentHospital.getSPQueue(), timestep);
			ui.display(" ");

			ui.display_same_line("EP Requests: ");

			ui.printPriPatient(currentHospital.getEPQueue(), timestep);
			ui.display(" ");

			//printing scars and ncars
			ui.display_same_line("Free Cars: ");
			ui.display_same_line(currentHospital.getnoScar());
			ui.display_same_line("Scars, ");
			ui.display_same_line(currentHospital.getnoNcar());
			ui.display("Ncars");

			ui.display_same_line("================  HOSPITAL #");
			ui.display_same_line(i + 1);
			ui.display("data  end =================");
			ui.display("-----------------------------------------");
			ui.display_same_line("Finished patients: ");
			ui.printPatient(finished,  timestep);
			ui.display(" ");
			ui.waitForEnter();

		}

		timestep++;
	}
	ui.display("Simulation Ended! ");
}


int Organizer::getHospitalnum() const { return Hospitalnumber; }
int Organizer::getReqno() const { return  Reqno; }
//void Organizer:: AssignNPToNC(Patient P, Hospital& h){
//	if (h.getnoNcar() != 0)
//	{
//		Car car1;
//		/*LinkedQueue<Patient> np = h.getNPQueue();
//		priQueue<Patient> ep = h.getEPQueue();
//		if (ep.isEmpty()==true)*/
//		LinkedQueue<Car>& c = h.getNCQueue();
//		c.dequeue(car1);
//		car1.setPatient(P);// this function takes a patient to assign to normal car; check for emergency first and type of patient to be done outside function
//	}
//}
//void Organizer::AssignEPToEC(Patient EP, Hospital& h) {
//	Car car1;
//	if (h.getnoNcar() != 0)
//	{
//		LinkedQueue<Car>& c = h.getNCQueue();
//		c.dequeue(car1);
//		car1.setPatient(EP);
//	}
//	else if (h.getnoScar() != 0) {
//		LinkedQueue<Car>& c = h.getSCQueue();
//		c.dequeue(car1); 
//		car1.setPatient(EP);  
//	}
//	else
//	{
//		for (int i = 0; i < Hospitalnumber; i++)
//		{
//			Hospital& currentHospital = hospital[i]; 
//			//if(currentHospital==EP.getNearestHospital()), howa el nearest int da bey3abar 3n eh?
//			if (currentHospital.getnoNcar() != 0)
//			{
//				LinkedQueue<Car>& c = h.getNCQueue();
//				c.dequeue(car1);//should I check if the car has a patient or should I just move the car to out car?? y3ni hal di function tania el howa el requirment el ba3do
//				car1.setPatient(EP); 
//				break;//es2ali 7ad; mmken while loop
//			}
//
//		}
//	}
//}
//void Organizer::AssignSPToSC(Patient SP, Hospital& h){
//	if (h.getnoScar()!=0)
//	{
//		Car car1;
//		LinkedQueue<Car>& c = h.getSCQueue();
//		c.dequeue(car1);
//		car1.setPatient(SP);
//	}
//}


void Organizer::moveNPReqToFinish(LinkedQueue<Patient*>& list, Hospital& h) {
	while (!list.isEmpty()) {
		Patient* p = new Patient; 
		list.dequeue(p);
		h.setnoNP((h.getnoNP()-1));
		finished.enqueue(p);
		FinishedPat++;
		
	
	}
}

void Organizer::moveEPReqToFinish(priQueue<Patient*>& list, Hospital& h) {
	int s = 0;
	while (!list.isEmpty()) {
		Patient* p = new Patient; 
		list.dequeue(p, s); 
		h.setnoEP((h.getnoEP() - 1));
		finished.enqueue(p);
		FinishedPat++;
	
	}
}


void Organizer::moveSPReqToFinish(LinkedQueue<Patient*>& list, Hospital& h) {
	while (!list.isEmpty()) {
		Patient* p=new Patient;
		list.dequeue(p);
		h.setnoSP((h.getnoSP() - 1));
		finished.enqueue(p);
		FinishedPat++;
	

	}
}
/*
void Organizer::moveNCartoOut(Hospital& h) {
	Car* c = h.dequeueNcar(); 
	if (c) { 
		outCars.enqueue(*c, 1); 
		delete c; 
	}
}


void Organizer::moveSCartoOut(Hospital& h) {
	Car* c = h.dequeueScar(); 
	if (c) { 
		outCars.enqueue(*c, 1); 
		delete c; 
	}
}
*/
/*
void Organizer::moveCarOuttoBack(priQueue<Car>& Carl) {
	while (!Carl.isEmpty()) {
		Car c;
		int x = 1;
		Carl.dequeue(c, x);
		backCars.enqueue(c, 1); //we will send any priority now, as car assignment in phase 2  

	}
}

void Organizer::moveCarBacktoFree(priQueue<Car>& backCars) {
	while(!backCars.isEmpty()){
		Car c;
		int x = 1;
		backCars.dequeue(c, x);
		for (int i = 0; i < Hospitalnumber; i++) {

				if (hospital[i].getID() == c.getHospID()) {

					if (c.getType() == 'N') {
						hospital[i].enqueueNcar(c);
						}
					else {
						hospital[i].enqueueScar(c);

					}
					break;
			}
		}
	
	}
	
}

*/
void Organizer::Loadfile(const string& filename) {
	fstream file(filename);
	UI ui;
	if (!file)
	{
		ui.display("Failed to open file!");  //checks if file opens safely
		return;
	}

	//reading data
	int  Nspeed, Sspeed = 0;
	file >> Hospitalnumber;
	file >> Sspeed >> Nspeed;
	hospital = new Hospital[Hospitalnumber];


	


	for (int i = 0; i< Hospitalnumber; i++) {
		hospital[i].setID(i+1);
	}


	//distmatrix
	for (int i = 0; i < Hospitalnumber; i++) {

		for (int j = 0; j < Hospitalnumber; j++) {
			int distance = 0;
			file >> distance;
			if (i >= 0 && i < Hospitalnumber && j >= 0 && j < Hospitalnumber) {
				hospital[i].setDistance(i, j, distance);
			}
		}
	
	}

	//looping on number of hospitals and creating instances 
	for (int i = 0; i < Hospitalnumber; i++) {
		
		int id = i + 1;
		file >> noScar >> noNcar;
		Car a('S', Sspeed, id);
		Car b('N', Nspeed, id);
		hospital[i].setnoScar(noScar);
		hospital[i].setnoNcar(noNcar);
		hospital[i].enqueueScar(a, noScar);
		hospital[i].enqueueNcar(b, noNcar);
	}
	//outcar failure probability and checkup time
	file >> FailProb;
	file >> CheckUpTime;
	//handling requests
	string type = "N/A";
	int QT = 0;
	int PID = -1;
	int HID = -1;
	int DST = -1;
	int SVR = 0;
	int CT = -1;
	file >> Reqno;
	for (int i = 0; i < Reqno; i++) {
		file >> type;
		if (type == "EP") {
			file >> QT >> PID >> HID >> DST >> SVR;
			Patient* p1 = new Patient(type, QT, PID, HID, DST, SVR);
			allReq.enqueue(p1);
			hospital[HID - 1].enqueueEp(p1, SVR);
			int a = hospital[HID - 1].getnoEP();
			hospital[HID - 1].setnoEP(a + 1);

			
		}
		else if (type == "NP") {
			file >> QT >> PID >> HID >> DST;
			Patient* p1 = new Patient(type, QT, PID, HID, DST);
			allReq.enqueue(p1);
			hospital[HID - 1].enqueueNp(p1);
			int a = hospital[HID - 1].getnoNP();
			hospital[HID - 1].setnoNP(a + 1);
		}
		else if (type == "SP"){
			file >> QT >> PID >> HID >> DST;
			Patient* p1 = new Patient(type, QT, PID, HID, DST);
			allReq.enqueue(p1);
			hospital[HID - 1].enqueueSp(p1);
			int a = hospital[HID - 1].getnoSP();
			hospital[HID - 1].setnoSP(a + 1);
		}
	}
	


	//handling cancellation
	file >> CancelReq;
	for (int i = 0; i < CancelReq; i++) {
		file >> CT >> PID >> HID;
		
		LinkedQueue <Patient*> tempQueue;  // temporary queue for traversal
		bool found = false;
		while (!allReq.isEmpty())
		{
			Patient *p=new Patient;
			 allReq.dequeue(p);
			 if (p->getID() == PID)
			 {
				 found = true;
				 if (!p->getpicked())
				 {
					 cancel.enqueue(p); 
				 }
				 else
				 {
					 tempQueue.enqueue(p); 
				 }
			 }
			 
			 while (!tempQueue.isEmpty()) {

				 Patient * tempPatient=new Patient;
				  tempQueue.dequeue(tempPatient); // Dequeue from tempQueue
				 allReq.enqueue(tempPatient);
			 }
		}

	}

}

//output file function 
bool Organizer::Writefile(LinkedQueue<Patient*>& p) {
	string Oname = "Output_" +filename;
	ofstream outputF(Oname);
	LinkedQueue<Patient*> temp1 = p;
	Patient* P=new Patient;
	if (!outputF) return false;

	outputF << "FT" << " " << "PID" << " " << "QT" << " " << "WT";
	while (!temp1.isEmpty())
		temp1.dequeue(P);
	for (int i = 0; i < FinishedPat; i++) {
		outputF << P->getFinishTime() << " " << P->getID() << " " << P->getRequestTime() << " " << P->getWaitTime();
	}

	outputF << "patients: " << Reqno << "[NP: " << TotalNpNo << ", " << "SP: " << TotalSpNo << ", " << "EP: " << TotalEPNo << "]";
	outputF << "hospitals: " << Hospitalnumber;
	outputF << "cars: " << Totalcars << "[Scars: " << noScar << ", " << "Ncars: " << noNcar << "]";
	outputF << "Avg wait time = "<<avgWaitTime(p, FinishedPat); 
	outputF << "Avg busy time = "; //PUT THESE HERE
	outputF << "Avg utilization = ";
	return true;
}



//interactive mode
void Organizer::InteractiveMode(int timestep, Hospital& currentHospital, int HoN) {
	UI ui;
	ui.display_same_line("Current Timestep:");
	ui.display(timestep);
	ui.display_same_line("================  HOSPITAL #");
	ui.display_same_line(HoN + 1);
	ui.display("data  =================");

	ui.display_same_line("NP Requests: ");
	ui.printPatient(currentHospital.getNPQueue(), timestep);
	ui.display(" "); //to leave a line between patients

	ui.display_same_line("SP Requests: ");
	ui.printPatient(currentHospital.getSPQueue(), timestep);
	ui.display(" ");

	ui.display_same_line("EP Requests: ");

	ui.printPriPatient(currentHospital.getEPQueue(), timestep);
	ui.display(" ");

	//printing scars and ncars
	ui.display_same_line("Free Cars: ");
	ui.display_same_line(currentHospital.getnoScar());
	ui.display_same_line("Scars, ");
	ui.display_same_line(currentHospital.getnoNcar());
	ui.display("Ncars");

	ui.display_same_line("================  HOSPITAL #");
	ui.display_same_line(HoN + 1);
	ui.display("data  end =================");
	ui.display("-----------------------------------------");
	//PUT OUTCAR NO
	ui.display_same_line("==> ");
	ui.display_same_line("Out Cars: ");
	//PRINT OUTCAR LIST 
	//PRINT BACKCAR NO
	ui.display_same_line("<== ");
	ui.display_same_line("Back Cars: ");
	//PRINT BACKCAR LIST 
	//PUT CHECKUP CAR NO
	ui.display_same_line("=== ");
	ui.display_same_line("Cars in Check up: ");
	//PRINT CHECK UP LIST

	ui.display("-----------------------------------------");
	ui.display_same_line("Finished patients: ");
	ui.printPatient(finished, timestep);
	ui.display(" ");
}

//generating a random number between zero and limit
int Organizer::getRandomNum(int limit) {
	if (limit <= 0) return 0;
	return rand() % (limit+1);
}


//timestep handling
void Organizer::HandleTimeStep(int timestep) {
	UI ui;
	for (int i = 0; i < Hospitalnumber; i++) {
		Hospital& currentHospital = hospital[i];
		currentHospital.AssignEp(timestep);
		currentHospital.AssignNPtoNc(timestep);
		currentHospital.AssignSPtoSC(timestep);
		FreetoOut(timestep, currentHospital);
		OuttoBack(timestep);
		//handle cancellation + check up here

	
		BacktoFree(timestep, currentHospital);
		if (ui.getmode() == 1) InteractiveMode(timestep, currentHospital, i);

	}
	int x = getRandomNum(100);
	if (x <= FailProb) {
		//choose random car to fail from out list
		int count = outCars.count(outCars);
		int random = getRandomNum(count);
		priQueue<Car*> temp;
		Car* c = nullptr;
		int pri = 0;
		for (int i = 0; i < random; i++) {
			outCars.dequeue(c, pri);
			temp.enqueue(c, pri);
		}
		outCars.dequeue(c, pri);
		//CALL FAILURE ACTION HERE WITH CAR c AND PRIORITY pri
		while (!temp.isEmpty()) {
			temp.dequeue(c, pri);
			outCars.enqueue(c, pri);
		}

	}
}
Car* Organizer::pickRandCar(priQueue<Car*>& carlist) {
	int count = carlist.count(carlist);
	int random = getRandomNum(count);

	priQueue<Car*> temp;
	Car* c = nullptr;
	int pri = 0;
	for (int i = 0; i < random; i++) {
		carlist.dequeue(c, pri);
		temp.enqueue(c, pri);
	}
	carlist.dequeue(c, pri);
	while (!temp.isEmpty()) {
		temp.dequeue(c, pri);
		carlist.enqueue(c, pri);
	}
	return c;
}


/*
//populating patient lists in hospitals if their timestep is reached
void Organizer::populateHospitals(int timestep) {
	Patient* p = nullptr;
	LinkedQueue<Patient*> temp;
	int c = 0;
	while (!allReq.isEmpty()) {
		allReq.peek(p);
		if (p->getRequestTime() <= timestep) {
			allReq.dequeue(p);
			temp.enqueue(p);
			c++;
		}
		else {
			break;
		}
	}
	for (int i = 0; i < c; i++) {
		temp.dequeue(p);
		for (int i; i < Hospitalnumber; i++) {
			int x = 
			if(p->getNearestHospital() == hospital[])
		}
	}
	
	
}


*/

/*
void Organizer::populateHospitals(int timestep) {
	LinkedQueue<Patient*> temp = allReq;
	Patient* p = nullptr;
	temp.peek(p);
	while (!temp.isEmpty()) {
		if (p->getRequestTime() <= timestep && (p->getNearestHospital() == h.getID())) {
			temp.dequeue(p);

										
		}

	}


}
*/

//main sim function
void Organizer::mainSimulation() {
	UI ui;
	bool complete = false;
	int timestep = 0;
	Loadfile(filename);
	while (!complete) {
		timestep++;
		HandleTimeStep(timestep);
		complete = (Reqno == (FinishedPat + CancelReq));
	}
	if (ui.getmode() == 2) SilentMode();
	else Writefile(finished);
	return;
}

void Organizer::SilentMode() {
	UI ui;
	ui.display("Silent Mode, Simulation Starts...");
	if (Writefile(finished)) ui.display("Simulation ends, Output file created! ");
	else ui.display("Simulation ends, failed to create Output file ");
}

void Organizer::FreetoOut(int timestep, Hospital& current) {
	LinkedQueue<Car*> temp;
	temp = current.getACQueue();
	while (!temp.isEmpty()) {
		Car* c = new Car;
		temp.dequeue(c);
		Patient* p = c->getPatient();
		int x = p->getPickupTime();
		outCars.enqueue(c, -1*x);

	}

}

void Organizer::OuttoBack(int timestep)
{
	//three cases: 
	Car* c = nullptr;
	int pri = 0;
	while (!outCars.isEmpty()) {
		outCars.peek(c, pri);
		if (-1 * pri <= timestep) {
			outCars.dequeue(c, pri);
			Patient* p = c->getPatient();
			p->setpicked(true);
			int ft = p->getFinishTime();
			c->setStatus("Loaded");
			backCars.enqueue(c, ( - 1 * ft));
		}
		else { break; }
	}

}

// car 1 -> -3, car2 -> -5 
//handle hospital and car list using hospital id in car
//when is move performed? when car reaches hospital, ya3ny el pri * -1 equal to or less than current time step. haye3mel eh ba3deha?
//haycheck eno de el hospital beta3to, w ye3mel get lel type, w 3al a7asab eltype ye3mel enqueue fel list
// set patient be nullptr
//set lel busy time
//set status of car -> Ready
//store cars that should be sent to free BUT NOT FREE OF THIS CURRENT HOSPITAL in temp queue, then at end of while enqueue again in back
//should take list (i can apply it to check up list too) ???
void Organizer::BacktoFree(int timestep, Hospital& current) {
	Car* c = new Car;
	int pri= 0;

	backCars.peek(c, pri);
	while (pri*-1 <= timestep) {
		backCars.dequeue(c, pri);
		c->getHospID();
	}
		

	
}

Organizer::~Organizer() {
	delete[] hospital; 
}