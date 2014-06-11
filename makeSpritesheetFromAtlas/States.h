#ifndef STATES_H
#define STATES_H

/** //////////////////////////////////////////////////////////////////////////
Módulo que descreve os estados de sprites, a ser usado por entidades tais como
player e enemy

Leia o arquivo makeSpritesheetFromAtlas.md para mais detalhes
//////////////////////////////////////////////////////////////////////////*/

// inclusão da biblioteca allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
// inclusão das bibliotecas básicas
#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

// estrutura que contém as características de cada sprite
struct spriteNode{
    
    float spritesheetX;
    float spritesheetY;
    float width;
    float height;
    
    // quantidade de frames que o sprite executa
    // quando há apenas um sprite em um estado, esse valor não é usado
    int frames;
    
    // definição de um quadrado no sprite (para definir onde está a espada, por
    // exemplo). Se -1 em qualquer dos valores abaixos, não há quadrado
    //
    // coordenada x do ponto inicial de um quadrado
    float squareBeginX;
    // coordenada y do ponto inicial de um quadrado
    float squareBeginY;
    // coordenada x do ponto final de um quadrado
    float squareEndX;
    // coordenada y do ponto final de um quadrado
    float squareEndY;
};

// estrutura que contém as características de um estado
struct stateNode{
    
    // nome do estado, concatenado com a direção (por exemplo, "walkL")
    string stateName;
    
    // quantidade de sprites do estado
    int nsprites;
    
    // valor que indica o sprite inicial de algum efeito (como um raio)
    // se 0 (zero), então não há efeito
    int effect;
    
    // vetor de sprites (vetor possui índice)
    vector<spriteNode> sprites;
};

/**
//=======================================================================
// Classe StatesClass
//=======================================================================
// Classe que contém todos os estados e suas características, além
// de funções de manipulação dessas características.
//=======================================================================
*/
class StatesClass{
    
    private:
    
    ALLEGRO_BITMAP* spritesheet;
    
    // lista de estados
    // veja as structs stateNode e spriteNode
    list<stateNode> states;
    
    public:
    
    // construtor padrão
    StatesClass();
    
    // destrutor
    ~StatesClass();
    
    void addSpritesheet(ALLEGRO_BITMAP* image);
    
    // adiciona um estado
    //
    // PARÂMETROS:
    // stateName : nome do estado
    // nsprites : quantidade de sprites do estado
    // effect : valor que indica o sprite inicial para algum efeito (0 se não há efeito)
    // image : bitmap com todos os sprites do estado
    // 
    // obs : um estado pode ser tratado como dois se possui duas direções. por exemplo, temos
    // o estado "walk", mas esse estado tem esquerda e direita. Logo, temos os estados "walkL"
    // e "walkR", ou seja, dois estados ao invés de um. Porém, o Allegro possui funções que
    // permitem espelhar uma imagem verticalmente, então você só precisa de um estado "walk".
    // leve isso em consideração quando for definir o nome do estado.
    void addState(const char* stateName, int nsprites, int effect);
    
    // adiciona todos os sprites para o state já criado
    //
    // PARÂMETROS:
    // stateName : nome do estado
    // frames : ponteiro que aponta para o início de um array de inteiros, representando
    //          a quantidade de frames que o sprite dura
    // squareBeginX : ponteiro que aponta para o início de um array de floats, representando
    //                a coordenada x do ponto inicial de um quadrado (-1 se não há quadrado)
    // squareBeginY : ponteiro que aponta para o início de um array de floats, representando
    //                a coordenada y do ponto inicial de um quadrado (-1 se não há quadrado)
    // squareEndX : ponteiro que aponta para o início de um array de floats, representando
    //              a coordenada x do ponto final de um quadrado (-1 se não há quadrado)
    // squareEndY : ponteiro que aponta para o início de um array de floats, representando
    //              a coordenada y do ponto final de um quadrado (-1 se não há quadrado)
    //
    // obs : os arrays devem ter uma quantidade de elementos igual a quantidade
    // de sprites do estado
    void addSpriteToState(const char* stateName,float spritesheetX, float spritesheetY,float width,
                            float height, int frames, float squareBeginX,
                            float squareBeginY, float squareEndX, float squareEndY);
    
    // pega um vetor de strings, o apaga (se houver algo) e o preenche com
    // os nomes dos states do objeto
    //
    // PARÂMETROS:
    // names : vetor de strings a ser modificado
    //
    // obs: o objetivo dessa função é obter a lista de estados do objeto desta classe,
    // e fazer o que for necessário com essa lista
    void getStateNames(vector<string> &names);
    
    // get State Value
    // retorna o valor de uma característica de um estado
    //
    // PARÂMETROS:
    // stateName : nome do estado em que se busca a informação
    // valueName : nome da informação buscada
    //
    // VALORES de valueName:
    // "nsprites" ou "effect"
    int getStV(const char* stateName, const char* valueName);
    
    // get Sprite Value
    // retorna o valor de uma característica de um sprite de um estado
    //
    // PARÂMETROS
    // stateName : nome do estado em que se busca a informação
    // spriteIndex : o índice do sprite desse estado (a partir de 0)
    // valueName : o nome da característica procurada
    //
    // VALORES de valueName:
    // "width","height","frames", "squareBeginX", "squareBeginY", "squareEndX", "squareEndY"
    int getSpV(const char* stateName, int spriteIndex,const char* valueName);
    
    void drawSpritesheet(float posX, float posY, int option);
    
    void drawSpritesheet(float posX, float posY);
    
    // desenha todo o conjunto de sprites de um state
    //
    // PARÂMETROS:
    // stateName : nome do estado que quer desenhar
    // posX : posição x em que deseja desenhar
    // posY : posição y em que deseja desenhar
    // option : permite inverter horizontalmente ou verticalmente (0 se nenhum dos dois)
    //
    // VALORES de option:
    // 0 : nenhuma inversão
    // ALLEGRO_FLIP_HORIZONTAL : inverte o bitmap com base no eixo y
    // ALLEGRO_FLIP_VERTICAL : inverte o bitmap com base no eixo x
    void drawState(const char* stateName, float posX, float posY, int option);
    
    // versão de drawState com option = 0
    void drawState(const char* stateName, float posX, float posY);
    
    // desenha um sprite de um state
    //
    // PARÂMETROS:
    // stateName : nome do estado que possui o sprite desejado
    // spriteIndex : índice do sprite (a partir de 0)
    // posX : posição x em que deseja desenhar
    // posY : posição y em que deseja desenhar
    // option : permite inverter horizontalmente ou verticalmente (0 se nenhum dos dois)
    //
    // VALORES de option:
    // 0 : nenhuma inversão
    // ALLEGRO_FLIP_HORIZONTAL : inverte o bitmap com base no eixo y
    // ALLEGRO_FLIP_VERTICAL : inverte o bitmap com base no eixo x
    void drawSprite(const char* stateName, int spriteIndex, float posX, float posY, int option);
    
    // versão de drawSprite com option = 0
    void drawSprite(const char* stateName, int spriteIndex, float posX, float posY);
};

#endif// STATES_H
