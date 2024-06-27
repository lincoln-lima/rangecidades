# Busca de municípios por Range Query
![imagem mapa do Brasil com latitude e longitude](https://docplayer.com.br/docs-images/17/147974/images/3-0.png)
## Descrição
O trabalho consiste na **adaptação** de árvore AVL para que suporte _range queries_ (busca por intervalos).

Conforme o [trabalho anterior](https://github.com/lincoln-lima/cidadesproximas), será utilizado a mesma base de dados: o arquivo [_`"municipios.json"`_](https://github.com/kelvins/municipios-brasileiros/blob/main/json/municipios.json).

Assim, é possível realizar consultas de todas as cidades que possuam:
- O DDD entre 15 e 20.
- A latitude entre -31 e -34, e a longitude entre -50 e -54.

Ou ainda fazer combinações entre latitude, longitude e DDD.
## Iniciando 
### Biblioteca parser de JSON
As funções utilizadas para leitura dos registros de municípios do arquivo _`.json`_ foram importadas da biblioteca [JSENSE](https://gitlab.com/greggink/youtube_episode_jsense).
> [!NOTE]
> Seu uso é restrito mediante referência por sua **licença**, disponibilizada na pasta [_`/license`_](/license/LICENSE) do projeto.
### Instalação
1. Clone o repositório.
   ```bash
   git clone https://github.com/lincoln-lima/rangecidades.git
   ```
2. Mude para diretório do projeto.
   ```bash
   cd rangecidades 
   ```
3. Compile os arquivos da pasta `src`.
   ```bash
   gcc -o run ./src/*.c
   ```
4. Execute o arquivo gerado.
   ```bash
   ./run
   ```
## Utilização
### Menu
> Um menu será exibido para dar início às buscas
```bash
[0] Encerrar
[1] Continuar

--> _
```
### Campos
> Será questionado ao usuário se determinado campo deverá ser incluso à busca.
```bash
Nome:
[0] não
[1] sim

--> _
```
> Ao incluí-lo ele será combinado apenas com os demais campos escolhidos.

> Do contrário, ele não será incluso no resultado da busca.
### Faixa
> Após optar por um campo[^1], o seguinte menu será exibido:
```bash
Intervalo:
[0] igual a(=)
[1] maior que(>)
[2] menor que(<)
[3] entre(< >)

--> _
```
> Tais opções se referem ao valor a ser especificado, logo após solicitando a chave.
```bash
Chave: _
```
> No caso da opção `(3) entre(< >)`[^2] será solicitado uma chave mínima e uma chave máxima.
### Resultado
> A busca retornará todas as informações referentes ao municípios encontrados, e logo após a quantidade.
```bash
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
> Por fim o menu inicial será reexibido para uma nova busca
[^1]: No caso do campo Nome, o menu não será exibido, apenas solicitará a chave
[^2]: Essa função não incluirá nem o mínimo nem o máximo solicitado
# Tudo certo!
Agora é só aproveitar.
