#define GL_SILENCE_DEPRECATION

#include "game.hpp"

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    
    Game game;
    
    game.load();
    game.run();
    
    return 0;
}
