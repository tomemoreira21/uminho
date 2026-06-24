USE sakila;

-- DELIMITER $$ <CODIGO> $$ faz com que não execute
-- P R O C E D I M E N T O
/*
CREATE PROCEDURE (
	IN pCliente INT,
    OUT Total VARCHAR(150)
) 
*/
-- Handler -> serve para detetar erros
-- Transações
-- Execuções em bloco, em vez de individuais, sendo uma bloco designado 1UT (unidade trabalho)
-- Início de transação da venda
START TRANSACTION;
/*
Ao corre tudo bem ou não correndo recorre:
	ROLLBACK -> se não corre bem uma operação, muda as anteriores retornado ao estado antes da transação
    COMMIT -> serve como confirmação para a sucesso

Propriedades de uma transação
ACID 
A -> Atomicidade -> devem ser vistas como uma única operação 
C -> Consistência -> nunca deixa a BD num estado inconsistente indo do estado consistente para o consistente
I -> Isolamento -> o efeito de uma operação não deve afetar a execução de outras operações  
D -> Durabilidade -> quando encontra o commit, a BD reflete de forma permanente as modificações na BD

Usa o handler para detetar erros durante a execução da transação, estando sempre a verificar a sua flag dando rollback caso necessário
*/

-- F U N C O E S
-- Tem de ter sempre um valor retorno

--  T R I G G E R S
-- Apenas atua no caso da realização de uma operação de inserção, update ou delete 
/*
NEW -> É uma tabela que só existe quando o trigger dispara, colocando na tabela NEW o registo criado, assumindo em tempo real 
OLD -> É  uma tabela que só existe quando o trigger dispara, colocando na tabela NEW o registo removido, tendo o registo anterior

Cada uma delas tem um único registo
*/

-- C U R S O R 
/*
DECLARE csClientes CURSOR FOR 
Ele guarda no cursor todos os atributos da tabela resultantes ficando guardado no csClientes

-- Declarar um handler para deteção final do cursor 

-- OPEN csClientes; carrega os dados para o cursor

-- FETCH csClintes; serve para obter os dados de uma linha do cursor

-- CLOSE csClientes; ele vai rempver o cursor de memória
*/

-- TEORIA DA NORMALIZAÇÃO DE DADOS
/*
Motivos para a normalização 
 -> Garantia de integridade de dados

Anomalias
Anomalia de Inserção 
Ocorre quando não se é capaz de inserir um dado registo numa tabela por causa da inexistência de outras dados

Anomalia de Atualização 
Sucede quando se atualizam apenas alguns elementos de dados (atualização parcial) contidos numa BD
Situação que leva a uma BD a um estado inconsistente
 
Regras da Normalização 
Formas Normais
1FN 
Uma tabela está na 1FN quando:
	-> tem uma chave primária
    -> apenas contém atributos atómicos
    -> não existem atributos multivalor
    -> não existem grupos repetidos

Todos os atributos devem ser atómicos (não podem conter valores compostos ou listas).
Objetivo: Eliminar grupos repetitivos.

2FN
Uma tabela está na 2FN quando:
	-> está na 1FN
    -> todos os atributos não pertencem à chave primária estão totalmente dependente 

Só acontece quando a chave primária à composta por mais de um atributo

DF -> dependência funcional 
A -------> B
B diz-se funcionalmente dependente de A se cada valor de A corresponder um e apenas um valor de B

Sempre que existam DF parciais devemos elimina-las
Resolvendo partindo a tabela, se as chaves primárias são simples então está normalizado segundo a 2FN
Objetivo: Garantir que atributos não-chave dependem de toda a PK.

Cria-mos novas tabelas
-> Cria-se uma com as chaves e os atributos que não dependem da mesma
-> E depois cria-se as tabelas necessárias para eliminar as dependências parciais

3FN
Uma tabela está na 3FN quando:
	-> está em 2FN
    -> todos os atributos que não pertencem à chave primária não apresentam dependência funcional transitiva com a chave primária

Dependência Transitiva: ocorre quando um atributo que não faz parte da chave primária determina outro atributo
Eliminar dependências transitivas 
Objetivo: Eliminar dependências entre atributos não-chave.

À medida que vai aplicando as normas aumenta o número de tabelas e a complexidade e diminiu a redundância

*/


