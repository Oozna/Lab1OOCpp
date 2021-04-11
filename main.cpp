#include <iostream>
#include <fstream>
#include <string> 

struct Adress{
	std::string street;
	std::string zip;
	std::string city;
};
struct Person{
	std::string name;
	std::string id;
	Adress adress;
};

std::istream& operator>>(std::istream &in, Person &person) {
	std::string temp; //to fix spaces
	std::getline(in, person.name);
	std::getline(in, person.id);
	std::getline(in, person.adress.street, ',');
	std::getline(in, temp, ' '); // removes space before the zip
	std::getline(in, person.adress.zip, ' '); //first part of zip
	std::getline(in, temp, ' ');//second part of zip
	person.adress.zip = (person.adress.zip + " " + temp);//concatonate the zip
	std::getline(in, temp, ' ');//removes space
	std::getline(in, person.adress.city);
	return in;
}
int main (){

}
