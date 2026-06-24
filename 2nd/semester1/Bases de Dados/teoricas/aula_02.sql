USE Sakila;

/*
INNER JOIN -> COMBINA DADOS
UNION -> JUNÇÃO DE DADOS

GRAU DA TABELA -> aumenta se tu não deres a filtragem inicial
QUERY1 -> JUNÇÕES ANINHADAS, não faz mal a ordem de junção
DISTINCT -> evita repetições 

SELECT 
	O.Country,
    C.First_Name, C.Last_Name,
    R.Rental_Id, R.Rental_Date
	FROM Customer AS C INNER JOIN Address AS A
		ON C.Adress_Id = A.Adress_Id
        INNER JOIN City AS I
			ON A.City_Id = I.City_Id -- soma dos graus é a soma dos graus de cada tabela
			INNER JOIN Country AS O 
				ON O.Country_id = I.Country_Id;
				INNER JOIN Rental AS R 
                ON C.Customer_Id = R.Customer_Id
            
	WHERE O.Country LIKE 'A%' -- 'A_O%'; especifica que a 1ºletra é 'A' e a 3ºletra é 'O'
    ORDER BY O.Country ASC; -- ordena os países de forma ascendente
	
SELECT 
	O.Country AS País,
    COUNT (R.Rental_Id) AS Alugueres 
	FROM Customer AS C INNER JOIN Address AS A
		ON C.Adress_Id = A.Adress_Id
        INNER JOIN City AS I
			ON A.City_Id = I.City_Id -- soma dos graus é a soma dos graus de cada tabela
			INNER JOIN Country AS O 
				ON O.Country_id = I.Country_Id;
				INNER JOIN Rental AS R 
                ON C.Customer_Id = R.Customer_Id
            
	WHERE O.Country LIKE 'A%' -- 'A_O%'; especifica que a 1ºletra é 'A' e a 3ºletra é 'O'
    GROUP BY O.Country -- agrupa países repetidos, e depois dá count
    ORDER BY O.Country ASC; -- ordena os países de forma ascendente
    
	
SELECT 
	O.Country AS País,
    C.Customer_Id AS Cliente,
    COUNT (R.Rental_Id) AS Alugueres 
	FROM Customer AS C INNER JOIN Address AS A
		ON C.Adress_Id = A.Adress_Id
        INNER JOIN City AS I
			ON A.City_Id = I.City_Id -- soma dos graus é a soma dos graus de cada tabela
			INNER JOIN Country AS O 
				ON O.Country_id = I.Country_Id;
				INNER JOIN Rental AS R 
                ON C.Customer_Id = R.Customer_Id
            
	WHERE O.Country LIKE 'A%' -- 'A_O%'; especifica que a 1ºletra é 'A' e a 3ºletra é 'O'
    GROUP BY O.Country,C.Customer_Id
    ORDER BY O.Country ASC; -- ordena os países de forma ascendente
    
-- SUM,MAX,MIN,AVG -> funções que dá para usar em atributos

SELECT 
    C.Customer_Id AS Número, CONCAT(C.First_Name,' ',C.Last_Name) AS Nome,
    I.City AS Cidade,
    O.Country AS País,
    COUNT (R.Rental_Id) AS NrAlugueres,
	SUM(P.Amount) AS ValorPagoAlugeres	
	FROM Customer AS C INNER JOIN Address AS A
		ON C.Adress_Id = A.Adress_Id
        INNER JOIN City AS I
			ON A.City_Id = I.City_Id -- soma dos graus é a soma dos graus de cada tabela
			INNER JOIN Country AS O 
				ON O.Country_id = I.Country_Id;
				INNER JOIN Rental AS R 
                ON C.Customer_Id = R.Customer_Id
					INNER JOIN Payment AS P
						on P.Rental_Id = R.Rental_Id
            
    GROUP BY C.Customer_Id
    ORDER BY SUM(P.Amount) DESC
    LIMIT 10; -- top10 melhores clientes


*/