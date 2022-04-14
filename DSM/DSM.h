#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DSM {
	int nrElems;
	vector<string> elems;
	int m[100][100];

public:
	DSM();
	DSM(int elementCount);
	DSM(vector<string> element_names);
	//DSM(const DSM& l, const DSM& n) {}	//copy ctor
	~DSM();

	//create...
	int size();	
	void set_element_name(int index, string name); 
	string get_name(int index);	
	void add_link(string from_element, string to_element, int weight);
	void delete_link(string from_element, string to_element);
	
	//analyse...
	bool have_link(string from_element, string to_element);
	int link_weight(string from_element, string to_link);
	int count_to_links(string element_name);
	int count_from_links(string element_name);
	int count_all_links();
	double calculate_matrix_density();

	//print...
	void print_string();
	void print_matrix();
	void print_dsm();

};