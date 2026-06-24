<template>
  <section class="card" aria-label="Comparação do cumprimento de medidas">
    <header class="cabecalho">
      <h2 class="titulo">Comparação do cumprimento de medidas</h2>
      <BotaoExportar 
        :elemento-grafico="cardRef"
        :dados="dadosExportar"
        nome-ficheiro="comparacao-medidas"
      />
    </header>

    <div class="filtro-pilares-wrapper">
      <FiltroPilares :pilares="pilares" v-model="filtroPilar" />
    </div>

    <div class="separador" role="separator" aria-hidden="true"></div>

    <div class="seletores-row" role="group" aria-label="Selecionar países para comparar">
      <FiltroPais :paises="paises" v-model="paisEsquerda" label-todos="Todos os países" />
      <div class="vs-badge" aria-hidden="true">vs</div>
      <FiltroPais :paises="paises" v-model="paisDireita"  label-todos="Todos os países" />
    </div>

    <div class="metricas-grid" ref="cardRef">
      <div class="coluna" :aria-label="paisEsquerda ? paisEsquerda.nome : 'Todos os países'">
        <MetricaCard label="TOTAL DE MARCOS" :valor="dadosEsquerda.total"     sufixo="medidas monitorizadas"    cor="var(--cor-azul-primario)" />
        <MetricaCard label="CUMPRIDOS"        :valor="dadosEsquerda.cumpridos" :pct="dadosEsquerda.pctCumpridos" cor="var(--cor-verde-escuro)"   cor-donut="var(--cor-verde-escuro)" />
        <MetricaCard label="EM RISCO"         :valor="dadosEsquerda.emRisco"   :pct="dadosEsquerda.pctEmRisco"   cor="var(--cor-laranja-escuro)" cor-donut="var(--cor-laranja-escuro)" />
        <MetricaCard label="ATRASADOS"        :valor="dadosEsquerda.atrasados" :pct="dadosEsquerda.pctAtrasados" cor="var(--cor-vermelho-escuro)" cor-donut="var(--cor-vermelho-escuro)" />
      </div>
      <div class="coluna" :aria-label="paisDireita ? paisDireita.nome : 'Todos os países'">
        <MetricaCard label="TOTAL DE MARCOS" :valor="dadosDireita.total"     sufixo="medidas monitorizadas"    cor="var(--cor-azul-primario)" />
        <MetricaCard label="CUMPRIDOS"        :valor="dadosDireita.cumpridos" :pct="dadosDireita.pctCumpridos" cor="var(--cor-verde-escuro)"   cor-donut="var(--cor-verde-escuro)" />
        <MetricaCard label="EM RISCO"         :valor="dadosDireita.emRisco"   :pct="dadosDireita.pctEmRisco"   cor="var(--cor-laranja-escuro)" cor-donut="var(--cor-laranja-escuro)" />
        <MetricaCard label="ATRASADOS"        :valor="dadosDireita.atrasados" :pct="dadosDireita.pctAtrasados" cor="var(--cor-vermelho-escuro)" cor-donut="var(--cor-vermelho-escuro)" />
      </div>
    </div>

  </section>
</template>

<script setup>
import { ref, computed } from 'vue'
import FiltroPais    from './FiltroPais.vue'
import FiltroPilares from './FiltroPilares.vue'
import MetricaCard   from './CardMetrica.vue'
import BotaoExportar from './BotaoExportar.vue'

const props = defineProps({
  paises: { type: Array, required: true },
  linhas: { type: Array, default: () => [] },
  pilares: { type: Array, required: true},
})

const filtroPilar  = ref(null)
const paisEsquerda = ref(null)
const paisDireita  = ref(null)
const cardRef = ref(null)

