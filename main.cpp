#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility> 
#include <cstdlib>
#include <vector>
#include <string>

#include "general.hpp"
#include "global.hpp"
#include "pieces.hpp"

struct World{
    std::vector<std::vector<int>> world={
        500, std::vector<int>(500,0)
    };

    int row=world.size();
    int col=world[0].size();

    void CreateBottom(sf::RenderWindow& window, int c, int r, sf::Color x){
        sf::RectangleShape bottom(sf::Vector2f(CELL,CELL)); //TAMAÑO DE LA CAJA
        bottom.setFillColor(x);
        bottom.setPosition(sf::Vector2f(250+CELL*c, 150+CELL*r)); //columnas, filas
        
        Boxes _box;
        _box.box=bottom;
        _box.coords={c,r}; //columna filas
        cajasDelMapa.push_back(_box);

        window.draw(bottom);
    }
};

void ThisPieceNotSelected(){
    std::cout<<"***************************"<<std::endl;
    std::cout<<"THIS PIECE NO WAS SELECTED!"<<std::endl;
    std::cout<<"***************************"<<std::endl;
}

void ThisPieceWasSelected(int pieceX, int pieceY){
    std::cout<<"***************************"<<std::endl;
    std::cout<<"TURN OF: ";
    if(turnWhite) std::cout<<"WHITE"<<std::endl;
    else std::cout<<"BLACK"<<std::endl;
    std::cout<<"***************************"<<std::endl;
    std::cout<<"CONGRATULATIONS! PIECE SELECTED"<<std::endl;
    x_1=pieceX;
    y_1=pieceY;
    std::cout<<"_x: "<<_x<<" - piece.x: "<<pieceX<<std::endl;
    std::cout<<"_y: "<<_y<<" - piece.y: "<<pieceY<<std::endl;
    std::cout<<"x_1: "<<x_1<<std::endl;
    std::cout<<"y_1: "<<y_1<<std::endl;
}

void evaluate(sf::RenderWindow& window, General& general, King& king, Queen& queen, Caballo& caballo1, Caballo& caballo2, 
              Alfil& alfil1, Alfil& alfil2, Tower& tower1, Tower& tower2, std::vector<Peon>& Peons){
    /***************
     2,3,4,5,6,4,3,2
     1,1,1,1,1,1,1,1
     0,0,0,0,0,0,0,0
     1,1,1,1,1,1,1,1
     2,3,4,5,6,4,3,2
     ***************/
    if(general.map[_x][_y]==1){
        for(auto& p: Peons){ 
            if(_x==p.x && _y==p.y){
                ThisPieceWasSelected(p.x, p.y);
                p.execute(general, window); //pinta los cuadros donde tiene permitido moverse
                return;
            }            
            ThisPieceNotSelected();
        }

    }else if(general.map[_x][_y]==2){
        if(tower1.x==_x && tower1.y==_y){

            ThisPieceWasSelected(tower1.x, tower1.y);
            //tower1.execute(general);

            return;
        }

        if(tower2.x==_x && tower2.y==_y){ 
            ThisPieceWasSelected(tower2.x, tower2.y);
            return;
        }

        ThisPieceNotSelected();

    }else if(general.map[_x][_y]==3){
        if(caballo1.x==_x && caballo1.y==_y){ 
            ThisPieceWasSelected(caballo1.x, caballo1.y);
            return;
        }

        if(caballo2.x==_x && caballo2.y==_y){ 
            ThisPieceWasSelected(caballo2.x, caballo2.y);
            return;
        }
        
        ThisPieceNotSelected();
        
    }else if(general.map[_x][_y]==4){
        if(alfil1.x==_x && alfil1.y==_y){
            ThisPieceWasSelected(alfil1.x, alfil1.y);
            return;
        }

        if(alfil2.x==_x && alfil2.y==_y){ 
            ThisPieceWasSelected(alfil2.x, alfil2.y);
            return;
        }

        ThisPieceNotSelected();
        
    }else if(general.map[_x][_y]==5){
        if(queen.x==_x && queen.y==_y){ 
            ThisPieceWasSelected(queen.x, queen.y);
            return;
        }

        ThisPieceNotSelected();

    }else if(general.map[_x][_y]==6){
        if(king.x==_x && king.y==_y){ 
            ThisPieceWasSelected(king.x, king.y);
            return;
        }

        ThisPieceNotSelected();
    }else{
        ThisPieceNotSelected();
    }
}

