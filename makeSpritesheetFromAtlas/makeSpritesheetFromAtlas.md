#Como usar esse módulo

Para usar este módulo, você vai precisar tratar alguns alguns adequadamente, principalmente quando construir o Atlas.

##Conceitos básicos

- Entidade: um objeto que interage no gameplay. Por exemplo, o *player* é uma entidade, assim como cada tipo de *enemy*, cada item, cada armadilha e assim por diante. Toda entidade precisa ter uma localização e uma atualização.
- *Spritesheet*: um conjunto de imagens pertencente a uma entidade em particular. Para os propósitos deste módulo, cada entidade terá um único *spritesheet*. Cada linha de um *spritesheet* será um estado da entidade; por exemplo, teríamos o estado *walk* numa linha, *run* em outra e assim por diante.
- *Sprite*: cada imagem em um *spritesheet*.

##Criando o Atlas

Você precisa nomear cada *sprite* individual antes de empacotá-los no Atlas. A nomeação é importante, e envolve as seguintes partes:

- Nome base: a string básica do *spritesheet*. Todo *sprite* precisa ter no início de seu nome.
- Estado: Após o nome base, adicionamos um *underline* e depois o seu estado. Estados possíveis são *walk*, *attack*, *run* e assim por diante. Você pode adicionar outras strings nesta parte, indicando seja lá o que for necessário na estrutura de jogo; por exemplo, se você tem sprites virados para a esquerda ou direita, talvez tenha os estados *walkl* e *walkr*. Se há variações de armas, talvez tenha *walkBasicL* e *walkBasicR*, ou seja, andando com a arma básica para a esquerda e para a direita.
- Ordem: Cada estado pode ter mais de um quadro. Logo devemos definir qual a ordem de cada *sprite* em um estado específico. Se há apenas um sprite, não defina essa parte (nem coloque um *underline* após o estado).

Exemplos de nomes de *sprites*: *GOBLINGUERREIRO_ATL_01.png*, *HERO_ATL_01.png*, *GOBLINGUERREIRO_DAMAGEL.png*, *GOBLINGUERREIRO_DEAD.png*, etc.

Uma última observação: use arquivos do tipo png. O allegro 5 suporta esse tipo de arquivo.

##Dependências

Como visto acima, a classe Atlas é necessária. Carregue um Atlas, com informações e a imagem.

Outra dependência é do allegro 5.

Também cada entidade deverá usar uma certa estrutura em jogo. Você deverá passar uma característica da entidade para a classe Spritesheet para esta possa preecher essa característica corretamente. Os campos necessários da entidade:

- states : um objeto da classe StatesClass que guarda um spritesheet de todos os estados e informações de cada estado, assim como de cada sprite de cada estado.
- spritesheet: imagem com todos os sprites de todos os estados.
- stateNode: um nó da lista de estados, que possui a seguinte estrutura:
    - stateName: string que representa o nome do estado mais qualquer coisa que este estado possui (como equipamento e/ou direção).
    - nsprites: quantidade de sprites
    - spritesheetX: a localização x do conjunto de sprites do estado no spritesheet.
    - spritesheetY: a localização y do conjunto de sprites do estado no spritesheet.
    - widthSprites: a largura de cada sprite do estado.
    - heightSprites: a largura de cada sprite do estado.
    - effect: número que indica o sprite do estado em que começa a ativar algum efeito (0 se não houver efeito a ser ativado).
    - sprites : ponteiro que aponta para um vetor de sprites
- spriteNode: um nó do vetor de sprites, que possui a seguinte estrutura:
    - frames : quantidade de frames executados para o sprite. é o tempo de execução do sprite.
    - squareBeginX : valor x inicial de um possível quadrado no sprite (-1 se não houver quadrado)
    - squareBeginY : valor y inicial de um possível quadrado no sprite (-1 se não houver quadrado)
    - squareEndX : valor x final de um possível quadrado no sprite (-1 se não houver quadrado)
    - squareEndY : valor y final de um possível quadrado no sprite (-1 se não houver quadrado)

O que a classe Spritesheet recebe é um objeto da classe *StatesClass*, e então aloca tudo o que for necessário alocar dentro da estrutura explicada acima. A desalocação de memória é feita pelos destrutores das classes *list* e *vector*.

