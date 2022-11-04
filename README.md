# Monitoring

Essa aplicação monitora serviços web em tempo real utilizando 3 protocolos: *HTTP*, *PING* e *DNS*.<br>

## Tecnologias e ferramentas<br>
- <a href="https://pt.wikipedia.org/wiki/C_(linguagem_de_programa%C3%A7%C3%A3o)">C</a><br>
- <a href="https://curl.se/">cURL</a><br>
#
## Setup e configurações
Para executar o programa é preciso que o arquivo `monitoring.db` esteja localizado na raiz do repositório e contendo as configurações de monitoramento que serão lidas e interpretadas pelo programa `monitoring` que iniciará a monitoração.<br><br>
Cada linha do arquivo `monitoring.db` representa uma espécie de monitoramento, e as configurações devem seguir uma estrutura estrita que difere de acordo com cada protocolo. A estrutura é definida por linhas e colunas, onde cada linha terá as configurações separadas por um TAB, que definem as colunas:<br>

| Protocolo   | Configurações                                                           |
|-------------|-------------------------------------------------------------------------|
| HTTP        | nome, protocolo, endereço, método HTTP, código HTTP esperado, intervalo |
| PING        | nome, protocolo, endereço, intervalo                                    |
| DNS         | nome, protocolo, endereço, intervalo, servidor DNS                      |

Abaixo, exemplo do arquivo descrito acima:

```txt
# monitoring.db

intra	HTTP	intra.42.fr	GET	200	120
game ping test	PING	game.42sp.org.br	60
workspaces monitoring	PING	workspaces.42sp.org.br	60
```
As informações obtidas no monitoramento serão armazenadas no arquivo `monitoring.log` e exibidas de forma sucinta no terminal
## Rodando o programa
- Clonar o repositório:
```txt
$ git clone https://github.com/42sp/42labs-selection-process-v3-AkakiAlice.git
```
- Executar o comando make na raiz do repositório:
```txt
$ make
```
- Executar o programa:
```txt
$ ./monitoring
```
- Para obter as informações sucintas no arquivo `monitoring.log` execute o programa com a flag `--simplify`
```txt
$ ./monitoring --simplify
```
