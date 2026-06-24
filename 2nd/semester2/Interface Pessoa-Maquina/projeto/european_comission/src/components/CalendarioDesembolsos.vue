<template>
    <div class="card">
      <div class="card-header">
        <h3 class="card-titulo">Calendário de Desembolsos</h3>
        
        <div class="header-direita">
          <ul role="listbox" aria-label="Filtrar por estado" class="pills-group">
            <li
              v-for="f in filtros"
              :key="f.id"
              role="option"
              :aria-selected="filtroAtivo === f.id ? 'true' : 'false'"
              :class="['btn-pill', { 'btn-pill--ativo': filtroAtivo === f.id }]"
              tabindex="0"
              @click="filtroAtivo = f.id"
              @keydown.enter.space.prevent="filtroAtivo = f.id"
            >
              {{ f.label }}
            </li>
          </ul>

          <FiltroPais :paises="paises" label-todos="Todos os países" v-model="paisFiltro" />
          <BotaoExportar 
            :elemento-grafico="tabelaRef"
            :dados="dadosExportar"
            :nome-ficheiro="`calendario-desembolsos-${filtroAtivo}`"
          />
        </div>
      </div>

      <div class="tabela-container" ref="tabelaRef">
        <table class="tabela">
          <thead>
            <tr>
              <th class="col-pais">País</th>
              <th class="col-data">Data</th>
              <th class="col-pedido">Pedido de Pagamento</th>
              <th class="col-tipo">Tipo de Financiamento</th>
              <th class="col-valor">Valor Total (€)</th>
              <th class="col-estado">Estado</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="(linha, i) in linhasFiltradas" :key="i">
              <td class="col-pais">
                <span class="bandeira">{{ linha.bandeira }}</span>{{ linha.pais }}
              </td>
              <td class="col-data">{{ linha.data }}</td>
              <td class="col-pedido">{{ linha.pedido }}</td>
              <td class="col-tipo">{{ linha.tipo }}</td>
              <td class="col-valor">{{ linha.valorEur }}</td>
              <td class="col-estado">
                <span class="estado-badge" :class="`estado--${linha.estadoId}`">
                  {{ linha.estado }}
                </span>
              </td>
            </tr>

            <tr v-if="linhasFiltradas.length === 0">
              <td colspan="6" class="sem-resultados">Nenhum resultado encontrado.</td>
            </tr>
          </tbody>
        </table>
      </div>

    <p v-if="descricao" class="nota-grafico">{{ descricao }}</p>
  </div>
</template>

<script setup>
import { ref, onMounted, computed, nextTick, watch } from 'vue'
import { dbAPI } from '../database/index.js' 
import { getCalendarioDesembolsos, getPaises } from '../services/getters.js'
import FiltroPais    from './FiltroPais.vue'
import BotaoExportar from './BotaoExportar.vue'

defineProps({ 
  paises: Array,
  descricao: { type: String, default: null }
})

const linhas = ref([])
const listaPaises = ref([])
const filtroAtivo = ref('todos')
const paisFiltro  = ref(null)
const tabelaRef = ref(null)
const btnRefs = ref([])
const anuncioAcessibilidade = ref('')

const filtros = [
  { id: 'todos',    label: 'Todos'    },
  { id: 'pagos',    label: 'Pagos'    },
  { id: 'proximos', label: 'Próximos' },
  { id: 'planeados', label: 'Planeados' },
]

const dadosExportar = computed(() =>
  linhasFiltradas.value.map(l => ({
    'País':                 `${l.bandeira} ${l.pais}`,
    'Data':                 l.data,
    'Pedido de Pagamento':  l.pedido,
    'Tipo de Financiamento': l.tipo,
    'Valor Total (€)':      l.valorEur,
    'Estado':               l.estado,
  }))
)

watch(filtroAtivo, async () => {
  anuncioAcessibilidade.value = ''
  await nextTick()  // espera o Vue recalcular linhasFiltradas
  const total = linhasFiltradas.value.length
  const label = filtros.find(f => f.id === filtroAtivo.value)?.label
  anuncioAcessibilidade.value = `${total} resultados para ${label}`
})

onMounted(async () => {
  // Carrega apenas as coleções necessárias da API
  // Promise.all permite carregar ambas em paralelo para ser mais rápido
  const [dadosCalendario, dadosPaises] = await Promise.all([
    getCalendarioDesembolsos(dbAPI),
    getPaises(dbAPI)
  ])
  
  linhas.value = dadosCalendario
  listaPaises.value = dadosPaises
})

