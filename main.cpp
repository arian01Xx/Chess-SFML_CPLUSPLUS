#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <cstdlib>
#include <vector>

constexpr int TILE=6;
constexpr int CELL=TILE*10;

struct General{
    sf::Sprite init(sf::Texture& texture, int& j, int i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        sf::Sprite Piece(texture);

        sf::Vector2u sizePiece=texture.getSize();

        float scaleX=static_cast<float>(CELL)/sizePiece.x;
        float scaleY=static_cast<float>(CELL)/sizePiece.y;

        Piece.setScale({scaleX, scaleY});
        Piece.setPosition(sf::Vector2f(250+CELL*j, 150+CELL*i));

        return Piece;
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

struct PeonBlack{
    sf::Sprite init(General& general, sf::Texture& texture, int& j, int i){
        return general.init(texture,j,i);
    } 
};

struct PeonWhite{
    sf::Sprite init(General& general, sf::Texture& texture, int& j, int i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!! 
        return general.init(texture,j,i);
    }
};

struct Tower{ //COLUMNA 4 FILA 0
    sf::Sprite init(General& general, sf::Texture& texture, int& j, int& i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        return general.init(texture,j,i);
    }
};

struct Alfil{
    sf::Sprite init(General& general,sf::Texture& texture, int& j, int& i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        return general.init(texture,j,i);
    }
};

struct Caballo{
    sf::Sprite init(General& general,sf::Texture& texture, int& j, int& i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        return general.init(texture,j,i);
    }
};

struct Queen{
    sf::Sprite init(General& general,sf::Texture& texture, int& j, int& i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        return general.init(texture,j,i);
    }
};

struct King{
    sf::Sprite init(General& general,sf::Texture& texture, int& j, int& i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        return general.init(texture,j,i);
    }
};

void infoGeneral(int& col, int& row, bool& evaluate){
    std::system("clear");
    std::cout<<"INFO COLUMN: "<<col<<std::endl;
    std::cout<<"INFO ROW: "<<row<<std::endl;
    std::cout<<"INFO POSITION: "<<evaluate<<std::endl;
}

/*void infoPosition(bool evaluate){
    std::system("clear");
    std::cout<<"INFO POSITION: "<<evaluate<<std::endl;
}*/

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
    
    //_----------------------------------------------------_
    int row_zero=0; int row_seven=7;
    
    ////////////////// REY  ////////////////////////////////
    King KW1, KB1; int king_pos=4;
    sf::Sprite king_white1=KW1.init(general,textPieces[10],king_pos,row_seven);
    sf::Sprite king_black1=KB1.init(general,textPieces[11],king_pos,row_zero);

    /////////////////// REINA ///////////////////////////////
    Queen QB1, QW1; int queen_pos=3;
    sf::Sprite queen_black1=QB1.init(general,textPieces[9],queen_pos,row_zero);
    sf::Sprite queen_white1=QW1.init(general,textPieces[8],queen_pos,row_seven);

    ////////////////// CABALLO /////////////////////////////
    Caballo CW1, CW2; int caballo_left=1, caballo_right=6;
    sf::Sprite caballo_white1=CW1.init(general,textPieces[6],caballo_left,row_seven);
    sf::Sprite caballo_white2=CW2.init(general,textPieces[6],caballo_right,row_seven);

    Caballo CB1, CB2;
    sf::Sprite caballo_black1=CB1.init(general,textPieces[7],caballo_left,row_zero);
    sf::Sprite caballo_black2=CB2.init(general,textPieces[7],caballo_right,row_zero);

    ///////////////   ALFIL   //////////////////////////////    
    Alfil AW1, AW2; int alfil_left=2, alfil_right=5;
    sf::Sprite alfil_white1=AW1.init(general,textPieces[4],alfil_left,row_seven);
    sf::Sprite alfil_white2=AW2.init(general,textPieces[4],alfil_right,row_seven);

    Alfil AB1, AB2;
    sf::Sprite alfil_black1=AB1.init(general,textPieces[5],alfil_left,row_zero);
    sf::Sprite alfil_black2=AB2.init(general,textPieces[5],alfil_right,row_zero);
    
    ///////////////  TORRES   ///////////////////////////////
    Tower TW1, TW2; int tower_left=0, tower_right=7;
    sf::Sprite tower_white1=TW1.init(general,textPieces[2],tower_left,row_seven);
    sf::Sprite tower_white2=TW2.init(general,textPieces[2],tower_right,row_seven);

    Tower TB1, TB2;
    sf::Sprite tower_black1=TB1.init(general,textPieces[3],tower_left,row_zero);
    sf::Sprite tower_black2=TB2.init(general,textPieces[3],tower_right,row_zero);

    ///////////////   PEONES   //////////////////////////////
    std::vector<sf::Sprite> teamBlack;
    std::vector<sf::Sprite> teamWhite;

    for(int i=0; i<8; i++){
        PeonBlack PB;
        sf::Sprite peonBlack=PB.init(general,textPieces[0],i,1); //todos en la fila 1 EQUIPO NEGRO
        teamBlack.push_back(peonBlack);

        PeonWhite PW;
        sf::Sprite peonWhite=PW.init(general,textPieces[1],i,6);
        teamWhite.push_back(peonWhite);
    }

    //--------------------ZONA TEXT-------------------------
    sf::Font font;
    if(!font.openFromFile("arial.ttf")) std::cerr<<"No se pudo cargar el archivo\n";

    //std::vector<sf::Text> _coords=general.coords(font);
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
                //infoCoords(col,row); //aqui se imprimen las coordenadas en la terminal!
                                     //usar este numero
            }
        }

        if(dragging){
            //make stuff...
            //bool _eva=general.evaluate(col,row);
            
            infoGeneral(col,row,_eva);
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
