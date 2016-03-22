#include "Card.hpp"
#include <iostream>
#include <cstring>

using std::cout;
using std::endl;
using std::cin;

Card::Card(int attack,int health,char name[],const char type[]){
	if(strlen(name)>98){
		char string[98];
		for(int i=0;i<96;i++){
			string[i]=name[i];
		}
		string[96]='\0';
		strcpy(this->name,string);
	}
	else{
		strcpy(this->name,name);
	}
	this->attack=attack;
	this->health=health;
	this->needed_energy=(health/100)+(attack/20);
	this->max_health=this->health;
	this->min_health=0;

}

Card::~Card(){
	
}

Card::Card(const Card& c){
	strcpy(this->name,c.name);
	this->attack=c.attack;
	this->health=c.health;
	this->needed_energy=c.needed_energy;
	this->max_health=c.get_max_health();
	this->min_health=c.get_min_health();
}

int Card::attack_card(const Card& c){
	if(this->attack>c.health){
		return 2;
	}
	else if(this->attack==c.health){
		return 3;
	}
	else{
		return 4;
	}
}

int Card::get_attack() const{
	return attack;
}

int Card::get_health() const{
	return health;
}

double Card::get_needed_energy() const{
	return needed_energy;
}

const char* Card::get_name()const{
	return name;
}

void Card::set_attack(int attack){
	this->attack=attack;
}
void Card::set_health(int health){
	this->health=health;
}


void Card::set_name(char* name){
	if(strlen(name)<99){
		strcpy(this->name,name);
	}
	else{
		strcpy(this->name,"invalid name");
	}
}

void Card::set_needed_energy(int attack,int health){
	this->needed_energy=(health/100)+(attack/20);
}


/// Operator == for class Card.Returns false if cards are different.
bool Card::operator==(Card const &c){

	return (!strcmp(this->name,c.name) && this->attack == c.attack && this->health == c.health);
}

/// Operator = for class Card
Card& Card::operator=(Card const &c){
	strcpy(this->name,c.name);
	this->attack=c.attack;
	this->health=c.health;
	this->needed_energy=c.needed_energy;
	this->max_health=c.get_max_health();
	this->min_health;
	return *this;
}

/// Operator != for class Cards.Returns false if the cards are exactly the same
bool Card::operator!=(Card const &c)
{
	return !(*this == c);
}

/// Operator for output
ostream& operator<<(ostream &out,const Card &c){
	out<<c.get_name()<<endl;
	out<<c.get_attack()<<endl;
	out<<c.get_health()<<endl;
	out<<c.get_needed_energy()<<endl;
	return out;
}

/// Operator for input
istream& operator>>(istream& in,Card &c){
	char name[100];
	int attack;
	int health;
	int need_needed;
	cout<<"Attack: ";
	in>>attack;
	if(!in){
		cout<<"Error"<<endl;
		return in;
	}
	cout<<"Health: ";
	in>>health;
	if(!in){
		cout<<"Error"<<endl;
		return in;
	}
	in.ignore();
	cout<<"Name: ";
	in.getline(name,98);
	if(!in){
		cout<<"Error"<<endl;
		return in;
	}
	c.set_attack(attack);
	c.set_health(health);
	c.set_needed_energy(attack,health);
	c.set_name(name);
	return in;
}

//// Adds points to attack 
Card& Card::operator+=(int a){
	this->health += a;
	if (this->health > this->max_health)
		this->health = this->max_health;
	if(this->health < 0)
		this->health = 0;
	return *this;

}

/// Decrease attack
Card& Card::operator-=(int a){
	return (*this += -a);
}

/// Get function
int Card::get_max_health() const{
	return max_health;
}

/// Get function
int Card::get_min_health() const{
	return min_health;
}

