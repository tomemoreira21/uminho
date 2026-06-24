Use sakila;

-- 1)
SELECT * FROM customer;

-- 2)
SELECT * FROM film
ORDER BY title ASC;
-- 	τ title ASC (film)

-- 3)
SELECT first_name, last_name FROM actor
ORDER BY last_name ASC;
	
-- 4)
SELECT rental_id, rental_date FROM rental 
WHERE rental_date BETWEEN '2005-05-01' AND '2005-05-31';

-- 5) 
SELECT COUNT(rental_id) AS Registos FROM rental
WHERE rental_date BETWEEN '2005-05-01 00:00:00' AND '2005-05-31 23:59:59';

-- v2 -> não usa o indice daí ser mais lento e o cálculo implicito do ano e mês -> menos eficiente
SELECT COUNT(rental_id) AS Registos FROM rental
WHERE MONTH(rental_date) = 5 AND YEAR(rental_date) = 2005;

-- γ COUNT(rental_id) (σ rental_date >= '2005-05-01 00:00:00' ∧ rental_date <= '2005-05-31 23:59:59' (rental));

-- 6)
SELECT DISTINCT C.customer_id 
FROM customer AS C
INNER JOIN rental AS R ON C.customer_id = R.customer_id
WHERE YEAR(R.rental_date) = 2006; 

-- 7)
SELECT SUM(P.amount) AS ValorTotal,
	COUNT(P.payment_id) AS NrPagamentos
FROM payment AS P;

-- 8)
SELECT C.customer_id, SUM(P.amount) AS Valor_Pago
FROM customer AS C 
	INNER JOIN payment AS P ON  C.customer_id = P.customer_id
WHERE C.customer_id IN ('1','11','111') 
	AND P.payment_date BETWEEN '2005-12-25' AND '2005-12-31 23:59:59'  
GROUP BY C.customer_id;

-- 9) 
PREPARE insertRental FROM
	'INSERT INTO rental (rental_date, inventory_id, customer_id, staff_id)
	VALUES (?, ?, ?, ?)';

-- 10)
SELECT * FROM rental AS R
WHERE R.customer_id IN (1,11);

-- 11)
SELECT * FROM rental AS R
WHERE R.return_date IS NULL;

-- 13)
CREATE VIEW vw_customer_emails 
AS 
	SELECT CONCAT(C.first_name,' ',C.last_name) AS Nome,
		   C.email AS Email 
	FROM customer AS C
	ORDER BY C.customer_id ASC;
    
-- SELECT * FROM vw_customer_emails; -- mostra a tabela da vista

/*
DAYOFWEEK(data) devolve o dia da semana 1 - Domingo, 2 - Segunda ... 
DAY(data) retorna o dia 
DAYOFYEAR(data) retorna o dia do ano por exemplo é o 321ª dia do ano
YEAR(data) retorna o ano
MONTH(data) retorna o mes
DATEDIFF(data2,data1) retorna o numero de dias entre a data2 - data1 
*/

-- 14) 
-- cria uma tabela nova igual à customer
CREATE TABLE IF NOT EXISTS customer_old LIKE customer;

-- copia os valores cujo active = 0
INSERT INTO customer_old 
	SELECT * FROM customer
	WHERE active = 0;
    
-- elimina os registos da customer com active = 0
DELETE FROM customer 
WHERE active = 0;

-- 15)
SELECT DISTINCT CONCAT(C.first_name,' ',C.last_name) AS Nome 
FROM customer AS C
INNER JOIN payment AS P ON P.customer_id = C.customer_id
WHERE P.staff_id = '1';

-- 16) Listar os dados dos clientes cujos países sejam a ‘Itália’, a ‘Espanha’ ou a ´Grécia´ 
SELECT * FROM customer AS CU
	INNER JOIN address AS A ON CU.address_id = A.address_id
    INNER JOIN city AS CI ON A.city_id = CI.city_id 
	INNER JOIN country AS C ON C.country_id = CI.country_id
WHERE C.country = 'Italy' OR C.country = 'Spain' OR C.country = 'Greece';

-- 17)
-- DAYOFWEEK(data) devolve o dia da semana 1 - Domingo 7 - Sábado
SELECT DISTINCT F.title AS Titulo 
	FROM film AS F
    INNER JOIN inventory AS I ON I.film_id = F.film_id
    INNER JOIN rental AS R ON I.inventory_id = R.inventory_id
WHERE YEAR(R.rental_date) = '2005' AND DAYOFWEEK(R.rental_date) IN (1,7)
ORDER BY F.title;

-- 18)
SELECT 0.125 * SUM(P.amount) AS Lucro 
FROM payment AS P
WHERE YEAR(P.payment_date) = '2005';

-- 19) Listar os 10 filmes mais alugados.
SELECT F.title,COUNT(F.film_id) AS Registos
	FROM film AS F
	INNER JOIN inventory AS I ON I.film_id = F.film_id 
    INNER JOIN rental AS R ON R.inventory_id = I.inventory_id
GROUP BY F.title 
ORDER BY Registos DESC 
LIMIT 10; 

