<template>
  <div class="tabela-card">

    <!-- Barra de título + filtros -->
    <div class="barra-topo">
      <h2 class="titulo-tabela" id="tabela-titulo">Marcos e Metas por medida</h2>
      <div class="filtros" role="group" aria-label="Filtros da tabela">
        <FiltroPais    :paises="paises"        v-model="filtroPais" />
        <FiltroReforma :opcoes="opcoesReforma" v-model="filtroReforma" />
        <FiltroEstado  :opcoes="opcoesEstado"  v-model="filtroEstado" />
        <FiltroPilares :pilares="pilares"      v-model="filtroPilar" />
      </div>
      <div class="botao-exportar-container">
        <BotaoExportar 
          :elemento-grafico="tabelaRef"
          :dados="dadosExportar"
          nome-ficheiro="marcos-e-metas"
        />
      </div>
    </div>

    <!-- Tabela -->
    <div class="tabela-container" ref="tabelaRef">
      <table class="tabela" aria-labelledby="tabela-titulo" aria-describedby="tabela-info tabela-descricao">
        <caption id="tabela-info" class="sr-only">
          {{ linhasFiltradas.length }} resultados encontrados. Clique numa linha para ver os detalhes.
        </caption>
        <thead>
          <tr>
            <th class="col-pais">País</th>
            <th class="col-medida">Medida</th>
            <th class="col-reforma">Reforma/Investimento</th>
            <th class="col-estado">Estado</th>
            <th class="col-progresso">Progresso</th>
            <th class="col-pilares">Pilares</th>
          </tr>
        </thead>
        <tbody>
          <tr
            v-for="(linha, i) in linhasPaginadas"
            :key="i"
            class="linha"
            tabindex="0"
            :aria-label="`${linha.pais}, ${linha.medida}, ${linha.tipo}, estado ${linha.estado}, progresso ${linha.progresso}%`"
            @click="abrirModal(linha)"
            @keydown.enter.space.prevent="abrirModal(linha)"
          >

            <!-- País -->
            <td class="col-pais">
              {{ linha.bandeira }} {{ linha.pais }}
            </td>

            <!-- Medida -->
            <td class="col-medida">{{ linha.medida }}</td>

            <!-- Reforma / Investimento -->
            <td class="col-reforma">
              <span
                class="badge-tipo"
                :class="linha.tipo === 'Investimento' ? 'badge-investimento' : 'badge-reforma'"
              >{{ linha.tipo }}</span>
            </td>

            <!-- Estado -->
            <td class="col-estado">
              <span class="badge-estado" :class="classeEstado(linha.estado)">
                {{ linha.estado }}
              </span>
            </td>

            <!-- Progresso -->
            <td class="col-progresso">
              <div class="progresso-wrapper">
                <span class="progresso-pct">{{ linha.progresso }}%</span>
                <div class="barra-bg">
                  <div class="barra-fill" :style="{ width: linha.progresso + '%' }"></div>
                </div>
              </div>
            </td>

            <!-- Pilares -->
            <td class="col-pilares">
              <div class="pilares-lista">
                <span
                  v-for="(nomeP, j) in linha.pilares"
                  :key="j"
                  class="pilar-circulo"
                  :style="{ backgroundColor: corDoPilar(nomeP) }"
                ></span>
              </div>
            </td>
          </tr>

          <tr v-if="linhasFiltradas.length === 0">
            <td colspan="6" class="sem-resultados">Nenhum resultado encontrado.</td>
          </tr>
        </tbody>
      </table>
    </div>

    <div class="rodape">
      <p class="descricao" id="tabela-descricao">
        A tabela contém medidas incluídas nos planos de recuperação e resiliência dos Estados-Membros. 
        Esta apresenta detalhes sobre cada medida, incluindo os domínios de intervenção para os quais 
        contribui, o marco ou meta correspondente e o seu estado de implementação. Ao clicar em qualquer 
        uma das medidas é possível ter uma visão mais detalhada de cada medida.
      </p>

      <!-- Paginação -->
      <nav class="paginacao" aria-label="Paginação da tabela">
        <button
          v-for="p in totalPaginas"
          :key="p"
          class="btn-pagina"
          :class="{ ativo: paginaAtual === p }"
          :aria-current="paginaAtual === p ? 'page' : undefined"
          :aria-label="`Página ${p}`"
          @click="paginaAtual = p"
        >{{ p }}
        </button>
      </nav>
    </div>
  </div>

  <ModalDetalhesMedida
    v-if="modalAberto"
    :key="medidaSelecionada.medida"
    :medida="medidaSelecionada"
    :detalhes="detalhesDaMedida"
    @fechar="modalAberto = false"
  />
</template>

<script setup>
import { ref, computed, watch } from 'vue'
import FiltroPais    from './FiltroPais.vue'
import FiltroPilares from './FiltroPilares.vue'
import FiltroReforma from './FiltroReforma.vue'
import FiltroEstado  from './FiltroEstado.vue'
import BotaoExportar from './BotaoExportar.vue'
import ModalDetalhesMedida from './ModalDetalhesMedida.vue'

