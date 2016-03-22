#include "Guard.hpp"
#include "Аssasin.hpp"
#include "BattleField.hpp"
#include <cstring>
#include <Windows.h>
#include <fstream>

using std::nothrow;
using std::cin;
using std::ofstream;
using std::ifstream;

BattleField :: BattleField(Player &p1,Player &p2){
	this->p1 = p1;
	this->p2 = p2;
}


void BattleField :: place_card1(const Card &c,int x){
	if(x==1){
		field_1.add(c);
	}
	else{
		field_2.add(c);
	}
}



void BattleField :: send_to_grave(const Card &c){
	graveyard.add(c);
}




void BattleField :: print_battle_field() const{
	cout<<"Player 1 : " ;
	for(int i=0;i<field_1.get_length();i++){
		cout<<field_1[i]->get_name()<<"     ";
	}
	cout<<endl<<endl;
	cout<<"Player 2 : ";
	for(int i=0;i<field_2.get_length();i++){
		cout<<field_2[i]->get_name()<<"     ";
	}
	cout<<endl;
}

void BattleField::graveyard_print(){
	for(int i=0;i<graveyard.get_length();i++){
		graveyard[i]->print_card();
		cout<<endl;
	}
}

void BattleField :: remove_card(const Card &c){
	field_2-=c;
}



Card* BattleField::get_at_position_player_1(int idx){
	return field_1[idx];
}


int BattleField :: battle_menu(){
	cout<<"If you play for first time or just want to see help menu press '1'.Press '2' if you do not want the help menu"<<endl;
	int x;
	do{
		cin.clear();
		cin.sync();
		cin>>x;
	}
	while(x!=2 && x!=1);
	if(x==1){
		help_menu();
	}
	cout<<"If you are ready press 3 "<<endl;
	do{
		cin.clear();
		cin.sync();
		cin>>x;
	}
	while(x!=3);
	int winner = battle();
	return winner;
}

int BattleField :: battle(){
	system("cls");
	char start;
	stats_screen();
	cout<<"Press 'y' to start " <<endl;
	cin>>start;
	int x = 1;
	bool no_winner = true;
	while(no_winner){
		system("cls");
		if(x==1){
			stats_screen();
			cout<<"PLAYER 1"<<endl;
			bool status = p1.make_move();
			if(status){
				place_card1(*p1.take_last_card(),1);
				help_attack1();
			}
			if(p2.get_life() <= 0 || p2.get_last()<=0){
				return 1;
			}
			system("cls");
			char end;
			stats_screen();
			cout<<"PLAYER 1 " <<endl;
			cout<<"Enter  'y' to end your turn " <<endl;
			cin>>end;
			x=2;
		}
		else{
			system("cls");
			stats_screen();
			cout<<"PLAYER 2"<<endl;
			bool status = p2.make_move();	
			if(status){
				place_card1(*p2.take_last_card(),2);
				help_attack2();
			}
			if(p1.get_life() <=0 || p2.get_last() <= 0){
				return 2;
			}
			system("cls");
			stats_screen();
			int z;
			cout<<"PLAYER 2 " <<endl;
			cout<<"Enter  'y' to end your turn " <<endl;
			cin>>z;
			x=1;
		}
	}
	
}

void BattleField :: help_attack1(){
	system("cls");
	stats_screen();
	cout<<endl;
	int x;
	int y;
	cout<<"PLAYER 1"<<endl;
	cout<<"You can attack now " <<endl;
	cout<<"Choose card or player to attack"<<endl;
	cout<<"Press '-1' to attack other player"<<endl;
	cout<<"Press  other number(from 0 to len of field) to attack card" <<endl;
	do{
		cin.clear();
		cin.sync();
		cin>>x;
	}
	while(!cin);
	cout<<"Now choose your card " <<endl;
	do{
		cin.clear();
		cin.sync();
		cin>>y;
	}
	while(!cin);
	bool statuss = attack(2,x,y);
	if(statuss){
		clean_func2();
	}
	else{
		cout<<"Wrong attack " <<endl;
		cout<<"Try next time " <<endl;
		Sleep(1000);
	}
}

