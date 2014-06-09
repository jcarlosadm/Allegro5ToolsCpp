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

// preenche uma informação de metrics de TileSet
void search_info(const char* info, string &line, tilesetInfo &metrics){

    // forma uma substring com a informação buscada
    int index = line.find(info);
    int index2 = line.find("\"",index+1);
    int index3 = line.find("\"",index2+1);
    string numberstr = line.substr(index2+1,index3-index2-1);
    
    // converte para inteiro e associa a um campo específico de metrics
    if(info == "numTilesTotal")
        metrics.numTilesTotal = stoi(numberstr);
    else if(info=="numTilesRow")
        metrics.numTilesRow = stoi(numberstr);
    else if(info=="tileW")
        metrics.wTile = stoi(numberstr);
    else if(info=="tileH")
        metrics.hTile = stoi(numberstr);
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
TileSet::TileSet(Atlas* atlas,const char* tilesName,ALLEGRO_DISPLAY* window){
    
    // tileset aponta para NULL
    tileset = NULL;
    
    // tenta contruir o tileset
    buildTileset(atlas, tilesName, window);
}

// gera tileset manualmente
void TileSet::buildTileset(Atlas* atlas,const char* tilesName,
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
    
    // abre o arquivo de texto com informações do tileset
    ifstream tilesets_info("tilesets_info.txt");
    
    // se o arquivo não foi aberto adequadamente, aborta
    if(!tilesets_info.good()){
        cout<<"problema ao abrir o arquivo"<<endl;
        if(tilesets_info.is_open())tilesets_info.close();
        return;
    }
    
    // aponta para o início do arquivo
    tilesets_info.seekg(0);
    
    // flag para verificar se houve sucesso em buscar o tileset no arquivo
    bool sucess = false;
    // guarda linha
    string line;
    
    // percorre todas as linhas
    while(getline(tilesets_info,line)){
        // se achar a linha do tileset correto, pega as informações e
        // sai com sucesso
        if(line.find(tilesName)!=string::npos){
            search_info("numTilesTotal",line,metrics);
            search_info("numTilesRow",line,metrics);
            search_info("tileW",line,metrics);
            search_info("tileH",line,metrics);
            sucess=true;
        }
    }
    
    // fecha arquivo
    if(tilesets_info.is_open())tilesets_info.close();
    // se não houve sucesso em encontrar as informações, sai da função
    if(!sucess)return;
    
    // encontrou as informações corretas. prosseguir.
    
    // declaração de variáveis
    // w : largura do tileset, h : altura do tileset
    int w = 0, h = 0;
    
    // Calcula largura do tileset, ou w
    // se o numero total de tiles for maior ou igual ao número por linha...
    if(metrics.numTilesTotal >= metrics.numTilesRow){
        // w será a quantidade por linha vezes a largura de cada tile
        w = metrics.numTilesRow*metrics.wTile;
    // caso contrário...
    }else{
        // w será a quantidade total de tiles vezes a largura de cada tile
        w = metrics.numTilesTotal*metrics.wTile;
    }
    
    // Calcula altura do tileset, ou h
    // Se o número total de tiles for menor ou igual a quantidade por linha...
    if(metrics.numTilesTotal <= metrics.numTilesRow){
        // a altura é igual a altura de um tile
        h = metrics.hTile;
    // caso contrário...
    }else{
        // divide a quantidade total de tiles pela quantidade por linha
        // arredonda o resultado para cima
        // multiplica pela altura de cada tile
        h = metrics.hTile * ceil((float) metrics.numTilesTotal/metrics.numTilesRow);
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
    for(int count=0;count<metrics.numTilesTotal;count++){
        
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
        posX = metrics.wTile * (count % metrics.numTilesRow);
        
        // calcula a posição y  do tile no tileset
        posY = metrics.hTile * floor( (float) count/metrics.numTilesRow);
        
        // desenha o tile com a string e posições calculadas
        drawTileOnTileset(atlas, nametile.c_str(), posX, posY);
    }
    
    // configura todos os desenho a serem feitos na tela principal
    al_set_target_bitmap(al_get_backbuffer(window));
}

// Função que desenha um tile no tileset
void TileSet::drawTileOnTileset(Atlas* atlas, const char* nametile,
                        int posX, int posY){
    
    // puxa informações de um tile do atlas se nametile for válido
    if(atlas->setSpriteData(nametile))
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

// versão de drawTileSetOnScreen com option = 0 
void TileSet::drawTileSetOnScreen(int xScreen, int yScreen){
    drawTileSetOnScreen(xScreen,yScreen,0);
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

// versão de drawTileOnScreen com option = 0
void TileSet::drawTileOnScreen(int index, int xScreen, int yScreen){
    
    // chama drawTileOnScreen com option = 0
    drawTileOnScreen(index,xScreen,yScreen,0);
}
