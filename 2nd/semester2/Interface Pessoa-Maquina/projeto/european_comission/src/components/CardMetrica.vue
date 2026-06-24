<template>
  <div class="metrica-card">
    <span class="label">{{ label }}</span>

    <div class="corpo">
      <span class="valor" :style="{ color: cor }">{{ valor }}</span>

      <!-- Donut com Chart.js -->
      <div v-if="pct !== undefined" class="donut-wrapper">
        <canvas ref="canvasRef" width="60" height="60"></canvas>
        <span class="pct-label">{{ pct }}%</span>
      </div>

      <!-- Sem donut: sufixo textual (linha "Total") -->
      <span v-else-if="sufixo" class="sufixo">{{ sufixo }}</span>
    </div>
  </div>
</template>

<script setup>
import { ref, onMounted, onUnmounted, watch } from 'vue'
import { Chart, DoughnutController, ArcElement, Tooltip } from 'chart.js'

Chart.register(DoughnutController, ArcElement, Tooltip)

const props = defineProps({
  label:    { type: String, required: true },
  valor:    { type: Number, default: 0 },
  pct:      { type: [String, Number], default: undefined },
  sufixo:   { type: String, default: undefined },
  cor:      { type: String, default: '#333' },
  corDonut: { type: String, default: '#333' },
})

const canvasRef = ref(null)
let chartInstance = null

// Resolve CSS variables para hex
// O Chart.js não percebe variáveis CSS como var(--cor-primaria). Esta função resolve esse problema:
// Se a cor já é um valor normal (#FF0000, blue) → devolve diretamente
// Se é uma variável CSS (var(--cor-primaria)) → extrai o nome --cor-primaria e vai buscar o valor real ao DOM
function resolverCor(cor) {
  if (!cor.startsWith('var(')) return cor
  const nomeProp = cor.match(/var\((--[^)]+)\)/)?.[1]
  if (!nomeProp) return '#333'
  return getComputedStyle(document.documentElement)
    .getPropertyValue(nomeProp)
    .trim() || '#333'
}

function destruir() {
  if (chartInstance) {
    chartInstance.destroy()
    chartInstance = null
  }
}

function criar() {
  if (!canvasRef.value || props.pct === undefined) return

  const pctNum  = parseFloat(props.pct)
  const corReal = resolverCor(props.corDonut)

  chartInstance = new Chart(canvasRef.value, {
    type: 'doughnut',
    data: {
      datasets: [{
        data: [pctNum, 100 - pctNum],
        backgroundColor: [corReal, '#e8ecf4'],
        borderWidth: 0,
        hoverOffset: 0,
      }]
    },
    options: {
      cutout: '72%',
      responsive: false,
      animation: { duration: 400 },
      plugins: {
        tooltip: { enabled: false },
        legend:  { display: false },
      },
    }
  })
}

onMounted(criar)
onUnmounted(destruir)

watch(() => [props.pct, props.corDonut], () => {
  destruir()
  criar()
  })
</script>

<style scoped>
.metrica-card {
  border: 1px solid var(--cor-border);
  border-radius: 8px;
  padding: 0.6rem 0.9rem;
  display: flex;
  flex-direction: column;
  gap: 0.25rem;
  background: white;
}

.label {
  font-size: 0.80rem;
  font-weight: 700;
  letter-spacing: 0.05em;
  color: var(--cor-texto);
  opacity: 0.6;
  text-transform: uppercase;
}

.corpo {
  display: flex;
  align-items: center;
  justify-content: space-between;
  gap: 0.5rem;
}

.valor {
  font-size: 2rem;
  font-weight: 700;
  line-height: 1;
}

.sufixo {
  font-size: 0.8rem;
  color: var(--cor-texto);
  opacity: 0.7;
  align-self: flex-end;
  padding-bottom: 4px;
}

.donut-wrapper {
  position: relative;
  width: 60px;
  height: 60px;
  flex-shrink: 0;
  display: flex;
  align-items: center;
  justify-content: center;
}

.pct-label {
  position: absolute;
  font-size: 0.75rem;
  font-weight: 700;
  color: var(--cor-texto);
  pointer-events: none;
  white-space: nowrap;
}
</style>