void whatPiecesWasSelected(sf::RenderWindow& window, General& general, King& kingW1, King& kingB1, Queen& queenW1, Queen& queenB1, 
                           Caballo& caballoW1, Caballo& caballoW2, Caballo& caballoB1,
                           Caballo& caballoB2, Alfil& alfilW1, Alfil& alfilW2, 
                           Alfil& alfilB1, Alfil& alfilB2, Tower& towerW1, Tower& towerW2,
                           Tower& towerB1, Tower& towerB2, 
                           std::vector<Peon>& PeonBs,
                           std::vector<Peon>& PeonWs){
    if(turnWhite){
        turnWhite=false; //SIN EMBARGO ESTO ES TEMPORAL YA QUE NO DEBE SER ASI
                         //EL TURNO ES SOLO CUANDO LA PIEZA SE MUEVA POR COMPLETO DEL SITIO
                         //POR LO QUE ESTO ES TEMPORAL Y NECESITA SER REUBICADO
        evaluate(window, general, kingW1, queenW1, caballoW1, caballoW2, alfilW1, alfilW2, towerW1, towerW2, PeonWs);
    }else{
        turnWhite=true; //SIN EMBARGO ESTO ES TEMPORAL YA QUE NO DEBE SER ASI
                         //EL TURNO ES SOLO CUANDO LA PIEZA SE MUEVA POR COMPLETO DEL SITIO
                         //POR LO QUE ESTO ES TEMPORAL Y NECESITA SER REUBICADO
        evaluate(window, general, kingB1, queenB1, caballoB1, caballoB2, alfilB1, alfilB2, towerB1, towerB2, PeonBs);
    }
}

void infoGeneral(int& col, int& row, bool& evaluate, General& general){
    //general._pieceSelected();
    _coords=general.coords(col, row); //vector en datos generales
    general._pieceSelected();

    std::system("clear");
    std::cout<<"INFO COLUMN: "<<col<<std::endl;
    std::cout<<"INFO ROW: "<<row<<std::endl;
    std::cout<<"INFO POSITION: boolean type! -> "<<evaluate<<std::endl;
    std::cout<<"COORDS: ("<< _coords[0]<<"-"<<_coords[1]<<")"<<std::endl;
    std::cout<<"PIECE SELECTED: "<<pieceSelected<<std::endl;
    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<"_x: "<<_x<<" - _y: "<<_y<<std::endl;
    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<"Who is the turn: "<<std::endl;
    //if(turnWhite) std::cout<<"WHITE TURN!"<<std::endl;
    //else std::cout<<"BLACK TURN!"<<std::endl;
    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<"COORD FOUND IT!: "<<x_1<<"-"<<y_1<<std::endl;
    std::cout<<"*********************************"<<std::endl;
    std::cout<<"*********************************"<<std::endl;
    std::cout<<"*********************************"<<std::endl;
}

