DROP DATABASE IF EXISTS teste1;
CREATE DATABASE teste1;
USE teste1;

DROP TABLE IF EXISTS Países;

CREATE TABLE Países (
	id INT NOT NULL PRIMARY KEY,
    designação VARCHAR(100)
);

INSERT INTO Países (id,designação)
VALUES (1,'Portugal'),
       (2,'Espanha'),
       (3,'Suíça'),
       (4,'Etiópia'),
       (5,'Alemanha');
	
/*
REPLACE -> substitui o registo se existir alterando todas as componentes, se não existir ele cria-o
AUTO-NUMERADO
O id auto-numerado no insert não metemos o id, já vai ser preenchido de forma automática
ao remover um elemento do auto-numerado faz com que aquele id não possa ser mais utilizado

*/

-- Remoção deve-se usar clausula de filtragem
-- DELETE FROM Países; // não fazer elimina toda a tabela
DELETE FROM Países
where id = 1;

-- TRUNCATE -> operação de descrição equivalente a drop table create table
/*
UPDATE -> atualização de dados numa tabela
Modificação dos dados de todos os registos de uma tabela (CUIDADO)
UPDATE Países
	SET designação = 'Um País';
*/
-- Altera o nome do país com o id = 1
UPDATE Países
	SET designação = 'Um País'
	WHERE id = 1;

/*
Não tendo o USE dá para fazer
SELECT *
	FROM <database>.<table>;
    
SELECT 'Olá Mundo!' AS "Mensagem"; -- cria a coluna "Mensagem" que tem o atributo "Olá Mundo!"
SELECT PI(); -- operações com funções 
SELECT 1 + 2 + 3 AS Resultado; -- operações matemáticas
SELECT NOW(); data e hora atual
SELECT CURDATE(); data atual
*/

SELECT * FROM Países; -- Devolve todos os atributos de todos os registos dos Países 

SELECT *
	FROM Países AS P 
    WHERE P.id = 2;
    
SELECT 
	P.id AS id,
    P.designação AS des
	FROM Países AS P
    WHERE id = 1 OR id = 2;

/*
Utilização da operação IN 
SELECT pais_id 
	FROM Países 
    WHERE pais_id IN (1,2,3,4,5);

também podemos usar o not IN
*/

-- Range Query
/*
SELECT customer_id,first_name,last_name,email
	FROM Customer 
    WHERE customer_id >= 1 AND customer_id <= 5;

importante os indices para não varrer a tabela toda, logo neste caso é importante o indice secundário

SELECT customer_id,first_name,last_name,email
	FROM Customer 
    WHERE customer_id BETWEEN 1 AND 5;
*/

/*
-- Pega nos registos com id = 1 || id = 2 || id = 3, ordenando por ordem crescente
SELECT staff_id,first_name,last_name,email
	FROM Staff 
    WHERE staff_id IN (1,2,3)
    ORDER BY staff_id ASC;

-- Ordena de forma crescente dando prioridade ao last_name usando em caso de empate no last_name, ordena decrescentemente pelo first_name
SELECT staff_id,first_name,last_name,email
	FROM Staff 
    ORDER BY last_name,first_name DESC;
*/

/*
Mapas de Interrogação - Querying Map
Envolve várias instruções para resolver uma query
*/

/*
SELECT First_Name, Last_Name
	FROM Customer
    WHERE Customer_id = 1;
    
Em álgebra;
projeção[first_name,last_name] (seleção [customer_id = 1] (customer))

A forma da árvore de resolução será:
	Customer 
       |
	seleção [customer_id = 1]
		|
	projeção[first_name,last_name]

DIBS -> bom para estudar álgebra relacional
*/

/*
Seleciona todos os registos que first_name começa por Su...
SELECT *
	FROM Customer
    WHERE First_Name LIKE 'Su%';

-- Mostra-me os pagamentos todos os realizados pela Susan id = 8
SELECT C.Customer_id, CONCAT(C.First_Name,' ',C.Last_Name),
	   P.Payment_Id,P.Payment_date,P.Amount
	FROM Payment AS P 
    INNER JOIN Customer AS C  -- faz a junção das tabelas com base id que tem de ser igual
		ON P.Customer_Id = C.Customer_Id
	WHERE C.Customer_Id = '8';
*/








