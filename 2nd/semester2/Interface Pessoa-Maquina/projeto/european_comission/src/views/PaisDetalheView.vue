<template>
  <div class="page" v-if="pais">

    <!-- Breadcrumb + Voltar -->
    <div class="breadcrumb">
      <BotaoVoltar @voltar="$router.push('/paises')" />
      <span class="breadcrumb-texto">
        Países > <strong>{{ pais.nome }}</strong>
      </span>
    </div>

    <!-- Título -->
    <h1 class="titulo">{{ pais.nome }} <span class="bandeira">{{ pais.bandeira }}</span></h1>

    <!-- Cards de totais -->
    <div class="totais-grid">
      <div class="total-card">
        <span class="total-label">Total de Subsídios Alocados</span>
        <span class="total-valor">€{{ pais.subsidios }}</span>
      </div>
      <div class="total-card">
        <span class="total-label">Total de empréstimos alocados</span>
        <span class="total-valor">€{{ pais.emprestimos }}</span>
      </div>
      <div class="total-card">
        <span class="total-label">Atribuição de RRP como parcela do PIB</span>
        <span class="total-valor">{{ pais.pib }}%</span>
      </div>
    </div>

    <!-- Impacto -->
    <div class="secao-card">
      <h2 class="secao-titulo">Impacto na vida das pessoas</h2>
      <div class="impacto-layout">
        <div class="impacto-grid">
          <div
            v-for="item in impactoComCores"
            :key="item.label"
            class="impacto-item"
            :style="{ borderColor: item.cor, backgroundColor: item.fundo }"
          >
            <span class="impacto-icone">{{ item.icone }}</span>
            <span class="impacto-valor" :style="{ color: item.cor }">{{ item.valor }}</span>
            <span class="impacto-label">{{ item.label }}</span>
          </div>
        </div>
        <div class="legenda-pilares">
          <div v-for="p in pilares" :key="p.nome" class="legenda-item">
            <span class="legenda-cor" :style="{ background: p.cor }"></span>
            <span class="legenda-nome">{{ p.nome }}</span>
          </div>
        </div>
      </div>
    </div>

    <!-- Alerta -->
    <div class="secao-card" v-if="pais.alerta">
      <div class="alerta-header">
        ⚠️ <strong>{{ pais.alerta.titulo }}</strong>
      </div>
      <p class="alerta-descricao" v-html="pais.alerta.descricao"></p>
      <div class="alerta-box">
        <p>📍 Isto é um problema mais alargado:</p>
        <ul>
          <li v-for="item in pais.alerta.comparacoes" :key="item">{{ item }}</li>
        </ul>
      </div>
    </div>

    <!-- Gráficos RRP + Categoria Social -->
    <div class="dois-cols">

      <!-- Gastos de RRP -->
      <div class="secao-card">
        <div class="grafico-header">
          <div>
            <h2 class="secao-titulo-dark">Gastos de RRP</h2>
            <p class="grafico-subtitulo">Parcela das despesas estimadas do plano contribuindo para cada pilar de política</p>
          </div>
          <BotaoExportar 
              :elemento-grafico="graficoRRPRef"
              :dados="dadosExportarRRP"
              :nome-ficheiro="`gastos-rrp-${pais?.nome ?? 'pais'}`"
          />
        </div>
         <div ref="graficoRRPRef">
          <GraficoBarras
            :categorias="gastosRRPComIcones"
            tema="claro"
            titulo=""
            :altura="320"
            :nota="'Este gráfico mostra a parte da contribuição estimada do plano de recuperação para cada pilar de política. Cada medida pode contribuir para várias políticas (primário e secundário), pelo que a contribuição total equivale a 200% dos fundos atribuídos.'"
            :mostrarBotao="false" 
          />
        </div>
      </div>

      <!-- Investimentos e reformas -->
      <CardInvestimentosReformas 
         :categoriasSociais="categoriasSociais"
      />
    </div>

    <!-- Marcos e Metas + Desembolsos -->
    <div class="dois-cols">
      <CardResumoMarcos :dados="marcos" />
      <CardResumoDesembolsos :dados="desembolsos" />
    </div>
  </div>
</template>

<script setup>
import { computed , ref, onMounted, watch} from 'vue'
import { useRoute } from 'vue-router'
import { dbAPI } from '../database/index.js'
import {
  getPaisPorId,
  getGastosRRPPorPais,
  getCategoriasSociaisPorPais,
  getMarcosPorPais,
  getDesembolsosPorPais,
} from '../services/getters.js'

