#ifndef PIECES_HPP
#define PIECES_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility> 
#include <cstdlib>
#include <vector>
#include <string>

#include "general.hpp"
#include "global.hpp"

struct Piece{
    bool white;
    int y, x; //es porque los parametros de texture estan al reves, i es columna y j fila, no como la matriz clasica[fila][columna]
    Piece(int _y, int _x, bool w): y(_y), x(_x), white(w){}

    sf::Sprite init(General& general, sf::Texture& texture){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!! 
        return general.init(texture,y,x);
    }

    void changeCoords(int& new_x, int& new_y){
        x=new_x;
        y=new_y;
    }

    virtual ~Piece(){}
};

/*                  BLACK TEAM:
 {2,3,4,5,6,4,3,2}, torres fila:0 columna:0, fila:0 columna:7 
 {1,1,1,1,1,1,1,1}, caballos fila:0 columna:1, fila:0 columna:6
 {0,0,0,0,0,0,0,0}, alfiles fila:0 columna:2, fila:0 columna:5
 {0,0,0,0,0,0,0,0}, reina fila:0 columna:3, rey fila:0, columna:4
 {0,0,0,0,0,0,0,0}, peones filas:1
 {0,0,0,0,0,0,0,0}, 
 {1,1,1,1,1,1,1,1},
 {2,3,4,5,6,4,3,2}
 WHITE TEAM: filas:7
 */

struct Peon: Piece{ //COLUMNA-FILA
    Peon(int _y, int _x, General& general): Piece(_y,_x,_x==6) {
        if(_x==6) general.teams[_x][_y]=2; //EQUIPO BLANCO
        else general.teams[_x][_y]=1; //EQUIPO NEGRO
    }

    void execute(General& general, sf::RenderWindow& window){
        if(white){ //team 2
            if(general.map[_x-1][_y]==0) general.Pos_moving(window, _x-1, _y); 
            if(general.map[_x-2][_y]==0) general.Pos_moving(window, _x-2, _y);
            if(_y-1>=0 && 
                general.teams[_x-1][_y-1]==1) general.Pos_moving(window, _x-1, _y-1);
            if(_y+1<8 && 
                general.teams[_x-1][_y+1]==1) general.Pos_moving(window, _x-1, _y+1);
        }
    }
};

struct Tower: Piece{ //COLUMNA - FILA
    Tower(int _y, int _x, General& general): Piece(_y,_x,_y==7) {
        if(_y==7) general.teams[_x][_y]=2;
        else general.teams[_x][_y]=1;
    } 

    /*PRIMERO QUE PINTE LOS LUGARES DONDE SE PUEDE MOVER, NO IMPORTA SI ROMPE REGLAS
     * LUEGO DEBO HACER QUE LAS PIEZAS INTERCAMBIEN INFORMACION DE QUE EQUIPO PERTENECEN 
     * PARA QUE EVALUEN SI PUEDEN COMERSE*/
    /*void execute(General& general){
        //UP
        for(int i=_x; i>0; i--){
            if(general.map==0){
                pintarCuadro(_y,i);
            }
        }
        //DOWN
        for(int i=_x; ){

        }
        //LEFT
        //RIGHT
    }*/
};

struct Alfil: Piece{
    Alfil(int _y, int _x, General& general): Piece(_y,_x,_y==7){
        if(_y==7) general.teams[_x][_y]=2;
        else general.teams[_x][_y]=1;
    } 
};

struct Caballo: Piece{
    Caballo(int _y, int _x, General& general): Piece(_y,_x,_y==7){
        if(_y==7) general.teams[_x][_y]=2;
        else general.teams[_x][_y]=1;
    }
};

struct Queen: Piece{
    Queen(int _y, int _x, General& general): Piece(_y,_x,_y==7){
        if(_y==7) general.teams[_x][_y]=2;
        else general.teams[_x][_y]=1;
    }
};

struct King: Piece{
    King(int _y, int _x, General& general): Piece(_y,_x,_y==7){
        if(_y==7) general.teams[_x][_y]=2;
        else general.teams[_x][_y]=1;
    }
};

#endif
