#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility> 
#include <cstdlib>
#include <vector>
#include <string>

#include "global.hpp"
//#include "pieces.hpp"

struct General{
    std::vector<std::vector<int>> map={
        {2,3,4,5,6,4,3,2}, 
        {1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1},
        {2,3,4,5,6,4,3,2}
    };

    std::vector<std::vector<int>> teams={ //NEGROS NUMERO 1, BLANCOS NUMERO 2
        {0,0,0,0,0,0,0,0}, 
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
    }; 

    sf::Sprite init(sf::Texture& texture, int& j, int i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        sf::Sprite Piece(texture);

        sf::Vector2u sizePiece=texture.getSize();

        float scaleX=static_cast<float>(CELL)/sizePiece.x;
        float scaleY=static_cast<float>(CELL)/sizePiece.y;

        Piece.setScale({scaleX, scaleY});
        Piece.setPosition(sf::Vector2f(250+CELL*j, 150+CELL*i));

        return Piece;
    }

    std::vector<int> coords(int& col, int& row){
        int x, y;
        
        if(row>=150 && row<=210) x=0;
        if(row>210 && row<=270) x=1;
        if(row>270 && row<=330) x=2;
        if(row>330 && row<=390) x=3;
        if(row>390 && row<=450) x=4;
        if(row>450 && row<=510) x=5;
        if(row>510 && row<=570) x=6;
        if(row>570 && row<=630) x=7;

        if(col>=250 && col<=310) y=0;
        if(col>310 && col<=370) y=1;
        if(col>370 && col<=430) y=2;
        if(col>430 && col<=490) y=3;
        if(col>490 && col<=550) y=4;
        if(col>550 && col<=610) y=5;
        if(col>610 && col<=670) y=6;
        if(col>670 && col<=730) y=7;

        _x=x; //COPIA DE LAS COORDENADAS CLICKEADAS!!!!!!!!!!!!!! USO DE COINCIDENCIA DE PIEZAS
        _y=y;

        return {x,y};
    }

    void _pieceSelected(){
        if(map[_x][_y]==0) pieceSelected="vacio";
        if(map[_x][_y]==1) pieceSelected="peon";
        if(map[_x][_y]==2) pieceSelected="torre";
        if(map[_x][_y]==3) pieceSelected="caballo";
        if(map[_x][_y]==4) pieceSelected="alfil";
        if(map[_x][_y]==5) pieceSelected="reina";
        if(map[_x][_y]==6) pieceSelected="rey";
    }

    void changeMoving(sf::Sprite& sprite, int& j, int& i){
        sprite.setPosition(sf::Vector2f(250+CELL*j, 150+CELL*i));
    }

    bool evaluate(int& col, int& row){
        bool ans=false;
        
        if((col>=250 && col<=730) && (row>=150 && row<=630)) ans=true;
        else ans=false;
        return ans;
    }

    void Pos_moving(sf::RenderWindow& window, int new_x, int new_y){
        std::cout<<"BUSCANDO CASILLA: "<<new_x<<" - "<<new_y<<std::endl;

        for(auto& x: cajasDelMapa){
            if(x.coords.first==new_y && x.coords.second==new_x){ //RECUERDA COLUMNA-FILA
                std::cout<<"!!!!CASILLA ENCONTRADA!!!!!!!"
                         <<x.coords.first<<" - "
                         <<x.coords.second<<std::endl;

                x.box.setFillColor(sf::Color(255, 182, 193));
                window.draw(x.box);
            }
        }
    }

    std::vector<sf::Texture> texturePieces(){
        std::vector<sf::Texture> list;

        sf::Texture texture;
        if(!texture.loadFromFile("peon.png")){
            std::cerr<<"FAIL OPEN PEON BLACK"<<std::endl;
        }

        sf::Texture peon_white_text;
        if(!peon_white_text.loadFromFile("peonblanco.png")){
            std::cerr<<"FAIL OPEN PEON WHITE"<<std::endl;
        }

        sf::Texture tower_white;
        if(!tower_white.loadFromFile("torreW.png")){
            std::cerr<<"FAIL OPEN TOWER_WHITE"<<std::endl;
        }

        sf::Texture tower_black;
        if(!tower_black.loadFromFile("torreB.png")){
            std::cerr<<"FAIL OPEN TOWER_BLACK"<<std::endl;
        }

        sf::Texture alfil_white;
        if(!alfil_white.loadFromFile("alfilW.png")){
            std::cerr<<"FAIL OPEN ALFIL_WHITE"<<std::endl;
        }

        sf::Texture alfil_black;
        if(!alfil_black.loadFromFile("alfilB.png")){
            std::cerr<<"FAIL OPEN ALFIL_BLACK"<<std::endl;
        }

        sf::Texture caballo_white;
        if(!caballo_white.loadFromFile("caballoW.png")){
            std::cerr<<"FAIL OPEN CABALLO_WHITE"<<std::endl;
        }

        sf::Texture caballo_black;
        if(!caballo_black.loadFromFile("caballoB.png")){
            std::cerr<<"FAIL OPEN CABALLO_BLACK"<<std::endl;
        }

        sf::Texture reina_white;
        if(!reina_white.loadFromFile("queenW.png")){
            std::cerr<<"FAIL OPEN REINA_WHITE"<<std::endl;
        }

        sf::Texture reina_black;
        if(!reina_black.loadFromFile("queenB.png")){
            std::cerr<<"FAIL OPEN REINA_BLACK"<<std::endl;
        }

        sf::Texture rey_white;
        if(!rey_white.loadFromFile("kingW.png")){
            std::cerr<<"FAIL OPEN REY_WHITE"<<std::endl;
        }

        sf::Texture rey_black;
        if(!rey_black.loadFromFile("kingB.png")){
            std::cerr<<"FAIL OPEN REY_BLACK"<<std::endl;
        }

        list.push_back(texture); //0
        list.push_back(peon_white_text); //1
        list.push_back(tower_white); //2
        list.push_back(tower_black); //3
        list.push_back(alfil_white); //4
        list.push_back(alfil_black); //5
        list.push_back(caballo_white); //6
        list.push_back(caballo_black); //7
        list.push_back(reina_white); //8
        list.push_back(reina_black); //9
        list.push_back(rey_white); //10
        list.push_back(rey_black); //11

        return list;
    }
};

#endif
