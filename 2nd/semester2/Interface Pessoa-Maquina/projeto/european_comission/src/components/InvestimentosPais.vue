<template>
  <div class="card">
    <div class="card-header">
      <h3 class="card-titulo">Investimentos por País</h3>
      <div class="header-controls">
        <!-- Botões de visualização -->
        <ul role="listbox" aria-label="Modo de visualização" class="btn-group">
          <li
            v-for="(modo, idx) in modos"
            :key="modo.id"
            :ref="el => btnRefs[idx] = el"
            role="option"
            :aria-selected="modoAtivo === modo.id ? 'true' : 'false'"
            :class="['btn-modo', { 'btn-modo--ativo': modoAtivo === modo.id }]"
            tabindex="0"
            @click="modoAtivo = modo.id"
            @keydown.enter.space.prevent="modoAtivo = modo.id"
          >
            {{ modo.label }}
          </li>
        </ul>
        <!-- Filtro pilares -->
        <FiltroPilares
          :pilares="pilares"
          label-todos="Todos os pilares"
          v-model="pilarSelecionado"
        />
        <BotaoExportar 
          :elemento-grafico="listaRef"
          :dados="dadosExportar"
          :nome-ficheiro="`investimentos-${modoAtivo}`"
        />
      </div>
    </div>

    <!-- Barras por país -->
    <div class="paises-lista" ref="listaRef">
      <div
        v-for="(pais, i) in paisesOrdenados"
        :key="pais.id"
        class="pais-linha"
      >
        <div class="pais-info">
          <span class="pais-bandeira">{{ pais.bandeira }}</span>
          <div class="pais-nome-rank">
            <span class="pais-nome">{{ pais.nome }}</span>
            <span class="pais-rank">#{{ ((pagina - 1) * porPagina) + i + 1 }}</span>
          </div>
        </div>
        <div class="barra-composta">
          <div
            class="barra-subsidios"
            :style="{ width: (pais._valorSub / maxTotal * 100) + '%' }"
          ></div>
          <div
              class="barra-emprestimos"
              :style="{ width: (pais._valorEmp / maxTotal * 100) + '%' }"
          ></div>
        </div>
        <span class="pais-valor">{{ pais._label }}</span>
      </div>
    </div>

    <!-- Legenda + paginação -->
    <div class="rodape">
      <div class="legenda">
        <span class="legenda-item"><span class="legenda-cor legenda-subsidios"></span> Subsídios</span>
        <span class="legenda-item"><span class="legenda-cor legenda-emprestimos"></span> Empréstimos</span>
      </div>
      <div class="paginacao">
        <button
          v-for="p in totalPaginas"
          :key="p"
          class="pag-btn"
          :class="{ 'pag-btn--ativo': pagina === p }"
          @click="pagina = p"
        >{{ p }}</button>
      </div>
    </div>

    <p v-if="descricao" class="nota-grafico">{{ descricao }}</p>
  </div>
</template>

<script setup>
import { ref, computed, watch, onMounted, nextTick } from 'vue'
import { dbAPI } from '../database/index.js'
import { getInvestimentosPais } from '../services/getters.js'
import FiltroPilares   from './FiltroPilares.vue'
import BotaoExportar from './BotaoExportar.vue'

const modoAtivo       = ref('total')
const pilarSelecionado = ref(null)
const pagina          = ref(1)
const porPagina       = 6
const todosPaises = ref([])
const listaRef = ref(null)
const btnRefs = ref([])

const modos = [
  { id: 'total',     label: 'Total €' },
  { id: 'pct_prr',   label: '% do PRR' },
  { id: 'per_capita', label: '€ per capita' },
]

const props = defineProps({
  pilares: { type: Array, required: true },
  descricao: { type: String, default: null }
})

const dadosExportar = computed(() =>
  [...paisesComValores.value]
    .sort((a, b) => b._valor - a._valor)
    .map((p, i) => ({
      'Rank':         i + 1,
      'País':         p.nome,
      'Subsídios':    p._valorSub.toFixed(2),
      'Empréstimos':  p._valorEmp.toFixed(2),
      'Total':        p._label,
      'Pilar':        pilarSelecionado.value?.label ?? 'Todos',
      'Modo':         modoAtivo.value,
    }))
)

onMounted(async () => {
  const dados = await getInvestimentosPais(dbAPI)
  todosPaises.value = dados
})

const paisesComValores = computed(() => {
  const pilarId = pilarSelecionado.value?.value ?? null
  const modo    = modoAtivo.value

  const comBase = todosPaises.value.map(p => {

    if (pilarId) {
      const d = p.pilares[pilarId] ?? { sub: 0, emp: 0 }
      return { ...p, base: d.sub + d.emp, baseSub: d.sub, baseEmp: d.emp }
    }
    return { ...p, 
      base:    p.subsidiosBilhoes + p.emprestimosBilhoes,  
      baseSub: p.subsidiosBilhoes,
      baseEmp: p.emprestimosBilhoes 
    }
  })

  const totalGeral = comBase.reduce((acc, p) => acc + p.base, 0)

  return comBase.map(p => {
    let valor, valorSub, valorEmp

    if (modo === 'pct_prr') {
      const f = totalGeral > 0 ? (100 / totalGeral) : 0
      valor    = p.base    * f
      valorSub = p.baseSub * f
      valorEmp = p.baseEmp * f
    } else if (modo === 'per_capita') {
      const f = p.populacaoMilhoes > 0 ? (1 / p.populacaoMilhoes) : 0
      valor    = p.base    * f
      valorSub = p.baseSub * f
      valorEmp = p.baseEmp * f
    } else {
      valor    = p.base
      valorSub = p.baseSub
      valorEmp = p.baseEmp
    }

    let label
    if (modo === 'pct_prr')         label = valor.toFixed(1) + '%'
    else if (modo === 'per_capita') label = '€' + valor.toFixed(2) + 'B/hab'
    else if (pilarId)               label = '€' + valor.toFixed(1) + 'B'
    else                            label = '€' + (p.base).toFixed(1) + 'B'

    return { ...p, _valor: valor, _valorSub: valorSub, _valorEmp: valorEmp, _label: label }
  })
})

