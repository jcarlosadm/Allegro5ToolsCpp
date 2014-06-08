#include "parserShoeBoxAtlas.h"

// Para maiores detalhes de uso, veja parserShoeBoxAtlas.h

//////////////////////////////////////////////////////////
//              Funções auxiliares                      //
//////////////////////////////////////////////////////////


// Configura todos os valores de currentSprite para -1, significando
// que não há sprite atual com dados disponível
void resetSpriteVal(spriteData *currentSprite){
    currentSprite->posX=-1;
    currentSprite->posY=-1;
    currentSprite->w=-1;
    currentSprite->h=-1;
    currentSprite->offX=-1;
    currentSprite->offY=-1;
    currentSprite->origW=-1;
    currentSprite->origH=-1;
}

////////////////////////////////////////////////////////////
//              funções membros de Atlas                  //
////////////////////////////////////////////////////////////

// contrutor padrão
Atlas::Atlas(){
    // configura todos os valores de currentSprite para -1
    resetSpriteVal(&currentSprite);
    
    // a imagem atlas aponta para nulo
    atlas = NULL;
}

// contrutor com parâmetros
Atlas::Atlas(const char* fileName){
    // configura todos os valores de currentSprite para -1
    resetSpriteVal(&currentSprite);
    // tenta abrir o arquivo solicitado e a imagem
    openFile(fileName);
}

// destrutor
Atlas::~Atlas(){
    
    // fecha atlasFile se estiver aberto
    // desaloca atlas se diferente de NULL
    closeFile();
    
}

// função que abre o arquivo com informações do atlas e carrega a imagem
void Atlas::openFile(const char* fileName){
    
    // abre o arquivo
    atlasFile.open(fileName);
    
    // se houver algum problema (como o arquivo não existir)
    if(!atlasFile.good()){
        cout<<"problema ao abrir o arquivo!"<<endl;
        
        // fecha atlasFile se estiver aberto
        closeFile();
        
        // imagem atlas aponta para nulo
        atlas = NULL;
        
    // caso contrário...
    }else{
        
        // compõe o nome da imagem atlas
        string imagename;
        imagename.assign(fileName);
        imagename.assign(imagename.begin()+0,imagename.end()-3);
        imagename.append("png");
        
        // carrega a imagem
        atlas = al_load_bitmap(imagename.c_str());
    }
}

// feacha arquivo e desaloca imagem associada
void Atlas::closeFile(){
    
    // fecha o atlasFile se estiver aberto
    if(atlasFile.is_open())atlasFile.close();
    
    // desaloca atlas se diferente de NULL
    if(atlas != NULL)al_destroy_bitmap(atlas);
    
}

// retorna largura ou altura do atlas
int Atlas::getMetricAtlas(const char* type){
    
    // se o atlasFile não estiver aberto, retorna 0
    if(!atlasFile.is_open())return 0;
    
    // aponta a leitura para o início do arquivo
    atlasFile.seekg(0);
    
    string line; // guarda a linha
    int value=0; // valor a ser retornado
    
    // pegar a primeira linha
    getline(atlasFile,line);
    
    // se a métrica solicitada não existir, retorna 0
    if(line.find(type)==string::npos)return 0;
    
    // a métrica foi encontrada
    // encontra a posição da métrica
    int index = line.find(type);
    // encontra a posição da primeira abre aspas após a métrica
    int index2 = line.find("\"",index+1);
    // encontra a posição da primeira fecha aspas após a métrica
    int index3 = line.find("\"",index2+1);
    // pega a string entre as aspas
    string numberstr = line.substr(index2+1,index3-index2-1);
    // converte para inteiro
    // deve usar a flag -std=c++0x no compilador
    value = stoi(numberstr);
    
    // retorna a métrica solicitada
    return value;
}

// guarda informações de um sprite de acordo com a string fornecida
bool Atlas::setSpriteData(const char* spriteName){
    
    // se o atlasFile não estiver aberto, retorna 0
    if(!atlasFile.is_open())return false;
    
    string line; // guarda a linha
    // índices para procurar caracteres específicos
    int index,index2,index3;
    // guarda pedaços da linha
    string valuestring;
    // array de strings para procurar quando encontrar o sprite correto
    string attributes[8]={"x=","y=","width=","height=","framex=","framey=","framew=","frameh="};
    
    // aponta a leitura para o início do arquivo
    atlasFile.seekg(0);
    
    // enquanto houver linha...
    while (getline(atlasFile,line)){
    
        // se achar a substring "SubTexture"...
        if(line.find("SubTexture")!=string::npos){
            
            // Verifica o valor de "SubTexture"
            // Se for igual a string fornecida para a função, então encontrou
            // o sprite correto
            index = line.find("SubTexture");
            index2 = line.find("\"",index+1);
            index3 = line.find("\"",index2+1);
            valuestring.assign(line.substr(index2+1,index3-index2-1));
            if(valuestring==spriteName){
                
                // percorre cada um dos oito atributos, procurando-os na linha
                // atual.
                for(int i=0;i<8;i++){
                    index = line.find(attributes[i]);
                    index2 = line.find("\"",index+1);
                    index3 = line.find("\"",index2+1);
                    valuestring.assign(line.substr(index2+1,index3-index2-1));
                    
                    // preenche currentSprite de acordo com o atributo encontado
                    switch(i){
                        case 0:
                            currentSprite.posX = stoi(valuestring);
                            break;
                        case 1:
                            currentSprite.posY = stoi(valuestring);
                            break;
                        case 2:
                            currentSprite.w = stoi(valuestring);
                            break;
                        case 3:
                            currentSprite.h = stoi(valuestring);
                            break;
                        case 4:
                            currentSprite.offX = stoi(valuestring);
                            break;
                        case 5:
                            currentSprite.offY = stoi(valuestring);
                            break;
                        case 6:
                            currentSprite.origW = stoi(valuestring);
                            break;
                        case 7:
                            currentSprite.origH = stoi(valuestring);
                    }
                }
                // sai da função com sucesso
                return true;
            }
        }
    
    }
    // não encontrou o sprite
    return false;
}

// pega uma parte da informação do sprite atual
int Atlas::getSD(const char* attribute){
    // se o atlas não estiver aberto, sai da função com falha
    if(!atlasFile.is_open())return -1;
    
    if(!strcmp(attribute,"posX")){
        return currentSprite.posX;
    }else if(!strcmp(attribute,"posY")){
        return currentSprite.posY;
    }else if(!strcmp(attribute,"w")){
        return currentSprite.w;
    }else if(!strcmp(attribute,"h")){
        return currentSprite.h;
    }else if(!strcmp(attribute,"offX")){
        return currentSprite.offX;
    }else if(!strcmp(attribute,"offY")){
        return currentSprite.offY;
    }else if(!strcmp(attribute,"origW")){
        return currentSprite.origW;
    }else if(!strcmp(attribute,"origH")){
        return currentSprite.origH;
    }else{
        // retorna -1 se não tiver sucesso
        return -1;
    }
}

// retorna 1 se atlasFile aberto
bool Atlas::is_open(){
    return atlasFile.is_open();
}

// retorna imagem atlas
ALLEGRO_BITMAP* Atlas::getAtlas(){
    return atlas;
}
