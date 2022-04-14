#include <iostream>
#include <string>
#include <vector>
#include "DSM.h"


using namespace std;


DSM::DSM() {
	this->nrElems = 0;
	this->elems = {};
}

DSM::DSM(vector<string> element_names) {	
	for (int i = 0; i < this->nrElems; i++) {		
		this->elems.emplace_back(element_names[i]);	//we build a vector with the names of the elements
	}
}

DSM::DSM(int elementCount) {
	this->nrElems = elementCount;
	for (int i = 0; i < this->nrElems; i++) {
		for (int j = 0; j < this->nrElems; j++) {
			this->m[i][j] = 0;						//we create the matrix with the links
		}
	}
}

int DSM::size() {
	return this->nrElems;
}

DSM::~DSM() {			//destructor
	this->elems.clear();
	for (int i = 0; i < this->nrElems; i++) {
		for (int j = 0; j <= this->nrElems; j++) {
			this->m[i][j] = 0;
		}
	}
	this->nrElems = 0;
}

void DSM::set_element_name(int index, string name) {
	if (this->nrElems < index)
		throw exception();
	else {
		this->elems[index] = name; //we insert the new name (over-write)
	}
}

string DSM::get_name(int index) {
	if (this->nrElems < index) {
		throw exception();
	}
	return this->elems.at(index);
}

void DSM::add_link(string from_element, string to_element, int weight) {
	int it_from = -1, it_to = -1;

	for (int i = 0; i < this->elems.size(); i++) {
		if (this->elems[i] == from_element) {
			it_from = i;
			break;
		}
	}
	for (int j = 0; j < this->elems.size(); j++) {
		if (this->elems[j] == to_element) {
			it_to = j;
			break;	
		}
	}
	if (it_from != -1 && it_to != -1) {		//if the 2 element exist, we set the link in the matrix
		this->m[it_from][it_to] = weight;
	}
	else {					
		if (it_from != -1) {		//if only the "to" element exists, we add the "from" element in the matrix and we set the link on 0
			this->elems.emplace_back(to_element);	
			this->m[it_from][this->elems.size() - 1] = 0;	
			this->nrElems++;		
		}
		if (it_to != -1) {		//if only the "from" element exists, we add the "to" element in the matrix and we set the link on 0
			this->elems.emplace_back(from_element);
			this->m[this->elems.size() - 1][it_to] = 0;
			this->nrElems++;
		}
		if (it_from == -1 && it_to == -1) {			//if neither of the 2 exist, we add them both to the matrix
			this->elems.emplace_back(from_element);
			this->elems.emplace_back(to_element);
			this->m[this->elems.size() - 2][this->elems.size() - 1] = 0;			//and we set the link on 0
			this->nrElems += 2;
		}
	}
}

void DSM::delete_link(string from_element, string to_element) {
	bool ok = true;
	int it_from = -1, it_to = -1;
	for (int i = 0; i < this->nrElems; i++) {
		if (from_element == this->elems[i]) {
			it_from = i;
		}
		if (to_element == this->elems[i]) {
			it_to = i;
		}
	}
	if (it_from == -1 || it_to == -1) {		//if at least one of the elements don't exist, we won't delete anything
		ok = false;
	}
	if (ok) {
		this->m[it_from][it_to] = 0;
	}
}

bool DSM::have_link(string from_element, string to_element) {
	int it_from = -1, it_to = -1;
	for (int i = 0; i < this->nrElems; i++) {
		if (from_element == this->elems[i]) {
			it_from = i;
		}
		if (to_element == this->elems[i]) {
			it_to = i;
		}
	}
	if (it_from == -1 || it_to == -1) {		//if neither of the elements exist, then we have no link
		return false;
	}
	if (it_from != -1 && it_to != -1){
		if (this->m[it_from][it_to] != 0)
			return true;			//the elements have a link when weight != 0
		else
			return false;
	}
}

int DSM::link_weight(string from_element, string to_link) {
	int it_from = -1, it_to = -1;
	for (int i = 0; i < this->nrElems; i++) {
		if (from_element == this->elems[i]) {
			it_from = i;
		}
		if (to_link == this->elems[i]) {
			it_to = i;
		}
	}
	if (it_from == -1 || it_to == -1) {		//we check if the elements exist
		return 0;
	}
	if (it_from != -1 && it_to != -1) {
		return this->m[it_from][it_to];
	}
}

int DSM::count_to_links(string element_name) {
	int it_el_name = -1, ct = 0;
	for (int i = 0; i < this->nrElems; i++) {
		if (element_name == this->elems[i]) {
			it_el_name = i;
		}
	}
	if (it_el_name != -1) {			//we check if the elements exist
		for (int i = 0; i < this->nrElems; i++) {
			if (this->m[it_el_name][i] != 0) {		
				ct++;
			}
		}
		return ct;
	}
	else
		return 0;
}

int DSM::count_from_links(string element_name) {
	int it_el_name = -1, ct = 0;
	for (int i = 0; i < this->nrElems; i++) {
		if (element_name == this->elems[i]) {
			it_el_name = i;
		}
	}
	if (it_el_name != -1) {			//we check if the elements exist
		for (int i = 0; i < this->nrElems; i++) {
			if (this->m[i][it_el_name] != 0) {		
				ct++;
			}
		}
		return ct;
	}
	else
		return 0;
}

int DSM::count_all_links() {
	int ct = 0;
	for (int i = 0; i < this->nrElems; i++) {
		for (int j = 0; j < this->nrElems; j++) {
			if (this->m[i][j] != 0) {
				ct++;
			}
		}
	}
	return ct;
}

double DSM::calculate_matrix_density() {
	double ct = 0, density;
	for (int i = 0; i < this->nrElems; i++) {
		for (int j = 0; j < this->nrElems; j++) {
			if (this->m[i][j] != 0) {
				ct++;
			}
		}
	}
	//density = quantity of all possible links / quantity of existing links
	density = ct / ((this->nrElems * this->nrElems) - this->elems.size());
}

void DSM::print_string() {
	for (int i = 0; i < this->nrElems; i++) {
		cout << this->elems[i] << " ";
	}
}

void DSM::print_matrix() {
	for (int i = 0; i < this->nrElems; i++) {
		for (int j = 0; j < this->nrElems; j++) {
			cout << this->m[i][j] << " ";
		}
		cout << "\n";
	}
}

void DSM::print_dsm() {	
	cout << "  ";
	for (int i = 0; i < this->nrElems; i++) {
		cout << this->elems[i] << " ";
	}
	cout << "\n";
	for (int i = 0; i < this->nrElems; i++) {
		cout << this->elems[i] << " ";
		for (int j = 0; j < this->nrElems; j++) {
			cout << this->m[i][j] << " ";
		}
		cout << "\n";
	}
}
