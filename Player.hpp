#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Deck.hpp"
#include "Card.hpp"

class Player{
	Deck d1;
	int energy;
	int life;
	int last_card;
public:
	Player();
	bool make_move();
	void set_deck(Deck &d1);
	void decrease_last();
	Card* take_last_card();
	int get_last() const;
	void decrease_life(int idx);
	int get_life() const;
	int get_energy() const;
	bool player_save(char* name);
};


#endif // !_PLAYER_HPP_
