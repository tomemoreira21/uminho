Use sakila;

/*
Sintaxe de uma vista (view):
CREATE VIEW name AS 	
	-- sql statement;

Sintaxe de um procedimento (stored procedure):
DELIMITER $$
CREATE PROCEDURE name ({INT|OUT|INOUT}) parameter datatype)
BEGIN
	-- body
END $$
DELIMITER;

Sintaxe de uma função (user-defined function):
DELIMITER $$
CREATE FUNCION name(parameter datatype)
RETURNS datatype
[NOT] DETERMINISTIC -- o valor calculado dá sempre o mesmo então mete DETERMINISTIC
BEGIN 
	-- body
    RETURN (...)
END $$ 
DELIMITER;

Sintaxe de um gatilho (trigger)
DELIMITER $$ 
CREATE TRIGGER name {BEFORE|AFTER} {INSERT|UPDATE|DELETE}
ON table_name
FOR EACH ROW
BEGIN 
	-- body
END $$
DELIMITER;

Sintaxe de um evento (event):

SET GLOBAL event_scheduler = ON;

DELIMITER $$
CREATE EVENT 
*

/*
1) Implemente um procedimento que receba o identificador (“customer_id”) de um cliente e
forneça uma lista com a informação de todos os alugueres (“rental”) feitos por esse cliente,
ordenada de forma decrescente por data de aluguer (“rental_date”).
*/
DELIMITER $$ 
CREATE PROCEDURE info_alugueres(IN id INT)
BEGIN	
	SELECT * FROM rental AS R 
	WHERE R.customer_id = id
    ORDER BY R.rental_date DESC;
END $$
DELIMITER ;

CALL info_alugueres(1);

/*
2) Desenvolva uma função que receba o identificador de um filme (“film_id”) e forneça o preço
do seu aluguer. Assuma que esse valor está armazenado no atributo “replacement_cost” na
tabela “film”.
*/
-- função retorna sempre uma variável à partida declaramos a variável e damos return dessa variavel
DELIMITER $$
CREATE FUNCTION calcular_preco(id INT)
RETURNS DECIMAL(8,2)
DETERMINISTIC 
BEGIN 
	DECLARE preco DECIMAL(8,2);
    
    SELECT F.replacement_cost INTO preco
    FROM film AS F
    WHERE F.film_id = id;
	
    RETURN preco;
END $$
DELIMITER ;

SELECT calcular_preco(1);

/*
3) Modifique os esquemas das tabelas “customer” e “film”, acrescentando a cada uma delas o
atributo “NrAlugueres”. De seguida, crie na tabela “rental” um gatilho que atue sempre que
seja registado um novo aluguer, incrementando o valor dos atributos agora criados, nas
respetivas tabelas.
*/

ALTER TABLE customer ADD NrAlugueres INT DEFAULT 0; 
ALTER TABLE film ADD NrAlugueres INT DEFAULT 0; 

DELIMITER $$ 
CREATE TRIGGER atualizaAluguer
AFTER INSERT ON rental 
FOR EACH ROW 
BEGIN 
	UPDATE customer 
	SET NrAlugueres = NrAlugueres + 1
	where NEW.customer_id = customer_id;
    
    UPDATE film 
    SET NrAlugueres = NrAlugueres + 1
    WHERE film_id = 	
		(SELECT film_id FROM inventory
		WHERE inventory_id = NEW.inventory_id);
END $$
DELIMITER ;

INSERT INTO rental (inventory_id, customer_id,staff_id)
VALUES (1,1,2);

SELECT * FROM customer
WHERE customer_id = 1;

/*
4) Remova o gatilho desenvolvido na alínea anterior. De seguida, desenvolva um procedimento
que faça o registo de um novo aluguer na tabela “rental” e, com os dados desse novo registo,
incremente o valor do atributo “NrAlugueres” nas tabelas “customer” e “film”,
respetivamente. Na implementação deste procedimento deve utilizar transações
*/

DROP TRIGGER IF EXISTS atualizaAluguer;

DELIMITER $$
CREATE PROCEDURE registar_novo_aluguer (IN i_id INT,IN c_id INT,IN s_id INT)
BEGIN
	START TRANSACTION;
	INSERT INTO rental (inventory_id, customer_id,staff_id)
    VALUES (i_id,c_id,s_id);
    
    UPDATE customer 
	SET NrAlugueres = NrAlugueres + 1
	where c_id = customer_id;
    
    UPDATE film 
    SET NrAlugueres = NrAlugueres + 1
    WHERE film_id = 	
		(SELECT film_id FROM inventory
		WHERE inventory_id = i_id);
	
    COMMIT;
END $$
DELIMITER ;

CALL registar_novo_aluguer(2,1,1);

/*
5) Criar um evento que permita transferir todos os dias, às 23:00, os dados contidos na tabela
“rental” para a tabela “alugueres” (com esquema igual à tabela “rental”) localizada na base de
dados “SakilaPt”.
*/
CREATE DATABASE IF NOT EXISTS SakilaPT;
CREATE TABLE IF NOT EXISTS SakilaPT.alugueres LIKE sakila.rental;

SET GLOBAL event_scheduler = ON;

DELIMITER $$
CREATE EVENT transfere_dados
ON SCHEDULE 
	EVERY 1 DAY 
	STARTS CONCAT(CURDATE(), ' 23:00:00')
DO
  BEGIN
	INSERT INTO SakilaPT.alugueres
    SELECT * FROM sakila.rental;
END $$
DELIMITER ;

-- DROP EVENT transfere_dados;

/*
6) Implemente um procedimento para atribuição de “pontos de desconto” aos clientes da
“Sakila”. Quando executado, o procedimento deve carregar para um cursor o valor dos últimos
50 pagamentos (“payment”) de alugueres, agrupados por identificador de cliente
(“customer_id”), e, para cada um desses clientes calcular os “pontos de desconto” a tribuir –
1 ponto por cada 2,50$ pago. No final, o procedimento deve apresentar uma lista com o nome
dos clientes e os pontos que lhe foram atribuídos – a lista deve ser apresentada ordenada de
forma crescente por nome de cliente.
*/
-- CURSOR  -> percorre a tabela linha a linha
-- DROP PROCEDURE IF EXISTS pontos;

DELIMITER $$ 
CREATE PROCEDURE pontos ()
BEGIN	
    DECLARE done INT DEFAULT FALSE;
    DECLARE c_id INT;
    DECLARE score DECIMAL(8,2);
    DECLARE cur CURSOR FOR  (SELECT customer_id,
							        SUM(amount)/2.5 AS pontos
						     FROM (SELECT * FROM payment
								ORDER BY payment_date DESC
								LIMIT 50) AS 50_payments
								GROUP BY customer_id);

	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	
    DROP TEMPORARY TABLE IF EXISTS tmp_scores;
    CREATE TEMPORARY TABLE tmp_scores (
		id INT NOT NULL,
        points DECIMAL(8,2)
	);
    
    OPEN cur;
    
    read_loop: LOOP 
		FETCH cur INTO c_id,score;
	IF done THEN
		LEAVE read_loop;
	END IF;
	
    INSERT INTO tmp_scores (id,points)
    VALUES	(c_id,score);
                  
	END LOOP;
	
	CLOSE cur;
    
    SELECT T.id,
		CONCAT(C.first_name,' ',C.last_name) AS Nome,
        T.points FROM tmp_scores AS T
    INNER JOIN customer AS C ON C.customer_id = T.id
    ORDER BY nome ASC;
    
END $$
DELIMITER ;

CALL pontos();


