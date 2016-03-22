#include "Deck.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include "BattleField.hpp"
#include <ctime>
#include "Guard.hpp"
#include "Player.hpp"
#include "Аssasin.hpp"


using std::cout;
using std::endl;
using std::cin;
using std::nothrow;
using std::ofstream;
using std::ifstream;
using std::ios;


Deck set_deck(int arr[], Deck &d1){
	Deck new_deck;
	for(int i=0;i<5;i++){
		new_deck.add((*d1[arr[i]]));
	}
	return new_deck;
}

int main(){

	Deck d;
	d.add(Guard(12,12,"SS"));
	d.add(Guard(12,12,"SS"));
	d.add(Guard(12,12,"SS"));
	d.add(Guard(12,12,"SS"));
	d.add(Assasin(15,18,"ss"));
	Player p1;
	Guard g(12,12,"SSD");
	p1.set_deck(d);
	Player p2;
	p2.set_deck(d);
	BattleField battle(p1,p2);
	bool flag = battle.save("Kris");
	if(flag==false){
		cout<<"Error" <<endl;
	}
	int  x = battle.battle_menu();
	if(x==1){
		cout<<"Winner - PLAYER 1" <<endl;
	}
	else{
		cout<<"Winner - PLAYER 2" <<endl;
	}
}