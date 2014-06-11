#include "makeSpritesheetFromAtlas.h"

//==========================================================================
// Funções auxiliares
//==========================================================================

// Procura alguma informação no arquivo
// retorna true se encontrar, e false pelo contrário
bool searchInfo(ifstream &spritesheets_info, const char* field, const char* info){
    
    // variável que controla se houve successo em encontrar a informação procurada
    bool success = false;
    // variável que guarda a linha atual
    string line;
    
    // percorre cada linha do arquivo
    while(getline(spritesheets_info,line)){
        
        // se a linha tiver o campo com o valor procurado...
        if(line.find(field)!=string::npos && line.find(info)!=string::npos){
            
            // teve successo
            success = true;
            break;
            
        }
        
    }
    return success;
}

// retorna um valor relacionado a field em line, em formato string
// Essa função considera que o campo field existe em line, e,
// portanto, o valor associado a field também existe
string returnValue(const string &line,const char *field){
    
    // variáveis que auxiliam na busca do valor de um campo
    int index,index2,index3;
    
    // variável que guardará o valor em formato string
    string value;
    
    // localiza o valor do campo
    index = line.find(field);
    index2 = line.find("\"",index+1);
    index3 = line.find("\"",index2+1);
    value.assign(line.substr(index2+1,index3-index2-1));
    
    // retorna value
    return value;
}

// preenche uma variável string com o valor de field, encontrado na linha
// obs: essa função não procura por field na linha, e sim já considera que você
// já encontrou esse campo de alguma outra forma
void fillVar(const string &line, const char *field, string &variable){
    
    variable.assign(returnValue(line,field));
    
}

// adiciona uma string (valor de field, encontrado na linha) no vetor variable
// obs: essa função não procura por field na linha, e sim já considera que você
// já encontrou esse campo de alguma outra forma
void fillVar(const string &line, const char *field, vector<string> &variable){
    
    variable.push_back(returnValue(line,field));
    
}

// preenche uma variável int com o valor de field, encontrado na linha
// obs: essa função não procura por field na linha, e sim já considera que você
// já encontrou esse campo de alguma outra forma
void fillVar(const string &line, const char *field, int &variable){
    
    variable = stoi(returnValue(line,field));
    
}

// preenche uma variável float com o valor de field, encontrado na linha
// obs: essa função não procura por field na linha, e sim já considera que você
// já encontrou esse campo de alguma outra forma
void fillVar(const string &line, const char *field, float &variable){
    
    variable = stof(returnValue(line,field));
    
}

//==========================================================================
// Funções membros de SpritesheetFactory
//==========================================================================

// contrutor padrão
SpritesheetFactory::SpritesheetFactory(){}

// destrutor
SpritesheetFactory::~SpritesheetFactory(){}

