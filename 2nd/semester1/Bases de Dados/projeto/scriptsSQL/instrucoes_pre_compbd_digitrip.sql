-- DigiTrip
-- Script de prepared statement
USE DigiTrip;

-- Definição da Instrução Pré-Compilada
PREPARE sizeTable FROM
	'SELECT table_name AS Tabela,
	ROUND(data_length / 1024, 2) AS Dados_KB,
	ROUND(index_length / 1024, 2) AS Índices_KB,
	ROUND((data_length + index_length) / 1024, 2) AS Total_KB
	FROM information_schema.tables
	WHERE table_schema = "DigiTrip"
	AND table_name = ?';

-- Execução
SET @tabela = '<nome_da_tabela>';
EXECUTE sizeTable USING @tabela;

-- Libertação dos recursos
DEALLOCATE PREPARE sizeTable;