O módulo **States.h** possui toda a estrutura necessária (esse módulo usa as bibliotecas *vector* e *list*).

##Informações sobre os *sprites*

Aqui vem uma parte crucial do módulo. Aquele que criou ou projetou os *sprites* precisam informar aos programadores as características desses *sprites*. Isso envolve criar um arquivo de texto chamado "spritesheets_info.txt", onde cada *spritesheet* preenche cada uma das seguintes linhas (esse é um exemplo):

```
spritesheet_name="HERO"
    state="WALKL" numSprites="4" effect="0" flip="no"
        frames="4" squareBeginX="-1" squareBeginY="-1" squareEndX="-1" squareEndY="-1"
        frames="4" squareBeginX="-1" squareBeginY="-1" squareEndX="-1" squareEndY="-1"
        frames="4" squareBeginX="-1" squareBeginY="-1" squareEndX="-1" squareEndY="-1"
        frames="4" squareBeginX="-1" squareBeginY="-1" squareEndX="-1" squareEndY="-1"
    state="WALKR" numSprites="4" effect="0" flip="no"
        frames="4" squareBeginX="-1" squareBeginY="-1" squareEndX="-1" squareEndY="-1"
        frames="4" squareBeginX="-1" squareBeginY="-1" squareEndX="-1" squareEndY="-1"
        frames="4" squareBeginX="-1" squareBeginY="-1" squareEndX="-1" squareEndY="-1"
        frames="4" squareBeginX="-1" squareBeginY="-1" squareEndX="-1" squareEndY="-1"
    state="ATL" numSprites="4" effect="0" flip="no"
        frames="6" squareBeginX="20" squareBeginY="30" squareEndX="30" squareEndY="50"
        frames="4" squareBeginX="10" squareBeginY="40" squareEndX="20" squareEndY="50"
        frames="4" squareBeginX="5" squareBeginY="20" squareEndX="10" squareEndY="40"
        frames="4" squareBeginX="5" squareBeginY="20" squareEndX="10" squareEndY="40"
    state="ATR" numSprites="4" effect="0" flip="no"
        frames="6" squareBeginX="20" squareBeginY="30" squareEndX="30" squareEndY="50"
        frames="4" squareBeginX="10" squareBeginY="40" squareEndX="20" squareEndY="50"
        frames="4" squareBeginX="5" squareBeginY="20" squareEndX="10" squareEndY="40"
        frames="4" squareBeginX="5" squareBeginY="20" squareEndX="10" squareEndY="40"
```

Agora a esplicação de cada campo:

- state : o estado de um conjunto de *sprites* no *spritesheet*. O nome desse state deve indicar toda variação possível (por exemplo, qual arma usa e qual direção está virado).
- numSprites : quantidade de *sprite* daquele estado. Se igual a 1, o módulo considerará o nome do *sprite* sem a numeração de ordem.
- effect : informa em que sprite se inicia algum efeito pretendido, como um raio. Se não há efeito pretendido, ou se não há idéia de quando se inicia (pode ser aleatório, por exemplo), informe "0".
- flip : *H* para flip horizontal, *V* para flip vertical e *no* para nenhum dos dois.
- frames : informa a duração de cada *sprite* deste estado na animação, em quadros (levando em consideração a quantidade de quadros por segundo do seu jogo, que em geral fica por volta de 60).
- squareBeginX: informa a coordenada x do início de um quadrado. Deve ser informada. Esse quadrado pode ser usado por alguma funcionalidade de jogo (como o quadrado da espada na mão do personagem). Informe "-1" se não houver quadrado associado.
- squareBeginY: informa a coordenada y do início de um quadrado. Deve ser informada. Esse quadrado pode ser usado por alguma funcionalidade de jogo (como o quadrado da espada na mão do personagem). Informe "-1" se não houver quadrado associado.
- squareEndX : informa a coordenada x do fim de um quadrado. Informe "-1" se não houver quadrado associado.
- squareEndY : informa a coordenada y do fim de um quadrado. Informe "-1" se não houver quadrado associado.


