#include "makeTilesFromAtlas.h"


// procura por um tile no arquivo atlas
// retorna 1 se encontrar, 0 se não encontrar
int searchTile(Atlas* atlas,const char* tilesName){
    
    string nametile = tilesName;
    nametile.append("001.png");
    if(atlas->setSpriteData(nametile))
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

TileSet::TileSet(Atlas* atlas,const char* tilesName, int numTilesTotal, int numTilesRow, int tilew=32, int tileh=32){
    
    // tileset aponta para NULL
    tileset = NULL;
    
    // tenta contruir o tileset
    buildTileset(atlas,tilesName, numTilesTotal, numTilesRow,tilew,tileh);
}

void TileSet::buildTileset(Atlas* atlas,const char* tilesName, int numTilesTotal, int numTilesRow, int tilew=32, int tileh=32){
    
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
    
    // desenha cada tile no tileset
    
}
