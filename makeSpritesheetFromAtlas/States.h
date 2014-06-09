#ifndef STATES_H
#define STATES_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
using namespace std;

struct spriteNode{
    int frames;
    int squareBeginX;
    int squareBeginY;
    int squareEndX;
    int squareEndY;
};

struct stateNode{
    string stateName;
    int nsprites;
    int effect;
    vector<spriteNode> sprites;
    ALLEGRO_BITMAP* image;
};

class StatesClass{
    
    private:
    
    list<stateNode> states;
    
    vector<string> stateNames;
    
    public:
    
    StatesClass();
    
    ~StatesClass();
    
    void addState(const char* stateName, int nsprites, int effect, ALLEGRO_BITMAP* image);
    
    // adiciona todos os sprites para o state já criado
    //
    // PARÂMETROS:
    // frames : ponteiro que aponta para o início de um array de inteiros
    //
    // obs : os arrays devem ter uma quantidade de elementos igual a quantidade
    // de sprites do módulo
    void addSpritesToState(const char* stateName, int* frames, int* squareBeginX,
                            int* squareBeginY, int* squareEndX, int* squareEndY);
    
    // pega um vetor de strings, o apaga (se houver algo) e o preenche com
    // os nomes dos states do objeto
    void getStateNames(vector<string> &names);
    
    // get State Value
    int getStV(const char* stateName, const char* valueName);
    
    // get Sprite Value
    int getSpV(const char* stateName, int spriteIndex,const char* valueName);
    
    // desenha todo o conjunto de sprites de um state
    void drawState(const char* state);
    
    // desenha um sprite de um state
    void drawSprite(const char* stateName, int spriteIndex, int posX, int posY);
    
};

#endif// STATES_H
