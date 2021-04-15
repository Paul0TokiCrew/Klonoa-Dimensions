#include <game.hpp>



int main(int argc, char* argv[]) {
	game* g = new game("Klonoa Dimensions");
	g->play();
	delete g;
	return 0;
}
