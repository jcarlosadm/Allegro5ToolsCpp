#ifndef MAKE_TILESET_ATLAS_H
#define MAKE_TILESET_ATLAS_H

/*////////////////////////////////////////////////////////
Módulo que cria um tileset, usando a biblioteca allegro 5. Considere tileset
como o conjunto de imagens inidividuais usadas para criar mapas

O Allegro 5 não é inicializado nem finalizado aqui. Tenha certeza de realizar
essas operações no programa principal.

Esse módulo só constrói tilesets com até 999 tiles. Além disso, depende do módulo
parserShoeBoxAtlas; carregue um atlas antes.
////////////////////////////////////////////////////////*/

#include "../parserShoeBoxAtlas/parserShoeBoxAtlas.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <cmath>

class TileSet{

    private:
    
    // guarda o tileset
    ALLEGRO_BITMAP *tileset;
    
    // desenha um tile no tileset
    void drawTile(Atlas* atlas, ALLEGRO_BITMAP* atlasImage, const char* nametile,
                    int posX, int posY);
    
    public:
    
    // construtor padrão
    // deixa tileset com valor NULL
    TileSet();
    
    // construtor que recebe a string padrão
    // Se tilesName não for uma string válida, tileset recebe NULL. Caso
    // contrário, receberá o endereço da imagem pronta.
    TileSet(Atlas* atlas, ALLEGRO_BITMAP* atlasImage,const char* tilesName,
            int numTilesTotal, int numTilesRow, int tilew, int tileh, ALLEGRO_DISPLAY* window);
    
    // destrutor
    ~TileSet();
    
    // controi o tileset manualmente (somente se tileset estiver apontando para NULL)
    void buildTileset(Atlas* atlas, ALLEGRO_BITMAP* atlasImage,const char* tilesName,
                    int numTilesTotal, int numTilesRow, int tilew, int tileh, ALLEGRO_DISPLAY* window);
    
    // desaloca o tileset manualmente
    void destructTileset();
    
    // desenha tileset na tela
    void drawTileSet();
};

#endif // MAKE_TILESET_ATLAS_H
