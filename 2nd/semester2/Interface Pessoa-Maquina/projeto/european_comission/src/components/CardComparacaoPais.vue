<template>
  <div class="card-comparacao">

    <!-- Card exterior -->
    <div class="card-exterior">
      <button class="fechar" @click="$emit('fechar')">✕</button>
      <h3 class="comparacao-titulo">Comparação</h3>

      <div class="blocos">

        <!-- País A -->
        <div class="bloco">
          <div class="bloco-topo">
            <RouterLink class="ver-mais" :to="`/paises/${paisA.id}`">Ver detalhes →</RouterLink>
          </div>
          <div class="bloco-header">
            <img class="bandeira" :src="`https://flagcdn.com/w80/${paisA.codigo.toLowerCase()}.png`" :alt="paisA.nome" />
            <h2 class="bloco-nome">{{ paisA.nome }}</h2>
          </div>
          <div class="stats">
            <div v-for="(stat, i) in stats" :key="i" class="stat-linha">
              <span class="stat-icone">{{ stat.icone }}</span>
              <span class="stat-label">{{ stat.label }}</span>
              <span class="stat-valor">{{ stat.valorA(paisA) }}</span>
              <span class="stat-delta" :class="stat.deltaClasseA(paisA, paisB)">
                {{ stat.deltaA(paisA, paisB) }}
              </span>
            </div>
          </div>
        </div>

        <!-- País B -->
        <div class="bloco" v-if="paisB">
          <div class="bloco-topo">
            <RouterLink class="ver-mais" :to="`/paises/${paisB.id}`">Ver detalhes →</RouterLink>
          </div>
          <div class="bloco-header">
            <img class="bandeira" :src="`https://flagcdn.com/w80/${paisB.codigo.toLowerCase()}.png`" :alt="paisB.nome" />
            <h2 class="bloco-nome">{{ paisB.nome }}</h2>
          </div>
          <div class="stats">
            <div v-for="(stat, i) in stats" :key="i" class="stat-linha">
              <span class="stat-icone">{{ stat.icone }}</span>
              <span class="stat-label">{{ stat.label }}</span>
              <span class="stat-valor">{{ stat.valorB(paisB) }}</span>
              <span class="stat-delta" :class="stat.deltaClasseB(paisA, paisB)">
                {{ stat.deltaB(paisA, paisB) }}
              </span>
            </div>
          </div>
        </div>

        <!-- Por selecionar -->
        <div class="bloco bloco-vazio" v-else>
          <p class="por-selecionar">Por selecionar</p>
          <p class="por-selecionar-sub">Clica num país no mapa</p>
        </div>

      </div>
    </div>

  </div>
</template>

<script setup>
const props = defineProps({
  paisA: { type: Object, required: true },
  paisB: { type: Object, default: null },
})

defineEmits(['fechar'])

function parseValor(str) {
  if (!str) return 0
  const n = parseFloat(str.replace(',', '.'))
  return isNaN(n) ? 0 : n
}

function diff(a, b) { return (parseValor(a) - parseValor(b)).toFixed(1) }
function seta(val) {
  const n = parseFloat(val)
  return n >= 0 ? `^ ${Math.abs(n)}` : `v ${Math.abs(n)}`
}
function classeByDiff(val) { return parseFloat(val) >= 0 ? 'positivo' : 'negativo' }

const stats = [
  {
    icone: '💰', label: 'Dotação MRR:',
    valorA: p => p.dotacao, valorB: p => p.dotacao,
    deltaA: (a, b) => b ? seta(diff(a.dotacao, b.dotacao)) : '',
    deltaB: (a, b) => b ? seta(diff(b.dotacao, a.dotacao)) : '',
    deltaClasseA: (a, b) => b ? classeByDiff(diff(a.dotacao, b.dotacao)) : '',
    deltaClasseB: (a, b) => b ? classeByDiff(diff(b.dotacao, a.dotacao)) : '',
  },
  {
    icone: '📤', label: 'Desembolsado:',
    valorA: p => p.desembolsado, valorB: p => p.desembolsado,
    deltaA: (a, b) => b ? seta(diff(a.desembolsado, b.desembolsado)) : '',
    deltaB: (a, b) => b ? seta(diff(b.desembolsado, a.desembolsado)) : '',
    deltaClasseA: (a, b) => b ? classeByDiff(diff(a.desembolsado, b.desembolsado)) : '',
    deltaClasseB: (a, b) => b ? classeByDiff(diff(b.desembolsado, a.desembolsado)) : '',
  },
  {
    icone: '✅', label: 'Execução:',
    valorA: p => p.execucao + '%', valorB: p => p.execucao + '%',
    deltaA: (a, b) => b ? seta((a.execucao - b.execucao).toFixed(1)) : '',
    deltaB: (a, b) => b ? seta((b.execucao - a.execucao).toFixed(1)) : '',
    deltaClasseA: (a, b) => b ? classeByDiff(a.execucao - b.execucao) : '',
    deltaClasseB: (a, b) => b ? classeByDiff(b.execucao - a.execucao) : '',
  },
]
</script>

