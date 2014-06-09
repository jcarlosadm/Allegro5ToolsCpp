#ifndef MAKE_TILESET_ATLAS_H
#define MAKE_TILESET_ATLAS_H

/** ////////////////////////////////////////////////////////////////////////////
Módulo que cria um tileset, usando a biblioteca allegro 5. Considere tileset
como o conjunto de imagens inidividuais usadas para criar mapas

O Allegro 5 não é inicializado nem finalizado aqui. Tenha certeza de realizar
essas operações no programa principal.

Esse módulo só constrói tilesets com até 999 tiles. Além disso, depende do módulo
parserShoeBoxAtlas; carregue um atlas antes.

Quando for inserir os tiles do tileset no atlas (usando algum empacotador de
imagens), deixe uma string padrão no início do nome de cada tile, seguindo
uma numeração:
Map001.png
Map002.png
(...)
Veja que somente são usados arquivos png. O allegro 5 suporta esse tipo de
arquivo sem precisar de qualquer plugin.
///////////////////////////////////////////////////////////////////////////*/

// inclui o arquivo parserShoeBoxAtlas.h
#include "../parserShoeBoxAtlas/parserShoeBoxAtlas.h"
// bibliotecas Allegro necessárias
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
// bibliotecas padrão necessárias
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

// Estrutura que servirá para guardar as informações do tileset
struct tilesetInfo{

    // guarda a quantidade total de tiles
    int numTilesTotal;
    
    // guarda a quantidade de tiles por linha
    int numTilesRow;
    
    // guarda a largura do tileset
    float wTileset;
    
    // guarda a altura do tileset
    float hTileset;
    
    // guarda a largura de cada tile
    float wTile;
    
    // guarda a altura de cada tile
    float hTile;
};

/**
//===========================================================================
// Classe TileSet
//===========================================================================
// Guarda uma imagem com partes do terreno de um mapa
// Guarda informações do tileset como um todo
// Possui métodos para manipulação do tileset
//===========================================================================
*/
class TileSet{

    private:
    
    // guarda a imagem do tileset
    ALLEGRO_BITMAP *tileset;
    
    // guarda informações sobre o tileset carregado (veja a struct acima)
    tilesetInfo metrics;
    
    // Função que desenha um tile no tileset (para criar este último)
    // 
    // PARÂMETROS:
    // atlas : objeto da classe Atlas, com informações da imagem Atlas
    // nametile : string que aparece no começo de cada tile (tile: um quadrado do tileset)
    // posX : coordenada x em que o tile é desenhado no tileset
    // posY : coordenada y em que o tile é desenhado no tileset
    void drawTileOnTileset(Atlas* atlas, const char* nametile,
                    float posX, float posY);
    
    public:
    
    // Construtor padrão
    // deixa tileset com valor NULL
    TileSet();
    
    // Construtor com argumentos
    // Chama a função buildTileset com os argumentos especificados
    //
    // PARÂMETROS:
    // atlas : objeto da classe Atlas, com informações da imagem Atlas
    // nametile : string que aparece no começo de cada tile (tile: um quadrado do tileset)
    // window : a janela de jogo
    //
    // obs: window é informada pois no allegro 5 precisamos informar onde estamos
    // desenhando no momento. A função buildTileset passa a desenhar no tileset e
    // depois reconfigura o desenho para a tela
    TileSet(Atlas* atlas, const char* tilesName,ALLEGRO_DISPLAY* window);
    
    // Destrutor
    // libera a memória alocada do bitmap tileset chamando destructTileset
    ~TileSet();
    
    // Função que constroi o tileset manualmente (somente se tileset estiver apontando para NULL)
    //
    // PARÂMETROS:
    // atlas : objeto da classe Atlas, com informações da imagem Atlas
    // nametile : string que aparece no começo de cada tile (tile: um quadrado do tileset)
    // window : a janela de jogo
    //
    // obs: window é informada pois no allegro 5 precisamos informar onde estamos
    // desenhando no momento. A função buildTileset passa a desenhar no tileset e
    // depois reconfigura o desenho para a tela
    void buildTileset(Atlas* atlas, const char* tilesName,ALLEGRO_DISPLAY* window);
    
    // Função que desaloca o bitmap tileset manualmente
    void destructTileset();
    
    // Função que desenha tileset na tela
    //
    // PARÂMETROS:
    // xScreen : coordenada x da tela
    // yScreen : coordenada y da tela
    // option : opção de desenho da tela
    //
    // VALORES DE option:
    // 0 : não adiciona efeitos extras
    // ALLEGRO_FLIP_HORIZONTAL : inverte o bitmap com base no eixo y
    // ALLEGRO_FLIP_VERTICAL : inverte o bitmap com base no eixo x
    void drawTileSetOnScreen(float xScreen, float yScreen, int option);
    
    // versão de drawTileSetOnScreen com option = 0
    void drawTileSetOnScreen(float xScreen, float yScreen);
    
    // Função que desenha um quadrado do tileset na tela
    //
    // PARÂMETROS:
    // index : índice que indica qual tile é o escolhido (Uma outra classe
    //          fornecerá os meios de selecionar os índices adequados)
    // xScreen : coordenada x da tela
    // yScreen : coordenada y da tela
    // option : opção de desenho da tela
    //
    // VALORES DE option:
    // 0 : não adiciona efeitos extras
    // ALLEGRO_FLIP_HORIZONTAL : inverte o bitmap com base no eixo y
    // ALLEGRO_FLIP_VERTICAL : inverte o bitmap com base no eixo x
    void drawTileOnScreen(int index, float xScreen, float yScreen, int option);
    
    // versão de drawTileOnScreen com option = 0
    void drawTileOnScreen(int index, float xScreen, float yScreen);
};

#endif // MAKE_TILESET_ATLAS_H
