#include "Deck.hpp"
#include <iostream>
#include <cstring>
#include <fstream>

using std::cout;
using std::endl;
using std::cin;
using std::nothrow;
using std::ofstream;
using std::ifstream;
using std::ios;


///Initialize class Deck
Deck::Deck(){
	deck=NULL;
	allocated_size=0;
	length=0;
}

/// Delete class Deck
Deck::~Deck(){
	free();
}

///Copy constructor
Deck::Deck(const Deck& c){
	deck=new(nothrow) Card*[c.allocated_size];
	for(int i=0;i<c.length;i++){
		deck[i]=c.deck[i];
	}
	allocated_size=c.allocated_size;
	length=c.length;
}

/// Add card in array
void Deck::add(const Card &card){
	size_t new_size;
	if(length>=allocated_size){
		if(allocated_size==0){
			new_size=2;
		}
		else{
			new_size=allocated_size*2;
		}
		reallocate(new_size);
	}

	deck[length] = card.clone();
	length++;
}

/// Reallocate size of an array
void Deck::reallocate(size_t new_size){
	Card** c_temp=new(nothrow) Card*[new_size];
	if(!c_temp){
		cout<<"Error"<<endl;
		return;
	}
	size_t limit;
	if(allocated_size<=new_size){
		limit=allocated_size;
	}
	else{
		limit=new_size;
	}
	for(int i=0;i<limit;i++){
		c_temp[i]=deck[i]->clone();
	}
	for(int i=0;i<allocated_size;i++){
		delete deck[i];
	}
	delete [] deck;
	deck=c_temp;
	allocated_size=new_size;
}

/// Delete all cards from deck
void Deck::free(){

	for(int i=0;i<length;i++){
		delete deck[i];
	}
	delete [] deck;
	deck=NULL;
	allocated_size=0;
	length=0;
}
/// Return the allocated size
size_t Deck::get_allocated_size() const{
	return allocated_size;
}

/// Return the count of cards
size_t Deck::get_length() const{
	return length;
}

/// Return card at position
Card* Deck::get_at_position(size_t index) const{
	return deck[index];
}

/// Print the elements in deck
void Deck::print() const{
	for(int i=0;i<length;i++){
		deck[i]->print_card();
		cout<<endl;
	}
}

/// Check if cards are more than 4 
bool Deck::is_valid(){
	if(length>=5){
		return true;
	}
	else{
		return false;
	}
}

/// Save deck in binary fail
bool Deck::save(char* path_name){
		ofstream save_file(path_name,ios::binary | ios::app);
		save_file.clear();
		if(!save_file){
			cout<<"You can not save the deck " <<endl;
			return false;
		}
		else{
			save_file.write((char*) &length,sizeof(int));
			for(int i=0;i<length;i++){
				if(save_file){
					int len_of_name=strlen(deck[i]->get_name());
					save_file.write((char*) &len_of_name,sizeof(int));
					save_file.write(deck[i]->get_name(),len_of_name);
					int attack=deck[i]->get_attack();
					save_file.write((char*) &attack,sizeof(int));
					int health=deck[i]->get_health();
					save_file.write((char*) &health,sizeof(int));
				}
				else{
					cout<<"Saving the deck is impossible  "<<endl;
					return false;
				}
			}
			save_file.close();
			save_file.clear();
		}
	return true;

}

