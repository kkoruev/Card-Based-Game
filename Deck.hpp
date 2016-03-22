#ifndef DECK_HPP__
#define DECK_HPP__

#include "Card.hpp"

using std::ostream;

class Deck{
private:
	/// Array of cards
	Card** deck;
	/// Size of deck
	size_t allocated_size;
	/// Count of cards
	size_t length;
	/// Resize function
	void reallocate(size_t new_size);
	/// Help function used for comparing positions
	bool is_index_used(int* arr,int pos, int index);
public:
	int sum_from_attack_and_health() const;
public:
	Deck();
	Deck(const Deck& c);
	~Deck();
public:
	void free();
	void add(const Card &card);
public:
	size_t get_allocated_size() const;
	size_t get_length() const;
	Card* get_at_position(size_t index) const;
public:
	void print() const;
	bool is_valid();
	bool save(char* path_name);
	void load(char* path_name);
	void add_new_card(char* path_name);
	void remove_card(char* path_name,char* name_of_card);
	void change_card(char* path_name,char* name_of_card);
	void top_five(char* name_of_text_file,char* principle);
public:
	Deck& operator=(Deck const &d);
	bool operator==(const Deck &d) const;
	Card* operator[](int idx);
	const Card* operator[]( int idx) const;
	bool operator!=(const Deck &d);
	bool operator>(const Deck &d);
	bool operator<(const Deck &d);
	bool operator<=(const Deck &d);
	bool operator>=(const Deck &d);
	Deck& operator+=(const Card &c);
	Deck& operator+=(const Deck &d);
	Deck& operator-=(const Card &c);
	operator int();
	operator bool();
	Deck& operator-(const Card &c);
};

ostream& operator<<(ostream& out,const Deck &d);
Deck operator+( Card &c, Deck &d);
Deck operator+(Deck &d,  Card &c);	
Deck operator+(Deck &d1, Deck &d2);


#endif
