# PROBLEMA INICIAL E PROPÓSITO DO SOFTWARE

Para facilitar o trabalho daqueles que buscam acessar informações de estudantes e equipe da 42, a instituição desenvolveu uma [API oficial](https://api.intra.42.fr/), onde qualquer pessoa com um token de acesso pode requisitar essas informações e recebe-las.

Entretanto, as informações são muito aprofundadas e tratam de todas as informações públicas de cada usuário cadastrado na Intra. Com intúito de filtrar essas informações, comecei a desenvolver uma API onde o usuário possa buscar por um cadastro, e receber apenas informações importantes para a análise de desempenho do aluno.

# INFORMAÇÕES ARMAZENADAS

Antes de filtrar as informações, foi preciso refletir sobre quais informações poderiam ser de grande ultilidade na análise de desempenho de cada aluno, para isso, foram inicialmente armazenadas as seguintes informações em uma table geral:

- Login;
- ID;
- Nome Completo;
- Campus;
- Data de Início do Curso;
- Level;
- Projeto Atual;
- Projetos Concluídos(Basecamp não incluído);
- Número de Medalhas;
- Pontos de Avaliação;
- Carteira;
- Posição (Staff ou Cadete);

Apesar de essas informações mostrarem o perfil do cadete de forma geral, ainda são muito superficiais para analisar seu desempenho em projetos, por isso, a cada perfil requisitado, é criado uma **Table de Projetos** que armazena detalhes sobre cada projeto do login. Essa table é nomeada a partir do **ID** (ID_projects). Assim, com o ID do estudante, é possível fazer uma análise mais aprofundada em seu desempenho nos projetos desde o Basecamp. As informações armazenadas são:

- Nome do Projeto;
- Data de Registro;
- Data de Aprovação (Se aprovado);
- Status (Finished/In Progress);
- Número de Retries;
- Nota final;

**As informações são atualizadas a cada request**

# Etapas de Desenvolvimento

Para o desenvolvimento do projeto, foram definidas algumas funcionalidades que este deveria possuir, e dividido em várias etapas.

- **Conexão com a API da Intra(working);**

	Nessa etapa, foi ultilizado a biblioteca **libcurl**. Essa biblioteca permite fazer requisições HTTP através de um programa C;

- **Receber e armazenar as informações(working);**

	Nessa etapa, foi ultilizada a função `freopen` para armazenar a response da API em um arquivo JSON.

- **Filtrar as informações úteis(working);**

	Atraves da biblioteca **json-c** foi possível filtrar as informações armazenadas no arquivo **response.json**, que são armazenadas antes em structs decladas no header `api.h`.

- **Armazenar as informações em um Banco de Dados(working);**

	Uma vez filtradas e armazenadas nas structs, fazemos uma conexão com o banco de dados usando a biblioteca **my_sql**. O programa deve informar que a conexão foi estabelecida e que os dados foram armazenados.

- **Se comportar como uma API, recebendo e retornando informações(working);**

	Depois de ter todos os dados filtrados e armazenados, era necessário conectar um server na rede local, para que pudesse ser acessado, receber requisições HTTP e retornar informações. A conexão foi feita através da biblioteca **ulfius**, que foi desenvolvida para facilitar a construção de API em C.

- **Tratar erros, leaks e comportamentos inesperados(in progress);**


## Dependências e Ultilização

**As bibliotecas `ulfius` e suas dependências, `json-c`, `mysql` e `libcurl` devem estar instaladas para que o programa funcione corretamente**

**As informações se referem à versão atual**
Uma vez pronto para usar e com as dependências instaladas, basta dar o comando `make` e o programa deverá compilar, retornando um arquivo **a.out**. Ao executar-lo, uma mensagem no terminal informará que o framework foi iniciado. Após fazer a requisição HTTP, com o endereço `http://localhost:8080/:user`, o login do usuário será requisitado à API da 42. Caso o usuário seja encontrado, o programa retornará a mensagem `Data found`, `Connection with Database Established` e `Data Stored`, e retornará os dados filtrados em formato **json** ao client. Todos os dados estaram salvo no banco de dados.

## Erros Conhecidos

- 404 Error : Data Not Found

	O login pesquisado não foi encontrado.

- 403 Error!! Not Authorized

	O Token usado não é válido

- 500 Error : Connection with 42API Failed!!

	A conexão com a API da 42 não pode ser estabelecida.

## Funções Detalhadas

- `main`: Inicia a conexão com a rede local. É essa função que vai receber as requisições HTTP, executar a função `ft_request` e enviar a string ao client API.

- `ft_request`: Inicia a conexão com o Curl, lê o Token e recebe o login a ser pesquisado. Após fazer a requisição à API da 42, irá armazenar o conteúdo no arquivo response.json. Após confirmação de conteúdo, chama as funções responsáveis pela filtragem e armazenamento. Retorna a string de informações obtidas em formato json, ou o erro detectado.

- `read_token`: Faz a leitura do arquivo .txt, onde o Token é armazenado. Deverá retornar o conteúdo em uma string.

- `test_input`: Faz a leitura do arquivo .json, onde a resposta da API é armazenada. Caso não encontre os dados, retornará uma string informando o erro. Caso não encontre erros, retorna ponteiro NULL.

- `data_filter`: Acessa o arquivo .json e armazena em um buffer. Então deve executar uma série de funções secundárias, onde cada informação do usuário é armazenada na struct profile. Caso o login pertença ao Staff, armazenará apenas nome, ID e campus, afim de evitar erros.

- `project_data`: Funcionamento é semelhante à `data_filter`, mas deverá armazenar apenas as informações referentes a determinado projeto na struct t_project. Funcionará em loop extraindo, armazenando na struct, guardando no banco de dados e retornando em um projeto por vez, até o mais antigo. Não é executada caso o login pertença ao Staff.

- `proj_db`: É chamada ao início da função `project_data`. Seu trabalho é criar uma nova Table exclusiva do login, e apagando os dados mais antigos.

- `populate_pdb`: É chamada a cada loop da função `project data`. Uma vez que todos os dados estão armazenados na struct t_project, essa função deverá transferir seu conteúdo para a table ID_projects.

- `store_data`: Armazena as informações guardadas na struct profile na Table users. Antes de armazenar, a função apaga os dados antigos para não duplicar o armazenamento.

- `ft_strjoin`: Usada para concatenar strings. É usada para construir a estrutura json ao servidor para que seja retornado ao client.

- `ft_strnstr`: Usada para analisar dados recebidos em formato de string, procura uma string menor dentro de outra maior dentro de uma quantidade de caracteres, retornando sua posição se encontrado, ou nulo se não encontrado

- `write_profile`: Transfere as informações de usuário para um endereço de memória, em formato JSON.

- `write_projects`: Transfere as informações de projeto para um endereço de memória, em formato JSON, sempre concatenando com o conteúdo anterior.