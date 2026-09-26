-- Queries DigiTrip

USE DigiTrip;

-- RM1: Listar os top 3 países mais visitados. Entende-se que um viajante visita
-- um determinado país durante uma viagem se pelos menos umas das localidades que 
-- visita se situa nesse país. Assim, se um viajante fizer uma viagem em que visita
-- duas localidades de um mesmo país isso apenas contará como uma visita a esse país.

SELECT  
	P.Nome AS País,
	COUNT(DISTINCT V.idViagem) AS TotalVisitas
	FROM Visita AS V 
    INNER JOIN Localidade AS L
	ON V.idLocalidade = L.idLocalidade 
	INNER JOIN Pais AS P
	ON L.idPais = P.idPais
	GROUP BY P.Nome
    ORDER BY TotalVisitas DESC	
    LIMIT 3;
    
-- RM2: Indicar o número de utilizadores registados.

SELECT COUNT(idViajante) AS NrUtilizadores FROM Viajante;

-- RM3: Listar todas as viagens feitas para um determinado país mostrando
-- o id da respetiva viagem, o título, a data início, a data final e por 
-- fim o motivo da viagem.

PREPARE RM3 FROM
	'SELECT
		VG.idViagem,
		VG.Titulo,
		VG.DataInicio,
		VG.DataFim,
		VG.Motivo
		FROM Viagem AS VG
		INNER JOIN Visita AS V 
		ON VG.idViagem = V.idViagem
		INNER JOIN Localidade AS L 
		ON V.idLocalidade = L.idLocalidade
		INNER JOIN Pais AS P 
		ON P.idPais = L.idPais
		WHERE P.Nome = ?';

SET @RM3_NomePais = 'Portugal';
EXECUTE RM3 USING @RM3_NomePais;
DEALLOCATE PREPARE RM3;

-- RM4: Indicar o viajante jovem (menos de 18 anos) com mais viagens feitas.

SELECT 
	VJ.Nome,
    COUNT(VG.idViagem) AS NrViagens,
    calculaIdade(VJ.DataNascimento) AS Idade
    FROM Viajante AS VJ
    INNER JOIN Viagem AS VG
    ON VJ.idViajante = VG.idViajante
    WHERE calculaIdade(VJ.DataNascimento) < 18
    GROUP BY VJ.idViajante
    ORDER BY NrViagens DESC
    LIMIT 1;
    
-- RM5: Listar o nome, email e data de registo de todos os Viajantes com 
-- nacionalidade 'Portuguesa'

SELECT 
	VJ.Nome,
    VJ.Email,
    VJ.DataRegisto
    FROM Viajante AS VJ
    WHERE VJ.Nacionalidade = 'Portuguesa';

-- RM6: Contar quantos Comentários cada Viajante experiente fez, listando 
-- o nome do viajante e o total de comentários. Considera-se que um viajante é experiente
-- se tiver uma pontuação superior a 100. 

SELECT
	VJ.NOME,
	COUNT(C.idComentario) AS NrComentários
    FROM Viajante AS VJ
    INNER JOIN Comentario AS C
    ON VJ.idViajante = C.idViajante
    WHERE VJ.Pontuacao > 100 
    GROUP BY VJ.idViajante;

-- RM7: Encontrar o Nome e ID das Localidades que foram visitadas em Viagens
-- iniciadas no ano de 2024 e que pertencem a um País no continente 'Europa'.

SELECT DISTINCT
	L.Nome,
    L.idLocalidade
    FROM Localidade AS L
    INNER JOIN Visita AS VS
    ON L.idLocalidade = VS.idLocalidade
    INNER JOIN Viagem AS VG
    ON VG.idViagem = VS.idViagem
    INNER JOIN Pais AS P
    ON L.idPais = P.idPais
    WHERE 
        P.Continente = 'Europa' 
        AND VG.DataInicio BETWEEN '2024-01-01' AND '2024-12-31';
    