// preenche um objeto de StatesClass corretamente
void SpritesheetFactory::fillStates(StatesClass* states, Atlas* atlas, const char* entityStatesName,
                                    ALLEGRO_DISPLAY* window){
    
    // **primeiro vai em busca de "spritesheets_info.txt" e tenta abrir**
    ifstream spritesheets_info("spritesheets_info.txt");
    
    // se houver algum problema, informa e sai da função
    if(!spritesheets_info.good()){
        cout<<"problema ao abrir o arquivo spritesheets_info.txt"<<endl;
        
        // fecha o arquivo se estiver aberto
        if(spritesheets_info.is_open())spritesheets_info.close();
        
        return;
    }
    
    // **passou no primeiro teste**
    
    // aponta para o início do arquivo
    spritesheets_info.seekg(0);
    
    // **procura no arquivo aberto por entityStatesName no campo spritesheet_name**
    
    // se não encontrou o campo "spritesheet_name" com o valor apropriado, sai com erro
    if(!searchInfo(spritesheets_info,"spritesheet_name=",entityStatesName)){
        cout<<" o arquivo nao possui o campo \"spritesheet_name\" com o valor "<<entityStatesName<<endl;
        if(spritesheets_info.is_open())spritesheets_info.close();
        return;
    }
    
    // **encontrou o campo "spritesheet_name" com o valor entityStatesName**
    
    // variável que guarda a linha atual
    string line;
    // variável que guarda o nome da entidade + estado + ordem
    string entStateOrder;
    // variável que guarda o nome do estado
    string state;
    // variável que guarda o número de sprites
    int nsprites=0;
    // variável que guarda o valor de effect
    int effect=0;
    // variável que guarda o flip
    vector<string> flip;
    // variáveis que guardam a largura e altura
    float widthSprites=0, heightSprites=0;
    // variáveis que controlam a posição dos sprites de um estado num spritesheet
    float spritesheetX=0, spritesheetY=0;
    // variáveis usadas posteriormente para criar o spritesheet
    float spritesheetW=0,spritesheetH=0;
    
    // guarda número de frames
    int frames=0;
    // guarda os valores squareBeginX, squareBeginY, squareEndX e squareEndY
    float squareBeginX=-1,squareBeginY=-1,squareEndX=-1,squareEndY=-1;
    
    // **enquanto não encontrar, a cada linha, o campo "spritesheet_name" novamente, continua**
    while(getline(spritesheets_info,line)){
        
        // se achar o campo state...
        if(line.find("state=")!=string::npos){
            
            // preenche state, nsprites e effect
            fillVar(line,"state=",state);
            fillVar(line,"numSprites=",nsprites);
            fillVar(line,"effect=",effect);
            fillVar(line,"flip=",flip);
            
            // compõe a variável entStateOrder
            entStateOrder.assign(entityStatesName);
            entStateOrder += "_";
            entStateOrder += state;
            if(nsprites>1){
                entStateOrder += "_01.png";
            }
            
            // agora procura pela largura e altura desta string no atlas
            // se nao encontrar o sprite, retorna erro
            if(!atlas->setSpriteData(entStateOrder.c_str())){
                cout<< "sprite nao encontrado no atlas" <<endl;
                break;
            }
            
            // preenche widthSprites e heightSprites
            widthSprites = atlas->getSD("origW");
            heightSprites = atlas->getSD("origH");
            
            // incrementa spritesheetH e verifica o maior spritesheetW
            // esses valores devem ser guardados para criar o spritesheet
            if((widthSprites*nsprites) > spritesheetW)
                spritesheetW = widthSprites*nsprites;
            spritesheetH += heightSprites;
            
            // Adiciona um estado em states
            states->addState(state.c_str(),nsprites,spritesheetX,spritesheetY,widthSprites,
            heightSprites,effect);
            
            // agora deverá preencher os dados de cada sprite em separado.
            // variável de controle para checar a quantidade de sprites
            int checkNumSprites = 0;
            
            // pega próxima linha, enquanto houver linha
            while(getline(spritesheets_info,line)){
                
                // se achou o campo "state=" ou "spritesheet_name", sair do loop
                if(line.find("state=")!=string::npos || line.find("spritesheet_name")!=string::npos)break;
                
                // se a linha contiver a string "frames=", pegar dados
                if(line.find("frames=")!=string::npos){
                    
                    // incrementar checkNumSprites
                    checkNumSprites++;
                    
                    // preeche frames, squareBeginX, squareBeginY, squareEndX, squareEndY
                    fillVar(line,"frames=",frames);
                    fillVar(line,"squareBeginX=",squareBeginX);
                    fillVar(line,"squareBeginY=",squareBeginY);
                    fillVar(line,"squareEndX=",squareEndX);
                    fillVar(line,"squareEndY=",squareEndY);
                    
                    // agora adiciona um sprite em states
                    states->addSpriteToState(state.c_str(), frames, squareBeginX,
                            squareBeginY, squareEndX, squareEndY);
                    
                    // se chegou ao número de sprites pretendidos, sai do loop
                    if(checkNumSprites==nsprites)break;
                }
                
            }
            
            // verifica se o número de sprites obtidos foram iguais aos pretendidos
            // se não, sai com erro
            if(checkNumSprites!=nsprites){
                cout<<"numero de sprites conseguidos diferente do numero pretendido"<<endl;
                return;
            }
            
            // incrementa spritesheetX e spritesheetY
            spritesheetY += heightSprites;
            spritesheetX = 0;
            
        }
        
    }
    
    // **encontrou "spritesheet_name" ou chegou ao final do arquivo
    
    // **constrói o spritesheet**
    
    // cria o bitmap
    ALLEGRO_BITMAP* spritesheetImage = al_create_bitmap(spritesheetW,spritesheetH);
    
    // configura para que todos os desenhos sejam feitos nessa imagem
    al_set_target_bitmap(spritesheetImage);
    
    // declara um vetor de strings
    vector<string> nameStates;
    
    // preenche com os nomes dos estados
    states->getStateNames(nameStates);
    
    // usa nameStates para percorrer todos os estado e preencher o spritesheet corretamente
    for(int count = 0; count < nameStates.size(); count++){
        
        // se o número de sprites for maior que zero...
        if(states->getStV(nameStates[count].c_str(),"nsprites") > 0){
            
            // percorre a quantidade de sprites no estado
            for(int count2 = 0; count2 < states->getStV(nameStates[count].c_str(),"nsprites"); count2++){
                
                // compõe o nome do sprite para procurar no atlas
                entStateOrder.assign(entityStatesName);
                entStateOrder += "_";
                entStateOrder += nameStates[count];
                
                // se o número de sprites no estado for maior que 1...
                if( states->getStV(nameStates[count].c_str(),"nsprites") > 1 ){
                    
                    // se for entre 2 e 9...
                    if( count2 < 9 ){
                        
                        entStateOrder += "_0";
                        entStateOrder += to_string(count2+1);
                        entStateOrder += ".png";
                    // se for entre 10 e 99 ...
                    }else if( count2 > 8 && count2 < 99){
                        entStateOrder += "_";
                        entStateOrder += to_string(count2+1);
                        entStateOrder += ".png";
                    // erro: tem mais de 99 sprites neste estado!
                    }else{
                        cout<< " erro: mais de 99 sprites em um estado " <<endl;
                        al_set_target_bitmap(al_get_backbuffer(window));
                        return;
                    }
                // caso tenha apenas 1 sprite
                }else{
                    entStateOrder += ".png";
                }
                
                // com o nome, procura no atlas e desenha no local correto
                if(!atlas->setSpriteData(entStateOrder.c_str())){
                    cout<<"erro! sprite nao encontrado no atlas"<<endl;
                    al_set_target_bitmap(al_get_backbuffer(window));
                    return;
                }
                
                // desenha sem flip
                if(flip[count].compare("no")==0){
                    atlas->drawCropAtlas(states->getStV(nameStates[count].c_str(),"spritesheetX")+
                    count2*(states->getStV(nameStates[count].c_str(),"widthSprites")),
                    states->getStV(nameStates[count].c_str(),"spritesheetY"));
                
                // desenha com flip horizontal
                }else if(flip[count].compare("H")==0){
                    atlas->drawCropAtlas(states->getStV(nameStates[count].c_str(),"spritesheetX")+
                    count2*(states->getStV(nameStates[count].c_str(),"widthSprites")),
                    states->getStV(nameStates[count].c_str(),"spritesheetY"),ALLEGRO_FLIP_HORIZONTAL);
                
                // desenha com flip vertical
                }else if(flip[count].compare("V")==0){
                    atlas->drawCropAtlas(states->getStV(nameStates[count].c_str(),"spritesheetX")+
                    count2*(states->getStV(nameStates[count].c_str(),"widthSprites")),
                    states->getStV(nameStates[count].c_str(),"spritesheetY"),ALLEGRO_FLIP_VERTICAL);
                
                // especificação erronea de flip
                }else{
                    cout<< " valor errado para flip " <<endl;
                    al_set_target_bitmap(al_get_backbuffer(window));
                    return;
                }
                
            }
        // número de sprites menor que 1!
        }else{
            // erro
            cout << "erro: nsprites igual a " << states->getStV(nameStates[count].c_str(),"nsprites") << " em "
            << nameStates[count] << endl;
            al_set_target_bitmap(al_get_backbuffer(window));
            return;
        }
        
    }
    
    // configura todos os desenho a serem feitos na tela principal
    al_set_target_bitmap(al_get_backbuffer(window));
    
    // guarda bitmap no states
    states->addSpritesheet(spritesheetImage);
    
    // fecha o arquivo
    spritesheets_info.close();
    
}
