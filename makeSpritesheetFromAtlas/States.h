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
    
    // localização x do estado no spritesheet
    float spritesheetX;
    
    // localização y do estado no spritesheet
    float spritesheetY;
    
    // largura de cada sprite no estado
    float widthSprites;
    
    // altura de cada sprite no estado
    float heightSprites;
    
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
    
    // guarda a imagem com todos os sprites de todos os estados
    ALLEGRO_BITMAP* spritesheet;
    
    // lista de estados
    // veja as structs stateNode e spriteNode
    list<stateNode> states;
    
    public:
    
    // construtor padrão
    // spritesheet aponta para NULL
    StatesClass();
    
    // destrutor
    // Destrói spritesheet se este for não nulo
    ~StatesClass();
    
    // Função que adiciona uma imagem para spritesheet
    // Se spritesheet apontar para NULL, spritesheet apontará para imagem.
    // Se spritesheet apontar para uma imagem, destrói essa imagem e o faz apontar
    // para uma nova imagem.
    void addSpritesheet(ALLEGRO_BITMAP* image);
    
    // adiciona um estado
    //
    // PARÂMETROS:
    // stateName : nome do estado
    // nsprites : quantidade de sprites do estado
    // spritesheetX : a localização x do conjunto de sprites do estado no spritesheet
    // spritesheetY : a localização y do conjunto de sprites do estado no spritesheet
    // widthSprites: a largura de cada sprite do estado
    // heightSprites: a altura de cada sprite do estado
    // effect : valor que indica o sprite inicial para algum efeito (0 se não há efeito)
    void addState(const char* stateName, int nsprites, float spritesheetX, float spritesheetY,
                    float widthSprites, float heightSprites, int effect);
    
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
    void addSpriteToState(const char* stateName, int frames, float squareBeginX,
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
    // retorna -1 se não encontrar o valor
    // retorna -2 se estado não existir
    //
    // PARÂMETROS:
    // stateName : nome do estado em que se busca a informação
    // valueName : nome da informação buscada
    //
    // VALORES de valueName:
    // "nsprites","spritesheetX","spritesheetY","widthSprites","heightSprites" ou "effect"
    float getStV(const char* stateName, const char* valueName);
    
    // get Sprite Value
    // retorna o valor de uma característica de um sprite de um estado
    // retorna -2 se não encontrar o valor
    // retorna -3 se o estado não existir
    //
    // PARÂMETROS
    // stateName : nome do estado em que se busca a informação
    // spriteIndex : o índice do sprite desse estado (a partir de 0)
    // valueName : o nome da característica procurada
    //
    // VALORES de valueName:
    // "frames", "squareBeginX", "squareBeginY", "squareEndX", "squareEndY"
    float getSpV(const char* stateName, int spriteIndex,const char* valueName);
    
    // desenha o spritesheet inteiro
    //
    // PARÂMETROS:
    // posX: posição x em que desenhará o spritesheet
    // posY: posição~y em que desenhará o spritesheet
    // option : permite inverter horizontalmente ou verticalmente (0 se nenhum dos dois)
    //
    // VALORES de option:
    // 0 : nenhuma inversão
    // ALLEGRO_FLIP_HORIZONTAL : inverte o bitmap com base no eixo y
    // ALLEGRO_FLIP_VERTICAL : inverte o bitmap com base no eixo x
    void drawSpritesheet(float posX, float posY, int option);
    
    // versão de drawSpritesheet com option = 0
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