const linhasFiltradas = computed(() => {
  let resultado = linhas.value
  if (filtroAtivo.value !== 'todos') {
    const mapa = { pagos: 'Pago', proximos: 'Próximo', planeados: 'Planeado' }
    resultado = resultado.filter(l => l.estado === mapa[filtroAtivo.value])
  }
  if (paisFiltro.value) {
    resultado = resultado.filter(l => l.pais === paisFiltro.value.nome)
  }
  return resultado
})
</script>

<style scoped>
.card {
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 12px;
  overflow: hidden;
  height: 100%;
  display: flex;
  flex-direction: column;
}

.card-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0.75rem 1.5rem;
  gap: 1rem;
  border-bottom: 1px solid var(--cor-border);
}

.card-titulo {
  font-size: 1.25rem;
  font-weight: 700;
  color: black;
  margin: 0;
  flex-shrink: 0; /* título nunca encolhe */
}

/* Filtros agrupados à direita */
.header-direita {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  flex-shrink: 0;
}

.pills-group {
  display: flex;
  gap: 0.4rem;
  list-style: none;
  padding: 0;
  margin: 0;
}

.sr-only {
  position: absolute;
  width: 1px;
  height: 1px;
  padding: 0;
  margin: -1px;
  overflow: hidden;
  clip: rect(0,0,0,0);
  white-space: nowrap;
  border: 0;
}

.btn-pill {
  padding: 0.3rem 1rem;
  border: 1px solid #E2E8F0;
  border-radius: 20px;
  background: #F8FAFC;
  font-size: 0.8rem;
  cursor: pointer;
  color: #64748B;
  transition: all 0.2s;
  white-space: nowrap;
}

.btn-pill--ativo {
  background: var(--cor-azul-escuro);
  color: white;
  border-color: var(--cor-azul-escuro);
}

/* Tabela */
.tabela-container {
  flex: 1;
  overflow-y: auto;   /* ← scroll vertical */
  overflow-x: auto;
  padding: 1.5rem 1rem 1rem;
  max-height: 400px;
  margin-bottom: 0.75rem;
}

.tabela {
  width: auto;
  min-width: 100%;
  border-collapse: collapse;
  font-size: 0.82rem;
  border: 1px solid var(--cor-border);
  border-radius: 8px;
}

.tabela thead tr {
  background-color: #eef2fa;
}

.tabela th {
  padding: 0.75rem 1rem;
  color: var(--cor-azul-primario);
  font-weight: 600;
  text-align: left;
  border-bottom: 1px solid var(--cor-border);
  border-right: 1px solid var(--cor-border);
  white-space: nowrap;
}

.tabela th:last-child { border-right: none; }

.tabela td {
  padding: 0.8rem 1rem;
  border-bottom: 1px solid var(--cor-border);
  border-right: 1px solid var(--cor-border);
  color: #1e293b;
}

.tabela td:last-child { border-right: none; }
.tabela tr:last-child td { border-bottom: none; }

.sem-resultados {
  text-align: center;
  padding: 2rem;
  color: var(--cor-texto);
  opacity: 0.5;
  font-size: 0.9rem;
}

/* Badges de Estado */
.estado-badge {
  display: inline-block;
  padding: 0.25rem 0.75rem;
  border-radius: 20px;
  font-size: 0.75rem;
  font-weight: 500;
}

.bandeira {
  margin-right: 0.4rem; 
}

.estado--proximo  { background: #DBEAFE; color: #1E40AF; }
.estado--planeado { background: #FEF9C3; color: #854D0E; }
.estado--pago     { background: #DCFCE7; color: #166534; }

/* Alinhamentos */
.col-pais   { width: 120px; }
.col-valor  { text-align: left; font-family: monospace; }
.col-estado { text-align: center; width: 120px; }

.nota-grafico {
  font-size: 0.90rem;
  color: var(--cor-texto);
  line-height: 1.5;
  text-align: justify;
  margin: 0;
  padding: 1.5rem 1.5rem 1rem;
}

@media (max-width: 768px) {
  .card-header {
    flex-direction: column;
    align-items: flex-start;
    gap: 0.75rem;
  }

  .header-direita {
    flex-wrap: wrap;
    gap: 0.4rem;
  }

  .pills-group {
    flex-wrap: wrap;
  }

  .tabela-container {
    padding: 0.5rem;
  }
}
</style>
