<template>
  <div class="exportar-wrapper" ref="wrapperRef">
    <!-- Botão que abre/fecha o menu -->
    <button 
      class="exportar-btn" 
      @click="aberto = !aberto" 
      :aria-expanded="aberto"
      :aria-label="aberto ? 'Fechar menu de exportação' : 'Abrir menu de exportação'"
      aria-haspopup="true"
    >
        <img :src="iconExportar" alt="Exportar" class="exportar-icon" aria-hidden="true"/>
    </button>

    <!-- Menu só aparece quando aberto = true -->
    <div v-if="aberto" class="exportar-menu" role="menu" aria-label="Opções de exportação">
      <!-- Cria um botão por cada opção de exportação -->
      <button
        v-for="opcao in opcoes"
        :key="opcao"
        class="exportar-opcao"
        role="menuitem"
        :disabled="aExportar"
        :aria-label="`Exportar como ${opcao}`"
        @click="exportar(opcao)"
      >
        Exportar {{ opcao }}
      </button>
    </div>
  </div>
</template>

<script setup>
import { ref, onMounted, onUnmounted } from 'vue'
import { useToast } from 'primevue/usetoast'
import iconExportar from '../assets/exportar.png'
import jsPDF from 'jspdf'
import html2canvas from 'html2canvas'
import * as XLSX from 'xlsx'
import { saveAs } from 'file-saver'

const props = defineProps({
  // Referência ao elemento DOM do gráfico (ex: <div ref="graficoRef">)
  elementoGrafico: {
    type: Object,
    default: null
  },
  // Dados para exportar (Excel, CSV, JSON)
  dados: {
    type: Array,
    default: () => []
  },
  // Nome base do ficheiro exportado
  nomeFicheiro: {
    type: String,
    default: 'exportacao'
  }
})

// Controla se o menu está aberto ou fechado
const toast      = useToast()
const aberto = ref(false)
const aExportar  = ref(false)
const wrapperRef = ref(null)

// Lista de formatos de exportação disponíveis
const opcoes = ['PNG', 'SVG', 'PDF', 'Excel', 'CSV', 'JSON']


// Helpers de feedback
function ok(tipo) {
  toast.add({
    severity: 'success',
    summary: 'Exportação concluída',
    detail: `O ficheiro ${tipo} foi exportado com sucesso.`,
    life: 3000
  })
}

function erro(mensagem) {
  toast.add({
    severity: 'error',
    summary: 'Erro na exportação',
    detail: mensagem,
    life: 4000
  })
}

function aviso(mensagem) {
  toast.add({
    severity: 'warn',
    summary: 'Atenção',
    detail: mensagem,
    life: 4000
  })
}

async function exportar(tipo) {
  aberto.value   = false
  aExportar.value = true

  try {
    switch (tipo) {
      case 'PNG':   await exportarPNG();  break
      case 'SVG':   await exportarSVG();  break
      case 'PDF':   await exportarPDF();  break
      case 'Excel': exportarExcel();      break
      case 'CSV':   exportarCSV();        break
      case 'JSON':  exportarJSON();       break
    }
  } catch (e) {
    erro(`Erro inesperado ao exportar ${tipo}: ${e.message}`)
    console.error(e)
  } finally {
    aExportar.value = false
  }
}

// PNG
async function exportarPNG() {
  const elemento = props.elementoGrafico
  if (!elemento) return erro('Elemento do gráfico não disponível.')

  const canvas = await html2canvas(elemento, { backgroundColor: '#ffffff', scale: 2 })
  canvas.toBlob((blob) => {
    if (!blob) return erro('Não foi possível gerar a imagem PNG.')
    saveAs(blob, `${props.nomeFicheiro}.png`)
    ok('PNG')
  })
}

