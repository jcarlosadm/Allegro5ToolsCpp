#ifndef MAKE_SPRITESHEET_ATLAS_H
#define MAKE_SPRITESHEET_ATLAS_H

/** //////////////////////////////////////////////////////////////////////////
Módulo que gera um spritesheet e todas as informações relacionadas, preenchendo
um objeto da classe StatesClass (veja o módulo States).

Veja makeSpritesheetFromAtlas.md para mais detalhes.
////////////////////////////////////////////////////////////////////////////*/

// inclusão do módulo States
#include "States.h"
// inclui o arquivo parserShoeBoxAtlas.h
#include "../parserShoeBoxAtlas/parserShoeBoxAtlas.h"
// inclusão da biblioteca allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
// inclusão das bibliotecas básicas
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
//===========================================================================
// Classe SpritesheetFactory
//===========================================================================
// Preenche um objeto StatesClass corretamente
//===========================================================================
*/
class SpritesheetFactory{
    
    public:
    
    // construtor padrão
    SpritesheetFactory();
    
    // destrutor padrão
    ~SpritesheetFactory();
    
    // pega um objeto da classe StatesClass e o preenche
    //
    // PARÂMETROS:
    // states: ponteiro para o objeto da classe StatesClass a ser preenchido
    // atlas: ponteiro para o objeto da classe Atlas
    // entityStatesName: string que define o nome padrão dos estados da entidade
    // window: a janela de jogo. Essa função muda o local de desenho para um
    //          bitmap específico. É necessário, depois de todas as operações,
    //          mudar novamente para a janela de jogo.
    void fillStates(StatesClass* states, Atlas* atlas, const char* entityStatesName,
                    ALLEGRO_DISPLAY* window);
};

#endif // MAKE_SPRITESHEET_ATLAS_H
