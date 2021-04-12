#include <iostream>
#include <fstream>
#include <string> 
#include <vector>

struct Adress{
	std::string street;
	std::string zip;
	std::string city;
};
struct person{
	std::string name;
	std::string id;
	Adress adress;
};

std::istream& operator>>(std::istream &in, person &person) {
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

std::vector<person> read_file(std::string filename){
	person dummy;
	std::vector<person> list;
	std::ifstream input(filename);
	if (input.is_open()){
		while (input >> dummy){
			list.push_back(dummy);
		}
	}
	else{
		std::cout << "Something is wrong with your file bro" << std::endl;
	}
	return list;
}

int main (){
	std::cout << "Hello man";
}