const props = defineProps({
  linhas:        { type: Array, required: true },
  paises:        { type: Array, required: true },
  opcoesReforma: { type: Array, required: true },
  opcoesEstado:  { type: Array, required: true },
  detalhesMedidas: { type: Object, required: true },
  pilares:       { type: Array, required: true},
})

const filtroPais    = ref(null)
const filtroReforma = ref(null)
const filtroEstado  = ref(null)
const filtroPilar   = ref(null)
const tabelaRef = ref(null)

const dadosExportar = computed(() =>
  linhasFiltradas.value.map(l => ({
    'País':              `${l.bandeira} ${l.pais}`,
    'Medida':            l.medida,
    'Tipo':              l.tipo,
    'Estado':            l.estado,
    'Progresso (%)':     l.progresso,
    'Pilares':           l.pilares.join(', ')
  }))
)

const linhasFiltradas = computed(() =>
  props.linhas.filter(l => {
    if (filtroPais.value    && l.pais   !== filtroPais.value.nome)     return false
    if (filtroReforma.value && l.tipo   !== filtroReforma.value.value) return false
    if (filtroEstado.value  && l.estado !== filtroEstado.value.value)  return false
    if (filtroPilar.value && !l.pilares.includes(filtroPilar.value.value)) return false
    return true
  })
)

const POR_PAGINA   = 5
const paginaAtual  = ref(1)

// Reset página ao mudar filtros
watch(linhasFiltradas, () => { paginaAtual.value = 1 })

const totalPaginas    = computed(() => Math.ceil(linhasFiltradas.value.length / POR_PAGINA) || 1)
const linhasPaginadas = computed(() => {
  const inicio = (paginaAtual.value - 1) * POR_PAGINA
  return linhasFiltradas.value.slice(inicio, inicio + POR_PAGINA)
})

function classeEstado(estado) {
  if (estado === 'Atrasado')        return 'estado-atrasado'
  if (estado === 'Em risco')        return 'estado-risco'
  if (estado === 'Dentro do Prazo') return 'estado-ok'
  return ''
}

function corDoPilar(value) {
  return props.pilares.find(p => p.value === value)?.cor ?? '#ccc'
}

const modalAberto      = ref(false)
const medidaSelecionada = ref(null)

const detalhesDaMedida = computed(() =>
  medidaSelecionada.value
    ? props.detalhesMedidas[medidaSelecionada.value.medida] ?? null
    : null
)

function abrirModal(linha) {
  medidaSelecionada.value = linha
  modalAberto.value = true
}

</script>

<style scoped>
/* ── Card geral ── */
.tabela-card {
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 10px;
}

.tabela-container {
  overflow-x: auto;
  padding: 1.5rem 1rem 1rem;
}

.tabela {
  width: auto;
  min-width: 100%;
  border-collapse: collapse;
  font-family: var(--font-principal);
  font-size: 0.82rem;
  border: 1px solid var(--cor-border);
  border-radius: 8px;
}

/* ── Barra topo (título + filtros) ── */
.barra-topo {
  display: flex;
  align-items: center;
  gap: 1rem;
  padding: 0.75rem 1.25rem;
  border-bottom: 1px solid var(--cor-border);
  flex-wrap: wrap;
}

.titulo-tabela {
  font-size: 1rem;
  font-weight: 700;
  font-family: monospace;
  color: #111;
  line-height: 1.3;
  margin: 0;
  white-space: nowrap;
}

.filtros {
  display: flex;
  align-items: center;
  gap: 0.6rem;
  flex-wrap: wrap;
  flex: 1;
  margin-left: auto;  
  justify-content: flex-end; 
}

.btn-menu {
  margin-left: auto;
  display: flex;
  flex-direction: column;
  justify-content: center;
  gap: 4px;
  padding: 0.45rem 0.55rem;
  border: 1px solid var(--cor-border);
  border-radius: 6px;
  background: white;
  cursor: pointer;
  flex-shrink: 0;
}

/* ── Tabela ── */
.tabela-container {
  overflow-x: auto;
  padding: 0.75rem 1rem 0;
}

.tabela {
  width: 100%;
  border-collapse: collapse;
  font-family: var(--font-principal);
  font-size: 0.82rem;
}

/* Header */
thead tr {
  background-color: #eef2fa;
}

th {
  padding: 0.7rem 1rem;
  color: var(--cor-azul-primario);
  font-weight: 600;
  font-size: 0.8rem;
  text-align: center;
  border-bottom: 1px solid var(--cor-border);
  border-right: 1px solid var(--cor-border);
  white-space: nowrap;
}

th:last-child {
  border-right: none;
}

