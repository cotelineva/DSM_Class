#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include "DSM.h"

using namespace std;

void create_dsm() {
	DSM a;
	a.DSM::DSM(4);
	a.DSM::DSM({ "a","b","c","d" });
	
	a.add_link("a", "b", 3);
	a.add_link("b", "d", 5);
	a.add_link("c", "a", 8);
	a.add_link("d", "c", 7);
	a.add_link("c", "d", 1);
	a.add_link("e", "a", 2);

	assert(a.size() == 5);
	assert(a.get_name(4) == "e");

	a.set_element_name(1, "z");
	assert(a.get_name(1) == "z");
	assert(a.have_link("b", "d") == false);
	assert(a.have_link("z", "d") == true);

	a.add_link("z", "d", 4);
	assert(a.link_weight("z", "d") == 4);

	a.delete_link("z", "d");
	assert(a.have_link("z", "d") == 0);
}

void analyse_dsm() {
	DSM a;
	a.DSM::DSM(4);
	a.DSM::DSM({ "a","b","c","d" });

	a.add_link("a", "b", 3);
	a.add_link("b", "d", 5);
	a.add_link("c", "a", 8);
	a.add_link("d", "c", 7);
	a.add_link("c", "d", 1);
	a.add_link("e", "a", 2);

	assert(a.have_link("b", "d") == true);
	assert(a.have_link("a", "c") == false);

	assert(a.link_weight("d", "c") == 7);
	assert(a.link_weight("d", "a") == 0);

	assert(a.count_to_links("c") == 2);
	assert(a.count_from_links("d") == 2);
	assert(a.count_all_links() == 5);

	assert(a.calculate_matrix_density() == 0.25);
}

void test_displaying() {
	DSM a;
	a.DSM::DSM(4);
	a.DSM::DSM({ "a","b","c","d" });

	a.add_link("a", "b", 3);
	a.add_link("b", "d", 5);
	a.add_link("c", "a", 8);

	cout << "Printing element names...\n";
	a.print_string();
	cout << "\n\n";
	cout << "Printing link matrix...\n";
	a.print_matrix();
	cout << "\n";
	cout << "Printing DSM...\n";
	a.print_dsm();
}

int main() {

	create_dsm();
	cout << "ASSERTION FOR CREATING WORKED!\n";

	analyse_dsm();
	cout << "\nASSERTION FOR ANALYSING WORKED!\n\n";

	test_displaying();
	cout << "\nDISPLAY METHODS WORK!\n";

	cout << "\nEVERYTHING IS PERFECT! :)\n";

	return 0;
}