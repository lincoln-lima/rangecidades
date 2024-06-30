# Busca de municípios por Range Query 🌎
![imagem mapa do Brasil com latitude e longitude](https://docplayer.com.br/docs-images/17/147974/images/3-0.png)

## Descrição 📰
O trabalho consiste na **adaptação** de árvore AVL para que suporte _range queries_ (busca por intervalos).  
Conforme o [trabalho anterior](https://github.com/lincoln-lima/cidadesproximas), será utilizado a mesma base de dados: o arquivo [`"municipios.json"`](https://github.com/kelvins/municipios-brasileiros/blob/main/json/municipios.json).

Assim, é possível realizar consultas de todas as cidades que possuam:
- O DDD entre 15 e 20.
- A latitude entre -31 e -34, e a longitude entre -50 e -54.

Ou ainda fazer combinações que representam a interseção entre nome, latitude, longitude, UF e DDD.

## Estrutura 🏛️
A estruturação a nível de código é responsável por tornar um programa **eficaz**, e ao mesmo tempo sua organização pode remeter à sua **complexidade**.

### 📚 Sucessor e Antecessor
> [!NOTE]
> O estudioso Thomas Cormen exemplificou um algoritmo do sucessor de um nó, em seu livro [Algoritmos: Teoria e Prática](https://computerscience360.files.wordpress.com/2018/02/algoritmos-teoria-e-prc3a1tica-3ed-thomas-cormen.pdf), cujo sua aplicação não se faz necessário a **comparação** das chaves dos nós, apenas o seu nó pai.

Ao percorrer uma árvore balanceada deve-se utilizar a estrutura ao seu favor, e com isso em mente, foi incorporado à AVL nós que possuam ponteiros para seus **pais**, de modo a possibilitar a criação de funções que retornem o _sucessor_ e também o _antecessor_ do respectivo nó.

### ➡️ Lista Encadeada
> Em uma estrutura de árvore comum, um registro é armazenado unicamente em seu próprio nó.

Entretanto, para a aplicação desejada, nós com chaves iguais serão armazenados conjuntamente em um nó por meio do encadeamento de uma lista de registros. Por exemplo:
- Cidades com o DDD (67) serão amazenadas em um mesmo nó.

O seu registro irá conter a **chave** do campo específico, e seu **código IBGE**.

### 🌲 Árvores de Busca
Cada campo será armazenado em sua respectiva árvore, de modo a serem independentes dos demais, com uma organização própria.

### 🉑 Tabela Hash
> Uma estrutura de Hash será utilizada para o armazenamento íntegro do registro do munícipio.
> 
> Assim sua consulta estará disponível ao informar seu código IBGE.

## Iniciando 🔰
Abaixo segue o _link_ de um vídeo no YouTube descrevendo e explicando a ferramenta.
> [!TIP]
> [![youtube-video](https://img.youtube.com/vi/f7JtkHlj6B0/0.jpg)](https://youtu.be/f7JtkHlj6B0)

### Pré-requisitos 🧰
- GCC (Compilador C)
- Make

### 🗄️ Biblioteca parser de JSON
As funções utilizadas para leitura dos registros de municípios do arquivo `.json`, e conversão de _strings_ para inteiros ou reais foram importadas da biblioteca [JSENSE](https://gitlab.com/greggink/youtube_episode_jsense).
> [!IMPORTANT]
> Seu uso é restrito mediante referência por sua **licença**, disponibilizada na pasta [`/license`](/license/LICENSE) do projeto.

### ⌨️ Instalação
1. Clone o repositório.
   ```git
   git clone https://github.com/lincoln-lima/rangecidades.git
   ```
2. Mude para diretório do projeto.
   ```bash
   cd rangecidades 
   ```
3. Defina o caminho das bibliotecas
   ```bash
   export LD_LIBRARY_PATH=./lib
   ```
4. Execute o comando abaixo para gerar o executável com suas bibliotecas dinâmicas.
   ```bash
   make
   ```
5. Com a linha abaixo execute o binário do programa.
   ```bash
   make run
   ```
6. Para limpeza de todos os arquivos gerados ao fim do uso, execute:
   ```bash
   make clean
   ```

## Utilização 🖱️

### 💻 Menu
```
[0] Encerrar
[1] Continuar

--> _
```
Um menu será exibido para dar início às buscas.

### 🔍 Campos
```
Nome:
[0] não
[1] sim

--> _
```
Será questionado ao usuário se determinado campo deverá ser incluso à busca.  
> - Ao incluí-lo ele será combinado apenas com os demais campos escolhidos.
> 
> - Do contrário, ele não será incluso no resultado da busca.

### 📊 Faixa
```
Intervalo:
[0] igual a(=)
[1] maior que(>)
[2] menor que(<)
[3] entre(< >)

--> _
```
Após optar por um campo, o menu acima será exibido.[^1]
> No caso da opção `(3) entre(< >)` será solicitado uma chave mínima e uma chave máxima.[^2]

### 🔑 Chave de busca
```
Chave: _
```
Logo após a chave será solicitada.[^3]

### 🖨️ Resultado
```
-----------------------------------
codigo_ibge: 5002704
nome: Campo Grande
latitude: -20.448601
longitude: -54.629501
capital: 1
codigo_uf: 50
siafi_id: 9051
ddd: 67
fuso_horario: America/Porto_Velho
-----------------------------------
Municípios encontrados: 1
```
A busca retornará todas as informações referentes ao municípios encontrados, e sua quantidade.
> Por fim o menu inicial será reexibido para uma nova busca.

## Tudo certo 🎉
Agora é só aproveitar!

[^1]: No caso do campo Nome, o menu não será exibido, apenas solicitará a chave.
[^2]: Essa função não incluirá nem o mínimo nem o máximo solicitado.
[^3]: Salienta-se que na busca por números racionais seu retorno não será tão preciso, uma vez que os registros são armazenados conjuntamente em um único nó, de acordo com sua parte inteira.