/* Linhas */
.linha td {
  padding: 0.8rem 1rem;
  border-bottom: 1px solid var(--cor-border);
  border-right: 1px solid var(--cor-border);
  vertical-align: middle;
  color: var(--cor-texto);
}

.linha td:last-child {
  border-right: none;
}

.linha:last-child td {
  border-bottom: none;
}

.linha {
  cursor: pointer;
}

.linha:hover td {
  background-color: var(--cor-azul-selecao);
}

/* ── Colunas ── */
.col-pais {
  width: 160px;
  text-align: center;
}

.cel-pais {
  display: table-cell; /* mantém layout de td */
}

.cel-pais .bandeira {
  margin-right: 4px;
}

.col-medida {
  text-align: left;
  min-width: 200px;
  font-family: monospace;
  font-size: 0.8rem;
}

.col-reforma {
  width: 170px;
  text-align: center;
}

.col-estado {
  width: 140px;
  text-align: center;
}

.col-progresso {
  width: 150px;
}

.col-pilares {
  width: 90px;
  text-align: center;
}

/* ── Badge Reforma / Investimento ── */
.badge-tipo {
  display: inline-block;
  padding: 0.28rem 1rem;
  border-radius: 5px;
  font-size: 0.78rem;
  font-weight: 500;
  white-space: nowrap;
}

.badge-reforma {
  border: 1px solid var(--cor-border);
  color: var(--cor-texto);
  background: white;
}

.badge-investimento {
  background-color: var(--cor-azul-primario);
  color: white;
  border: none;
}

/* ── Badge Estado ── */
.badge-estado {
  display: inline-block;
  padding: 0.25rem 0.7rem;
  border-radius: 20px;
  font-size: 0.75rem;
  font-weight: 500;
  white-space: nowrap;
}

.estado-atrasado { background-color: #fde8e8; color: var(--cor-vermelho-escuro); }
.estado-risco    { background-color: #fef3cd; color: var(--cor-laranja-escuro); }
.estado-ok       { background-color: #e0f3e8; color: var(--cor-verde-escuro); }

/* ── Progresso ── */
.progresso-wrapper {
  display: flex;
  flex-direction: column;
  align-items: flex-end;
  gap: 3px;
}

.progresso-pct {
  font-size: 0.75rem;
  font-weight: 600;
  color: var(--cor-azul-primario);
}

.barra-bg {
  width: 100%;
  height: 5px;
  background-color: #dde3ef;
  border-radius: 3px;
  overflow: hidden;
}

.barra-fill {
  height: 100%;
  background-color: var(--cor-azul-primario);
  border-radius: 3px;
}

/* ── Pilares — círculos ── */
.pilares-lista {
  display: flex;
  gap: 5px;
  justify-content: center;
  flex-wrap: wrap;
}

.pilar-circulo {
  display: inline-block;
  width: 16px;
  height: 16px;
  border-radius: 50%;   /* ← círculo perfeito */
}

/* ── Sem resultados ── */
.sem-resultados {
  text-align: center;
  padding: 2rem;
  color: var(--cor-texto);
  opacity: 0.5;
  font-size: 0.9rem;
}

/* ── Paginação ── */
.paginacao {
  display: flex;
  justify-content: flex-end;
  gap: 0.4rem;
  padding: 0.65rem 1.25rem;
}

.btn-pagina {
  width: 28px;
  height: 28px;
  border-radius: 6px;
  border: 1px solid var(--cor-border);
  background: white;
  font-family: var(--font-principal);
  font-size: 0.78rem;
  cursor: pointer;
  color: var(--cor-texto);
}

.btn-pagina:hover {
  background-color: var(--cor-azul-selecao);
}

.btn-pagina.ativo {
  background-color: var(--cor-azul-primario);
  color: white;
  border-color: var(--cor-azul-primario);
}

.botao-exportar-container {
  display: contents;
}

.sr-only {
  position: absolute;
  width: 1px;
  height: 1px;
  padding: 0;
  margin: -1px;
  overflow: hidden;
  clip: rect(0, 0, 0, 0);
  white-space: nowrap;
  border: 0;
}

.rodape {
  display: flex;
  align-items: center;
  gap: 1rem;
  padding: 0.65rem 1.25rem;
}

.descricao {
  flex: 1;
  font-size: 0.95rem;
  color: var(--cor-texto);
  line-height: 1.5;
  text-align: justify;
  margin: 0;
  padding: 1.5rem 1.5rem 1rem;
}

@media (max-width: 768px) {
  .barra-topo {
    flex-direction: column;
    align-items: stretch;
  }

  .filtros {
    flex-direction: column;
    justify-content: flex-start;
    align-items: stretch;
    margin-left: 0;
  }

  .filtros > * {
    width: 100%;
  }

  .botao-exportar-container {
    display: flex;
    justify-content: flex-end; 
  }

  .descricao {
    display: none;
  }

  .paginacao {
    margin-left: auto;
  }
}
</style>