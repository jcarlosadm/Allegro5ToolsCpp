#ifndef READ_XML_TP
#define READ_XML_TP
/*////////////////////////////////////////////////////////////////
Módulo que trata o arquivo txt gerado pelo shoebox (veja o parserShoeBoxAtlas.md)

/////////////////////////////////////////////////////////////////*/


// deve usar a flag -std=c++0x no compilador, para usar a função std::stoi(), que converte de string para inteiro

#include <iostream> // remover depois
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

// Estrutura dos dados de um único sprite
struct spriteData{

    // posição x no atlas
    int posX;
    
    // posição y no atlas
    int posY;
    
    // largura no atlas (não necessariamente da imagem original)
    int w;
    
    // altura no atlas (não necessariamente da imagem original)
    int h;
    
    // ajuste na posição x
    int offX;
    
    // ajuste na posição y
    int offY;
    
    // largura da imagem original
    int origW;
    
    // altura da imagem original
    int origH;
};

// Classe que contém informações do Atlas
class Atlas{

    private:
    
    // guarda o arquivo de atlas
    ifstream atlasFile;
    
    // guarda dados de um sprite (para evitar grandes alocações, apenas um
    // conjunto de dados é disponível por vez)
    //
    // Se algum dado de currentSprite for -1, isso quer dizer que não há dados
    // de sprite carregados no momento
    spriteData currentSprite;
    
    public:
    
    // construtor padrão
    //
    // inicializa todos os valores de currentSprite para -1
    Atlas();
    
    // construtor
    //
    // tenta executar openFile()
    // inicializa todos os valores de currentSprite para -1
    //
    // PARÂMETROS:
    // fileName    : o nome do arquivo com extensão
    //
    // se o arquivo não existir, openFile() emitirá um alerta
    Atlas(const char* fileName);
    
    // destrutor
    // fecha o arquivo atlasFile
    ~Atlas();
    
    // abre o arquivo de atlas em atlasFile manualmente
    //
    // PARÂMETROS
    // fileName    : o nome do arquivo com extensão
    //
    // se o arquivo não existir, essa função emitirá um alerta
    void openFile(const char* fileName);
    
    // fecha o arquivo atlasFile manualmente
    void closeFile();
    
    // obtem métrica do Atlas (largura ou altura)
    // retorna o valor da métrica solicitada
    // se retornar 0, a métrica solicitada não foi encontrada
    //
    // PARÂMETROS:
    // type    : string da métrica solicitada
    //
    // VALORES DE type
    // Os valores para type podem ser: "width" ou "height"
    int getMetricAtlas(const char* type);
    
    // Função que configura os dados do currentSprite de acordo com a string fornecida
    // retorna 1 se achou o sprite, e 0 se ocorrer erro ou não encontrar o sprite
    //
    // PARÂMETROS:
    // spriteName : nome do sprite, com extensão
    int setSpriteData(const char* spriteName);
    
    // Função que retorna o valor de um dos atributos de currentSprite
    // retorna -1 se não tiver sucesso, ou se o atlasFile estiver fechado
    //
    // PARÂMETROS:
    // attribute : string do nome do atributo, idêntico a struct spriteData
    //
    // VALORES DE attribute
    // os valores de attribute podem ser: "posX", "posY", "w", "h", "offX", "offY", "origW" ou "origH".
    // (para mais informações sobre esses valores, veja a struct spriteData)
    int getSD(const char* attribute);
};

#endif // READ_XML_TP
