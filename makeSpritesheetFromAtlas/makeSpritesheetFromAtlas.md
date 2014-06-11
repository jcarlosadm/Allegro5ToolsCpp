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
- Ordem: Cada estado pode ter mais de um quadro. Logo devemos definir qual a ordem de cada *sprite* em um estado específico. Se há apenas um sprite, não defina essa parte.

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
    - effect: número que indica o sprite do estado em que começa a ativar algum efeito (0 se não houver efeito a ser ativado).
    - sprites : ponteiro que aponta para um vetor de sprites
- sprite : um nó do vetor de sprites, que possui a seguinte estrutura:
    - spritesheetX: coordenada x do sprite no spritesheet.
    - spritesheetY: coordenada y do sprite no spritesheet.
    - width: largura do sprite (todos os sprites de um mesmo estado devem possuir mesma largura)
    - height: altura do sprite (todos os sprites de um mesmo estado devem possuir mesma altura)
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
    state="WalkL" numSprites="4" effect="0" flipV="no" flipH="no"
        frames="4" squareBegin="-1,-1" squareEnd="-1,-1"
        frames="4" squareBegin="-1,-1" squareEnd="-1,-1"
        frames="4" squareBegin="-1,-1" squareEnd="-1,-1"
        frames="4" squareBegin="-1,-1" squareEnd="-1,-1"
    state="WalkR" numSprites="4" effect="0" flipV="no" flipH="no"
        frames="4" squareBegin="-1,-1" squareEnd="-1,-1"
        frames="4" squareBegin="-1,-1" squareEnd="-1,-1"
        frames="4" squareBegin="-1,-1" squareEnd="-1,-1"
        frames="4" squareBegin="-1,-1" squareEnd="-1,-1"
    state="AtL" numSprites="4" effect="0" flipV="no" flipH="no"
        frames="6" squareBegin="20,30" squareEnd="30,50"
        frames="4" squareBegin="10,40" squareEnd="20,50"
        frames="4" squareBegin="5,20" squareEnd="10,40"
        frames="4" squareBegin="5,20" squareEnd="10,40"
    state="AtR" numSprites="4" effect="0" flipV="no" flipH="no"
        frames="6" squareBegin="20,30" squareEnd="30,50"
        frames="4" squareBegin="10,40" squareEnd="20,50"
        frames="4" squareBegin="5,20" squareEnd="10,40"
        frames="4" squareBegin="5,20" squareEnd="10,40"
```

Agora a esplicação de cada campo:

- state : o estado de um conjunto de *sprites* no *spritesheet*. O nome desse state deve indicar toda variação possível (por exemplo, qual arma usa e qual direção está virado).
- numSprites : quantidade de *sprite* daquele estado. Se igual a 1, o módulo considerará o nome do *sprite* sem a numeração de ordem.
- effect : informa em que sprite se inicia algum efeito pretendido, como um raio. Se não há efeito pretendido, ou se não há idéia de quando se inicia (pode ser aleatório, por exemplo), informe "0".
- flipV : se deseja inverter verticalmente a imagem (a imagem pode estar virada para a esquerda, e você deseja que fique virada para a direita), ponha *yes*. Caso contrário, *no* (se a imagem já estiver virada para o lado correto).
- flipH : se deseja inverter horizontalmente a imagem (se quiser que fique de cabeça para baixo, por exemplo), ponha *yes*. Caso contrário, *no*.
- frames : informa a duração de cada *sprite* deste estado na animação, em quadros (levando em consideração a quantidade de quadros por segundo do seu jogo, que em geral fica por volta de 60).
- squareBegin: informa as coordenadas x e y do início de um quadrado, separadas por uma vírgula, na forma[x,y]. Deve ser informada. Esse quadrado pode ser usado por alguma funcionalidade de jogo (como o quadrado da espada na mão do personagem). Informe "-1,-1" se não houver quadrado associado.
- squareEnd : informa as coordenadas x e y do fim de um quadrado, separadas por uma vírgula. Informe "-1,-1" se não houver quadrado associado.


