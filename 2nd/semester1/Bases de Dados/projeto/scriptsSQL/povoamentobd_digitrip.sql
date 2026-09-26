-- DigiTrip 
-- Script para o Povoamento da Base de Dados

Use DigiTrip;

-- Povoamento da Tabela Viajante
INSERT INTO Viajante 
	(Nome, Password, Biografia, DataRegisto, Email, Telefone, FotoPerfil, DataNascimento, Nacionalidade, Pontuacao)
	VALUES
	('Ana Martins', 'ana123', 'Viajante apaixonada por fotografia.', '2025-01-10', 'ana.martins@example.com', '+351 967334956', NULL, '2007-04-12', 'Portuguesa', 0),
	('Bruno Ferreira', 'bf_pass', NULL, '2025-01-12', 'bruno.ferreira@example.com', NULL, 'https://pics.com/bruno.jpg', '2006-09-21', 'Brasileira', 0),
	('Carla Sousa', 'carla_pw', 'Adora aventuras e natureza.', '2025-01-15', 'carla.sousa@example.com', NULL, NULL, '2010-11-03', 'Angolana', 0),
	('Daniel Rocha', 'dan12345', NULL, '2025-01-17', 'daniel.rocha@example.com','+351 967223883', 'https://pics.com/daniel.png', '2009-06-18', 'Portuguesa', 0),
	('Gabriela Costa', 'gab12pw', 'Ama conhecer novas culturas.', '2025-01-23', 'gabriela.costa@example.com', '+351 964554987', NULL, '2008-05-29', 'Portuguesa', 0),
    ('Luisa Oliveira', 'luisa134', NULL, '2025-04-22', 'luisa.oliveira@example.com', NULL, NULL, '2009-11-23', 'Angolana', 0);

-- SELECT * FROM Viajante;

-- Povoamento da Tabela Pais
INSERT INTO Pais 
	(Nome,Continente)
    VALUES 
    ('Portugal','Europa'),
    ('Espanha','Europa'),
    ('França','Europa'), 
    ('Suiça','Europa'),
	('Angola','África'),
    ('Brasil','América do Sul'); 
    
-- SELECT * FROM Pais;
    
-- Povoamento da Tabela Idiomas 
INSERT INTO Idiomas 
	(idPais,Idioma)
    VALUES 
    (1,'Português'),
    (2,'Espanhol'),
    (3,'Francês'),
    (4,'Alemão'),
    (4,'Francês'),
    (4,'Italiano'),
    (4,'Romanche'),
    (5,'Português'),
    (6,'Português');
    
-- SELECT * FROM Idiomas;

-- Povoamento da Tabela Viagem
-- A T E N Ç Ã O: Necessário correr primeiro o trigger
INSERT INTO Viagem
	(Titulo, Descricao, DataInicio, DataFim, Motivo, idViajante)
	VALUES
	('Fotografia Urbana Lisboa', 'Explorando as ruas de Lisboa em busca de fotografia de rua.', '2024-02-01', '2024-02-05', 'Lazer', 1),
	('Trilhas Montanhosas', 'Caminhadas e escaladas nas montanhas portuguesas.', '2024-03-10', '2024-03-15', 'Outros', 1),
	('Museus e Cultura', 'Visita aos museus e exposições de arte em Portugal.', '2024-04-01', '2024-04-05', 'Trabalho', 1),
	('Carnaval Rio', 'Participação nas festividades do Carnaval brasileiro.', '2025-03-01', '2025-03-07', 'Lazer', 2),
	('Praias Nordeste', 'Relaxamento nas praias do nordeste brasileiro.', '2024-06-01', '2024-06-07', 'Lazer', 2),
	('Safari Angola', 'Aventura na natureza selvagem de Angola.', '2025-04-10', '2025-04-20', 'Outros', 3),
	('Exploração Cultural Angola', 'Visita a museus e locais históricos angolanos.', '2024-05-05', '2024-05-12', 'Trabalho', 3),
	('Rota Castelos Portugal', 'Visita aos castelos históricos de Portugal.', '2025-05-05', '2025-05-15', 'Trabalho', 4),
	('Parques Naturais', 'Passeio por parques naturais e reservas em Portugal.', '2024-07-10', '2024-07-15', 'Outros', 4),
	('Gastronomia Francesa', 'Exploração da gastronomia francesa em Paris.', '2024-08-01', '2024-08-05', 'Outros', 5);

-- SELECT * FROM Viagem;

-- Povoamento da Tabela Localidade
INSERT INTO Localidade
	(Nome, Descricao, idPais)
	VALUES
	('Lisboa', 'Capital de Portugal, conhecida pelos seus bairros históricos e cultura vibrante.', 1),
	('Porto', NULL, 1),
	('Barcelona', 'Cidade espanhola conhecida pela arquitetura de Gaudí e praias.', 2),
	('Madrid', NULL, 2),
	('Paris', 'Capital da França, famosa pela Torre Eiffel e museus de arte.', 3),
	('Lyon', NULL, 3),
	('Genebra', 'Cidade suíça com instituições internacionais e belas paisagens.', 4),
	('Zurique', NULL, 4),
	('Luanda', 'Capital de Angola, com praias e cultura africana.', 5),
	('Benguela', NULL, 5),
	('Rio de Janeiro', 'Cidade brasileira famosa pelo Carnaval, praias e Cristo Redentor.', 6),
	('São Paulo', NULL, 6);
    
-- SELECT * FROM Localidade;

