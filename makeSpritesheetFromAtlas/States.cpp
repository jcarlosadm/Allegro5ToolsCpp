#include "States.h"

//===================================================================
// Funções Auxiliares
//===================================================================

// Procura um estado na lista de estados
// returna true se encontrar, e false caso contrário
//
// PARÂMETROS:
// states: recebe o endereço da lista de estados
// stateName: string do nome do estado
// pointer: recebe o endereço do iterador para procurar na lista de estados
bool searchState(list<stateNode> &states,const char* stateName,
                                        list<stateNode>::iterator &pointer){
    
    // variável que controla se houve sucesso na procura
    bool sucess = false;
    
    // percorre states a procura de stateName
    for(pointer=states.begin(); pointer!= states.end(); pointer++){
        
        // se encontrou...
        if(pointer->stateName.compare(stateName) == 0){
            // obteve sucesso
            sucess = true;
            // sai do loop, e pointer estará no lugar correto
            break;
        }
    }
    
    // retorna true ou false
    return sucess;
}

//===================================================================
// Funções membros de StatesClass
//===================================================================

// construtor padrão
StatesClass::StatesClass(){
    spritesheet = NULL;
}

// destrutor
StatesClass::~StatesClass(){
    
    // desaloca o spritesheet
    if(spritesheet!=NULL)al_destroy_bitmap(spritesheet);
    spritesheet=NULL;
    
}

void StatesClass::addSpritesheet(ALLEGRO_BITMAP* image){
    
    if(spritesheet==NULL)spritesheet = image;
    else{
        al_destroy_bitmap(spritesheet);
        spritesheet = image;
    }
    
}

// adiciona um estado na lista states
void StatesClass::addState(const char* stateName, int nsprites, float spritesheetX,
                            float spritesheetY,float widthSprites, float heightSprites,
                            int effect){
    
    // declara uma nova estrutura de estado e preenche seus valores
    stateNode state;
    state.stateName.assign(stateName);
    state.nsprites = nsprites;
    state.spritesheetX = spritesheetX;
    state.spritesheetY = spritesheetY;
    state.widthSprites = widthSprites;
    state.heightSprites = heightSprites;
    state.effect = effect;
    
    // adiciona esse estado em states
    states.push_back(state);
}

// adiciona informações de um sprite para um estado já configurado
void StatesClass::addSpriteToState(const char* stateName, int frames, float squareBeginX,
                            float squareBeginY, float squareEndX, float squareEndY){
    
    // procura pelo estado correto
    // declara iterator
    list<stateNode>::iterator pointer;
    
    // se não encontrar o estado, retorna erro
    if(!searchState(states,stateName,pointer)){
        cout<< "estado nao existe!" <<endl;
        return;
    }
    
    // cria uma nova estrutura de spriteNode e associa os valores da função
    spriteNode sprite;
    
    sprite.frames = frames;
    sprite.squareBeginX = squareBeginX;
    sprite.squareBeginY = squareBeginY;
    sprite.squareEndX = squareEndX;
    sprite.squareEndY = squareEndY;
    
    // adiciona um novo sprite a caracteristica sprites de states
    pointer->sprites.push_back(sprite);
    
}

// pega um vetor de strings e o modifica para conter os nomes de todos
// os estados
void StatesClass::getStateNames(vector<string> &names){
    
    // limpa o vetor de strings
    names.clear();
    
    // declara um iterator
    list<stateNode>::iterator pointer;
    
    // percorre states, preenchendo names
    for(pointer=states.begin(); pointer!= states.end(); pointer++)
        names.push_back(pointer->stateName);
    
}

