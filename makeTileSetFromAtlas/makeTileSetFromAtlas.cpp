#include "makeTileSetFromAtlas.h"

//====================================================================
//   Funções auxiliares
//====================================================================

// procura por um tile no arquivo atlas
// retorna 1 se encontrar, 0 se não encontrar
int searchTile(Atlas* atlas,const char* tilesName){
    
    // configura o nome inicial do tile
    string nametile = tilesName;
    // adiciona o complemento básico no nome do tile
    nametile.append("001.png");
    
    // converte o tile para const char* e tentar configurar em atlas
    // se encontrar o tile básico, retorna 1
    if(atlas->setSpriteData(nametile.c_str()))
        return 1;
    // se não encontrar o tile básico, retorna 0
    else
        return 0;
}

//======================================================================
//   Funções membros de TileSet
//======================================================================

// contrutor padrão de TileSet
TileSet::TileSet(){
    
    // tileset aponta para NULL
    tileset = NULL;
}

// contrutor com argumentos
TileSet::TileSet(Atlas* atlas,const char* tilesName,
                        int numTilesTotal, int numTilesRow, int tilew, int tileh,
                        ALLEGRO_DISPLAY* window){
    
    // tileset aponta para NULL
    tileset = NULL;
    
    // tenta contruir o tileset
    buildTileset(atlas, tilesName, numTilesTotal, numTilesRow, tilew, tileh,
                    window);
}

// gera tileset manualmente
void TileSet::buildTileset(Atlas* atlas,const char* tilesName,
                        int numTilesTotal, int numTilesRow, int tilew, int tileh,
                        ALLEGRO_DISPLAY* window){
    
    //primeiro verifica se o ponteiro é diferente de NULL
    if(tileset != NULL){
        cout<<"Ponteiro nao nulo. Saindo."<<endl;
        return;
    }
    
    // Se o atlas não foi carregado, informa
    if(!atlas->is_open()){
        cout<<"arquivo de atlas nao esta aberto"<<endl;
        return;
    }
    
    // verifica se existe pelo menos um tile com a string fornecida no Atlas
    if(!searchTile(atlas,tilesName)){
        // erro
        cout<<"Nenhum tile encontrado"<<endl;
        return;
    }
    
    // Passou pelos testes iniciais. É possível contruir o tileset
    
    // guarda valores no objeto para referência futura
    metrics.numTilesTotal = numTilesTotal;
    metrics.numTilesRow = numTilesRow;
    metrics.wTile = tilew;
    metrics.hTile = tileh;
    
    // declaração de variáveis
    // w : largura do tileset, h : altura do tileset
    int w = 0, h = 0;
    
    // Calcula largura do tileset, ou w
    // se o numero total de tiles for maior ou igual ao número por linha...
    if(numTilesTotal >= numTilesRow){
        // w será a quantidade por linha vezes a largura de cada tile
        w = numTilesRow*tilew;
    // caso contrário...
    }else{
        // w será a quantidade total de tiles vezes a largura de cada tile
        w = numTilesTotal*tilew;
    }
    
    // Calcula altura do tileset, ou h
    // Se o número total de tiles for menor ou igual a quantidade por linha...
    if(numTilesTotal <= numTilesRow){
        // a altura é igual a altura de um tile
        h = tileh;
    // caso contrário...
    }else{
        // divide a quantidade total de tiles pela quantidade por linha
        // arredonda o resultado para cima
        // multiplica pela altura de cada tile
        h = tileh * ceil((float) numTilesTotal/numTilesRow);
    }
    
    // guarda esses valores no objeto para referência futura
    metrics.wTileset = w;
    metrics.hTileset = h;
    
    // cria o tileset base
    tileset = al_create_bitmap(w,h);
    
    // variável para armazenar a string de cada tile
    string nametile;
    
    // variáveis para guardar as posições x e y de cada tile no tileset
    int posX, posY;
    
    // configura para que todos os desenhos sejam feitos no tileset
    al_set_target_bitmap(tileset);
    
    // desenha cada tile no tileset
    for(int count=0;count<numTilesTotal;count++){
        
        // compõe a string da tile atual
        nametile.assign(tilesName);
        if(count+1<10){
            nametile.append("00");
            nametile.append(to_string(count+1).c_str());
        }else if(count+1>9 && count+1<100){
            nametile.append("0");
            nametile.append(to_string(count+1).c_str());
        }else{
            nametile.append(to_string(count+1).c_str());
        }
        nametile.append(".png");
        
        // calcula a posição x do tile no tileset
        posX = tilew * (count % numTilesRow);
        
        // calcula a posição y  do tile no tileset
        posY = tileh * floor( (float) count/numTilesRow);
        
        // desenha o tile com a string e posições calculadas
        drawTileOnTileset(atlas, nametile.c_str(), posX, posY);
    }
    
    // configura todos os desenho a serem feitos na tela principal
    al_set_target_bitmap(al_get_backbuffer(window));
}

// Função que desenha um tile no tileset
void TileSet::drawTileOnTileset(Atlas* atlas, const char* nametile,
                        int posX, int posY){
    
    // puxa informações de um tile do atlas
    atlas->setSpriteData(nametile);
    
    // desenha no tileset
    al_draw_bitmap_region(atlas->getAtlas(), atlas->getSD("posX"), atlas->getSD("posY"),
                         atlas->getSD("w"),atlas->getSD("h"),atlas->getSD("offX")+posX,
                         atlas->getSD("offY")+posY,0);
}

// Destrutor
TileSet::~TileSet(){
    destructTileset();
}

// função que desaloca o bitmap tileset
void TileSet::destructTileset(){
    
    // destroi bitmap
    al_destroy_bitmap(tileset);
}

// Desenha tileset na tela (para teste, por exemplo)
void TileSet::drawTileSetOnScreen(int xScreen, int yScreen, int option){
    
    // função do allegro que desenha bitmaps
    al_draw_bitmap(tileset,xScreen,yScreen,option);
}

// Função que desenha um único tile na tela
// Essa função será usada por outra classe para desenhar um mapa inteiro
// usando informações do tileset
void TileSet::drawTileOnScreen(int index, int xScreen, int yScreen, int option){
    
    // o índice 0 (zero) indica sem tile nessa posição
    if(index<=0)return;
    
    // reduz índice em 1 para os cálculos que serão realizados
    index--;
    
    // calcula posição x do tile no tileset
    int posX = metrics.wTile * (index % metrics.numTilesRow);
    
    // calcula posição y do tile no tileset
    int posY = metrics.hTile * floor( (float) index/metrics.numTilesRow);
    
    // desenha tile na tela
    al_draw_bitmap_region(tileset, posX, posY,metrics.wTile,metrics.hTile,xScreen,yScreen,option);
    
}

