# Micromouse (Grupo 4)

**Grupo 4**:  
Daniel Conceição  
Diogo Carreiro  
Manuel Cabral

## Objetivos

<details><summary>(Click here)</summary>

### Segunda Etapa

#### Objetivos Obrigatórios

* [x] a) Crie o seu próprio espaço no github para inicial projeto novo.
* [x] b) Crie um programa que testa a utilização de sockets que permita a comunicação entre dois processos utilizando a comunicação no protocolo UDP.
* [x] c) Crie um cliente que possa enviar os comandos de movimento do cursor através de socket.
* [x] d) Para além dos comandos de controlo da direção, um comando de fim de interação.
* [x] e) [modo de funcionamento do servidor] O programa deverá funcionar em dois modos:
  * [x] i. Modo com apenas três teclas - virar à direita, virar à esquerda e ir em frente
  * [x] ii. Modo habitual com quatro teclas, a saber, mover-se para a esquerda, mover-se para a direita, mover-se para cima e mover-se para baixo.
* [x] f) [modelo de prog. concorrente] Altere o servidor de forma a que a sua execução se faça com duas threads com a partilha de uma estrutura de dados do tipo fila, onde são armazenados os comandos pela primeira thread (que os recebe via socket) e onde são retirados para execução da segunda thread para atualizar o movimento do cursor no simulador.
* [x] g) [interação com servidor] Com o comando de teclas no cliente irá observar-se o movimento do cursor no simulador na parte do servidor.

#### Objetivos Opcionais

* [ ] h) [info. retornada ao cliente] Deteção por parte do simulador do que se passa à sua volta (paredes, casa partida, casa objetivo) e retorno dessa informação para o cliente.
* [ ] i) [registo de info. sobre o lab. no lado do cliente] Do lado do cliente, inicialmente não se tem conhecimento do formato do labirinto, mas à medida que são executados movimentos utilizando os comandos do lado do cliente, essa informação começa a chegar permitindo registá-la e poderá servir para registar numa matriz a informação recolhida, tendo conhecimento gradual do mundo à medida que executa a tarefa de ida e regresso.  
  Deverá:
  * [ ] 1. Registar numa matriz da informação recolhida passo a passo pelo “rato” no labirinto, com uma eventual representação gráfica dessa informação no lado do cliente.
  * [ ] 2. Estabelecer um algoritmo simples que, com base na informação recolhida, possa estabelecer um percurso mais rápido possível entre a casa de partida e o objetivo.
* [ ] j) [tornar o rato autónomo] Colocar o “rato” a executar autonomamente o movimento de partida e chegada ao objetivo, com recolha de informação e apresentação dessa informação no lado do cliente. O “rato” termina quando chega ao objetivo.
* [ ] k) [pesquisar info. para definir percurso] O cliente explora o labirinto através de comandos do lado do cliente (sem que o rato tenha autonomia). Depois de ter obtido informação necessária, o rato parte da posição de partida e executa o percurso que considera mais rápido até ao objetivo G.
* [ ] l) [tornar rato totalmente autónomo] O “rato” é agora autónomo a pesquisar/explorar o labirinto. Definir o número de vezes que o “rato” pode aceder ao objetivo antes de uma demonstração onde o rato autonomamente executa executa o percurso o mais rapido possível. É contabilizado o número de passos (movimento em frente, virar direita, virar esquerda, recuar) executados e atribuído uma pontuação (a definir).
* [ ] m) [ simulador para usar pelos participantes num micromouse] Pesquisar e, eventualmente, implementar algoritmo que é utilizado pelos investigadores neste tipo de provas.

### Elementos de Qualidade

* [ ] Código segue o modelo proposto no contexto do documento orientador do projeto.
* [ ] O código é dividido em ficheiros diferentes de acordo com a funcionalidade (e.g. o produtor num ficheiro diferente do consumidor).
* [x] Existe facilidade em estabelecer comunicação entre o cliente e o servidor.
* [x] O código é comentado tanto do lado do servidor como do cliente.
* [x] A compilação faz-se através da ferramenta Makefile.
* [x] O código está disponível no github para poder ser descarregado e um ficheiro readme descreve a sua funcionalidade.
* [x] Existe facilidade em carregar diferentes tipos de labirinto.
* [ ] (Mais ou menos?) O código está preparado para acrescentar algumas das novas funcionalidades previstas/propostas em discussão. 

---

</details>

## Informação

Para utilizar o programa, compile os binários com o programa `make` primeiro. Depois, abra duas janelas de terminal, e numa corra `./bin/server` e noutra o `./bin/client`.  
Se quiser um mapa específico, pode adicionar a opção `-map ./maps/50.txt`, com um dos mapas nessa pasta.  
Se quiser utilizar o modo de três teclas, pode adicionar a opção `--three`.

---

## Developing

Please use [EditorConfig](https://editorconfig.org/).

## Building

This command builds `./bin/server` and `./bin/client`.
```sh
make
```

## Running

Run `./bin/server [map_file.txt]` and `./bin/client`.

Map defaults to [./maps/86.txt](./maps/86.txt).

Then on the client, press <kbd>W</kbd><kbd>A</kbd><kbd>S</kbd><kbd>D</kbd> to move. <kbd>Q</kbd> to quit.

If you need to force-close, use <kbd>Ctrl+C</kbd>.