///Load deck from binary fail
void Deck::load(char* path_name){
	ifstream load_file(path_name,ios::binary);
	if(!load_file){
		cout<<"Can`t load the file "<<endl;
		load_file.close();
		load_file.clear();
		return;
	}
	else{
		this->length=0;
		int limit;
		int len_of_name;
		char name[100];
		int attack;
		int health;
		load_file.read((char*) &limit,sizeof(int));
		if(limit<5){
			cout<<"The deck is not valid"<<endl;
			return;
		}
		for(int i=0;i<limit;i++){
			if(load_file){
				load_file.read((char*) &len_of_name,sizeof(int));
				if(!load_file){
					load_file.clear();
					load_file.close();
					cout<<"Error"<<endl;
					return ;
				}
				load_file.read(name,len_of_name);
				if(!load_file){
					load_file.clear();
					load_file.close();
					cout<<"Error"<<endl;
					return ;
				}
				name[len_of_name] = '\0';
				load_file.read((char*) &attack,sizeof(int));
				if(!load_file){
					load_file.clear();
					load_file.close();
					cout<<"Error"<<endl;
					return ;
				}
				load_file.read((char*) &health,sizeof(int));
				if(!load_file){
					load_file.clear();
					load_file.close();
					cout<<"Error"<<endl;
					return ;
				}
				Card* c_help;
				c_help->set_name(name);
				c_help->set_attack(attack);
				c_help->set_health(health);
				c_help->set_needed_energy(attack,health);
				add(*c_help);
			}
			else{
				cout<<"Error in loading " <<endl;
				break;
			}
		}
		load_file.close();
		load_file.clear();
	}
}

/// 
void Deck::add_new_card(char* path_name){
	char name[100];
	int attack;
	int health;
	cout<<"Enter the name of the card(max 90 symbols):" ;
	cin.get(name,90);
	cout<<"Enter attack points: ";
	cin>>attack;
	if(!cin){
		cout<<"Sry your card can not be created with this attack"<<endl;
		return;
	}
	cout<<"Enter health points: ";
	cin>>health;
	if(!cin){
		cout<<"Sry your card can not be created with this health"<<endl;
		return;
	}
	Card* new_card;
	new_card->set_attack(attack);
	new_card->set_health(health);
	new_card->set_name(name);
	new_card->set_needed_energy(attack,health);
	cout<<"This is your card "<<endl;
	new_card->print_card();
	add(*new_card);
	if(!save(path_name)){
		return;
		cout<<"Can not save" <<endl;
	}
}

/// Remove one card from deck 
void Deck::remove_card(char* path_name,char* name_of_card){
	int temp=-1;
	Card *c;
	for(int i=0;i<length;i++){
		if(strcmp(name_of_card,deck[i]->get_name())==0){
			temp=i;
			break;
		}
	}
	if(temp==-1){
		cout<<"This card does not exist "<<endl;
		return ;
	}
	if(length<=5){
		cout<<"Can not remove card " <<endl;
		return;
	}
	Card* tempCard= deck[temp];
	for(int i=temp;i<length-1;i++){
		deck[i]=deck[i+1];
	}
	deck[length-1]=tempCard;
	length--;
	save(path_name);
}

/// Change existing card from the deck
void Deck::change_card(char* path_name,char* name_of_card){
	int temp=-1;
	for(int i=0;i<length;i++){
		if(strcmp(name_of_card,deck[i]->get_name())==0){
			temp=i;
			break;
		}
	}
	if(temp==-1){
		cout<<"This card does not exist "<<endl;
		return ;
	}
	char name[100];
	int attack;
	int health;
	cout<<"Enter the name of the card(max 90 symbols):" ;
	cin>>name;
	if(strlen(name)>90){
		cout<<"Invalid name " <<endl;
		return ;
	}
	cout<<"Enter attack points: ";
	cin>>attack;
	if(!cin){
		cout<<"Error in changing!"<<endl;
		return;
	}
	cout<<"Enter health points: ";
	cin>>health;
	if(!cin){
		cout<<"Error in changing!"<<endl;
		return;
	}
	deck[temp]->set_attack(attack);
	deck[temp]->set_health(health);
	deck[temp]->set_name(name);
	deck[temp]->set_needed_energy(attack,health);
	if(!save(path_name)){
		cout<<"The card is changed but not saved" <<endl;
		return;
	}
}

/// Help function
bool Deck::is_index_used(int* arr,int pos, int index){
	for(int i=0;i<pos;i++){
		if(arr[i]==index){
			return true;
		}
	}
	return false;
}

