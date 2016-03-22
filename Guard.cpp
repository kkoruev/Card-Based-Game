#include "Guard.hpp"
#include <cstring>

Guard::Guard(int attack,int health,char name[])
	:Card(attack,health,name,"Guard")
{}


void Guard::print_card(){
	cout << "Type: " << " GUARD " <<endl;
	cout<<"Name : "<<this->name<<endl;
	cout<<"Attack points : "<<this->attack<<endl;
	cout<<"Health points : "<<this->health<<endl;
	cout<<"Needed energy : " <<this->needed_energy<<endl;
	cout<<endl;
}

Guard::~Guard(){
}

 Card* Guard::clone() const {
	 return new Guard(*this);
 }

 const char* Guard:: get_type() const{
	 return "Guard";
 }