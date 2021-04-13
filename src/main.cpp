#include <game.hpp>



extern float get_current_time();

int main(int argc, char* argv[]) {
	game* g = new game("Klonoa Dimensions");
	g->play();
	delete g;
	return 0;
}
