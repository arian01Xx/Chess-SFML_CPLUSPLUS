#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <vector>

constexpr int TILE=6;
constexpr int CELL=TILE*10;

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
    sf::Sprite init(sf::Texture& texture, int& j, int i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        sf::Sprite peonBlack(texture);

        sf::Vector2u sizePeon=texture.getSize();

        float scaleX=static_cast<float>(CELL)/sizePeon.x;
        float scaleY=static_cast<float>(CELL)/sizePeon.y;

        peonBlack.setScale({scaleX, scaleY});
        peonBlack.setPosition(sf::Vector2f(250+CELL*j, 150+CELL*i)); //COLUMNA 4 FILA 0

        return peonBlack;
    } 
};

struct PeonWhite{
    sf::Sprite init(sf::Texture& texture, int& j, int i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        sf::Sprite peonWhite(texture);

        sf::Vector2u sizePeon=texture.getSize();

        float scaleX=static_cast<float>(CELL)/sizePeon.x;
        float scaleY=static_cast<float>(CELL)/sizePeon.y;

        peonWhite.setScale({scaleX, scaleY});
        peonWhite.setPosition(sf::Vector2f(250+CELL*j, 150+CELL*i)); //COLUMNA 4 FILA 0

        return peonWhite;
    }
};

struct Tower{
    sf::Sprite init(sf::Texture& texture, int& j, int i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        sf::Sprite tower(texture);

        sf::Vector2u sizeTower=texture.getSize();

        float scaleX=static_cast<float>(CELL)/sizeTower.x;
        float scaleY=static_cast<float>(CELL)/sizeTower.y;

        tower.setScale({scaleX, scaleY});
        tower.setPosition(sf::Vector2f(250+CELL*j, 150+CELL*i)); //COLUMNA 4 FILA 0

        return tower;
    }
};

struct Alfil{
    sf::Sprite init(sf::Texture& texture, int& j, int i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        sf::Sprite alfil(texture);

        sf::Vector2u sizeAlfil=texture.getSize();

        float scaleX=static_cast<float>(CELL)/sizeAlfil.x;
        float scaleY=static_cast<float>(CELL)/sizeAlfil.y;

        alfil.setScale({scaleX, scaleY});
        alfil.setPosition(sf::Vector2f(250+CELL*j, 150+CELL*i)); //COLUMNA 4 FILA 0

        return alfil;
    }
};

struct Caballo{
    sf::Sprite init(sf::Texture& texture, int& j, int i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        sf::Sprite caballo(texture);

        sf::Vector2u sizeCaballo=texture.getSize();

        float scaleX=static_cast<float>(CELL)/sizeCaballo.x;
        float scaleY=static_cast<float>(CELL)/sizeCaballo.y;

        caballo.setScale({scaleX, scaleY});
        caballo.setPosition(sf::Vector2f(250+CELL*j, 150+CELL*i)); //COLUMNA 4 FILA 0

        return caballo;
    }
};

struct Queen{
    sf::Sprite init(sf::Texture& texture, int& j, int i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        sf::Sprite queen(texture);

        sf::Vector2u sizeQueen=texture.getSize();

        float scaleX=static_cast<float>(CELL)/sizeQueen.x;
        float scaleY=static_cast<float>(CELL)/sizeQueen.y;

        queen.setScale({scaleX, scaleY});
        queen.setPosition(sf::Vector2f(250+CELL*j, 150+CELL*i)); //COLUMNA 4 FILA 0

        return queen;
    }
};

struct King{
    sf::Sprite init(sf::Texture& texture, int& j, int i){ //NO OLVIDES LA REFERENCIA PARA QUE APAREZCAN LOS CAMBIOS!!
        sf::Sprite queen(texture);

        sf::Vector2u sizeQueen=texture.getSize();

        float scaleX=static_cast<float>(CELL)/sizeQueen.x;
        float scaleY=static_cast<float>(CELL)/sizeQueen.y;

        queen.setScale({scaleX, scaleY});
        queen.setPosition(sf::Vector2f(250+CELL*j, 150+CELL*i)); //COLUMNA 4 FILA 0

        return queen;
    }
};

