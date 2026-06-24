USE fe11;

-- 1
SELECT * FROM pedidos AS P
WHERE P.Funcionário IN (3,6,9);

-- 2
SELECT * FROM funcionários AS F
WHERE F.Responsável = (SELECT F.ID FROM funcionários AS F
WHERE F.Nome = 'João Chefinho');

-- 3
SELECT * FROM pedidos AS P
WHERE P.DataReceção BETWEEN '2025-10-25' AND '2025-10-30';

-- 4
SELECT I.id, I.Designação,
	COUNT(I.id) AS TotalVendas
FROM itens AS I
INNER JOIN pedidos_itens AS PI ON I.Id = PI.Item 
INNER JOIN pedidos AS P ON P.Nr = PI.Pedido 
WHERE P.DataReceção >= DATE_SUB(CURDATE(),INTERVAL 2 WEEK)
GROUP BY I.id,I.Designação
ORDER BY TotalVendas DESC
LIMIT 10;

-- 5
DELIMITER $$
CREATE PROCEDURE insereItens
(IN id INT,IN desgn VARCHAR(75),IN descr VARCHAR(250),IN preco DECIMAL(8,2),IN dose CHAR(1),IN tipo CHAR(1),IN iva INT)
BEGIN
	INSERT INTO itens (Id,Designação,Descrição,Preço,Dose,Tipo,IVA)
    VALUES (id,desgn,descr,preco,dose,tipo,iva);
END $$
DELIMITER ;

-- 6
SELECT I.Id, I.Designação
FROM itens AS I
WHERE I.Id NOT IN (
		SELECT DISTINCT PD.Item FROM pedidos_itens AS PD
        INNER JOIN pedidos AS P ON P.Nr = PD.Pedido
		WHERE P.DataReceção >= DATE_SUB(CURDATE(),INTERVAL 2 MONTH));

-- 7
ALTER TABLE itens
ADD COLUMN Estado CHAR(1) DEFAULT 'A';

-- 8
SET SQL_SAFE_UPDATES = 0;

UPDATE itens
SET Estado = 'R'
WHERE Id NOT IN (
 SELECT Id FROM (
	SELECT I.Id FROM itens AS I
	INNER JOIN pedidos_itens AS PI ON I.Id = PI.Item
	INNER JOIN pedidos AS P ON P.Nr = PI.Pedido
	WHERE P.DataReceção >= DATE_SUB(CURDATE(),INTERVAL 1 YEAR)
	) AS temp
);

SELECT * FROM itens;
SET SQL_SAFE_UPDATES = 1;

-- 9
CREATE VIEW vw_pedidoNaoAtendido 
AS
	SELECT
    *,
	TIMESTAMPDIFF(MINUTE,P.DataReceção,NOW()) AS DiffTime
    FROM pedidos AS P
    WHERE P.DataEntrega IS NULL
    ORDER BY DiffTime DESC;

SELECT * FROM vw_pedidoNaoAtendido;

-- 10
PREPARE valorMedioRefeicoes FROM 
 "SELECT AVG(P.Valor) AS ValorMedio FROM pedidos AS P
  WHERE DATE(P.DataPagamento) = ?";

SET @DataDoDia = '2025-12-02';
EXECUTE valorMedioRefeicoes USING @DataDoDia;
DEALLOCATE PREPARE valorMedioRefeicoes;

-- 11
DELIMITER $$
CREATE FUNCTION determinaPreco (nome_item VARCHAR(75))
RETURNS DECIMAL(8,2)
DETERMINISTIC 
BEGIN
	DECLARE precoFinal DECIMAL(8,2);
	
    SET precoFinal = (
		SELECT I.Preço FROM itens AS I
        WHERE I.Id = (SELECT I.Id FROM itens AS I
					  WHERE I.Designação = nome_item));
    
    RETURN precoFinal;
END $$ 
DELIMITER ;

-- 12
DELIMITER $$
CREATE TRIGGER atualizaPontos AFTER INSERT
ON pedidos
FOR EACH ROW
BEGIN 
	UPDATE clientes
    SET Pontos = Pontos + 10
    WHERE NEW.Cliente = Id;
END $$ 
DELIMITER ;

