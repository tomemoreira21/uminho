<template>
  <div class="card">
    <div class="card-topo">
      <RouterLink class="ver-mais" :to="`/paises/${pais.id}`">Ver detalhes →</RouterLink>
      <div class="header-central">
        <h2 class="card-titulo">{{ pais.nome }}</h2>
        <img class="bandeira-mini" :src="`https://flagcdn.com/w80/${pais.codigo.toLowerCase()}.png`" :alt="pais.nome" />
      </div>
      <button class="fechar" @click="$emit('fechar')">✕</button>
    </div>

    <div class="stats">
      <div class="stat-card">
        <span class="stat-icone">💰</span>
        <div class="stat-texto">
          <p class="stat-label">Dotação MRR:</p>
          <p class="stat-valor">{{ pais.dotacao }}</p>
        </div>
      </div>
      <div class="stat-card">
        <span class="stat-icone">📤</span>
        <div class="stat-texto">
          <p class="stat-label">Desembolsado:</p>
          <p class="stat-valor">{{ pais.desembolsado }}</p>
        </div>
      </div>
      <div class="stat-card">
        <span class="stat-icone">✅</span>
        <div class="stat-texto">
          <p class="stat-label">Marcos cumpridos:</p>
          <p class="stat-valor">{{ pais.marcos }}</p>
        </div>
      </div>
    </div>

    <div class="historico">
      <p class="historico-titulo">Histórico</p>
      <div class="linha-tempo">
        <div v-for="(evento, i) in pais.historico" :key="i" class="evento">
          <div class="evento-ponto" />
          <div class="evento-info">
            <span class="evento-data">{{ evento.data }}</span>
            <span class="evento-tipo">{{ evento.tipo }}</span>
            <span class="evento-descricao">{{ evento.descricao }}</span>
            <span v-if="evento.justificacao" class="evento-meta"><b>Justificação:</b> {{ evento.justificacao }}</span>
            <span v-if="evento.impacto" class="evento-meta"><b>Impacto:</b> {{ evento.impacto }}</span>
          </div>
        </div>
      </div>
    </div>

    <div class="card-footer">
      <button class="btn-comparar" @click="$emit('comparar')">Comparar</button>
    </div>
  </div>
</template>

<script setup>
defineProps({ pais: { type: Object, required: true } })
defineEmits(['fechar', 'comparar'])
</script>

<style scoped>
.card {
  position: absolute;
  top: 1.5rem;
  right: 4.5rem;
  width: 400px;
  max-height: 90%;
  overflow-y: auto;
  background: #0e2044;
  border-radius: 14px;
  padding: 1.5rem;
  z-index: 100;
  color: white;
  font-family: var(--font-principal);
  display: flex;
  flex-direction: column;
  gap: 1.1rem;
}

.card-topo {
  display: flex;
  justify-content: space-between;
  align-items: center;
  gap: 0.5rem;
}

.header-central {
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 0.8rem;
  flex: 1;
}

.card-titulo {
  font-size: 1.2rem;
  font-weight: 800;
  margin: 0;
  font-family: monospace;
}

.bandeira-mini {
  width: 38px;
  height: auto;
  border-radius: 4px;
}

.ver-mais {
  font-size: 0.75rem;
  text-decoration: underline;
  color: #7ab3f0;
  white-space: nowrap;
}

.fechar {
  background: none;
  border: none;
  color: rgba(255,255,255,0.4);
  cursor: pointer;
  padding: 0 0 0 10px;
}
.fechar:hover { color: white; }

.stats { display: flex; flex-direction: column; gap: 0.5rem; }

.stat-card {
  background: rgba(255,255,255,0.08);
  border-radius: 8px;
  padding: 0.65rem 0.85rem;
  display: flex;
  align-items: center;
  gap: 0.75rem;
}

.stat-icone { font-size: 1.4rem; flex-shrink: 0; }

.stat-texto {
  display: flex;
  justify-content: space-between;
  align-items: center;
  flex: 1;
  gap: 0.4rem;
}

.stat-label { font-size: 0.75rem; color: rgba(255,255,255,0.65); margin: 0; }
.stat-valor { font-size: 0.88rem; font-weight: 800; font-family: monospace; margin: 0; white-space: nowrap; }

.historico-titulo { font-size: 0.82rem; font-weight: 700; margin: 0 0 0.6rem; color: rgba(255,255,255,0.7); }

.linha-tempo {
  display: flex;
  flex-direction: column;
  gap: 0.7rem;
  border-left: 2px solid rgba(255,255,255,0.15);
  padding-left: 1rem;
}

.evento { position: relative; }
.evento-info { display: flex; flex-direction: column; gap: 0.2rem; }

.evento-ponto {
  position: absolute;
  left: -1.38rem;
  top: 0.25rem;
  width: 10px;
  height: 10px;
  border-radius: 50%;
  background: #4a9eff;
  border: 2px solid #0e2044;
}

.evento-data { font-size: 0.68rem; color: #4a9eff; font-family: monospace; }
.evento-tipo { font-size: 0.75rem; font-weight: 700; }
.evento-descricao { font-size: 0.74rem; color: rgba(255,255,255,0.75); line-height: 1.4; }
.evento-meta { font-size: 0.71rem; color: rgba(255,255,255,0.55); line-height: 1.4; }

.card-footer { display: flex; justify-content: flex-end; }

.btn-comparar {
  background: #2563eb;
  color: white;
  border: none;
  border-radius: 8px;
  padding: 0.4rem 1rem;
  font-size: 0.8rem;
  font-weight: 600;
  cursor: pointer;
}
.btn-comparar:hover { background: #1d4ed8; }

@media (max-width: 768px) {
  .card { top: auto; bottom: 1rem; right: 1rem; width: calc(100% - 2rem); }
}
</style>