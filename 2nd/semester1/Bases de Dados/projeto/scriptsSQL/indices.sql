/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
ATENÇÃO NÃO É PARA EXECUTAR ESTE SCRIPT
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*/

-- RM1
CREATE INDEX idx_visita_localidade ON Visita(idLocalidade);
CREATE INDEX idx_localidade_pais ON Localidade(idPais);

-- RM3
CREATE INDEX idx_pais_nome ON Pais(Nome);

-- RM4
CREATE INDEX idx_viagem_viajante ON Viagem(idViajante);
CREATE INDEX idx_visita_idViagem ON Visita(idViagem);
CREATE INDEX idx_comentario_idViagem ON Comentario(idViagem);

-- RM5
CREATE INDEX idx_viajante_nacionalidade ON Viajante(Nacionalidade);

-- RM6
CREATE INDEX idx_viajante_pontuacao ON Viajante(Pontuacao);

-- RM7
CREATE INDEX idx_pais_continente ON Pais(Continente);
CREATE INDEX idx_viagem_dataInicio ON Viagem(DataInicio);

-- RM8
CREATE INDEX idx_comentario_avaliacao_viagem ON Comentario(idViagem, Avaliacao);

-- RM9
CREATE INDEX idx_comentario_avaliacao ON Comentario(Avaliacao);
CREATE INDEX idx_comentario_data ON Comentario(DataPublicacao);

-- RM11
CREATE INDEX idx_visita_idViagem ON Visita(idViagem);
