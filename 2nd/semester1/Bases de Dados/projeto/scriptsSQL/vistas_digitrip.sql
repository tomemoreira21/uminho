-- Vistas DigiTrip

USE DigiTrip;

-- Vista 1 -> Listar todos os perfis existentes na aplicação
CREATE VIEW vw_PerfilPublicoViajante AS
 SELECT
    V.idViajante AS id,
    V.Nome AS Nome,
    V.Biografia AS Biografia,
    V.DataNascimento AS DataNascimento,
    V.Nacionalidade AS Nacionalidade,
    V.FotoPerfil AS FotoPerfil,
    V.Pontuacao AS Pontuacao,
    V.DataRegisto AS DataRegisto
FROM Viajante AS V;

-- Vista 2 -> Todas os detalhes das Viagens existentes
CREATE VIEW vw_ViagensDetalhadas AS
 SELECT 
    Vi.idViagem AS idViagem,
    Vi.Titulo AS Titulo,
    Vi.Descricao AS Descricao,
    Vi.DataInicio AS DataInicio,
    Vi.DataFim AS DataFim,
    Vi.Motivo AS Motivo,
    Vj.idViajante AS idViajante,
    Vj.Nome AS NomeViajante,
    Vj.FotoPerfil AS FotoPerfil
FROM Viagem AS Vi
INNER JOIN Viajante AS Vj ON Vi.idViajante = Vj.idViajante;
    
-- Vista 3 -> Listar o ranking de países visitados
CREATE VIEW vw_TopPaisesVisitados AS
 SELECT 
	  P.Nome AS NomePais,
	  P.Continente AS Continente,
	  COUNT(DISTINCT Vis.idViagem) AS TotalVisitas
 FROM Pais AS P
	  INNER JOIN Localidade AS L ON P.idPais = L.idPais
	  INNER JOIN Visita AS Vis ON L.idLocalidade = Vis.idLocalidade
	  GROUP BY P.idPais, P.Nome, P.Continente
	  ORDER BY TotalVisitas DESC;
      