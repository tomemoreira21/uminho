// Funções de acesso assíncrono à API do PRR via json-server

export async function getPaises(db) {
  return await db.get('paises');
}

export async function getPaisPorId(db, id) {
  const paises = await db.get('paises');
  return paises.find(p => p.id === id) ?? null;
}

export async function getImpactoPais(db, paisId) {
  const pais = await getPaisPorId(db, paisId);
  return pais?.impacto ?? [];
}

export async function getAlertaPais(db, paisId) {
  const pais = await getPaisPorId(db, paisId);
  return pais?.alerta ?? null;
}

export async function getGastosRRP(db) {
  return await db.get('gastos_rrp');
}

export async function getGastosRRPPorPais(db, paisId) {
  const todos = await db.get('gastos_rrp');
  return todos.find(g => g.paisId === paisId)?.gastosRRP ?? [];
}

export async function getGastosRRPPorPilar(db, pilarId) {
  const todos = await db.get('gastos_rrp');
  return todos.map(g => ({
    paisId: g.paisId,
    pilar: g.gastosRRP.find(p => p.pilarId === pilarId) ?? null
  })).filter(g => g.pilar !== null);
}

export async function getCategoriasSociais(db) {
  return await db.get('categorias_sociais');
}

export async function getCategoriasSociaisPorPais(db, paisId) {
  const todos = await db.get('categorias_sociais');
  return todos.find(c => c.paisId === paisId)?.categoriasSociais ?? [];
}

export async function getMarcos(db) {
  return await db.get('marcos');
}

export async function getMarcosPorPais(db, paisId) {
  const todos = await db.get('marcos');
  return todos.find(m => m.paisId === paisId)?.marcos ?? null;
}

export async function getDesembolsos(db) {
  return await db.get('desembolsos');
}

export async function getDesembolsosPorPais(db, paisId) {
  const todos = await db.get('desembolsos');
  return todos.find(d => d.paisId === paisId)?.desembolsos ?? null;
}

export async function getInvestimentosPais(db) {
  return await db.get('investimentos_pais');
}

export async function getInvestimentosPorId(db, id) {
  const todos = await db.get('investimentos_pais');
  return todos.find(p => p.id === id) ?? null;
}

export async function getInvestimentosPorPaisId(db, paisId) {
  const todos = await db.get('investimentos_pais');
  return todos.find(p => p.paisId === paisId) ?? null;
}

export async function getInvestimentosPorPaisEPilar(db, paisId, pilarId) {
  const pais = await getInvestimentosPorPaisId(db, paisId);
  return pais?.pilares?.[pilarId] ?? null;
}

export async function getInvestimentosPaisOrdenadosPorTotal(db) {
  const todos = await db.get('investimentos_pais');
  return [...todos].sort((a, b) => 
    (b.subsidiosBilhoes + b.emprestimosBilhoes) - (a.subsidiosBilhoes + a.emprestimosBilhoes)
  );
}

export async function getCalendarioDesembolsos(db) {
  return await db.get('calendario_desembolsos');
}

export async function getCalendarioPorEstado(db, estado) {
  const todos = await db.get('calendario_desembolsos');
  return todos.filter(d => d.estado === estado);
}

export async function getCalendarioPorPais(db, paisId) {
  const todos = await db.get('calendario_desembolsos');
  return todos.filter(d => d.paisId === paisId);
}

export async function getCalendarioPorTipo(db, tipo) {
  const todos = await db.get('calendario_desembolsos');
  return todos.filter(d => d.tipo === tipo);
}

export async function getMarcosMetas(db) {
  return await db.get('marcos_metas');
}

export async function getMarcoMetasPorPais(db, paisId) {
  const todos = await db.get('marcos_metas');
  return todos.filter(m => m.paisId === paisId);
}

export async function getMarcoMetasPorEstado(db, estado) {
  const todos = await db.get('marcos_metas');
  return todos.filter(m => m.estado === estado);
}

export async function getMarcoMetasPorTipo(db, tipo) {
  const todos = await db.get('marcos_metas');
  return todos.filter(m => m.tipo === tipo);
}

export async function getMarcoMetasPorPilar(db, pilarId) {
  const todos = await db.get('marcos_metas');
  return todos.filter(m => m.pilares.includes(pilarId));
}

