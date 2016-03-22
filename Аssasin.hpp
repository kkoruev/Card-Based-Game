#ifndef _ASSASIN_HPP_
#define _ASSASIN_HPP_

#include "Card.hpp"



class Assasin : public Card{
public:
	Assasin(int attack,int health,char namer[]);
	~Assasin();
	virtual void print_card();
	virtual Card* clone() const;
	virtual const char* get_type() const;
};

#endif // !_ASSASIN_HPP_