-- 20)
SELECT CONCAT(C.first_name,' ',C.last_name) AS Nome,
	COUNT(R.rental_id) AS Total_Alugueres
FROM customer AS C
	INNER JOIN rental AS R ON R.customer_id = C.customer_id
GROUP BY Nome
ORDER BY Total_Alugueres DESC
LIMIT 3;

-- 21)
SELECT A.first_name,A.last_name 
FROM actor AS A
	INNER JOIN film_actor AS FA ON FA.actor_id = A.actor_id
	INNER JOIN film AS F ON F.film_id = FA.film_id 
WHERE F.release_year = '2006';

-- π first_name,last_name (actor ⨝ actor_id = actor_id (film_actor ⨝ film_id = film_id (σ release_year = '2006' (film))))

-- 22) 
SELECT first_name,last_name,email FROM customer
UNION 
SELECT first_name,last_name,email FROM staff
ORDER BY first_name,last_name ASC;

-- 23)
SELECT CI.city AS Cidade,
	COUNT(C.customer_id) AS Nr_Total
FROM city AS CI
INNER JOIN address AS A ON CI.city_id = A.city_id
INNER JOIN customer AS C ON C. address_id = A.address_id
GROUP BY Cidade;

-- γ city,COUNT(customer_id) → Nr_Total (city ⨝ city_id = city_id (customer ⨝ address_id = address_id address))

-- 24)
SELECT DISTINCT F.title
FROM film AS F
	INNER JOIN inventory AS I ON F.film_id = I.film_id
	INNER JOIN rental AS R ON I.inventory_id = R.inventory_id
WHERE YEAR(R.rental_date) = 2005 AND MONTH(R.rental_date) BETWEEN 1 AND 3;

-- 25)
SELECT C.customer_id,
	COUNT(*) AS NrFilmesAlugados
FROM rental as R
INNER JOIN customer AS C ON C.customer_id = R.customer_id
INNER JOIN address AS A ON A.address_id = C.address_id
INNER JOIN city AS CI ON CI.city_id = A.city_id
WHERE CI.city = 'London' AND YEAR(R.rental_date) = 2006
GROUP BY C.customer_id;

-- 26)
SELECT CONCAT(C.first_name,' ',C.last_name) AS Nome,
	SUM(P.amount) AS ValorPago
FROM customer AS C
INNER JOIN payment AS P ON P.customer_id = C.customer_id
WHERE P.payment_date >= '2005-12-01' AND P.payment_date <= '2005-12-31'
GROUP BY Nome,C.customer_id
ORDER BY ValorPago DESC
LIMIT 10;

-- 27)
SELECT F.film_id,F.title,F.release_year
FROM film AS F
INNER JOIN inventory AS I ON F.film_id = I.film_id 
LEFT OUTER JOIN rental AS R ON I.inventory_id = R.inventory_id
WHERE R.rental_id IS NULL
ORDER BY F.release_year ASC;

-- 28) 
SELECT AVG(DATEDIFF(return_date,rental_date)) AS Nr_médio FROM rental AS R
INNER JOIN inventory AS I ON I.inventory_id = R.inventory_id
WHERE I.store_id = '1';

-- 29) 
SELECT * FROM rental AS R 
LEFT OUTER JOIN payment AS P ON P.rental_id = R.rental_id; 

-- 30)
-- Criar uma View que armazene os film_id dos 10 filmes alugados mais recentemente.
CREATE OR REPLACE VIEW vw_ultimos10_films
AS
	SELECT I.film_id
    FROM inventory AS I
    INNER JOIN rental AS R ON R.inventory_id = I.inventory_id
    ORDER BY R.rental_date DESC
    LIMIT 10;
    
CREATE OR REPLACE VIEW vw_atores_ultimos10_films 
AS 
	SELECT DISTINCT CONCAT(A.first_name, ' ', A.last_name) AS NomeActor
	FROM actor AS A
	INNER JOIN film_actor AS FA ON FA.actor_id = A.actor_id
	INNER JOIN vw_ultimos10_films AS UF ON UF.film_id = FA.film_id
	ORDER BY NomeActor ASC;

-- SELECT * FROM vw_atores_ultimos10_films;

-- 31) 
-- (1) Definição da instrução pré-compilada
PREPARE insertCity FROM 
	'INSERT INTO city (city,country_id)
    VALUES (?,?)';  

-- Execução 
SET @city = 'Porto';
SET @country_id = '1';
EXECUTE insertCity USING @city,@country_id;

-- Libertação 
DEALLOCATE PREPARE insertCity;

-- 32)
-- (1) Definição da instrução pré-compilada
PREPARE listFilms FROM 
	'SELECT * FROM film AS F
    INNER JOIN inventory AS I ON F.film_id = I.film_id
    INNER JOIN rental AS R ON R.inventory_id = I.inventory_id
    WHERE R.customer_id = ?
    ';  

-- Execução 
SET @customer_id = '1';
EXECUTE listFilms USING @customer_id;

-- Libertação 
DEALLOCATE PREPARE listFilms;


 