-- Povoamento da Tabela Visita
INSERT INTO Visita
	(idLocalidade, idViagem, Descricao, DataInicio, DataFim)
	VALUES
	(1, 1, 'Passeio fotográfico pelos bairros históricos de Lisboa.', '2024-02-01', '2024-02-05'), 
	(2, 2, NULL, '2024-03-10', '2024-03-15'),
	(1, 3, 'Visita a museus e centros culturais de Lisboa.', '2024-04-01', '2024-04-05'), 
	(12, 4, 'Carnaval e festas locais.', '2025-03-01', '2025-03-07'), 
	(11, 5, NULL, '2024-06-01', '2024-06-07'),
	(9, 6, 'Safari e vida selvagem.', '2025-04-10', '2025-04-20'), 
	(10, 7, 'Visita cultural em museus e centros históricos.', '2024-05-05', '2024-05-12'), 
	(1, 8, 'Roteiro pelos castelos históricos de Portugal.', '2025-05-05', '2025-05-15'), 
	(2, 9, NULL, '2024-07-10', '2024-07-15'), 
	(5, 10, 'Degustação da gastronomia francesa em Paris.', '2024-08-01', '2024-08-05'); 

-- SELECT * FROM Visita;

-- Povoamento da Tabela Comentario
INSERT INTO Comentario (Texto, Avaliacao, DataPublicacao, idViajante, idViagem)
	VALUES
	('Museus e ruas históricas fantásticos!', 5.0, '2024-02-06 10:00:00', 2, 1),
	('Adorei os detalhes arquitetónicos.', 4.5, '2024-02-06 11:00:00', 3, 1),
	('Fotografia perfeita, lugares incríveis.', 5.0, '2024-02-06 12:00:00', 5, 1),
	('Trilhas desafiadoras e paisagens lindas.', 4.5, '2024-03-16 09:00:00', 2, 2),
	('Caminhada muito bem organizada.', 4.0, '2024-03-16 10:00:00', 4, 2),
	('Museus incríveis, recomendo a visita.', 5.0, '2024-04-06 09:00:00', 2, 3),
	('Aprendi muito sobre a cultura portuguesa.', 4.5, '2024-04-06 10:00:00', 5, 3),
	('Carnaval animadíssimo e divertido!', 5.0, '2025-03-08 11:00:00', 1, 4),
	('Energia incrível nas ruas do Rio.', 4.5, '2025-03-08 12:00:00', 3, 4),
	('Praias lindas e água cristalina.', 5.0, '2024-06-08 10:00:00', 1, 5),
	('Relaxamento total, muito bom!', 4.5, '2024-06-08 11:00:00', 4, 5),
	('Safari espetacular, animais incríveis!', 5.0, '2025-04-21 16:00:00', 2, 6),
	('Paisagens naturais maravilhosas.', 4.5, '2025-04-21 17:00:00', 4, 6),
	('Museus e história locais fascinantes.', 4.5, '2024-05-13 10:00:00', 1, 7),
	('Aprendi muito sobre a cultura angolana.', 4.0, '2024-05-13 11:00:00', 5, 7),
	('Castelos lindos e bem preservados.', 5.0, '2025-05-16 09:00:00', 1, 8),
	('Muito interessante a arquitetura histórica.', 4.5, '2025-05-16 10:00:00', 3, 8),
	('Parques naturais incríveis e bem cuidados.', 4.5, '2024-07-16 12:00:00', 2, 9),
	('Trilhas bem sinalizadas e vistas fantásticas.', 4.0, '2024-07-16 13:00:00', 5, 9),
	('Gastronomia francesa maravilhosa, recomendo!', 5.0, '2024-08-06 13:00:00', 1, 10),
	('Paris tem pratos incríveis e restaurantes excelentes.', 4.5, '2024-08-06 14:00:00', 2, 10),
	('Experiência gastronômica incrível.', 4.5, '2024-08-06 15:00:00', 4, 10);

-- SELECT * FROM Comentario;

-- Povoamento da Tabela Conteudo
INSERT INTO Conteudo (Tipo,Url,Legenda, idLocalidade,idViagem)
	VALUES
	(0, 'https://pics.com/lisboa1.jpg', 'Vista panorâmica de Lisboa ao pôr do sol.', 1, 1),
    (1, 'https://videos.com/lisboa1.mp4', NULL, 1, 1),
    (0, 'https://pics.com/porto1.jpg', NULL, 2, 2),
    (0, 'https://pics.com/barcelona1.jpg', 'Arquitetura única em Barcelona.', 3, 3),
    (1, 'https://videos.com/barcelona1.mp4', NULL, 3, 3),
    (0, 'https://pics.com/madrid1.jpg', NULL, 4, 3),
    (0, 'https://pics.com/paris1.jpg', 'Torre Eiffel iluminada à noite.', 5, 10),
    (1, 'https://videos.com/paris1.mp4', NULL, 5, 10),
    (0, 'https://pics.com/lyon1.jpg', NULL, 6, 10),
    (0, 'https://pics.com/geneva1.jpg', 'Lago de Genebra com montanhas ao fundo.', 7, 9),
    (0, 'https://pics.com/zurich1.jpg', NULL, 8, 9),
    (0, 'https://pics.com/luanda1.jpg', 'Praia de Luanda ao amanhecer.', 9, 7),
    (0, 'https://pics.com/benguela1.jpg', NULL, 10, 6),
    (0, 'https://pics.com/rio1.jpg', 'Cristo Redentor visto do Corcovado.', 11, 4),
    (1, 'https://videos.com/rio1.mp4', NULL, 11, 4),
    (0, 'https://pics.com/saopaulo1.jpg', NULL, 12, 4),
    (1, 'https://videos.com/saopaulo1.mp4', NULL, 12, 4);

-- SELECT * FROM Conteudo;

