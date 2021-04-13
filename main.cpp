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

size_t find_in_names(std::vector<person> haystack, std::string name_part){ //returns the amount of people that have the name_part of their name in haystack
	size_t total = 0;
	size_t found;
	for (auto &c : name_part){
		if (c <= 'Z' && c >= 'A')
			c = c - ('Z' - 'z');
	}
	for (auto a : haystack){
		for (auto &c : a.name){
			if (c <= 'Z' && c >= 'A')
				c = c - ('Z' - 'z');
		}
		found = a.name.find(name_part);
		if (found != std::string::npos){
			total++;
		}
	}
	return total;
}

std::vector<person> find_person_from_city(std::vector<person> haystack, std::string city){
	std::vector<person> result;
	size_t found;
	for (auto &c : city) {
		if ((c <= 'z') and (c >= 'a')) c = toupper(c);
	}	

	for (auto a : haystack){
		found = a.adress.city.find(city);
		if (found != std::string::npos){
			result.push_back(a);
		}
	}
	return result;
}


int main (){
	std::vector<person>contacts;
	contacts = read_file("names.txt");
	bool check = true;
	int answer;

	while (check){
		std::cout << "Welcome to the contact book motherfucker! Here are your options" << std::endl << "1. Search by name" << std::endl << "2. Search by city" << std::endl << "3. Exit the program" << std::endl;
		std::cin >> answer;
		switch(answer){
			case 1:{
				std::cout << "Write full name or part of name" << std::endl;
				size_t numberOfPeople;
				std::string searchName;
				std::cin >> searchName;
				numberOfPeople = find_in_names(contacts, searchName);
				std::cout << "Your search resulted in " << numberOfPeople << " matches" << std::endl << std::endl;

				break;
			}
			case 2:{
			    std::cout << "Write full name of city" << std::endl;
			    std::string searchCity;
			    std::vector<person> inCity;
			    std::getline(std::cin, searchCity);
			    std::getline(std::cin, searchCity);
			    inCity = find_person_from_city(contacts, searchCity);

				for (const auto &a : inCity){
					std::cout << a.id << ", " << a.name << ", " << a.adress.city << std::endl;
				}
				break;
			}
			case 3:{
			    std::cout << "Alright have a good day/night" << std::endl;
				check = false;	
			}
		}
	}
}