/// Save top five cards in text file
void Deck::top_five(char* name_of_text_file,char* principle){
	if(strcmp(principle,"attack")==0){
		Card* best_cards[5];
		int arr_pos[5];
		for(int i=0;i<5;i++){
			arr_pos[i]=-1;
		}
		int max_index=-1;
		int max_attack=-2147483648;
		int previous_max=2147483647;
		for (int pos=0;pos<5;pos++){
			for (int i=0;i<length;i++){ 
				if(deck[i]->get_attack()<=previous_max && max_attack<deck[i]->get_attack() && !is_index_used(arr_pos,pos,i)){
					max_index=i;
					max_attack=deck[i]->get_attack();
				}
			}
			best_cards[pos]=deck[max_index];
			arr_pos[pos]=max_index;
			previous_max=max_attack;
			max_attack=-2147483648;
			max_index=-1;
		}
		ofstream text_file(name_of_text_file,ios::trunc);
		if(!text_file){
			cout<<"Can not open this file"<<endl;
			return ;
		}
		for(int i=0;i<5;i++){
			text_file<<best_cards[i]->get_name()<<endl;
			text_file<<best_cards[i]->get_attack()<<endl;
			text_file<<best_cards[i]->get_health()<<endl;
			text_file<<best_cards[i]->get_needed_energy()<<endl;
			text_file<<endl;
		}
		text_file.close();
		text_file.clear();
	}
	else if(strcmp(principle,"health")==0){
		Card* best_cards[5];
		int arr_pos[5];
		for(int i=0;i<5;i++){
			arr_pos[i]=-1;
		}
		int max_index=-1;
		int max_health=-2147483648;
		int previous_max=2147483647;
		for (int pos=0;pos<5;pos++){
			for (int i=0;i<length;i++){ 
				if(deck[i]->get_health()<=previous_max && max_health<deck[i]->get_health() && !is_index_used(arr_pos,pos,i)){
					max_index=i;
					max_health=deck[i]->get_health();
				}
			}
			best_cards[pos]=deck[max_index];
			arr_pos[pos]=max_index;
			previous_max=max_health;
			max_health=-2147483648;
			max_index=-1;
		}
		ofstream text_file(name_of_text_file,ios::trunc);
		if(!text_file){
			cout<<"Can not open this file"<<endl;
			return ;
		}
		for(int i=0;i<5;i++){
			text_file<<best_cards[i]->get_name()<<endl;
			text_file<<best_cards[i]->get_attack()<<endl;
			text_file<<best_cards[i]->get_health()<<endl;
			text_file<<best_cards[i]->get_needed_energy()<<endl;
			text_file<<endl;
		}
		text_file.close();
		text_file.clear();
	}
	else if(strcmp(principle,"needed energy")==0){
		Card* best_cards[5];
		int arr_pos[5];
		for(int i=0;i<5;i++){
			arr_pos[i]=-1;
		}
		int max_index=-1;
		int max_energy=-2147483648;
		int previous_max=2147483647;
		for (int pos=0;pos<5;pos++){
			for (int i=0;i<length;i++){ 
				if(deck[i]->get_needed_energy()<=previous_max && max_energy<deck[i]->get_needed_energy() && !is_index_used(arr_pos,pos,i)){
					max_index=i;
					max_energy=deck[i]->get_needed_energy();
				}
			}
			best_cards[pos]=deck[max_index];
			arr_pos[pos]=max_index;
			previous_max=max_energy;
			max_energy=-2147483648;
			max_index=-1;
		}
		for(int i=0;i<5;i++){
			best_cards[i]->print_card();
		}
		ofstream text_file(name_of_text_file,ios::trunc);
		if(!text_file){
			cout<<"Can not open this file"<<endl;
			return ;
		}
		for(int i=0;i<5;i++){
			text_file<<best_cards[i]->get_name()<<endl;
			text_file<<best_cards[i]->get_attack()<<endl;
			text_file<<best_cards[i]->get_health()<<endl;
			text_file<<best_cards[i]->get_needed_energy()<<endl;
			text_file<<endl;
		}
		text_file.close();
		text_file.clear();
	}
	else{
		cout<<"Invalid principle"<<endl;
		return;
	}
}

int Deck::sum_from_attack_and_health() const{
	int sum=0;
	for(int i=0;i<length;i++){
		sum=deck[i]->get_attack()+deck[i]->get_health()+sum;
	}
	return sum;
}

