#pragma once
#include"passenger_class.h"

//The linked list and operations
class PassengerList {

public:
	//initialize with arguments offered
	PassengerList(int total, int startnum, int deathnum, int residue) :
	total_(total),startnum_(startnum),deathnum_(deathnum),residue_(residue){
		head_ = new Passenger(total_);
	}
	//delete the nodes
	~PassengerList() {
		auto current = head_->next_;
		Passenger *following = NULL;

		while (current != head_) {
			following = current->next_;
			delete current;
			current = following;
		}
		delete current;
	}

public:

	int residue() { return residue_; }

	//create the linked list
	void Create();
	//kill the unlucky guys
	void Kill();
	//print the lucky guys
	void SurvivalListOutput();

private:
	//used as the tail of the linked list
	Passenger *head_;
	int total_;
	int startnum_;
	int deathnum_;
	int residue_;
};