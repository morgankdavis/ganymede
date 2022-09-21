
#include "Ganymede.h"


int main(int argc, char **argv) {

	return std::make_unique<ganymede::Ganymede>()->start(argc, argv);
}