/// Operator '=' for Deck
Deck& Deck::operator=(Deck const &d){
	if(this!=&d){
		deck=new(nothrow) Card*[d.allocated_size];
		if(!deck){
			return *this;
		}
		for(int i=0;i<d.length;i++){
			deck[i]=d.deck[i]->clone();
		}
		allocated_size=d.allocated_size;
		length=d.length;
	}
	return *this;
}

/// Operator == for Deck 
bool Deck::operator==(const Deck &d) const{
	if(length!=d.get_length()){
		return false;
	}
	for(int i=0;i<length;i++){
		if(strcmp(deck[i]->get_name(),d[i]->get_name())==0){

		}
		else{
			return false;
		}
	}
 	return true;
}

/// Operator [] , returns pointer to idx-Card from the Deck
Card* Deck::operator[]( int idx) {
	if(idx>(length-1) || idx<0){
		cout<<"------------------------------Error---------------------------------" <<endl;
	}
	return deck[idx];
}

/// Operator [] for const objects
const Card* Deck::operator[]( int idx) const{
	if(idx>(length-1) || idx<0){
		cout<<"---------------------Error------------------------" <<endl;
	}
	return deck[idx];
}

/// Operator != for Decks
bool Deck::operator!=(const Deck &d){
	Deck d1=*this;

	if(d1==d){
		return false;
	}
	return true;
}

/// Next 4 operators are '<,>,>=,<='
bool Deck::operator>(const Deck &d){
	if(sum_from_attack_and_health()>d.sum_from_attack_and_health()){
		return true;
	}
	return false;
}

bool Deck::operator<(const Deck &d){
	if(sum_from_attack_and_health()<d.sum_from_attack_and_health()){
		return true;
	}
	return false;
}

bool Deck::operator<=(const Deck &d){
	if(sum_from_attack_and_health()<=d.sum_from_attack_and_health()){
		return true;
	}
	return false;
}

bool Deck::operator>=(const Deck &d){
	if(sum_from_attack_and_health()>=d.sum_from_attack_and_health()){
		return true;
	}
	return false;
}

/// Operator for output
ostream& operator<<(ostream& out,const Deck &d){
	for(int i=0;i<d.get_length();i++){
		out<<d[i]->get_name()<<endl;
		out<<d[i]->get_attack()<<endl;
		out<<d[i]->get_health()<<endl;
		out<<d[i]->get_needed_energy()<<endl;
		out<<endl;
	}

	return out;
}

/// Adds card to deck(left argument card)
Deck operator+(Card &c,Deck &d){
	Deck new_deck=d;
	new_deck+=c;
	return new_deck;;

}

/// Adds card to deck(left argument deck)
Deck operator+(Deck &d, Card &c){
	Deck new_deck=d;
	new_deck+=c;
	return new_deck;
}

/// Adds all cards from one deck to another
Deck operator+(Deck &d1,Deck &d2){
	Deck new_deck;
	for(int i=0;i<d1.get_length();i++){
		new_deck.add(*d1[i]);
	}
	for(int i=0;i<d2.get_length();i++){
		new_deck.add(*d2[i]);
	}
	return new_deck;
}

/// Adds card to deck
Deck& Deck::operator+=(const Card &c){
	add(c);
	return *this;
}

/// Adds all cards from deck to another
Deck& Deck::operator+=(const Deck &d){
	int y=d.get_length();
	int x=0;
	while(x<y){
		add(*d[x]);
		x++;
	}
	return *this;
}

/// Returns length of the deck
Deck::operator int(){
	return length;
}

/// Removes card from deck
Deck& Deck::operator-=(const Card &c){
	int temp=-1;
	for(int i=0;i<length;i++){
		if(*deck[i]==c){
			temp=i;
			break;
		}
	}
	if(temp==-1){
		return *this;
	}
	Card* tempCard= c.clone();
	for(int i=temp;i<length-1;i++){
		deck[i]=deck[i+1];
	}
	deck[length-1]=tempCard;
	length--;
	return *this;
}

/// If returns true then the deck is valid 
Deck::operator bool(){
	return is_valid();
}

/// Removes card from deck
Deck& Deck::operator-(const Card &c){
	*this-=c;
	return *this;
}
