#ifndef CARD_HPP__
#define CARD_HPP__

#include <iostream>
#include <fstream>

class Skill;

using std::ostream;
using std::endl;
using std::istream;
using std::cout;

const int MAX_SIZE=100;
const int MAX_SKILLS=3; 
const int MAX_S=20;

class Card{
protected:
	int attack;
	int health;
	double needed_energy;
	char name[MAX_SIZE];
protected:
	int max_health;
	int min_health;
public:
	virtual ~Card();
	Card& operator=(Card const &c);
	Card(const Card& c);
	Card(int attack,int health,char name[],const char type[]);
public:
	virtual void print_card()=0;
	virtual int attack_card(const Card& c);
	virtual Card* clone() const = 0;
	virtual const char* get_type() const = 0;
public:
	int get_attack() const;
	int get_health() const;
	double get_needed_energy() const;
	const char* get_name() const;
	int get_max_health() const;
	int get_min_health() const;
public:
	void set_attack(int attack);
	void set_health(int health);
	void set_name(char* name);
	void set_needed_energy(int attack,int health);
public:
	bool operator==(Card const &c);
	bool operator!=(Card const &c);
	Card& operator+=(int a);
	Card& operator-=(int a);
};

ostream& operator<<(ostream &out,const Card &c);
istream& operator>>(istream& in,Card &c);


#endif