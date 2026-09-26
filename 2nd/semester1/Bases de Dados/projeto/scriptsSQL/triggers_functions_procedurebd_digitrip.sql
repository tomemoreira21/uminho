-- DigiTrip
-- Criação de triggers, procedures e functions

Use DigiTrip;

-- Trigger para adicionar +50 pontos a cada viagem inserida
DELIMITER $$
CREATE TRIGGER AtualizaPontuacao AFTER INSERT ON Viagem
FOR EACH ROW
BEGIN
    UPDATE Viajante
    SET Pontuacao = Pontuacao + 50
    WHERE idViajante = NEW.idViajante;
END $$
DELIMITER ;

-- Função de calculo de idade
DELIMITER $$

CREATE FUNCTION calculaIdade (DataNascimento DATE)
RETURNS INT
NOT DETERMINISTIC
READS SQL DATA
BEGIN
    DECLARE Idade INT;
    DECLARE AnoAtual INT;
    DECLARE MesAtual INT;
    DECLARE DiaAtual INT;
    DECLARE AnoNascimento INT;
    DECLARE MesNascimento INT;
    DECLARE DiaNascimento INT;
    
    SET AnoAtual = YEAR(CURDATE());
    SET MesAtual = MONTH(CURDATE());
    SET DiaAtual = DAY(CURDATE());
    SET AnoNascimento = YEAR(DataNascimento);
    SET MesNascimento = MONTH(DataNascimento);
    SET DiaNascimento = DAY(DataNascimento);

    SET Idade = AnoAtual - AnoNascimento;

    IF (MesAtual < MesNascimento OR (MesAtual = MesNascimento AND DiaAtual < DiaNascimento)) THEN
        SET Idade = Idade - 1;
    END IF;

    RETURN Idade;
END $$
DELIMITER ;

-- Procedimento que apaga por completo um utilizador. Remove a sua conta, as suas viagens, comentários e todos os
-- conteúdos por ele publicados.
DELIMITER $$
CREATE PROCEDURE spApagaViajante(IN id INT)
BEGIN
    DECLARE msg_text TEXT;
	DECLARE msg_number INT;
    -- Declara um handler para capturar qualquer exceção e reverter a transação
	DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
		GET DIAGNOSTICS CONDITION 1
        msg_text = MESSAGE_TEXT,
        msg_number = MYSQL_ERRNO;
		SELECT CONCAT('Erro ', msg_number, ': ', msg_text) AS Erro;
		ROLLBACK;
	END;
	
	START TRANSACTION;
    
    DELETE FROM Conteudo
    WHERE idConteudo IN (
		SELECT
            idConteudo
            FROM Viajante AS VJ 
            INNER JOIN Viagem AS VG
            ON VJ.idViajante = VG.idViajante
            INNER JOIN Conteudo AS C
            ON VG.idViagem = C.idViagem
            WHERE VJ.idViajante = id
    );
    
    DELETE FROM Visita
    WHERE idViagem IN (
		SELECT idViagem
		FROM Viagem
        WHERE idViajante = id
    );
    
    DELETE FROM Comentario
    WHERE idVijante = id;
    
    DELETE FROM Viagem 
    WHERE idViajante = id;
    
    DELETE FROM Viajante
    WHERE idViajante = id;
    
    COMMIT;
END $$
DELIMITER ;

