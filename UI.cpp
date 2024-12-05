#include "UI.h"
#include "LinkedQueue.h"
#include "priQueue.h"

UI::UI():mode(-1) { }
string UI::getFilename(){
	cout << "Please Enter Filename to be Loaded!";
	string a;
	cin >> a;
	return a;
}

int UI::getmode() const {
	return mode;
}
void UI::waitForEnter() {
	cout << "Press Enter to display next hospital! " << endl;
	cin.get();
}


int UI::readmode()
{
	cout << "1. Interactive Mode" << endl << "2. Silent Mode" << endl << "Please choose a mode: ";
	cin >> mode;

	while (mode != 1 && mode != 2)
	{
		cout << "Invalid Entry!!" << endl << "1. Interactive Mode" << "2. Silent Mode" << endl << "Please choose a mode: " << endl;
		cin >> mode;

	}
	return mode;

}

void UI::printPatient(LinkedQueue<Patient> &p, int T)
{
	int c = 0;
	LinkedQueue<Patient> temp1 = p;
	LinkedQueue<Patient> temp2;
	//if timestep of patient arrives, put that patient in temp Queue
	while (!temp1.isEmpty()) {
		Patient a;
		temp1.dequeue(a);
		if (a.getRequestTime() <= T) {
			c++;
			temp2.enqueue(a);
		}
	}
	cout << "Total Number: " << c<<" ";
	cout << "Patient's IDs: ";
	while (!temp2.isEmpty()) {
		Patient b;
		temp2.dequeue(b);
		cout << b;
	}
}

void UI::printPriPatient(priQueue<Patient> &p, int T)
{
	int c = 0;
	priQueue<Patient> temp1 = p;
	priQueue<Patient> temp2;
	int x = 0;
	//if timestep of patient arrives, put that patient in temp Queue
	while (!temp1.isEmpty()) {
		Patient a;
		temp1.dequeue(a, x);
		if (a.getRequestTime() <= T) {
			c++;
			temp2.enqueue(a,x);
		}

	}
	cout << "Total Number: " << c << " ";
	cout << "Patient's IDs: ";
	while (!temp2.isEmpty()) {
		Patient b;
		temp2.dequeue(b, x);
		cout << b;
	}
	//delete temp2;
}