-- 13
DELIMITER $$
CREATE PROCEDURE registaPedido (IN nr INT,IN dataR DATETIME,IN dataE DATETIME,IN dataP DATETIME,
								IN me INT,IN v DECIMAL(8,2),IN vIVA DECIMAL(8,2),IN qS CHAR(1),IN e CHAR(1),
                                IN f INT,IN c INT)
BEGIN
	DECLARE EXIT HANDLER FOR SQLEXCEPTION 
    BEGIN 
		ROLLBACK;
	END;
	
    START TRANSACTION;
    
    INSERT INTO pedidos (Nr,DataReceção,DataEntrega,DataPagamento,Mesa,Valor,ValorComIVA,QualidadeServiço,Estado,Funcionário,Cliente)
	VALUES (nr,dataR,dataE,dataP,me,v,vIVA,qS,e,f,c);
    
    COMMIT;
    
END $$ 
DELIMITER ;

-- 14
CREATE TABLE IF NOT EXISTS taloes (
	Pedido INT NOT NULL,
    DataPagamento DATETIME,
    Valor DECIMAL(8,2) NOT NULL,
    ValorComIVA DECIMAL(8,2) AS (Valor * 1.23),
    Funcionário INT NOT NULL,
    Cliente INT NOT NULL,
	PRIMARY KEY (Pedido)
);

DELIMITER $$ 
CREATE PROCEDURE registarTalao 
(IN nr INT, IN dat DATETIME,IN VA DECIMAL(8,2), IN F INT,IN C INT) 
BEGIN
	INSERT INTO taloes (Nr,DataPagamento,Valor,Funcionário,Cliente)
	VALUES (nr,dat,VA,F,C);
END $$
DELIMITER ;

DELIMITER $$ 
CREATE TRIGGER emiteTalao AFTER INSERT 
ON pedidos
FOR EACH ROW 
BEGIN 
	CALL registarTalao (NEW.Nr,NEW.DataPagamento,NEW.Valor,NEW.Funcionário,NEW.Cliente);
END $$
DELIMITER ;	

-- 15
DELIMITER $$ 
CREATE PROCEDURE exportar_xlsx (IN P INT)
BEGIN
	SELECT * FROM taloes
	WHERE Pedido = p
	INTO OUTFILE "/var/lib/mysql-files/talao_13.xlsx"
	FIELDS TERMINATED BY '\t'
	LINES TERMINATED BY '\n';
END $$ 
DELIMITER ;

INSERT INTO taloes (Pedido, DataPagamento, Valor, Funcionário, Cliente)
VALUES (1, '2025-12-09 12:00:00', 25.50, 101, 202);

CALL exportar_xlsx (1);

-- 16
DELIMITER $$
CREATE PROCEDURE registaPedidos (IN mes INT)
BEGIN
	DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN 
		ROLLBACK;
	END;

	START TRANSACTION;
    
    CREATE TEMPORARY TABLE tmp_pedidos LIKE pedidos;
	CREATE TEMPORARY TABLE tmp_pedidosItens LIKE pedidos_itens;
	CREATE TEMPORARY TABLE tmp_itens LIKE itens;
    
    INSERT INTO tmp_pedidos
    SELECT * FROM pedidos AS P
	WHERE MONTH(P.DataReceção) = mes;

	INSERT INTO tmp_pedidosItens 
    SELECT PI.* FROM pedidos_itens AS PI
    INNER JOIN tmp_pedidos AS TP ON TP.Nr = PI.Pedido; 
		
	INSERT INTO tmp_itens 
    SELECT I.* FROM itens AS I
    INNER JOIN tmp_pedidosItens AS TPPI ON TPPI.Item = I.Id;
    
    COMMIT;
END $$
DELIMITER ;

-- 18
ALTER TABLE clientes
ADD COLUMN Cupao CHAR(1) DEFAULT 'N'; -- N indica NÃO sem desconto, S indica SIM com desconto 10%

SET GLOBAL event_scheduler = ON;

DELIMITER $$
CREATE EVENT emiteCupao
ON SCHEDULE
	AT '2025-12-31 23:59:59'
DO
BEGIN
	UPDATE clientes
    SET Cupao = 'S',Pontos = 0
    WHERE Pontos > 99;
END $$
DELIMITER ;

SET GLOBAL event_scheduler = OFF;