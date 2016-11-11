#include "library.hpp"
Library::Library(){
}

Library::~Library(){
	list<Employee*>::iterator it;
	for (it = employeeList.begin(); it != employeeList.end(); it++){
		delete *it;
	}
}

void Library::add_book(string newBook){
	Book tempBook(newBook);
	toBeCirculated.push_back(tempBook);
}

void Library::add_employee(string name){
	Employee *temp; 
	temp = new Employee(name);
	employeeList.push_back(temp);
}

void Library::circulate_book(string bookToMove, Date dayOfMove){
	list<Book>::iterator it; 
	for (it = toBeCirculated.begin(); it != toBeCirculated.end(); it++){ // find book : O(n)
		if (it->getname() == bookToMove){ // this is the book
			it->populate_queue(employeeList); // create queue
			it->setstartDate(dayOfMove); // save start date
			cout << "book: "<<bookToMove << " have been circulated on " <<dayOfMove<< endl;
			return;
		}
	}
	cerr << "Book not found" << endl;
}

void Library::pass_on(string bookToMove, Date date){
	Employee *next, *prev; // prev is employee that is popped
	list<Book>::iterator it;
	for (it = toBeCirculated.begin(); it != toBeCirculated.end(); it++){ // find book : O(n)
		if (it->getname() == bookToMove){
			prev = it->pop_max(); // pop max, save to prev
			prev->retain(date - it->getHeld()); // retain = current date - last pass of book
			if (!it->isEmpty()){
				next = it->top(); // next is now max
				next->wait(date - it->getstartDate()); // wait = current date - book start date
				it->setHeld(date); // save pass date for next employee
			}
			else{ // circulation complete
				it->setarchived(true);
				it->setendDate(date);
				archived.push_back(*it); // archive
				toBeCirculated.erase(it); // erase
			}
			cout << "book: " << bookToMove << " have been passed to the next employee on " << date << endl;
			return;
		}
	}
	cerr << "pass on: Book not found" << endl;
}