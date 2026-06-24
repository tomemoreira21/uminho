<template>
  <div :class="['distribuicao-container', { 'com-card': comCard }]">

    <div v-if="comCard" class="card-header">
      <h3 class="card-titulo">{{ titulo }}</h3>
      <div class="card-controls">
        <FiltroPais
          :paises="paises"
          :label-todos="labelTodos"
          v-model="paisInterno"
        />
        <BotaoExportar 
          :elemento-grafico="graficoRef"
          :dados="dadosExportar"
          :nome-ficheiro="titulo"
        />
      </div>
    </div>

    <div class="conteudo" ref="graficoRef">
      <div class="chart-wrapper">
        <svg :viewBox="`0 0 ${size} ${size}`" class="donut-chart">
          <circle
            v-for="(seg, i) in segmentos"
            :key="i"
            :cx="center" :cy="center" :r="raio"
            fill="transparent"
            :stroke="seg.cor"
            :stroke-width="espessura"
            :stroke-dasharray="`${seg.dash} ${circunferencia - seg.dash}`"
            stroke-dashoffset="0"
            :transform="`rotate(${seg.rotacao}, ${center}, ${center})`"
            class="segmento"
            @mouseenter="hoveredIndex = i"
            @mouseleave="hoveredIndex = null"
          />
          <text :x="center" :y="center + (labelCentroComputado ? 4 : 10)" text-anchor="middle" font-size="28">
            {{ iconeCentro }}
          </text>
          <text v-if="labelCentroComputado" :x="center" :y="center + 22" text-anchor="middle" font-size="11" fill="var(--cor-texto)">
            {{ labelCentroComputado }}
          </text>
        </svg>
      </div>

      <div class="legenda">
        <div
          v-for="(seg, i) in segmentos"
          :key="i"
          class="legenda-item"
          :class="{ 'legenda-hover': hoveredIndex === i }"
          @mouseenter="hoveredIndex = i"
          @mouseleave="hoveredIndex = null"
        >
          <div class="legenda-topo">
            <div class="legenda-esquerda">
              <span class="legenda-cor" :style="{ background: seg.cor }"></span>
              <span class="legenda-nome">{{ seg.nome }}</span>
            </div>
            <span class="legenda-pct" :style="{ color: seg.cor }">{{ seg.pct }}%</span>
          </div>
          <div class="barra-fundo">
            <div class="barra-preenchimento" :style="{ width: seg.pct + '%', background: seg.cor }"></div>
          </div>
        </div>
      </div>
    </div>

  </div>
</template>

<script setup>
import { ref, computed } from 'vue'
import FiltroPais    from './FiltroPais.vue'
import BotaoExportar from './BotaoExportar.vue'

const props = defineProps({
  paises:          { type: Array,   required: true },
  pilares:         { type: Array,   required: true },
  comCard:         { type: Boolean, default: false },
  titulo:          { type: String,  default: 'Distribuição por Pilares' },
  labelTodos:      { type: String,  default: 'Média UE' },
  paisSelecionado: { type: Object,  default: null },
  linhas:          { type: Array,   default: null },
  gastos:          { type: Array, default: () => [] },
  mostrarMedidas:  { type: Boolean, default: false },
})

const emit = defineEmits(['update:paisSelecionado'])

const paisInterno = ref(null)
const graficoRef = ref(null)

const dadosExportar = computed(() =>
  segmentos.value.map(s => ({
    'Pilar': s.nome,
    'Percentagem (%)': s.pct
  }))
)

const paisAtivo = computed(() =>
  props.comCard ? paisInterno.value : props.paisSelecionado
)

function calcularDeLinhas(fonte) {
  return props.pilares.map(p =>
    fonte.filter(l => l.pilares?.includes(p.value)).length
  )
}

