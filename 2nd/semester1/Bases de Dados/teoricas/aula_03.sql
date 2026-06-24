USE sakila;

-- junção interna: usar o INNER JOIN
-- não dando a indicacao * dará a projecao de tabela que junta as duas
SELECT C.customer_id, C.first_name, C.last_name, R.rental_date
	FROM customer AS C INNER JOIN rental AS R
		ON C.customer_id = R.customer_id
	WHERE R.rental_id IN (1,2,3,4);

SELECT C.customer_id, C.first_name, C.last_name, R.rental_date
	FROM customer AS C INNER JOIN rental AS R
		ON C.customer_id = R.customer_id AND R.rental_id IN (1,2,3,4); -- mais otimizada
        
-- theta junção, junção interna que envolve nao sao uma igualdade, expressão relacional
-- equi junção nao tem expressao relacional

-- Junção externas
-- mete na mesma os dados mesmo tendo NULL
-- EXEMPLO de junção externa à esquerda
-- vai aparecer os NULL à esquerda
SELECT C.customer_id, C.first_name, C.last_name, R.rental_date
	FROM customer AS C LEFT OUTER JOIN rental AS R 
		ON C.customer_id = R.customer_id;
	
-- testar o NULL metemos WHERE R.rental_id IS NULL;
-- EXEMPLO de junção externa à direita
-- vai aparecer os NULL à direita
SELECT * 
	FROM film_actor AS FA RIGHT OUTER JOIN film AS F
		ON FA.film_id = F.film_id;

-- SUBQUERIES
-- mostrar os clientes que não tem um aluguer
-- dá vazio pois todos os clientes têm aluguer
SELECT customer_id 
	FROM customer
    WHERE customer_id NOT IN (
		SELECT DISTINCT customer_id FROM rental);
	
-- SELECT DISTINCT customer_id FROM rental -> querie interna
-- a de fora é querie externa
/*
SELECT T.customer_id 
	FROM (SELECT * FROM customer WHERE customer_id IN (1,2,3)) AS T
	INNER JOIN ... 
    
    WHERE customer_id IN (...);
*/

-- VISTA 
-- Criação de uma vista != vista de utilizadores
-- Faz parte da área de descrição de dados
-- coloca a querie na vista de clientes, vista é uma tabela virtual (só mostra após da envocação) 
/*
- conseguimos esconder dados
- evita de ter queries numerosas
- podemos fazer queries mais elaboradas mais simples
*/

CREATE VIEW Clientes  
AS 
	SELECT customer_id AS "Id",
    CONCAT(first_name,' ',last_name) AS "Nome",
    store_id AS "Loja"
	FROM customer;
    
-- SELECT * FROM Clientes; -- mostra a tabela da vista

-- Instruções PRÉ-PREPARADAS
-- (1) Definição da instrução pré-compilada
PREPARE selCustomer FROM 
	'SELECT * FROM customer'; 
-- apenas avalia a sintaxe neste momento do prepare
-- depois de ficar compilada é só executar 

-- Execução 
EXECUTE selCustomer;

-- (3) Remoção da definição da instrução pré-compilada 
-- Libertação dos recursos reservados
DEALLOCATE PREPARE selCustomer;

-- permite passar parâmetros 
PREPARE selCustomerI FROM 
	'SELECT * FROM customer WHERE customer_id = ?';

-- (2) Execucao da instrução preparada 
SET @Id = '1'; -- define o valor para a variável
EXECUTE selCustomerI USING @Id;

-- (3) Remoção da instrução pré-compilada
-- Libertação dos recursos reservados
DEALLOCATE PREPARE selCustomerI;

-- NOTA: para não ter problema de pelicas usamos sempre "" para definir a instrução preparada

-- EVENTOS
-- permite definir um hoŕario para executar certa querie
 



	
