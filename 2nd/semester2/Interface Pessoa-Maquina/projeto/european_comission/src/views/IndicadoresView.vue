<template>
    <div class="page">
      <div class="cabecalho">
        <h1 class="titulo">Indicadores Comuns</h1>
      </div>

      <p class="descricao">
        <span class="letra-inicial">A</span> comissão europeia identificou 14 indicadores
        comuns no âmbito do Recovery and Resilience Facility, que permitem acompanhar o
        crescimento de cada país nos seis pilares estratégicos do plano de recuperação.
      </p>

      <!-- Filtro de países -->
      <FiltrosPaises  
          :paises="paises"
          v-model="paisDistribuicao"/>

      <!-- Legenda dos pilares -->
      <LegendaPilares />

      <!-- Grid de cards -->
      <div class="grid">
        <CardIndicador
          v-for="indicador in indicadores"
          :key="indicador.numero"
          :indicador="indicador"
          :pais="paisDistribuicao"
        />
      </div>
    </div>
</template>

<script setup>
import { ref, onMounted } from 'vue'
import CardIndicador from '../components/CardIndicador.vue'
import LegendaPilares from '../components/LegendaPilares.vue'
import FiltrosPaises from '../components/FiltroPais.vue'
import { dbAPI } from '../database/index.js'
import { getIndicadores, getPaises } from '../services/getters.js'

const indicadores = ref([])
const paisDistribuicao = ref(null)
const paises = ref([])

onMounted(async () => {
  const [dadosIndicadores, dadosPaises] = await Promise.all([
    getIndicadores(dbAPI),
    getPaises(dbAPI)
  ])
  indicadores.value = dadosIndicadores
  paises.value = dadosPaises
})
</script>

<style scoped>
.page {
  background-color: var(--cor-sidebar-bg);
  min-height: 100%;
  padding: 2rem;
}

/* Título da página */
.cabecalho {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 1rem;
  width: 100%; /* ocupa toda a largura */
}

.titulo {
  color: var(--cor-azul-primario);
  font-size: 2rem;
  margin-bottom: 1rem;
}

/* Parágrafo de descrição */
.descricao {
  color: black;
  font-size: 0.95rem;
  line-height: 1.6;
  margin-bottom: 2rem;
}

/* Primeira letra grande como no Figma */
.letra-inicial {
  font-size: 2rem;
  font-weight: bold;
  float: left;
  line-height: 1;
  margin-right: 2px;
  margin-top: -8px;
  color: black;
}

.grid {
  display: grid;
  grid-template-columns: repeat(5, 1fr);
  gap: 1.3rem;
  margin-bottom: 1.5rem;
  align-items: stretch;
}

:deep(.seletor) {
  margin-bottom: 1rem;
}

@media (max-width: 768px) {
  .page {
    padding: 1rem;
  }

  .titulo {
    font-size: 1.3rem;
  }

  .grid {
    grid-template-columns: repeat(2, 1fr);
    gap: 0.75rem;
  }
}
</style>