#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility> 
#include <cstdlib>
#include <vector>
#include <string>

constexpr int TILE=6;
constexpr int CELL=TILE*10;

int _x, _y; //copia de la coordenada clickeada
int x_1, y_1; //coordenadas de la pieza encontrada (solo para verificar que en serio coinciden)
std::string pieceSelected; //utilizar esto para reconocer pieza seleccionada 
std::vector<int> _coords; //ESTO CREO QUE NO LO UTILIZAMOS
bool turnWhite=true; //empiezan las blancas siempre!

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
        window.draw(bottom);
    }
};

struct Peon{
    int y, x; //es porque los parametros de texture estan al reves, i es columna y j fila, no como la matriz clasica[fila][columna]
    Peon(int _y, int _x): y(_y), x(_x){}

    sf::Sprite init(General& general, sf::Texture& texture, int& i, int j){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!! 
        return general.init(texture,i,j);
    }

    void changeCoords(int& new_x, int& new_y){
        x=new_x;
        y=new_y;
    }

    void executeMove(){
        std::cout<<"working yet"<<std::endl;
    }
};

struct Tower{ //COLUMNA 4 FILA 0
    int x, y;
    Tower(int _x, int _y): x(_x), y(_y){}

    void changeCoords(int& new_x, int& new_y){
        x=new_x;
        y=new_y;
    }

    sf::Sprite init(General& general, sf::Texture& texture, int& j, int& i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        return general.init(texture,j,i);
    }
};

struct Alfil{
    int x, y;
    Alfil(int _x, int _y): x(_x), y(_y){}

    void changeCoords(int& new_x, int& new_y){
        x=new_x;
        y=new_y;
    }

    sf::Sprite init(General& general,sf::Texture& texture, int& j, int& i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        return general.init(texture,j,i);
    }
};

struct Caballo{
    int x, y;
    Caballo(int _x, int _y): x(_x), y(_y){}

    void changeCoords(int& new_x, int& new_y){
        x=new_x;
        y=new_y;
    }

    sf::Sprite init(General& general,sf::Texture& texture, int& j, int& i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        return general.init(texture,j,i);
    }
};

struct Queen{
    int x, y;
    Queen(int _x, int _y): x(_x), y(_y){}

    void changeCoords(int& new_x, int& new_y){
        x=new_x;
        y=new_y;
    }

    sf::Sprite init(General& general,sf::Texture& texture, int& j, int& i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        return general.init(texture,j,i);
    }
};

struct King{
    int x, y;
    King(int _x, int _y): x(_x), y(_y){}

    void changeCoords(int& new_x, int& new_y){
        x=new_x;
        y=new_y;
    }

    sf::Sprite init(General& general,sf::Texture& texture, int& j, int& i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        return general.init(texture,j,i);
    }
};

void evaluate(General& general, King& king, Queen& queen, Caballo& caballo1, Caballo& caballo2, 
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
                std::cout<<"CONGRATULATIONS! "<<std::endl;
                x_1=p.x;
                y_1=p.y;
                std::cout<<"_x: "<<_x<<" - p.x: "<<p.x<<std::endl;
                std::cout<<"_y: "<<_y<<" - p.y: "<<p.y<<std::endl;
                std::cout<<"x_1: "<<x_1<<std::endl;
                std::cout<<"y_1: "<<y_1<<std::endl;
                p.executeMove(); //funcion void que redibujarà el mapa, creo que se le pasaràn muchos parametros
            }else{
                std::cout<<"*************************"<<std::endl;
                std::cout<<"ERROR! "<<std::endl; 
                std::cout<<"_x: "<<_x<<" - p.x: "<<p.x<<std::endl;
                std::cout<<"_y: "<<_y<<" - p.y: "<<p.y<<std::endl;
                std::cout<<"x_1: "<<x_1<<std::endl;
                std::cout<<"y_1: "<<y_1<<std::endl;
            }
        }
    }else if(general.map[_x][_y]==2){

    }else if(general.map[_x][_y]==3){

    }else if(general.map[_x][_y]==4){

    }else if(general.map[_x][_y]==5){

    }else if(general.map[_x][_y]==6){

    }
}

void whatPiecesWasSelected(General& general, King& kingW1, King& kingB1, Queen& queenW1, Queen& queenB1, 
                           Caballo& caballoW1, Caballo& caballoW2, Caballo& caballoB1,
                           Caballo& caballoB2, Alfil& alfilW1, Alfil& alfilW2, 
                           Alfil& alfilB1, Alfil& alfilB2, Tower& towerW1, Tower& towerW2,
                           Tower& towerB1, Tower& towerB2, 
                           std::vector<Peon>& PeonBs,
                           std::vector<Peon>& PeonWs){
    if(turnWhite){
        turnWhite=false;
        evaluate(general, kingW1, queenW1, caballoW1, caballoW2, alfilW1, alfilW2, towerW1, towerW2, PeonWs);
        //turnWhite=false;
    }else{
        turnWhite=true;
        evaluate(general, kingB1, queenB1, caballoB1, caballoB2, alfilB1, alfilB2, towerB1, towerB2, PeonBs);
        //turnWhite=true;
    }
}

