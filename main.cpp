#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

class Transport {
public:
	virtual void print(ostream &output)  = 0 ;
	int speed; // скорость
	int distance; // расстояние 
};

class Airplane : public Transport{
public:
	Airplane(){ 	
		cout<<"Airplane"<<endl;
		range=0;
		capacity=0;
	}
	void print(ostream &output) {
		output<<"airplane"<< " " << speed<< " " << distance << " " << range << " " << capacity<< endl;
	}
public:
	int range; // дистанция дальность
	int capacity; // грузоподьемность 
};

class Train : public Transport {
public :
	Train() {
		cout<<"Train"<<endl;
		countCar=0;
	}
	void print(ostream &output) {
		output << "train "<< speed << " " << distance << " " << countCar <<endl;
	}
	int countCar; // количество вагонов
};

class Ship : public Transport{
public:
	Ship() {
	cout<<"Ship"<<endl;
		displacement = 0;
	}
	void print(ostream &output) {
		output << "ship "<< speed << " " << distance << " " << displacement << endl;
	} 
	int displacement; // водоизмещение
	enum ship_type { lainer, tow, tanker, empty };
};

int main (int argc, char *argv[])
{
	cout << "Start. Read from file input.txt...." << endl;
	ifstream infile("input.txt", ios::out | ios::app | ios::binary);
	// Сначала считываем из файл самолеты в первой строке, потом поезда а после корабли.
	// сначала идет количество N данных типов, после их характеристики заданое количесво N раз
	int n;
	infile>>n;
	cout<<n<<endl;
	vector<Transport*> vec;
	string name;
	for ( int i=0;i<n;i++) {
			infile >> name;
			cout<<"name: " << name<<endl;
			if (name == "airplane" ) {
				Airplane* air = new Airplane();
				infile >> air->speed >> air->distance>>air->range >> air->capacity;
				cout<< air->speed <<" " << air->distance << " " << air->range <<  " "<< air->capacity<<" "<< static_cast<void*>(air) << endl;
				vec.push_back(air);
			} 
			else if (name == "train") {
				Train* train = new Train();
				infile >> train->speed >> train->distance >> train->countCar;
				cout<< train->speed << " " << train->distance <<  " " << train->countCar << " "<<static_cast<void*>(train) << endl;
				vec.push_back(train);
			}
			else if (name == "ship") {
				Ship* ship = new Ship();
				infile >> ship->speed >> ship->distance >> ship->displacement;
				cout<< ship->speed << " " << ship->distance << " " << ship->displacement<< " "<< static_cast<void*>(ship)<<endl;
				vec.push_back(ship);
			}
			
	}
	cout<<endl<<"Data before start sort"<<endl;
	for (int i=0;i<vec.size(); i++) {
		vec[i]->print(cout);
	}

	cout<<endl<<"Sorting...."<<endl<<endl;
	
	/*
	Сортировка пузырьком
	*/
	for (int i=0;i<n;i++) {
		for ( int j=n-1;j>i;j--) {
			if(vec[j]->speed < vec[j-1]->speed) {
				swap(vec[j], vec[j-1]);
			}
		}
	}
	
	cout<<"Data after sort"<<endl;
	ofstream outfile("output.txt",ios::out | ios::app | ios::binary);
	for (int i=0;i<vec.size(); i++) {
		cout<< vec[i]->speed << " " ; // print on screen
		vec[i]->print(outfile);      // print on file 
	}
	vec.clear();

	return 0;
}