const dadosExportar = computed(() => [
  {
    'País':               paisEsquerda.value?.nome ?? 'Todos os países',
    'Pilar':              filtroPilar.value?.label ?? 'Todos',
    'Total':              dadosEsquerda.value.total,
    'Cumpridos':          dadosEsquerda.value.cumpridos,
    'Cumpridos (%)':      dadosEsquerda.value.pctCumpridos,
    'Em Risco':           dadosEsquerda.value.emRisco,
    'Em Risco (%)':       dadosEsquerda.value.pctEmRisco,
    'Atrasados':          dadosEsquerda.value.atrasados,
    'Atrasados (%)':      dadosEsquerda.value.pctAtrasados,
  },
  {
    'País':               paisDireita.value?.nome ?? 'Todos os países',
    'Pilar':              filtroPilar.value?.label ?? 'Todos',
    'Total':              dadosDireita.value.total,
    'Cumpridos':          dadosDireita.value.cumpridos,
    'Cumpridos (%)':      dadosDireita.value.pctCumpridos,
    'Em Risco':           dadosDireita.value.emRisco,
    'Em Risco (%)':       dadosDireita.value.pctEmRisco,
    'Atrasados':          dadosDireita.value.atrasados,
    'Atrasados (%)':      dadosDireita.value.pctAtrasados,
  }
])

function calcular(pais) {
  let fonte = pais
    ? props.linhas.filter(l => l.pais === pais.nome)
    : props.linhas

    if (filtroPilar.value) {
    fonte = fonte.filter(l => l.pilares?.includes(filtroPilar.value.value))
  }

  const total     = fonte.length
  const cumpridos = fonte.filter(l => l.estado === 'Dentro do Prazo').length
  const emRisco   = fonte.filter(l => l.estado === 'Em risco').length
  const atrasados = fonte.filter(l => l.estado === 'Atrasado').length

  return {
    total,
    cumpridos,
    emRisco,
    atrasados,
    pctCumpridos: total ? ((cumpridos / total) * 100).toFixed(1) : '0.0',
    pctEmRisco:   total ? ((emRisco   / total) * 100).toFixed(1) : '0.0',
    pctAtrasados: total ? ((atrasados / total) * 100).toFixed(1) : '0.0',
  }
}

const dadosEsquerda = computed(() => calcular(paisEsquerda.value))
const dadosDireita  = computed(() => calcular(paisDireita.value))
</script>

<style scoped>
.card {
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 10px;
  padding: 1.25rem 1.5rem;
  display: flex;
  flex-direction: column;
  gap: 1rem;
}

.cabecalho {
  display: flex;
  align-items: center;
  justify-content: space-between;
}

.titulo {
  font-size: 0.95rem;
  font-weight: 700;
  font-family: monospace;
  color: #111;
  margin: 0;
}

/* Filtro pilares a 100% */
.filtro-pilares-wrapper :deep(.seletor) {
  width: 100%;
}

.filtro-pilares-wrapper {
  width: 100%;
}

.filtro-pilares-wrapper :deep(.filtro-wrapper) {
  width: 100%;
}

.filtro-pilares-wrapper :deep(.filtro-btn) {
  width: 100%;
}

.filtro-pilares-wrapper :deep(.filtro-menu) {
  width: 100%;
}

/* Separador */
.separador {
  height: 3px;
  background: var(--cor-azul-primario);
  margin: 0 -0.05rem;
  opacity: 0.15;
}

/* Seletores de país — cada um ocupa metade disponível */
.seletores-row {
  display: flex;
  align-items: center;
  gap: 0.75rem;
}

.seletores-row :deep(.seletor) {
  flex: 1;
  width: auto;
  min-width: 0;
}

.seletores-row :deep(.btn-seletor) {
  width: 100%;
}

.vs-badge {
  background-color: var(--cor-azul-primario);
  color: white;
  font-size: 0.75rem;
  font-weight: 700;
  width: 32px;
  height: 32px;
  border-radius: 50%;
  display: flex;
  align-items: center;
  justify-content: center;
  flex-shrink: 0;
}

.metricas-grid {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 0.75rem;
}

.coluna {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
}
</style>