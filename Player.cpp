#include "Player.hpp"
#include <fstream>


using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

Player::Player(){
	this->energy = 1;
	this->life = 30;
}	



bool Player :: make_move(){
	if(energy<30){
		energy++;
	}
	cout<<"You draw this card " <<endl;
	d1[last_card]->print_card();
	char end;
	cout<<"Enter 'y' to continue your move "<<endl;
	cin.clear();
	cin.sync();
	cin>>end;
	if( d1[last_card]->get_needed_energy() > energy ){
		char n;
		cout<<"You can not use this card now" <<endl
			<<"Press '1' : Discard and earn one energy "<<endl
			<<"Press '2' : Keep it and try next time "  <<endl;
		do{
			cin>>n;
			if(!cin){
				cin.clear();
				cin.sync();
			}
		}
		while(n!=2 && n!=1);
		if(n==1){
			last_card--;
			if(energy<30){
				energy++;
			}
		}
		else{

		}
		return false;
	}
	else{
		cout<<"You must play your card " <<endl;
		char end;
		cout<<"Enter 'y' to place your card"<<endl;
		cin>>end;
		last_card--;
		return true;
	}
}

void Player::set_deck(Deck &d1){
	this->d1 = d1;
	this->last_card = d1.get_length() - 1;
}

void Player::decrease_last(){
	last_card--;
}

int Player::get_last() const{
	return last_card;
}

Card* Player::take_last_card(){
	return d1[last_card];
	last_card--;
}

void Player :: decrease_life(int idx){
	life = life - idx;
}

int Player :: get_life() const{
	return life;
}

int Player::get_energy() const{
	return energy;
}

bool Player :: player_save(char* name){
	ofstream file(name,std::ios::binary | std::ios::app);
	if(!file){
		return false;
	}
	file.write((char*) &energy,sizeof(int));
	if(!file){
		return false;
	}
	file.write((char*) &life,sizeof(int));
	if(!file){
		return false;
	}
	file.write((char*) &last_card,sizeof(int));
	if(!file){
		return false;
	}
	file.close();
	file.clear();
	bool flag = d1.save(name);
	return flag;
}