void execute(){

    World w;

    sf::RenderWindow window{
        sf::VideoMode({
                static_cast<unsigned>(TILE*w.col), //COLUMNAS
                static_cast<unsigned>(TILE*w.row) //FILAS
                }), "CHESS"
    };

    window.setFramerateLimit(50);

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
    ////////////////// REY  ////////////////////////////////
    King KW1, KB1; int king_pos=4;
    sf::Sprite king_white1=KW1.init(rey_white,king_pos,7);
    sf::Sprite king_black1=KB1.init(rey_black,king_pos,0);

    /////////////////// REINA ///////////////////////////////
    Queen QB1, QW1; int queen_pos=3;
    sf::Sprite queen_black1=QB1.init(reina_black,queen_pos,0);
    sf::Sprite queen_white1=QW1.init(reina_white,queen_pos,7);

    ////////////////// CABALLO /////////////////////////////
    Caballo CW1, CW2; int caballo_left=1, caballo_right=6;
    sf::Sprite caballo_white1=CW1.init(caballo_white,caballo_left,7);
    sf::Sprite caballo_white2=CW2.init(caballo_white,caballo_right,7);

    Caballo CB1, CB2;
    sf::Sprite caballo_black1=CB1.init(caballo_black,caballo_left,0);
    sf::Sprite caballo_black2=CB2.init(caballo_black,caballo_right,0);

    ///////////////   ALFIL   //////////////////////////////    
    Alfil AW1, AW2; int alfil_left=2, alfil_right=5;
    sf::Sprite alfil_white1=AW1.init(alfil_white,alfil_left,7);
    sf::Sprite alfil_white2=AW2.init(alfil_white,alfil_right,7);

    Alfil AB1, AB2;
    sf::Sprite alfil_black1=AB1.init(alfil_black,alfil_left,0);
    sf::Sprite alfil_black2=AB2.init(alfil_black,alfil_right,0);
    
    ///////////////  TORRES   ///////////////////////////////
    Tower TW1, TW2; int tower_left=0, tower_right=7;
    sf::Sprite tower_white1=TW1.init(tower_white,tower_left,7);
    sf::Sprite tower_white2=TW2.init(tower_white,tower_right,7);

    Tower TB1, TB2;
    sf::Sprite tower_black1=TB1.init(tower_black,tower_left,0);
    sf::Sprite tower_black2=TB2.init(tower_black,tower_right,0);

    ///////////////   PEONES   //////////////////////////////
    std::vector<sf::Sprite> teamBlack;
    std::vector<sf::Sprite> teamWhite;

    for(int i=0; i<8; i++){
        PeonBlack PB;
        sf::Sprite peonBlack=PB.init(texture,i,1); //todos en la fila 1 EQUIPO NEGRO
        teamBlack.push_back(peonBlack);

        PeonWhite PW;
        sf::Sprite peonWhite=PW.init(peon_white_text,i,6);
        teamWhite.push_back(peonWhite);
    }
    ////////////////////////////////////////////////////////////

    while(window.isOpen()){
        while(const std::optional event=window.pollEvent()){
            if(event->is<sf::Event::Closed>()) window.close();
        }

        window.clear();

        //////////////////    TABLERO      /////////////////////
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                if((i+j)%2==0) w.CreateBottom(window, j, i, sf::Color::White);
                else w.CreateBottom(window, j, i, sf::Color(0, 100, 0));
            }
        }
        ///////////////////////////////////////////////////////
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

        /*w.CreateBottom(window, 10, 10);
        w.CreateBottom(window, 21, 10); //se pone al costado, por ser columnas
        w.CreateBottom(window, 10, 21); //deberia ponerse abajo*/

        window.display();
    }
}

int main(){

    execute();

    return 0;
}