void infoGeneral(int& col, int& row, bool& evaluate, General& general){
    general._pieceSelected();
    _coords=general.coords(col, row); //vector en datos generales

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
    if(turnWhite) std::cout<<"WHITE TURN!"<<std::endl;
    else std::cout<<"BLACK TURN!"<<std::endl;
    std::cout<<"----------------------------------------"<<std::endl;
    std::cout<<"COORD FOUND IT!: "<<x_1<<"-"<<y_1<<std::endl;
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
    King KW1(king_pos, row_seven), KB1(king_pos, row_zero);
    sf::Sprite king_white1=KW1.init(general,textPieces[10],king_pos,row_seven); //29
    sf::Sprite king_black1=KB1.init(general,textPieces[11],king_pos,row_zero); //5
    
    /////////////////// REINA ///////////////////////////////
    int queen_pos=3;
    Queen QB1(queen_pos, row_zero), QW1(queen_pos, row_seven);
    sf::Sprite queen_black1=QB1.init(general,textPieces[9],queen_pos,row_zero);//4
    sf::Sprite queen_white1=QW1.init(general,textPieces[8],queen_pos,row_seven);//28
    
    ////////////////// CABALLO /////////////////////////////
    int caballo_left=1, caballo_right=6;
    Caballo CW1(caballo_left, row_seven), CW2(caballo_right, row_seven); 
    sf::Sprite caballo_white1=CW1.init(general,textPieces[6],caballo_left,row_seven);//26
    sf::Sprite caballo_white2=CW2.init(general,textPieces[6],caballo_right,row_seven);//31

    Caballo CB1(caballo_left, row_zero), CB2(caballo_right, row_zero);
    sf::Sprite caballo_black1=CB1.init(general,textPieces[7],caballo_left,row_zero);//2
    sf::Sprite caballo_black2=CB2.init(general,textPieces[7],caballo_right,row_zero);//7
                                                                                     
    ///////////////   ALFIL   //////////////////////////////    
    int alfil_left=2, alfil_right=5;
    Alfil AW1(alfil_left, row_seven), AW2(alfil_right, row_seven);
    sf::Sprite alfil_white1=AW1.init(general,textPieces[4],alfil_left,row_seven);//27
    sf::Sprite alfil_white2=AW2.init(general,textPieces[4],alfil_right,row_seven);//30

    Alfil AB1(alfil_left, row_zero), AB2(alfil_right, row_zero);
    sf::Sprite alfil_black1=AB1.init(general,textPieces[5],alfil_left,row_zero);//3
    sf::Sprite alfil_black2=AB2.init(general,textPieces[5],alfil_right,row_zero);//6
    
    ///////////////  TORRES   ///////////////////////////////
    int tower_left=0, tower_right=7;
    Tower TW1(tower_left, row_seven), TW2(tower_right, row_seven);
    sf::Sprite tower_white1=TW1.init(general,textPieces[2],tower_left,row_seven);//25
    sf::Sprite tower_white2=TW2.init(general,textPieces[2],tower_right,row_seven);//32

    Tower TB1(tower_left, row_zero), TB2(tower_right, row_zero);
    sf::Sprite tower_black1=TB1.init(general,textPieces[3],tower_left,row_zero);//1
    sf::Sprite tower_black2=TB2.init(general,textPieces[3],tower_right,row_zero);//8

    ///////////////   PEONES   //////////////////////////////
    std::vector<Peon> PBs, PWs;

    std::vector<sf::Sprite> teamBlack;
    std::vector<sf::Sprite> teamWhite;

    for(int i=0; i<8; i++){
        Peon PB(i,1); //9 hasta -> 16
        PBs.push_back(PB);
        sf::Sprite peonBlack=PB.init(general,textPieces[0],i,1); //todos en la fila 1 EQUIPO NEGRO
        teamBlack.push_back(peonBlack);

        Peon PW(i,6); //17 hasta -> 24
        PWs.push_back(PW);
        sf::Sprite peonWhite=PW.init(general,textPieces[1],i,6); //EQUIPO BLANCO FILA 6
        teamWhite.push_back(peonWhite);
    }

    //--------------------ZONA TEXT-------------------------
    sf::Font font;
    if(!font.openFromFile("arial.ttf")) std::cerr<<"No se pudo cargar el archivo\n";

    //......................................................
    int col, row;
    bool _eva=false;

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
                col=mouseButtonPressed->position.x;
                row=mouseButtonPressed->position.y;

                _eva=general.evaluate(col,row);
            }
        }

        if(dragging){
            infoGeneral(col,row,_eva,general); //se imprimen coordenadas etc...
            whatPiecesWasSelected(general,KW1,KB1,QW1,QB1,CW1,CW2,CB1,CB2,
                                  AW1,AW2,AB1,AB2,TW1,TW2,TB1,TB2,
                                  PBs,PWs); //pieza seleccionada, calculo de los cuadros que puede moverse
        }

        window.clear();

        //////////////////    TABLERO      /////////////////////
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                if((i+j)%2==0) w.CreateBottom(window, j, i, sf::Color::White);
                else w.CreateBottom(window, j, i, sf::Color(0, 100, 0));
            }
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