// SVG
async function exportarSVG() {
  const elemento = props.elementoGrafico
  if (!elemento) return erro('Elemento do gráfico não disponível.')

  // Caso 1 — existe um <svg> nativo (Recharts, D3, ApexCharts, etc.)
  const svgEl = elemento.querySelector('svg')
  if (svgEl) {
    const clone = svgEl.cloneNode(true)
    const { width, height } = svgEl.getBoundingClientRect()
    if (!clone.getAttribute('width'))  clone.setAttribute('width', width)
    if (!clone.getAttribute('height')) clone.setAttribute('height', height)

    clone.querySelectorAll('*').forEach(el => {
      const cs = window.getComputedStyle(el)
      ;['fill', 'stroke', 'font-size', 'font-family'].forEach(p => {
        if (!el.style[p]) el.style[p] = cs.getPropertyValue(p)
      })
    })

    const blob = new Blob(
      [new XMLSerializer().serializeToString(clone)],
      { type: 'image/svg+xml;charset=utf-8' }
    )
    saveAs(blob, `${props.nomeFicheiro}.svg`)
    ok('SVG')
    return
  }

  // Caso 2 — gráfico feito com divs/CSS — constrói SVG a partir dos dados
  if (props.dados.length) {
    const svgStr = construirSVGdeDados(props.dados, elemento)
    const blob = new Blob([svgStr], { type: 'image/svg+xml;charset=utf-8' })
    saveAs(blob, `${props.nomeFicheiro}.svg`)
    ok('SVG')
    return
  }

  // Caso 3 — canvas (Chart.js)
  const canvas = elemento.querySelector('canvas')
  if (canvas) {
    aviso('Gráfico em Canvas — exportado como PNG em alternativa ao SVG.')
    canvas.toBlob((blob) => blob && saveAs(blob, `${props.nomeFicheiro}.png`))
    return
  }

  erro('Não foi possível exportar SVG: formato de gráfico não suportado.')
}

// Constrói SVG a partir de dados [{ nome, valor }]
function construirSVGdeDados(dados, elemento) {
   const temFormato = dados.every(d => d.nome !== undefined && d.valor !== undefined)
  if (!temFormato) {
    throw new Error('Exportação SVG não disponível para este tipo de conteúdo. Use PNG ou PDF para exportar visualmente, ou Excel/CSV para os dados.')
  }

  const largura     = 600
  const alturaLinha = 40
  const paddingEsq  = 220
  const paddingDir  = 50
  const paddingTopo = 20
  const barraMax    = largura - paddingEsq - paddingDir
  const alturaTotal = paddingTopo + dados.length * alturaLinha + 40
  const valorMax    = Math.max(...dados.map(d => d.valor), 1)

  const corBarra = (() => {
    const el = elemento?.querySelector('[class*="barra-fill"], [class*="bar"], rect')
    if (el) {
      const bg = window.getComputedStyle(el).backgroundColor
      if (bg && bg !== 'rgba(0, 0, 0, 0)') return bg
    }
    return '#4a90d9'
  })()

  const linhas = dados.map((item, i) => {
    const y    = paddingTopo + i * alturaLinha
    const larg = (item.valor / valorMax) * barraMax
    return `
      <text x="${paddingEsq - 10}" y="${y + 24}"
        text-anchor="end" font-size="13" font-family="sans-serif" fill="#333333">
        ${item.nome}
      </text>
      <rect x="${paddingEsq}" y="${y + 8}"
        width="${Math.max(larg, 0)}" height="20" rx="4" fill="${corBarra}" />
      <text x="${paddingEsq + larg + 6}" y="${y + 23}"
        font-size="12" font-family="sans-serif" fill="#555555">
        ${item.valor.toFixed(1)}%
      </text>`
  }).join('')

  return `<svg xmlns="http://www.w3.org/2000/svg"
    width="${largura}" height="${alturaTotal}"
    viewBox="0 0 ${largura} ${alturaTotal}">
    <rect width="${largura}" height="${alturaTotal}" fill="white"/>
    ${linhas}
  </svg>`
}

