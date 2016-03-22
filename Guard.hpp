#ifndef _GUARD_HPP_
#define _GUARD_HPP_

#include "Card.hpp"

const int number = 20;

class Guard : public Card {
public:
	Guard(int attack,int health,char name[]);
	~Guard();
	virtual void print_card();
	virtual Card* clone() const ;
	virtual const char* get_type() const;
};
#endif // !_GUARD_HPP_