-- RM8: Listar os top 5 países com maior média das avaliações dos Comentários
-- feitos sobre as Viagens que visitaram as suas Localidades, e mostrar o nome
-- do país, a média e o total de comentários considerados.

SELECT 
	P.Nome,
    AVG(C.Avaliacao) AS AvaliaçãoMédia,
    COUNT(C.idComentario) AS TotalComentários
    FROM Comentario AS C
    INNER JOIN Viagem AS VG
    ON C.idViagem = VG.idViagem
    INNER JOIN Visita AS VS
    ON VG.idViagem = VS.idViagem
    INNER JOIN Localidade AS L
    ON VS.idLocalidade = L.idLocalidade
    INNER JOIN Pais AS P
    ON L.idPais = P.idPais
    GROUP BY P.idPais
    ORDER BY AVG(C.Avaliacao) DESC
    LIMIT 5;
    
-- RM9: Encontrar o Comentário com a melhor avaliação para cada Viagem 
-- (no caso de haver empate, escolher o mais recente) e mostrar o título
-- da viagem, o texto do comentário e a avaliação.

SELECT 
	TVC.idViagem,
	TVC.Titulo,
    TVC.Texto,
    TVC.Avaliacao
    FROM (
		SELECT 
			VG.idViagem,
			VG.Titulo,
            C.Texto,
            C.Avaliacao,
            C.DataPublicacao,
            ROW_NUMBER() OVER (PARTITION BY VG.idViagem ORDER BY C.Avaliacao DESC, C.DataPublicacao DESC) AS RankAvaliacao
            FROM Viagem AS VG
            INNER JOIN Comentario AS C
            ON VG.idViagem = C.idViagem
    ) AS TVC
    WHERE RankAvaliacao = 1;
    
-- RM10: Listar o Nome de todos os Viajantes, e para cada um, indicar o número 
-- total de Países diferentes visitados. Viajantes que nunca participaram de 
-- uma Viagem (e, portanto, não têm visitas) devem aparecer na lista com a 
-- contagem de países igual a zero (0).

SELECT 
	VJ.Nome,
    COUNT(DISTINCT P.idPais) AS NrPaísesVisitados
    FROM Viajante AS VJ
    LEFT OUTER JOIN Viagem AS VG
    ON VJ.idViajante = VG.idViajante
    LEFT OUTER JOIN Visita AS VS
    ON VG.idViagem = VS.idViagem 
    LEFT OUTER JOIN Localidade AS L
    ON VS.idLocalidade = L.idLocalidade
    LEFT OUTER JOIN Pais AS P
    ON L.idPais = P.idPais
    GROUP BY VJ.idViajante;
    
-- RM11: Consultar numa única linha temporal todos os eventos relevantes associados a uma
-- determinada viagem — incluindo o início e fim da viagem, o início e fim das visitas realizadas 
-- e as datas de publicação de comentários — apresentando-os organizados por ordem cronológica.
PREPARE RM11 FROM 
	"SELECT 
		DataInicio AS Data,
        'Início Viagem' AS Tipo
        FROM Viagem
        WHERE idViagem = ?
        
	UNION
    
    SELECT 
		DataFim AS Data,
        'Fim Viagem' AS Tipo
        FROM Viagem
        WHERE idViagem = ?
        
	UNION 
    
    SELECT 
		DataInicio AS Data,
        'Início Visita' AS Tipo
        FROM Visita
        WHERE idViagem = ?
        
	UNION
    
    SELECT 
		DataFim AS Data,
        'Fim Visita' AS Tipo
        FROM Visita
        WHERE idViagem = ?
        
	UNION ALL
    
    SELECT 
		DataPublicacao AS Data,
		'Comentário Publicado' AS Tipo
        FROM Comentario
        WHERE idViagem = ?
        
	ORDER BY Data";
SET @RM11_idViagem = 3;
EXECUTE RM11 USING @RM11_idViagem,
					@RM11_idViagem,
                    @RM11_idViagem,
                    @RM11_idViagem,
                    @RM11_idViagem;
DEALLOCATE PREPARE RM11;