import BotaoVoltar   from '../components/BotaoVoltar.vue'
import BotaoExportar from '../components/BotaoExportar.vue'
import GraficoBarras from '../components/GraficoBarras.vue'
import CardInvestimentosReformas from '../components/CardInvestimentosReformas.vue'
import CardResumoMarcos from '../components/CardResumoMarcos.vue'
import CardResumoDesembolsos from '../components/CardResumoDesembolsos.vue'

import iconVerde       from '../assets/icons/transicao-verde.png'
import iconDigital     from '../assets/icons/transformacao-digital.png'
import iconCrescimento from '../assets/icons/crescimento.png'
import iconCoesao      from '../assets/icons/coesao.png'
import iconSaude       from '../assets/icons/saude.png'
import iconPoliticas   from '../assets/icons/politicas.png'

const route = useRoute()

const pais            = ref(null)
const gastosRRP       = ref([])
const categoriasSociais = ref([])
const marcos          = ref(null)
const desembolsos     = ref(null)
const graficoRRPRef = ref(null)

const CORES_PILARES = {
  'transicao-verde':      { cor: '#74D5BE', fundo: '#74D5BE22' },
  'transformacao-digital':{ cor: '#9333EA', fundo: '#9333EA22' },
  'crescimento':          { cor: '#0066CC', fundo: '#0066CC22' },
  'coesao':               { cor: '#E12F2F', fundo: '#E12F2F22' },
  'saude':                { cor: '#5CD0F1', fundo: '#5CD0F122' },
  'politicas':            { cor: '#E05A00', fundo: '#E05A0022' },
}

const ICONES_PILARES = {
  'transicao-verde':       iconVerde,
  'transformacao-digital': iconDigital,
  'crescimento':           iconCrescimento,
  'coesao':                iconCoesao,
  'saude':                 iconSaude,
  'politicas':             iconPoliticas,
}

const CORES_IMPACTO = Object.values(CORES_PILARES)

const dadosExportarRRP = computed(() =>
  gastosRRPComIcones.value.map(c => ({
    nome:  c.nome,
    valor: c.valor,
  }))
)

async function carregarDados(paisId) {
  const [dadosPais, dadosGastos, dadosCategorias, dadosMarcos, dadosDesembolsos] =
    await Promise.all([
      getPaisPorId(dbAPI, paisId),
      getGastosRRPPorPais(dbAPI, paisId),
      getCategoriasSociaisPorPais(dbAPI, paisId),
      getMarcosPorPais(dbAPI, paisId),
      getDesembolsosPorPais(dbAPI, paisId),
    ])

  pais.value = {
    ...dadosPais,
    subsidios:   dadosPais.subsidiosMilhoes?.toLocaleString('pt-PT') + ' Milhões',
    emprestimos: dadosPais.emprestimosMilhoes?.toLocaleString('pt-PT') + ' Milhões',
    pib: dadosPais.pibPct,
  }
  gastosRRP.value = dadosGastos
  categoriasSociais.value = dadosCategorias
  marcos.value = dadosMarcos
  desembolsos.value = dadosDesembolsos ? {
    ...dadosDesembolsos,
    subsidios:   dadosDesembolsos.subsidiosLabel,
    emprestimos: dadosDesembolsos.emprestimosLabel,
  } : null
}

onMounted(() => carregarDados(route.params.id))

// Se navegares entre países sem sair da view
watch(() => route.params.id, (novoId) => carregarDados(novoId))

// Impacto com cores injetadas por índice
const impactoComCores = computed(() =>
  (pais.value?.impacto ?? []).map((item, i) => ({
    ...item,
    ...CORES_IMPACTO[i % CORES_IMPACTO.length],
  }))
)

// gastosRRP com ícones (pilarId já vem do JSON)
const gastosRRPComIcones = computed(() =>
  gastosRRP.value.map(g => ({
    nome:  g.nome,
    valor: g.valorPct,
    cor:   CORES_PILARES[g.pilarId]?.cor ?? '#ccc',
    icone: ICONES_PILARES[g.pilarId] ?? null,
  }))
)

const pilares = [
  { nome: 'Transição verde',                                       cor: '#74D5BE' },
  { nome: 'Crescimento inteligente, sustentável e inclusivo',      cor: '#0066CC' },
  { nome: 'Transformação digital',                                 cor: '#9333EA' },
  { nome: 'Coesão social e territorial',                           cor: '#E12F2F' },
  { nome: 'Saúde e resiliência económica, social e institucional', cor: '#5CD0F1' },
  { nome: 'Políticas para a próxima geração',                      cor: '#E05A00' },
]
</script>

<style scoped>
.page {
  background-color: var(--cor-sidebar-bg);
  min-height: 100%;
  padding: 2rem;
}

