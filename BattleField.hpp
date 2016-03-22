#ifndef  _BATTLEFIELD_HPP_
#define  _BATTLEFIELD_HPP_

#include "Card.hpp"
#include "Deck.hpp"
#include "Player.hpp"


class BattleField{
private:

	// data for field(player1,player2)
	Player p1;
	Deck field_1;
	Player p2;
	Deck field_2;
public:
	void place_card1(const Card &c,int x);
	void remove_card(const Card &c);
private:
	Deck graveyard;
	void send_to_grave(const Card &c);
	Card* get_at_position_player_1(int idx);
	bool attack(int who,int card_n,int m_card);
	void help_attack1();
	void help_attack2();
	void clean_func2();
	void clean_func1();
public:
	void stats_screen();
public:
	void graveyard_print();
public:
	BattleField(Player &p1,Player &p2);
	~BattleField();
public:
	void attack(int number_of_card,int your_card,Deck field);
public:
	void print_battle_field() const;

public:
	void serialize(int number);
public:
	int battle_menu();
	
private:
	int battle();
	void help_menu();
public:
	bool save(char* name);
};


#endif // ! _BATTLEFIELD_HPP_
