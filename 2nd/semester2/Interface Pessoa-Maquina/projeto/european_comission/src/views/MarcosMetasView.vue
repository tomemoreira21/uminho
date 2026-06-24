<!-- MarcosMetasView.vue -->
<template>
  <main class="page">
    <h1 class="title">Marcos e Metas</h1>

    <p class="description">
      <span class = "initial_character">F</span>inanciamento baseado em resultados. Os países só recebem os fundos quando cumprem os objetivos definidos nos seus planos de recuperação.
    </p>

    <!-- Cards lado a lado -->
    <section class="cards-row" aria-label="Tipos de objetivos">
      <MarcoMetaCard
        tipo="marco"
        descricao="Etapas de caráter qualitativo que marcam progressos legislativos, regulatórios ou institucionais."
      />
      <MarcoMetaCard
        tipo="meta"
        descricao="Resultados mensuráveis que traduzem o impacto concreto das medidas implementadas."
      />
    </section>


    <!-- Legenda dos pilares -->
    <section aria-label="Legenda dos pilares">
      <LegendaPilares />
    </section>

    <!-- Tabela-->
    <section aria-label="Tabela de marcos e metas por medida">
      <TabelaMarcosMetas
        :linhas="linhas"
        :paises="paises"
        :opcoes-reforma="opcoesReforma"
        :opcoes-estado="opcoesEstado"
        :detalhes-medidas="detalhesMedidas"
        :pilares="pilares"
      />
    </section>

    <!-- Secção de distribuição e comparação -->
    <section class="layout-inferior" aria-label="Análise e comparação">
      <DistribuicaoPilares
        :paises="paises"
        :linhas="linhas"
        :pilares="pilares"
        com-card
        titulo="Distribuição por Pilares"
        label-todos="Todos os países"
        mostrar-medidas
      />
      <div class="coluna-direita">
        <ComparacaoCumprimento :paises="paises" :linhas="linhas" :pilares="pilares"/>
      </div>
    </section>

  </main>
</template>

<script setup>
import { ref, onMounted } from 'vue'

import MarcoMetaCard from '../components/MarcosMetasCard.vue'
import LegendaPilares from '../components/LegendaPilares.vue'
import TabelaMarcosMetas from '../components/TabelaMarcosMetas.vue'
import DistribuicaoPilares from '../components/DistribuicaoPilares.vue'
import CardExplicacao        from '../components/CardExplicacao.vue'
import ComparacaoCumprimento from '../components/ComparacaoCumprimentoMarcosMetas.vue'

import {
  getMarcosMedidas,
  getPaises,
  getDetalhesMedidas,
} from '../services/getters.js'

import { dbAPI } from '../database/index.js'

import iconVerde       from '../assets/icons/transicao-verde.png'
import iconDigital     from '../assets/icons/transformacao-digital.png'
import iconCrescimento from '../assets/icons/crescimento.png'
import iconCoesao      from '../assets/icons/coesao.png'
import iconSaude       from '../assets/icons/saude.png'
import iconPoliticas   from '../assets/icons/politicas.png'

const linhas = ref([]);
const paises = ref([]);
const detalhesMedidas = ref({});

const opcoesReforma = [
  { value: 'Reforma',      label: 'Reforma' },
  { value: 'Investimento', label: 'Investimento' },
]

const opcoesEstado = [
  { value: 'Dentro do Prazo', label: 'Dentro do Prazo', cor: 'var(--cor-verde-escuro)' },
  { value: 'Em risco',        label: 'Em risco',        cor: 'var(--cor-laranja-escuro)' },
  { value: 'Atrasado',        label: 'Atrasado',        cor: 'var(--cor-vermelho-escuro)' },
]

const pilares = [
  { icon: iconVerde,       label: 'Transição Verde',                                  value: 'transicao-verde',        cor: 'var(--cor-verde-escuro)' },
  { icon: iconDigital,     label: 'Transformação Digital',                            value: 'transformacao-digital',  cor: 'var(--cor-roxo-escuro)' },
  { icon: iconCrescimento, label: 'Crescimento inteligente, sustentável e inclusivo', value: 'crescimento',            cor: 'var(--cor-azul-ue)' },
  { icon: iconCoesao,      label: 'Coesão social e territorial',                      value: 'coesao',                 cor: 'var(--cor-vermelho-escuro)' },
  { icon: iconSaude,       label: 'Saúde e resiliência económica, social e institucional',       value: 'saude',                  cor: 'var(--cor-azul-ciano-claro)' },
  { icon: iconPoliticas,   label: 'Políticas para a próxima geração',                 value: 'politicas',              cor: 'var(--cor-laranja-escuro)' },
]

onMounted(async () => {
  linhas.value          = await getMarcosMedidas(dbAPI)
  paises.value          = await getPaises(dbAPI)
  detalhesMedidas.value = await getDetalhesMedidas(dbAPI, pilares);
})
</script>

<style scoped>
/*Geral páginas*/
.page {
  background-color: var(--cor-sidebar-bg);
  min-height: 100%;
  padding: 2rem;
}

.title {
  color: var(--cor-azul-primario);
  font-size: 2rem;
  margin-bottom: 1rem;
}

/* Parágrafo de descrição */
.description {
  color: black;
  font-size: 0.95rem;
  line-height: 1.6;
  margin-bottom: 2rem;
}

/* Primeira letra grande como no Figma */
.initial_character {
  font-size: 2rem;
  font-weight: bold;
  float: left;
  line-height: 1;
  margin-right: 2px;
  margin-top: -8px;
  color: black;
}

/*Cards marcos e metas*/
.cards-row {
  display: flex;
  gap: 1.5rem;
  flex-wrap: wrap;
  width: 100%;
  margin-bottom: 1rem;
}

.layout-inferior {
  display: flex;
  gap: 1.5rem;
  align-items: stretch; /* Alinha o topo dos dois cards */
  width: 100%;
  margin-top: 1.5rem;
}

.coluna-direita {
  flex: 1;
  display: flex;
  flex-direction: column;
  gap: 1.5rem;
  min-width: 0;
}

@media (max-width: 768px) {
  .page {
    padding: 1rem;
  }

  .title {
    font-size: 1.3rem;
  }

  .cards-row {
    flex-direction: column;
  }

  .layout-inferior {
    flex-direction: column;
  }

  .coluna-direita {
    width: 100%;
  }
}
</style>