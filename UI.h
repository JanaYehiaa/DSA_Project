#pragma once
#include<iostream>
#include <string>
#include "Car.h"
#include"Patient.h"
#include"PriQueue.h"
using namespace std;
template <typename T>
class LinkedQueue;
template <typename T>
class priQueue;
class UI
{
	int mode;
public:
	UI();
	//~UI();
	int readmode();
	int getmode() const;
	void printPatient(LinkedQueue<Patient> &p, int T);
	string getFilename() const;
	void waitForEnter();
	void printPriPatient(priQueue<Patient> &p, int T);
	template<typename T>
	void display_same_line(T x)
	{
		cout << x << " ";
	}
	template<typename T>
	void display(T x) {
		cout << x << endl;
	}

};
	