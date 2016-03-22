#include "Аssasin.hpp"


Assasin::Assasin(int attack,int health,char namer[])
	:Card(attack,health,namer,"Assasin")
{}


Assasin::~Assasin(){

}


void Assasin :: print_card(){
	cout << "Type: " << " ASSASIN " <<endl;
	cout<<"Name : "<<this->name<<endl;
	cout<<"Attack points : "<<this->attack<<endl;
	cout<<"Health points : "<<this->health<<endl;
	cout<<"Needed energy : " <<this->needed_energy<<endl;
	cout<<endl;
}

Card* Assasin :: clone() const {
	return new Assasin(*this);
}

const char* Assasin :: get_type() const{
	return "Assasin";
}