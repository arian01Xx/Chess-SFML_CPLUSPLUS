#pragma once

constexpr int TILE=6;
constexpr int CELL=TILE*10;

int _x, _y; //copia de la coordenada clickeada
int x_1, y_1; //coordenadas de la pieza encontrada (solo para verificar que en serio coinciden)
std::string pieceSelected; //utilizar esto para reconocer pieza seleccionada 
std::vector<int> _coords; //ESTO CREO QUE NO LO UTILIZAMOS
bool turnWhite=true; //empiezan las blancas siempre!

struct Boxes{
    sf::RectangleShape box;
    std::pair<int,int> coords; //COLUMNA - FILAS!!!
};

std::vector<Boxes> cajasDelMapa;

//struct Boxes;

//extern std::vector<Boxes> cajasDelMapa;
