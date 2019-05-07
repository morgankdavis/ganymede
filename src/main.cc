
#include "Ganymede.h"


int main(int argc, char **argv) {

	return std::make_shared<ganymede::Ganymede>()->start(argc, argv);
}
