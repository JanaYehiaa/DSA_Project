#include "Organizer.h"




Organizer::Organizer() {
	Simulation();
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
				moveSCartoOut(currentHospital);
			}
			else if (randomNum >= 70 && randomNum < 75) {
				moveNCartoOut(currentHospital);
			}
			else if (randomNum >= 80 && randomNum < 90) {
				moveCarOuttoBack(outCars);
			}
			else if (randomNum >= 91 && randomNum < 95) {
				moveCarBacktoFree(backCars);
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
void Organizer:: AssignNPToNC(Patient P, Hospital& h){
	if (h.getnoNcar() != 0)
	{
		Car car1;
		/*LinkedQueue<Patient> np = h.getNPQueue();
		priQueue<Patient> ep = h.getEPQueue();
		if (ep.isEmpty()==true)*/
		LinkedQueue<Car>& c = h.getNCQueue();
		c.dequeue(car1);
		car1.setPatient(P);// this function takes a patient to assign to normal car; check for emergency first and type of patient to be done outside function
	}
}
void Organizer::AssignEPToEC(Patient EP, Hospital& h) {
	Car car1;
	if (h.getnoNcar() != 0)
	{
		LinkedQueue<Car>& c = h.getNCQueue();
		c.dequeue(car1);
		car1.setPatient(EP);
	}
	else if (h.getnoScar() != 0) {
		LinkedQueue<Car>& c = h.getSCQueue();
		c.dequeue(car1); 
		car1.setPatient(EP);  
	}
	else
	{
		for (int i = 0; i < Hospitalnumber; i++)
		{
			Hospital& currentHospital = hospital[i]; 
			//if(currentHospital==EP.getNearestHospital()), howa el nearest int da bey3abar 3n eh?
			if (currentHospital.getnoNcar() != 0)
			{
				LinkedQueue<Car>& c = h.getNCQueue();
				c.dequeue(car1);//should I check if the car has a patient or should I just move the car to out car?? y3ni hal di function tania el howa el requirment el ba3do
				car1.setPatient(EP); 
				break;//es2ali 7ad; mmken while loop
			}

		}
	}
}
void Organizer::AssignSPToSC(Patient SP, Hospital& h){
	if (h.getnoScar()!=0)
	{
		Car car1;
		LinkedQueue<Car>& c = h.getSCQueue();
		c.dequeue(car1);
		car1.setPatient(SP);
	}
}


void Organizer::moveNPReqToFinish(LinkedQueue<Patient>& list, Hospital& h) {
	while (!list.isEmpty()) {
		Patient p;
		list.dequeue(p);
		h.setnoNP((h.getnoNP()-1));
		finished.enqueue(p);
		FinishedPat++;
		
	
	}
}

void Organizer::moveEPReqToFinish(priQueue<Patient>& list, Hospital& h) {
	int s = 0;
	while (!list.isEmpty()) {
		Patient p;
		list.dequeue(p, s);
		h.setnoEP((h.getnoEP() - 1));
		finished.enqueue(p);
		FinishedPat++;
	
	}
}


void Organizer::moveSPReqToFinish(LinkedQueue<Patient>& list, Hospital& h) {
	while (!list.isEmpty()) {
		Patient p;
		list.dequeue(p);
		h.setnoSP((h.getnoSP() - 1));
		finished.enqueue(p);
		FinishedPat++;
	

	}
}

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


void Organizer::Loadfile(const string& filename) {
	fstream file(filename);
	if (!file)
	{
		cout << "Failed to open file!";  //checks if file opens safely
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
			Patient p1(type,QT,PID,HID,DST,SVR);
			allReq.enqueue(p1);
			hospital[HID - 1].enqueueEp(p1, SVR);
			int a = hospital[HID - 1].getnoEP();
			hospital[HID - 1].setnoEP(a + 1);

			
		}
		else if (type == "NP") {
			file >> QT >> PID >> HID >> DST;
			Patient p1(type, QT, PID, HID, DST);
			allReq.enqueue(p1);
			hospital[HID - 1].enqueueNp(p1);
			int a = hospital[HID - 1].getnoNP();
			hospital[HID - 1].setnoNP(a + 1);
		}
		else if (type == "SP"){
			file >> QT >> PID >> HID >> DST;
			Patient p1(type, QT, PID, HID, DST);
			allReq.enqueue(p1);
			hospital[HID - 1].enqueueSp(p1);
			int a = hospital[HID - 1].getnoSP();
			hospital[HID - 1].setnoSP(a + 1);
		}
	}
	


	//handling cancellation
	int nbofcancellation = 0;
	file >> nbofcancellation;
	for (int i = 0; i < nbofcancellation; i++) {
		file >> CT >> PID >> HID;
		
		LinkedQueue <Patient> tempQueue;  // temporary queue for traversal
		bool found = false;
		while (!allReq.isEmpty())
		{
			Patient p;
			 allReq.dequeue(p);
			 if (p.getID() == PID)
			 {
				 found = true;
				 if (!p.getpicked())
				 {
					 cancel.enqueue(p);
				 }
				 else
				 {
					 tempQueue.enqueue(p);
				 }
			 }
			 
			 while (!tempQueue.isEmpty()) {

				 Patient tempPatient;
				  tempQueue.dequeue(tempPatient); // Dequeue from tempQueue
				 allReq.enqueue(tempPatient);
			 }
		}

	}

}

//load file function 
void Organizer::Writefile() {
	string Oname = "Output_" +filename;
	ofstream outputF;
	outputF.open(Oname);
	outputF << "FT" << " " << "PID" << " " << "QT" << " " << "WT";
//PUT LOOP HERE


	outputF << "patients: " << Reqno << "[NP: " << TotalNpNo << ", " << "SP: " << TotalSpNo << ", " << "EP: " << TotalEPNo << "]";
	outputF << "hospitals: " << Hospitalnumber;
	outputF << "cars: " << Totalcars << "[Scars: " << noScar << ", " << "Ncars: " << noNcar << "]";
	outputF << "Avg wait time = "; //PUT THESE HERE
	outputF << "Avg busy time = ";
	outputF << "Avg utilization = ";

}


Organizer::~Organizer() {
	delete[] hospital; 
}