void BattleField :: help_attack2(){
	system("cls");
	stats_screen();
	int x;
	int y;
	cout<<"You can attack now " <<endl;
	cout<<"Choose card or player to attack"<<endl;
	cout<<"Press '-1' to attack other player"<<endl;
	cout<<"Press  other number(from 0 to len of field) to attack card" <<endl;
	do{
		cin.clear();
		cin.sync();
		cin>>x;
	}
	while(!cin);
	cout<<"Now choose your card " <<endl;
	do{
		cin.clear();
		cin.sync();
		cin>>y;
	}
	while(!cin);
	bool statuss = attack(1,x,y);
	if(statuss){
		clean_func1(); 
		system("cls");
		stats_screen();
	}
	else{
		cout<<"Wrong attack " <<endl;
		cout<<"Try next time " <<endl;
		Sleep(1000);
	}
}


void BattleField :: clean_func1(){
	for(int i=0;i<field_1.get_length();i++){
		if(field_1[i]->get_health() <= 0){
			remove_card(*field_1[i]);
		}
	}
}

void BattleField::clean_func2(){
	for(int i=0;i<field_2.get_length();i++){
		if(field_2[i]->get_health() <= 0){
			remove_card(*field_2[i]);
		}
	}
}

void BattleField::help_menu(){
	cout<<"You will have 10 cards in deck.When you draw one you can discard it for energy."<<endl
		<<"You will need that energy to place another card."<<endl
		<<"IF you have energy you must place a card."<<endl
		<<"If there is a Guard you have to atack him"<<endl
		<<"When your life points or your card  end the game is over"<<endl;
	cout<<endl;

}


BattleField ::~BattleField(){

};


bool BattleField :: attack(int who,int card_n,int m_card){
	if(who == 2){
		if(card_n == -1){
			for(int i=0;i<field_2.get_length();i++){
				if(strcmp(field_2[i]->get_type(),"Guard") == 0){
					return false;
				}
			}
			if(field_1.get_length()<=m_card){
				return false;
			}
			p2.decrease_life(field_1[m_card]->get_attack());
			return true;
		}
		else{
			if(card_n>=field_2.get_length()){
				return false;
			}
			else if(m_card>=field_1.get_length()){
				return false;
			}
			else{
				if(strcmp(field_2[card_n]->get_type(),"Guard") == 0){
					int new_health = field_2[card_n]->get_health() - field_1[card_n]->get_attack();
					field_2[card_n]->set_health(new_health);
					return true;
				}
				else{
					for(int i=0;i>field_1.get_length();i++){
						if(strcmp(field_2[card_n]->get_type(),"Guard") == 0){
							return false;
						}
					}
					int new_health = field_2[card_n]->get_health() - field_1[card_n]->get_attack();
					field_2[card_n]->set_health(new_health);
					return true;
				}
			}

		}
	}
	else{
		if(card_n == -1){
			for(int i=0;i<field_1.get_length();i++){
				if(strcmp(field_1[i]->get_type(),"Guard") == 0){
					return false;
				}
			}
			if(field_2.get_length()<=m_card){
				return false;
			}
			p1.decrease_life(field_2[m_card]->get_attack());
			return true;
		}
		else{
			if(card_n>=field_1.get_length()){
				return false;
			}
			else if(m_card>=field_2.get_length()){
				return false;
			}
			else{
				if(strcmp(field_1[card_n]->get_type(),"Guard") == 0){
					int new_health = field_1[card_n]->get_health() - field_2[card_n]->get_attack();
					field_1[card_n]->set_health(new_health);
					return true;
				}
				else{
					for(int i=0;i>field_2.get_length();i++){
						if(strcmp(field_1[card_n]->get_type(),"Guard") == 0){
							return false;
						}
					}
					int new_health = field_1[card_n]->get_health() - field_2[card_n]->get_attack();
					field_1[card_n]->set_health(new_health);
					return true;
				}
			}

		}
	}

}


void BattleField :: stats_screen(){
	cout<<"Player 1              vs                   Player 2 " <<endl
		<<p1.get_life()<<"                                         "<<p2.get_life()<<endl
		<<p1.get_energy()<<"                                          "<<p2.get_energy()<<endl;
	print_battle_field();
}


bool BattleField :: save(char* name){
	bool flag1 = field_1.save(name);
	if(!flag1){
		return flag1;
	}
	bool flag2 = field_2.save(name);
	if(!flag2){
		return flag2;
	}
	bool flag3 = p1.player_save(name);
	if(!flag3){
		return flag3;
	}
	bool flag4 = p2.player_save(name);
	if(!flag4){
		return flag4;
	}
	return true;
}