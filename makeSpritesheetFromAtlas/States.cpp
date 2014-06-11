#include "States.h"

//===================================================================
// Funções Auxiliares
//===================================================================

bool searchState(list<stateNode> &states,const char* stateName,
                                        list<stateNode>::iterator &pointer){
    
    bool sucess = false;
    
    for(pointer=states.begin(); pointer!= states.end(); pointer++){
        
        if(pointer->stateName.compare(stateName) == 0){
            sucess = true;
            break;
        }
    }
    
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
void StatesClass::addState(const char* stateName, int nsprites, int effect){
    
    // declara uma nova estrutura de estado e preenche seus valores
    stateNode state;
    state.stateName.assign(stateName);
    state.nsprites = nsprites;
    state.effect = effect;
    
    // adiciona esse estado em states
    states.push_back(state);
}

void StatesClass::addSpriteToState(const char* stateName,float spritesheetX, float spritesheetY,float width,
                            float height, int frames, float squareBeginX,
                            float squareBeginY, float squareEndX, float squareEndY){
    
    // procura pelo estado correto
    // declara iterator
    list<stateNode>::iterator pointer;
    
    if(!searchState(states,stateName,pointer))return;
    
    // cria uma nova estrutura de spriteNode e associa os valores da função
    spriteNode sprite;
    
    sprite.spritesheetX = spritesheetX;
    sprite.spritesheetY = spritesheetY;
    sprite.width = width;
    sprite.height = height;
    sprite.frames = frames;
    sprite.squareBeginX = squareBeginX;
    sprite.squareBeginY = squareBeginY;
    sprite.squareEndX = squareEndX;
    sprite.squareEndY = squareEndY;
    // adiciona um novo sprite a caracteristica sprites de states
    pointer->sprites.push_back(sprite);
    
}

void StatesClass::getStateNames(vector<string> &names){
    
    names.clear();
    
    list<stateNode>::iterator pointer;
    
    for(pointer=states.begin(); pointer!= states.end(); pointer++)
        names.push_back(pointer->stateName);
    
}

int StatesClass::getStV(const char* stateName, const char* valueName){
    
    list<stateNode>::iterator pointer;
    
    if(!searchState(states,stateName,pointer))return -1;
    
    string nameToCompare;
    nameToCompare.assign(valueName);
    
    if(nameToCompare.compare("nsprites")==0)
        return pointer->nsprites;
    else if(nameToCompare.compare("effect")==0)
        return pointer->effect;
    else
        return -1;
    
}

int StatesClass::getSpV(const char* stateName, int spriteIndex,const char* valueName){
    
    list<stateNode>::iterator pointer;
    
    if(!searchState(states,stateName,pointer))return -2;
    
    string nameToCompare;
    nameToCompare.assign(valueName);
    
    if(nameToCompare.compare("spritesheetX") == 0)
        return pointer->sprites[spriteIndex].spritesheetX;
    else if(nameToCompare.compare("spritesheetX") == 0)
        return pointer->sprites[spriteIndex].spritesheetY;
    else if(nameToCompare.compare("width") == 0)
        return pointer->sprites[spriteIndex].width;
    else if(nameToCompare.compare("height") == 0)
        return pointer->sprites[spriteIndex].height;
    else if(nameToCompare.compare("frames") == 0)
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

void StatesClass::drawSpritesheet(float posX, float posY){
    
    drawSpritesheet(posX,posY,0);
    
}

void StatesClass::drawSpritesheet(float posX, float posY, int option){
    
    al_draw_bitmap(spritesheet,posX,posY,option);
    
}

void StatesClass::drawState(const char* stateName, float posX, float posY){
    
    drawState(stateName,posX,posY,0);
    
}

void StatesClass::drawState(const char* stateName, float posX, float posY, int option){
    
    list<stateNode>::iterator pointer;
    
    if(!searchState(states,stateName,pointer))return;
    
    al_draw_bitmap_region(spritesheet,pointer->sprites[0].spritesheetX,pointer->sprites[0].spritesheetY,
    pointer->sprites[0].width * pointer->sprites.size(),pointer->sprites[0].height,posX,posY,option);
    
}

void StatesClass::drawSprite(const char* stateName, int spriteIndex, float posX, float posY){
    drawSprite(stateName,spriteIndex,posX,posY,0);
}

void StatesClass::drawSprite(const char* stateName, int spriteIndex, float posX, float posY,int option){
    
    list<stateNode>::iterator pointer;
    
    if(!searchState(states,stateName,pointer))return;
    
    al_draw_bitmap_region(spritesheet,pointer->sprites[0].spritesheetX,pointer->sprites[0].spritesheetY,
    pointer->sprites[0].width,pointer->sprites[0].height,posX,posY,option);
    
}