// PDF
async function exportarPDF() {
  const elemento = props.elementoGrafico
  if (!elemento) return erro('Elemento do gráfico não disponível.')

  const canvas = await html2canvas(elemento, { backgroundColor: '#ffffff', scale: 2 })
  const imgData = canvas.toDataURL('image/png')
  const pdf = new jsPDF({
    orientation: canvas.width > canvas.height ? 'landscape' : 'portrait',
    unit: 'px',
    format: [canvas.width / 2, canvas.height / 2]
  })
  pdf.addImage(imgData, 'PNG', 0, 0, canvas.width / 2, canvas.height / 2)
  pdf.save(`${props.nomeFicheiro}.pdf`)
  ok('PDF')
}

// Excel
function exportarExcel() {
  if (!props.dados.length) return erro('Sem dados disponíveis para exportar.')

  const ws = XLSX.utils.json_to_sheet(props.dados)
  const wb = XLSX.utils.book_new()
  XLSX.utils.book_append_sheet(wb, ws, 'Dados')
  XLSX.writeFile(wb, `${props.nomeFicheiro}.xlsx`)
  ok('Excel')
}

// CSV
function exportarCSV() {
  if (!props.dados.length) return erro('Sem dados disponíveis para exportar.')

  const ws  = XLSX.utils.json_to_sheet(props.dados)
  const csv = XLSX.utils.sheet_to_csv(ws)
  const blob = new Blob(['\uFEFF' + csv], { type: 'text/csv;charset=utf-8' })
  saveAs(blob, `${props.nomeFicheiro}.csv`)
  ok('CSV')
}

// JSON
function exportarJSON() {
  if (!props.dados.length) return erro('Sem dados disponíveis para exportar.')

  const blob = new Blob(
    [JSON.stringify(props.dados, null, 2)],
    { type: 'application/json' }
  )
  saveAs(blob, `${props.nomeFicheiro}.json`)
  ok('JSON')
}

function fecharFora(e) {
  if (wrapperRef.value && !wrapperRef.value.contains(e.target)) {
    aberto.value = false
  }
}

onMounted(()  => document.addEventListener('click', fecharFora))
onUnmounted(() => document.removeEventListener('click', fecharFora))
</script>

<style scoped>
/* Wrapper com position relative para o menu se posicionar em relação a ele */
.exportar-wrapper {
  position: relative;
  display: inline-block;
}

/* Botão de exportação */
.exportar-btn {
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 6px;
  padding: 0.4rem 0.75rem;
  cursor: pointer;
  font-size: 1rem;
  color: var(--cor-texto);
  font-family: var(--font-principal);
  transition: background 0.2s;
}

/* Ícone de exportação */
.exportar-icon {
  width: 24px;
  height: 24px;
  object-fit: contain;
}

.exportar-btn:hover {
  background-color: var(--cor-azul-selecao);
}

/* Menu dropdown — posicionado abaixo do botão */
.exportar-menu {
  position: absolute;
  right: 0; /* alinha à direita do botão */
  top: 110%;
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 6px;
  display: flex;
  flex-direction: column;
  min-width: 160px;
  z-index: 100; /* fica por cima dos outros elementos */
  box-shadow: 0 4px 12px rgba(0,0,0,0.1);
}

/* Cada opção do menu */
.exportar-opcao {
  padding: 0.6rem 1rem;
  background: none;
  border: none;
  border-bottom: 1px solid var(--cor-border); /* linha separadora entre opções */
  text-align: left;
  cursor: pointer;
  font-family: var(--font-principal);
  color: var(--cor-texto);
  font-size: 0.9rem;
  transition: background 0.2s;
}

/* Remove a linha do último item */
.exportar-opcao:last-child {
  border-bottom: none;
}

.exportar-opcao:hover {
  background-color: var(--cor-azul-selecao);
}

.exportar-opcao:disabled {
  opacity: 0.5;
  cursor: not-allowed;
}
</style>