// obtem uma caracteristica de um estado
float StatesClass::getStV(const char* stateName, const char* valueName){
    
    // declara um iterator
    list<stateNode>::iterator pointer;
    
    // se não encontrar o estado, retorna -2
    if(!searchState(states,stateName,pointer))return -2;
    
    // declara uma string para igualar a valueName
    string nameToCompare;
    nameToCompare.assign(valueName);
    
    // compara nameToCompare com cada string de caracteristica
    // retorna -1 se a caracteristica não for encontrada
    if(nameToCompare.compare("nsprites")==0)
        return pointer->nsprites;
    else if(nameToCompare.compare("spritesheetX")==0)
        return pointer->spritesheetX;
    else if(nameToCompare.compare("spritesheetY")==0)
        return pointer->spritesheetY;
    else if(nameToCompare.compare("widthSprites")==0)
        return pointer->widthSprites;
    else if(nameToCompare.compare("heightSprites")==0)
        return pointer->heightSprites;
    else if(nameToCompare.compare("effect")==0)
        return pointer->effect;
    else
        return -1;
    
}

// retorna uma caracteristica de um sprite de um estado
float StatesClass::getSpV(const char* stateName, int spriteIndex,const char* valueName){
    
    // declara um iterator
    list<stateNode>::iterator pointer;
    
    // se não encontrar o estado, retorna -3
    if(!searchState(states,stateName,pointer))return -3;
    
    // declara variável string para guardar valueName
    string nameToCompare;
    nameToCompare.assign(valueName);
    
    // compara nameToCompare com a string da caracteristica procurada
    // retorna -2 se não encontrar
    if(nameToCompare.compare("frames") == 0)
        return pointer->sprites[spriteIndex].frames;
    else if(nameToCompare.compare("squareBeginX") == 0)
        return pointer->sprites[spriteIndex].squareBeginX;
    else if(nameToCompare.compare("squareBeginY") == 0)
        return pointer->sprites[spriteIndex].squareBeginY;
    else if(nameToCompare.compare("squareEndX") == 0)
        return pointer->sprites[spriteIndex].squareEndX;
    else if(nameToCompare.compare("squareEndY") == 0)
        return pointer->sprites[spriteIndex].squareEndY;
    else
        return -2;
    
}

// versão de drawSpritesheet com option = 0
void StatesClass::drawSpritesheet(float posX, float posY){
    
    drawSpritesheet(posX,posY,0);
    
}

// desenha spritesheet
void StatesClass::drawSpritesheet(float posX, float posY, int option){
    
    al_draw_bitmap(spritesheet,posX,posY,option);
    
}

// versão de drawState com option = 0
void StatesClass::drawState(const char* stateName, float posX, float posY){
    
    drawState(stateName,posX,posY,0);
    
}

// desenha sprites de um estado
void StatesClass::drawState(const char* stateName, float posX, float posY, int option){
    
    // declara iterator
    list<stateNode>::iterator pointer;
    
    // se o estado não for encontrado, retorna erro
    if(!searchState(states,stateName,pointer)){
        cout<< "estado nao encontrado" << endl;
    }
    
    // desenha estado
    al_draw_bitmap_region(spritesheet,pointer->spritesheetX,pointer->spritesheetY,
    pointer->widthSprites * pointer->nsprites, pointer->heightSprites,posX,posY,option);
    
}

// versão de drawSprite com option = 0
void StatesClass::drawSprite(const char* stateName, int spriteIndex, float posX, float posY){
    drawSprite(stateName,spriteIndex,posX,posY,0);
}

// desenha um sprite de um estado
void StatesClass::drawSprite(const char* stateName, int spriteIndex, float posX, float posY,int option){
    
    // declara iterator
    list<stateNode>::iterator pointer;
    
    // se não encontrar o estado, retorna erro
    if(!searchState(states,stateName,pointer)){
        
        cout<< "estado nao encontrado" <<endl;
        return;
    }
    
    // desenha sprite
    al_draw_bitmap_region(spritesheet,pointer->spritesheetX + pointer->widthSprites*spriteIndex,
    pointer->spritesheetY, pointer->widthSprites, pointer->heightSprites,posX,posY,option);
    
}