const maxTotal = computed(() =>
  Math.max(...paisesComValores.value.map(p => p._valor))
)

const totalPaginas = computed(() => Math.ceil(todosPaises.value.length / porPagina))

const paisesOrdenados = computed(() => {
  const sorted = [...paisesComValores.value].sort((a, b) => b._valor - a._valor)
  const inicio = (pagina.value - 1) * porPagina
  return sorted.slice(inicio, inicio + porPagina)
})

// Reset página ao mudar filtros
watch([modoAtivo, pilarSelecionado], () => { pagina.value = 1 })

</script>

<style scoped>
.card {
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 12px;
  padding: 1.5rem;
  margin-bottom: 1.5rem;
}

.card-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding-bottom: 0.80rem; 
  margin-bottom: 0;
  flex-wrap: wrap;
  gap: 0.75rem;
  border-bottom: 1px solid var(--cor-border);
}

.card-titulo {
  font-size: 1.1rem;
  font-weight: 700;
  color: black;
  margin: 0;
}

.header-controls {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  flex-wrap: wrap;
  align-self: center;
}

.btn-group {
  display: flex;
  border: 1px solid var(--cor-border);
  border-radius: 8px;
  overflow: hidden;
  background: var(--cor-azul-selecao);
  padding: 2px;
  list-style: none; 
  margin: 0; 
}

.btn-modo {
  padding: 0.25rem 0.75rem;
  background: transparent;
  border: none;
  border-right: 1px solid var(--cor-border);
  border-radius: 6px;
  font-size: 0.78rem;
  cursor: pointer;
  font-family: var(--font-principal);
  font-weight: 400; /* não negrito */
  color: var(--cor-azul-primario);
  transition: all 0.2s;
}

.btn-modo:last-child { border-right: none; }

.btn-modo--ativo {
  background: white;
  color: var(--cor-azul-primario);
  box-shadow: 0 1px 3px rgba(0,0,0,0.1);
}

/* Linhas de país */
.paises-lista {
  display: flex;
  flex-direction: column;
}

.pais-linha {
  display: grid;
  grid-template-columns: 140px 1fr 80px;
  align-items: center;
  gap: 1rem;
  padding: 1.2rem 0; /* Mais respiro vertical */
  border-bottom: 1px solid var(--cor-border); /* Linha separadora horizontal */
}

.pais-linha:last-child { border-bottom: none; }

.pais-info {
  display: flex;
  align-items: center;
  gap: 0.5rem;
}

.pais-bandeira { font-size: 1.2rem; }

.pais-nome-rank {
  display: flex;
  flex-direction: column;
}

.pais-nome {
  font-size: 0.9rem;
  font-weight: 400;
  color: black;
}

.pais-rank {
  font-size: 0.7rem;
  color: var(--cor-azul-primario);
}

.barra-composta {
  display: flex;
  height: 20px;
  border-radius: 4px;
  overflow: hidden;
  background: #e0e0e0;
}

.barra-subsidios {
  background: var(--cor-verde-escuro);
  height: 100%;
  transition: width 0.4s ease;
}

.barra-emprestimos {
  background: var(--cor-azul-claro);
  height: 100%;
  transition: width 0.4s ease;
}

.pais-valor {
  font-size: 0.9rem;
  font-weight: 400;
  color: black;
  text-align: right;
}

/* Rodapé */
.rodape {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-top: 1rem;
  padding-top: 0.75rem;
  border-top: 1px solid var(--cor-border);
}

.legenda {
  display: flex;
  gap: 1rem;
}

.legenda-item {
  display: flex;
  align-items: center;
  gap: 0.4rem;
  font-size: 0.82rem;
  color: var(--cor-texto);
  font-weight: 400;
}

.legenda-cor {
  width: 14px;
  height: 14px;
  border-radius: 3px;
}

.legenda-subsidios   { background: var(--cor-verde-escuro); }
.legenda-emprestimos { background: var(--cor-azul-claro); }

.paginacao {
  display: flex;
  gap: 0.4rem;
}

.pag-btn {
  width: 28px;
  height: 28px;
  border: 1px solid var(--cor-border);
  border-radius: 4px;
  background: white;
  cursor: pointer;
  font-size: 0.8rem;
  font-family: var(--font-principal);
  color: var(--cor-texto);
}

.pag-btn--ativo {
  background: var(--cor-azul-primario);
  color: white;
  border-color: var(--cor-azul-primario);
}

.nota-grafico {
  font-size: 0.90rem;
  color: var(--cor-texto);
  line-height: 1.5;
  text-align: justify;
  margin-top: 0.75rem;
  padding-top: 0.75rem;
}

@media (max-width: 768px) {
  .card-header {
    flex-direction: column;
    align-items: flex-start;
  }

  .header-controls {
    width: 100%;
  }

  .pais-linha {
    grid-template-columns: 110px 1fr 60px;
    gap: 0.5rem;
  }

  .rodape {
    flex-direction: column;
    gap: 0.75rem;
    align-items: flex-start;
  }
}
</style>