const percentagensAtivas = computed(() => {
  if (props.linhas) {
    const fonte = paisAtivo.value
      ? props.linhas.filter(l => l.pais === paisAtivo.value.nome)
      : props.linhas
    return calcularDeLinhas(fonte)
  }
  
   if (props.gastos?.length) {
    const chave = paisAtivo.value?.id ?? null
    const entrada = props.gastos.find(g => g.paisId === chave)
    
    if (!entrada) return props.pilares.map(() => 0)

    return props.pilares.map(pilar =>
      entrada.gastosRRP.find(d => d.pilarId === pilar.value)?.valorPct ?? 0
    )
  }

  return props.pilares.map(() => 0)
})

const totalMedidas = computed(() => {
  if (!props.linhas) return 0
  return paisAtivo.value
    ? props.linhas.filter(l => l.pais === paisAtivo.value.nome).length
    : props.linhas.length
})

const labelCentroComputado = computed(() =>
  props.mostrarMedidas ? `${totalMedidas.value} medidas` : null
)

const iconeCentro = computed(() =>
  paisAtivo.value?.bandeira ?? '🇪🇺'
)

const hoveredIndex = ref(null)
const size           = 220
const center         = size / 2
const raio           = 75
const espessura      = 30
const circunferencia = 2 * Math.PI * raio

const segmentos = computed(() => {
  const vals  = percentagensAtivas.value
  const total = vals.reduce((a, b) => a + b, 0)
  if (!total) return props.pilares.map(p => ({ ...p, nome: p.label, pct: '0.0', dash: 0, rotacao: 0 }))

  let angulo = -90
  return props.pilares.map((pilar, i) => {
    const pct     = (vals[i] / total) * 100
    const dash    = (pct / 100) * circunferencia
    const rotacao = angulo
    angulo       += (pct / 100) * 360
    return { ...pilar, nome: pilar.label, pct: pct.toFixed(1), dash, rotacao }
  })
})
</script>

<style scoped>
.distribuicao-container {
  font-family: var(--font-principal);
}

.com-card {
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 12px;
  overflow: hidden;
}

.card-header {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  padding: 1.25rem 1.25rem 0;
}

.card-titulo {
  font-size: 1rem;
  font-weight: 700;
  color: black;
  margin: 0;
}

.card-controls {
  display: flex;
  align-items: center;
  gap: 0.4rem;
}

.conteudo {
  padding: 1rem 1.25rem 1.25rem;
  min-width: 280px;
  max-width: 340px;
}

.chart-wrapper {
  display: flex;
  justify-content: center;
  margin: 0.5rem 0 1.25rem;
}

.donut-chart {
  width: 180px;
  height: 180px;
  overflow: visible;
}

.segmento {
  cursor: pointer;
  transition: opacity 0.2s;
}

.segmento:hover { opacity: 0.8; }

.legenda {
  display: flex;
  flex-direction: column;
  gap: 0.6rem;
}

.legenda-item {
  padding: 0.2rem 0.3rem;
  border-radius: 5px;
  cursor: pointer;
  transition: background 0.15s;
}

.legenda-hover { background: #f5f5f5; }

.legenda-topo {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 0.3rem;
}

.legenda-esquerda {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  flex: 1;
  min-width: 0;
}

.legenda-cor {
  width: 12px;
  height: 12px;
  border-radius: 3px;
  flex-shrink: 0;
}

.legenda-nome {
  font-size: 0.72rem;
  color: var(--cor-texto);
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}

.legenda-pct {
  font-size: 0.8rem;
  font-weight: 700;
  min-width: 36px;
  text-align: right;
  flex-shrink: 0;
}

.barra-fundo {
  width: 100%;
  height: 5px;
  background: #e0e0e0;
  border-radius: 99px;
  overflow: hidden;
}

.barra-preenchimento {
  height: 100%;
  border-radius: 99px;
  transition: width 0.4s ease;
}

@media (max-width: 768px) {
  .conteudo {
    min-width: unset;
    max-width: unset;
  }

  .donut-chart {
    width: 140px;
    height: 140px;
  }
}
</style>