.breadcrumb {
  display: flex;
  align-items: center;
  gap: 1rem;
  margin-bottom: 1rem;
}

.breadcrumb-texto {
  font-size: 0.85rem;
  color: var(--cor-texto);
}

.breadcrumb-texto strong { font-weight: 700; }

.titulo {
  color: var(--cor-azul-primario);
  font-size: 2rem;
  margin-bottom: 1.5rem;
  font-family: monospace;
}

.bandeira { margin-left: 0.5rem; }

.totais-grid {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  gap: 1rem;
  margin-bottom: 1.5rem;
}

.total-card {
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 10px;
  padding: 1rem 1.25rem;
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
}

.total-label {
  font-size: 0.85rem;
  color: var(--cor-texto);
  font-family: monospace;
  font-weight: 600;
}

.total-valor {
  font-size: 1.4rem;
  font-weight: 700;
  color: var(--cor-azul-primario);
  font-family: monospace;
}

.secao-card {
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 10px;
  padding: 1.25rem 1.5rem;
  margin-bottom: 1.5rem;
  overflow: hidden;
}

.secao-titulo {
  font-size: 1rem;
  font-weight: 700;
  font-family: monospace;
  margin-bottom: 1rem;
  color: black;
}

.impacto-layout {
  display: flex;
  gap: 3rem;
  align-items: flex-start;
}

.impacto-grid {
  display: grid;
  grid-template-columns: repeat(3, 180px);
  gap: 0.75rem;
  flex-shrink: 0;
}

.impacto-item {
  border: 1px solid;
  border-radius: 10px;
  padding: 0.75rem;
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 0.3rem;
  text-align: center;
}

.impacto-icone { font-size: 1.5rem; }

.impacto-valor {
  font-size: 1.3rem;
  font-weight: 700;
  font-family: monospace;
}

.impacto-label {
  font-size: 0.75rem;
  color: var(--cor-texto);
  line-height: 1.3;
}

.legenda-pilares {
  display: flex;
  flex-direction: column;
  gap: 0.75rem;
  min-width: 260px;
  padding-top: 2.5rem;
  padding-left: 1.5rem;
}

.legenda-item {
  display: flex;
  align-items: center;
  gap: 0.75rem;
}

.legenda-cor {
  width: 18px;
  height: 18px;
  border-radius: 4px;
  flex-shrink: 0;
}

.legenda-nome {
  font-size: 0.85rem;
  color: var(--cor-texto);
}

.alerta-header {
  background: #E12F2F;
  color: white;
  padding: 0.5rem 1rem;
  border-radius: 6px;
  font-size: 0.9rem;
  margin-bottom: 1rem;
  display: inline-flex;
  align-items: center;
  gap: 0.5rem;
}

.alerta-descricao {
  font-size: 0.88rem;
  line-height: 1.6;
  color: var(--cor-texto);
  margin-bottom: 1rem;
}

.alerta-box {
  background: #FFF9C4;
  border: 1px solid #F5C300;
  border-radius: 8px;
  padding: 0.75rem 1rem;
  font-size: 0.85rem;
  color: var(--cor-texto);
}

.alerta-box ul { margin: 0.5rem 0 0 1rem; padding: 0; }
.alerta-box li { margin-bottom: 0.25rem; }

.dois-cols {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 1.5rem;
  margin-bottom: 1.5rem;
  align-items: stretch;
}

.dois-cols > .secao-card {
  margin-bottom: 0;
  display: flex;
  flex-direction: column;
}

.grafico-header {
  display: flex;
  justify-content: space-between;
  align-items: flex-start;
  margin-bottom: 1rem;
}

.secao-titulo-dark {
  font-size: 1rem;
  font-weight: 700;
  font-family: monospace;
  color: black;
  margin: 0 0 0.25rem;
}

.grafico-subtitulo {
  font-size: 0.78rem;
  color: var(--cor-texto);
  background: #e8f0fe;
  padding: 0.3rem 0.6rem;
  border-radius: 4px;
  margin: 0.5rem 0 0;
  display: inline-block;
}

@media (max-width: 768px) {
  .page {
    padding: 1rem;
  }

  .titulo {
    font-size: 1.3rem;
  }

  .totais-grid {
    grid-template-columns: 1fr;
  }

  .impacto-layout {
    flex-direction: column;
    gap: 1rem;
  }

  .impacto-grid {
    grid-template-columns: repeat(2, 1fr);
  }

  .legenda-pilares {
    padding-top: 0;
    padding-left: 0;
    min-width: unset;
  }

  .dois-cols {
    grid-template-columns: 1fr;
  }
}
</style>