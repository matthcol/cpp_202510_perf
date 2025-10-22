#include "Shape.h"

void scenario1() {
	// interdit d'instancier une classe abstraite
	Shape shape; 
	Shape* shape_ptr = new Shape();
}

int main() {
	return 0;
}