<style scoped>
.card-comparacao {
  position: absolute;
  top: 1.5rem;
  right: 4.5rem;
  width: 400px;
  max-height: 90%;
  overflow-y: auto;
  z-index: 100;
  font-family: var(--font-principal);
}

/* Card exterior */
.card-exterior {
  background: #0e2044;
  border-radius: 16px;
  padding: 1.25rem;
  border: 1px solid rgba(255,255,255,0.08);
  display: flex;
  flex-direction: column;
  gap: 1rem;
  position: relative;
}

.fechar {
  position: absolute;
  top: 0.75rem;
  right: 0.85rem;
  background: none;
  border: none;
  color: rgba(255,255,255,0.4);
  font-size: 0.85rem;
  cursor: pointer;
  padding: 0;
}
.fechar:hover { color: white; }

.comparacao-titulo {
  font-size: 0.9rem;
  font-weight: 700;
  font-family: monospace;
  color: rgba(255,255,255,0.6);
  margin: 0;
  text-align: center;
}

.blocos {
  display: flex;
  flex-direction: column;
  gap: 0.75rem;
}

/* Cards interiores dos países */
.bloco {
  background: rgba(255,255,255,0.07);
  border-radius: 10px;
  padding: 1rem 1.1rem;
  color: white;
}

.bloco-topo {
  display: flex;
  justify-content: flex-start;
  margin-bottom: 0.6rem;
}

.ver-mais {
  font-size: 0.72rem;
  font-weight: 700;
  color: #7ab3f0;
  text-decoration: none;
  background: rgba(122,179,240,0.1);
  border: 1px solid rgba(122,179,240,0.2);
  border-radius: 6px;
  padding: 0.2rem 0.55rem;
}
.ver-mais:hover { background: rgba(122,179,240,0.2); }

.bloco-header {
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 0.65rem;
  margin-bottom: 0.9rem;
}

.bandeira { width: 38px; border-radius: 4px; }

.bloco-nome {
  font-size: 1.05rem;
  font-weight: 800;
  font-family: monospace;
  margin: 0;
}

.stats { display: flex; flex-direction: column; gap: 0.55rem; }

.stat-linha {
  display: grid;
  grid-template-columns: 24px 1fr auto auto;
  align-items: center;
  gap: 0.4rem;
}

.stat-icone { font-size: 0.95rem; }
.stat-label { font-size: 0.74rem; color: rgba(255,255,255,0.55); }
.stat-valor { font-size: 0.84rem; font-weight: 800; font-family: monospace; text-align: right; white-space: nowrap; }
.stat-delta { font-size: 0.74rem; font-weight: 700; font-family: monospace; min-width: 44px; text-align: right; }

.positivo { color: #4ade80; }
.negativo { color: #f87171; }

.bloco-vazio {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  min-height: 140px;
  border: 2px dashed rgba(255,255,255,0.2);
  background: transparent;
}

.por-selecionar { font-size: 0.95rem; font-weight: 700; font-family: monospace; color: rgba(255,255,255,0.45); margin: 0; }
.por-selecionar-sub { font-size: 0.72rem; color: rgba(255,255,255,0.25); margin: 0.3rem 0 0; }

@media (max-width: 768px) {
  .card-comparacao { top: auto; bottom: 1rem; right: 1rem; width: calc(100% - 2rem); }
}
</style>