void execute(){

    World w;
    General general;
    bool dragging=false;
    sf::Vector2i lastMouse;

    sf::RenderWindow window{
        sf::VideoMode({
                static_cast<unsigned>(TILE*w.col), //COLUMNAS
                static_cast<unsigned>(TILE*w.row) //FILAS
        }), "CHESS"
    };

    window.setFramerateLimit(50);

    std::vector<sf::Texture> textPieces=general.texturePieces(); //debe tener 12 texturas   
     /***************
     2,3,4,5,6,4,3,2
     1,1,1,1,1,1,1,1
     0,0,0,0,0,0,0,0
     1,1,1,1,1,1,1,1
     2,3,4,5,6,4,3,2
     ***************/
    //_----------------------------------------------------_
    int row_zero=0; int row_seven=7;
    
    ////////////////// REY  ////////////////////////////////
    int king_pos=4;
    King KW1(king_pos, row_seven, general), KB1(king_pos, row_zero, general);
    sf::Sprite king_white1=KW1.init(general,textPieces[10]); //29
    sf::Sprite king_black1=KB1.init(general,textPieces[11]); //5
    
    /////////////////// REINA ///////////////////////////////
    int queen_pos=3;
    Queen QB1(queen_pos, row_zero, general), QW1(queen_pos, row_seven, general);
    sf::Sprite queen_black1=QB1.init(general,textPieces[9]);//4
    sf::Sprite queen_white1=QW1.init(general,textPieces[8]);//28
    
    ////////////////// CABALLO /////////////////////////////
    int caballo_left=1, caballo_right=6;
    Caballo CW1(caballo_left, row_seven, general), CW2(caballo_right, row_seven, general); 
    sf::Sprite caballo_white1=CW1.init(general,textPieces[6]);//26
    sf::Sprite caballo_white2=CW2.init(general,textPieces[6]);//31

    Caballo CB1(caballo_left, row_zero, general), CB2(caballo_right, row_zero, general);
    sf::Sprite caballo_black1=CB1.init(general,textPieces[7]);//2
    sf::Sprite caballo_black2=CB2.init(general,textPieces[7]);//7
                                                                                     
    ///////////////   ALFIL   //////////////////////////////    
    int alfil_left=2, alfil_right=5;
    Alfil AW1(alfil_left, row_seven, general), AW2(alfil_right, row_seven, general);
    sf::Sprite alfil_white1=AW1.init(general,textPieces[4]);//27
    sf::Sprite alfil_white2=AW2.init(general,textPieces[4]);//30

    Alfil AB1(alfil_left, row_zero, general), AB2(alfil_right, row_zero, general);
    sf::Sprite alfil_black1=AB1.init(general,textPieces[5]);//3
    sf::Sprite alfil_black2=AB2.init(general,textPieces[5]);//6
    
    ///////////////  TORRES   ///////////////////////////////
    int tower_left=0, tower_right=7;
    Tower TW1(tower_left, row_seven, general), TW2(tower_right, row_seven, general);
    sf::Sprite tower_white1=TW1.init(general,textPieces[2]);//25
    sf::Sprite tower_white2=TW2.init(general,textPieces[2]);//32

    Tower TB1(tower_left, row_zero, general), TB2(tower_right, row_zero, general);
    sf::Sprite tower_black1=TB1.init(general,textPieces[3]);//1
    sf::Sprite tower_black2=TB2.init(general,textPieces[3]);//8

    ///////////////   PEONES   //////////////////////////////
    std::vector<Peon> PBs, PWs;

    std::vector<sf::Sprite> teamBlack;
    std::vector<sf::Sprite> teamWhite;

    for(int i=0; i<8; i++){
        Peon PB(i,1, general); //9 hasta -> 16
        PBs.push_back(PB);
        sf::Sprite peonBlack=PB.init(general,textPieces[0]); //todos en la fila 1 EQUIPO NEGRO
        teamBlack.push_back(peonBlack);

        Peon PW(i,6, general); //17 hasta -> 24
        PWs.push_back(PW);
        sf::Sprite peonWhite=PW.init(general,textPieces[1]); //EQUIPO BLANCO FILA 6
        teamWhite.push_back(peonWhite);
    }

    //--------------------ZONA TEXT-------------------------
    sf::Font font;
    if(!font.openFromFile("arial.ttf")) std::cerr<<"No se pudo cargar el archivo\n";

    //......................................................
    int col, row;
    bool _eva=false;

    //---------SE CREA EL TABLERO SOLO UNA VEZ!!!------------------!!!!
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if((i+j)%2==0) w.CreateBottom(window, j, i, sf::Color::White);
            else w.CreateBottom(window, j, i, sf::Color(0, 100, 0));
        }
    }

    while(window.isOpen()){
        while(const std::optional event=window.pollEvent()){
            if(event->is<sf::Event::Closed>()) window.close();
            if(event->is<sf::Event::MouseButtonPressed>()){
                if(event->getIf<sf::Event::MouseButtonPressed>()->button==sf::Mouse::Button::Left){
                    dragging=true;
                    lastMouse=sf::Mouse::getPosition(window);
                }
            }
            if(event->is<sf::Event::MouseButtonReleased>()){
                if(event->getIf<sf::Event::MouseButtonReleased>()->button==sf::Mouse::Button::Left){
                    dragging=false;
                }
            }
            if(const auto* mouseButtonPressed=event->getIf<sf::Event::MouseButtonPressed>()){
                if(mouseButtonPressed->button == sf::Mouse::Button::Left){
                    col=mouseButtonPressed->position.x;
                    row=mouseButtonPressed->position.y;

                    _eva=general.evaluate(col,row);

                    if(_eva){
                        infoGeneral(col,row,_eva,general);
                        whatPiecesWasSelected(window, general,KW1,KB1,QW1,QB1,CW1,CW2,CB1,CB2,
                                  AW1,AW2,AB1,AB2,TW1,TW2,TB1,TB2,
                                  PBs,PWs
                        ); //pieza seleccionada, calculo de los cuadros que puede moverse
                        //infoGeneral(col,row,_eva,general);
                    }
                } 
            }
        } 

        window.clear();
        //cajasDelMapa.clear();

        //////////////////    TABLERO      /////////////////////
        /*for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                if((i+j)%2==0) w.CreateBottom(window, j, i, sf::Color::White);
                else w.CreateBottom(window, j, i, sf::Color(0, 100, 0));
            }
        }*/
        for(auto& x: cajasDelMapa){
            window.draw(x.box);
        }

        //drawingVectors(window, teamBlack, teamWhite);
        /////////////////   DIBUJADO DE PEONES EQUIPO NEGRO //////
        for(int i=0; i<8; i++){
            window.draw(teamBlack[i]);
            window.draw(teamWhite[i]);
        }
        ///////////////// DIBUJADO DE TORRES ////////////////
        window.draw(tower_white1);
        window.draw(tower_white2);

        window.draw(tower_black1);
        window.draw(tower_black2);

        //////////////// DIBUJADO DE ALFILES  //////////////
        window.draw(alfil_white1);
        window.draw(alfil_white2);

        window.draw(alfil_black1);
        window.draw(alfil_black2);

        //////////////// DIBUJADO DE CABALLOS  ////////////////
        window.draw(caballo_white1);
        window.draw(caballo_white2);

        window.draw(caballo_black1);
        window.draw(caballo_black2);

        //////////////// DIBUJADO DE REINAS   ///////////////
        window.draw(queen_black1);
        window.draw(queen_white1);

        ////////////////  DIBUJADO DE REYES   ///////////////
        window.draw(king_black1);
        window.draw(king_white1);

        window.display();
    }
}

int main(){

    execute();

    return 0;
}