export async function getMarcoMetaPorId(db, id) {
  const todos = await db.get('marcos_metas');
  return todos.find(m => m.id === id) ?? null;
}

export async function getIndicadores(db) {
  return await db.get('indicadores');
}

export async function getIndicadorPorNumero(db, numero) {
  const todos = await db.get('indicadores');
  return todos.find(i => i.numero === numero) ?? null;
}

export async function getIndicadorValorPorPais(db, numero, paisId) {
  const indicador = await getIndicadorPorNumero(db, numero);
  return indicador?.valorPorPais?.[paisId] ?? 'N/D';
}

export async function getIndicadoresPorPilar(db, pilarId) {
  const todos = await db.get('indicadores');
  return todos.filter(i => i.pilaresIds.includes(pilarId));
}

export async function getTodosIndicadoresPorPais(db, paisId) {
  const todos = await db.get('indicadores');
  return todos.map(i => ({
    numero: i.numero,
    titulo: i.titulo,
    icone: i.icone,
    pilaresIds: i.pilaresIds,
    label: i.label,
    valorTotal: i.valorTotal,
    valorPais: i.valorPorPais?.[paisId] ?? 'N/D'
  }));
}

export async function getPilarCategoriasPorPais(db) {
  return await db.get('pilar_categorias_por_pais');
}

export async function getPilarCategorias(db, pilarId) {
  const todos = await db.get('pilar_categorias_por_pais')
  return todos.find(p => Number(p.pilarId) === Number(pilarId)) ?? null
}

export async function getPilarCategoriasParaPais(db, pilarId, paisCodigo) {
  const pilar = await getPilarCategorias(db, pilarId);
  if (!pilar) return [];
  return pilar.valorPorPais?.[paisCodigo]?.categorias ?? 
         pilar.categorias.map(c => ({ nome: c.nome, valor: c.mediaUE }));
}

export async function getPilarCategoriasMediaUE(db, pilarId) {
  const pilar = await getPilarCategorias(db, pilarId);
  return pilar?.categorias ?? [];
}

export async function getMapaPaises(db) {
  return await db.get('mapa_paises');
}

export async function getMapaPaisPorCodigo(db, codigo) {
  const todos = await db.get('mapa_paises');
  return todos.find(p => p.codigo === codigo) ?? null;
}

export async function getMapaPaisPorId(db, id) {
  const todos = await db.get('mapa_paises');
  return todos.find(p => p.id === id) ?? null;
}

export async function getMapaPaisesOrdenadosPorExecucao(db) {
  const todos = await db.get('mapa_paises');
  return [...todos].sort((a, b) => b.execucao - a.execucao);
}

export async function getHistoricoPais(db, codigo) {
  const pais = await getMapaPaisPorCodigo(db, codigo);
  return pais?.historico ?? [];
}

export async function getPilaresInfo(db) {
  return await db.get('pilares_info')
}

export async function getPilarInfoPorId(db, id) {
  const todos = await db.get('pilares_info')
  return todos.find(p => Number(p.id) === Number(id)) ?? null
}

export async function getMarcosMedidas(db) {
  return await db.get('marcos_medidas');
}

export async function getDetalhesMedidas(db, pilares) {
  const todos = await db.get('marcos_medidas')
  
  return Object.fromEntries(
    todos.map(m => [
      m.medida,
      {
        tipo:      m.tipo,
        pais:      m.pais,
        progresso: m.progresso,
        estado:    m.estado,
        pilares:   m.pilares.map(pilarValue => {
          const pilar = pilares.find(p => p.value === pilarValue)
          return { label: pilar?.label ?? pilarValue, cor: pilar?.cor ?? '' }
        }),
        historico: m.historico ?? [],
      }
    ])
  )
}

export async function getMarcosMedidasPorPais(db, pais) {
  const todos = await db.get('marcos_medidas');
  return todos.filter(m => m.pais === pais);
}

export async function getMarcosMedidasPorEstado(db, estado) {
  const todos = await db.get('marcos_medidas');
  return todos.filter(m => m.estado === estado);
}

export async function getMarcosMedidasPorTipo(db, tipo) {
  const todos = await db.get('marcos_medidas');
  return todos.filter(m => m.tipo === tipo);
}

export async function getMarcosMedidasPorPilar(db, pilar) {
  const todos = await db.get('marcos_medidas');
  return todos.filter(m => m.pilares.includes(pilar));
}