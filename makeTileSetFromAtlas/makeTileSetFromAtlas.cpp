#include "makeTileSetFromAtlas.h"


// procura por um tile no arquivo atlas
// retorna 1 se encontrar, 0 se não encontrar
int searchTile(Atlas* atlas,const char* tilesName){
    
    string nametile = tilesName;
    nametile.append("001.png");
    if(atlas->setSpriteData(nametile.c_str()))
        return 1;
    else
        return 0;
}

/*/////////////////////////////////////////////////////////////////////
    Funções membros de TileSet
/////////////////////////////////////////////////////////////////////*/

TileSet::TileSet(){
    
    // tileset aponta para NULL
    tileset = NULL;
}

TileSet::TileSet(Atlas* atlas, ALLEGRO_BITMAP* atlasImage,const char* tilesName,
                        int numTilesTotal, int numTilesRow, int tilew, int tileh,
                        ALLEGRO_DISPLAY* window){
    
    // tileset aponta para NULL
    tileset = NULL;
    
    // tenta contruir o tileset
    buildTileset(atlas, atlasImage, tilesName, numTilesTotal, numTilesRow, tilew, tileh,
                    window);
}

void TileSet::buildTileset(Atlas* atlas, ALLEGRO_BITMAP* atlasImage,const char* tilesName,
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
    
    // verifica se existe pelo menos um tile
    if(!searchTile(atlas,tilesName)){
        // erro
        cout<<"Nenhum tile encontrado"<<endl;
        return;
    }
    
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
    
    // cria o tileset base
    tileset = al_create_bitmap(w,h);
    
    // variável para armazenar a string de cada tile
    string nametile;
    
    // variáveis para guardar as posições x e y de cada tile no tileset
    int posX, posY;
    
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
        
        // desenha o tile com a string criada
        drawTile(atlas, atlasImage, nametile.c_str(), posX, posY);
    }
    
    al_set_target_bitmap(al_get_backbuffer(window));
}

void TileSet::drawTile(Atlas* atlas, ALLEGRO_BITMAP* atlasImage, const char* nametile,
                        int posX, int posY){
    
    atlas->setSpriteData(nametile);
    cout<<nametile<<endl;
    al_draw_bitmap_region(atlasImage, atlas->getSD("posX"), atlas->getSD("posY"),
                         atlas->getSD("w"),atlas->getSD("h"),atlas->getSD("offX")+posX,
                         atlas->getSD("offY")+posY,0);
}

TileSet::~TileSet(){
    destructTileset();
}

void TileSet::destructTileset(){
    al_destroy_bitmap(tileset);
}

void TileSet::drawTileSet(){
    al_draw_bitmap(tileset,0,0,0);
}
