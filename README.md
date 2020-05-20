# Micromouse (Grupo 4)

**Grupo 4**:  
Daniel Conceição  
Diogo Carreiro  
Manuel Cabral

## Objetivos
<details><summary>(Click here)</summary>

### Primeira Etapa

* [x] a) Programa que mexe o rato no ecrã de terminal de comandos utilizando as teclas "w","s","a" e "d". Este programa servirá para colocar o cursor a deslocar-se no labirinto do micro-rato.
* [x] b) Programa que cria uma matriz (vetor de duas dimensões) que guarda informação de um ficheiro labirinto do micro-rato. Este programa deve mostrarque as posições da matriz correspondem a posições no labirinto.
* [x] c) Junção de ambos os programas: um labirinto a ser explorado por um utilizador utilizando as teclas do terminal.
* [x] d) Preparar um ficheiro Makefile para a compilação automática de todas as componentes.
* [x] e) Criação de um espaço no github para o projeto e introdução da última versão do projeto. Criação de pequeno manual de introdução ao funcionamento do git gerir as versões de um projeto.

### Segunda Etapa

#### Objetivos Obrigatórios

* [x] a) Crie o seu próprio espaço no github para inicial projeto novo.
* [x] b) Crie um programa que testa a utilização de sockets que permita a comunicação entre dois processos utilizando a comunicação no protocolo UDP.
* [x] c) Crie um cliente que possa enviar os comandos de movimento do cursor através de socket.
* [x] d) Para além dos comandos de controlo da direção, um comando de fim de interação.
* [ ] e) [modo de funcionamento do servidor] O programa deverá funcionar em dois modos:
  * [ ] i. Modo com apenas três teclas - virar à direita, virar à esquerda e ir em frente
  * [x] ii. Modo habitual com quatro teclas, a saber, mover-se para a esquerda, mover-se para a direita, mover-se para cima e mover-se para baixo.
* [ ] f) [modelo de prog. concorrente] Altere o servidor de forma a que a sua execução se faça com duas threads com a partilha de uma estrutura de dados do tipo fila, onde são armazenados os comandos pela primeira thread (que os recebe via socket) e onde são retirados para execução da segunda thread para atualizar o movimento do cursor no simulador.
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

---

</details>

## Developing

Please use [EditorConfig](https://editorconfig.org/).

## Building

This command builds to `./bin/main`
```sh
make
```

## Running

Run `./bin/server [map_file.txt]` and `./bin/client`.

Map defaults to [./maps/86.txt](./maps/86.txt).

Then on the client, press <kbd>W</kbd><kbd>A</kbd><kbd>S</kbd><kbd>D</kbd> to move. <kbd>Q</kbd> to quit.

If you need to force-close, use <kbd>Ctrl+C</kbd>.
