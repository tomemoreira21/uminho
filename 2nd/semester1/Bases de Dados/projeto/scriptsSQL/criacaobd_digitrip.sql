DROP DATABASE IF EXISTS DigiTrip;

CREATE DATABASE DigiTrip
	CHARACTER SET utf8mb4;

USE DigiTrip;

CREATE TABLE Viajante (
	idViajante INT NOT NULL AUTO_INCREMENT,
	Nome VARCHAR(75) NOT NULL,
	Password VARCHAR(75) NOT NULL,
	Biografia TEXT NULL,
	DataRegisto DATE NOT NULL,
	Email VARCHAR(150) NOT NULL UNIQUE,
    Telefone VARCHAR(20) NULL,
	FotoPerfil VARCHAR(2048) NULL,
	DataNascimento DATE NOT NULL,
	Nacionalidade VARCHAR(75) NOT NULL,
	Pontuacao INT NOT NULL DEFAULT 0,
	PRIMARY KEY (idViajante),
    CONSTRAINT chk_pontuacao_viajante CHECK (MOD(Pontuacao, 50) = 0)
);

CREATE TABLE Pais (
	idPais INT NOT NULL AUTO_INCREMENT,
	Nome VARCHAR(75) NOT NULL,
	Continente VARCHAR(75) NOT NULL,
	PRIMARY KEY (idPais)
);

CREATE TABLE Idiomas (
	idPais INT NOT NULL,
	Idioma VARCHAR(75) NOT NULL,
	PRIMARY KEY (idPais, Idioma),
	FOREIGN KEY (idPais) REFERENCES Pais (idPais)
);

CREATE TABLE Viagem (
	idViagem INT NOT NULL AUTO_INCREMENT,
	Titulo VARCHAR(75) NOT NULL,
	Descricao TEXT NOT NULL,
	DataInicio DATE NOT NULL,
	DataFim DATE NOT NULL,
	Motivo ENUM('Trabalho', 'Lazer', 'Outros') NOT NULL,
	idViajante INT NOT NULL,
	PRIMARY KEY (idViagem),
	FOREIGN KEY (idViajante) REFERENCES Viajante (idViajante),
	CONSTRAINT chk_datas_viagem CHECK (DataInicio <= DataFim)
);

CREATE TABLE Localidade (
	idLocalidade INT NOT NULL AUTO_INCREMENT,
	Nome VARCHAR(75) NOT NULL,
	Descricao TEXT NULL,
	idPais INT NOT NULL,
	PRIMARY KEY (idLocalidade),
	FOREIGN KEY (idPais) REFERENCES Pais (idPais)
);

CREATE TABLE Visita (
	idLocalidade INT NOT NULL,
	idViagem INT NOT NULL,
	Descricao TEXT NULL,
	DataInicio DATE NOT NULL,
	DataFim DATE NOT NULL,
	PRIMARY KEY (idLocalidade, idViagem),
	FOREIGN KEY (idLocalidade) REFERENCES Localidade (idLocalidade),
    FOREIGN KEY (idViagem) REFERENCES Viagem (idViagem),
    CONSTRAINT chk_datas_visita CHECK (DataInicio <= DataFim)
);

CREATE TABLE Comentario (
	idComentario INT NOT NULL AUTO_INCREMENT,
    Texto TEXT NOT NULL,
    Avaliacao DECIMAL(2,1) NOT NULL,
    DataPublicacao DATETIME NOT NULL,
    idViajante INT NOT NULL,
    idViagem INT NOT NULL,
    PRIMARY KEY (idComentario),
    FOREIGN KEY (idViajante) REFERENCES Viajante (idViajante),
    FOREIGN KEY (idViagem) REFERENCES Viagem (idViagem),
    CONSTRAINT chk_avaliacao 
		CHECK ((Avaliacao >= 0.0 AND Avaliacao <= 5.0) AND (MOD(Avaliacao * 2, 1) = 0))
);

CREATE TABLE Conteudo (
	idConteudo INT NOT NULL AUTO_INCREMENT,
	Tipo TINYINT NOT NULL,
    Url VARCHAR(2048) NOT NULL,
    Legenda TEXT NULL,
	idLocalidade INT NOT NULL,
    idViagem INT NOT NULL,
	PRIMARY KEY (idConteudo),
	FOREIGN KEY (idLocalidade) REFERENCES Localidade (idLocalidade),
    FOREIGN KEY (idViagem) REFERENCES Viagem (idViagem)
);
