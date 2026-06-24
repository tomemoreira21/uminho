<template>
  <main class="page">

    <!-- Cabeçalho com título e botão de exportar -->
    <div class="cabecalho">
      <h1 class="titulo">Desembolsos</h1>
  
    </div>
    
    <!--<SeletorPaises :paises="listaDePaises" v-model="paisFiltrado" /> -->

    <p class="descricao">
      <span class="letra-inicial">P</span>ermite consultar os desembolsos realizados a cada
      Estado-Membro da União Europeia, através de duas modalidades: subsídios
      (transferências não reembolsáveis) e empréstimos (contribuições reembolsáveis),
      mediante o cumprimento dos marcos e metas definidos em cada plano nacional.
    </p>

     <!-- Investimentos por País -->
    <section aria-label="Investimentos por país">
      <InvestimentosPais 
        :pilares="pilares"
        descricao="Este gráfico apresenta o montante total de fundos do Mecanismo de Recuperação e Resiliência (MRR) atribuídos a cada Estado-Membro, ordenados por valor decrescente. 
        As barras dividem-se em duas componentes: subsídios, representados a verde, que são transferências financeiras não reembolsáveis atribuídas com base numa chave de alocação; e empréstimos, a azul, 
        que são contribuições reembolsáveis cujo montante não pode exceder 6,8% do Rendimento Nacional Bruto de 2019 de cada país.
        Pode filtrar os dados por pilar estratégico ou alternar entre o valor total em milhares de milhões de euros, a percentagem face ao total do PRR e o valor per capita por habitante."
      />
    </section>

    <!-- Secção inferior: tabela + gráfico lado a lado -->
     <section class="secao-inferior" aria-label="Calendário e distribuição por pilares">

      <!-- Calendário de Desembolsos -->
      <div class="calendario-col">
        <CalendarioDesembolsos 
          :paises="paises" 
          descricao="Calendário com todos os pedidos de pagamento submetidos por cada Estado-Membro ao abrigo do Mecanismo de Recuperação e Resiliência (MRR), 
          indicando a data de submissão, o número sequencial do pagamento, o tipo de financiamento, 
          o valor total em euros e o estado atual de aprovação pela Comissão Europeia: Pago, Próximo ou Planeado."
        />
      </div>

      <!-- Distribuição por Pilares com header próprio aqui -->
      <DistribuicaoPilares
        :paises="paises"
        :pilares="pilares"
        :gastos="gastos"
        com-card
        titulo="Distribuição por Pilares"
        label-todos="Média UE"
      />
    </section>
  </main>
</template>

<script setup>
import { ref, onMounted } from 'vue'
import InvestimentosPais     from '../components/InvestimentosPais.vue'
import CalendarioDesembolsos from '../components/CalendarioDesembolsos.vue'
import DistribuicaoPilares from '../components/DistribuicaoPilares.vue'
import { dbAPI } from '../database/index.js' 
import { getPaises, getGastosRRP } from '../services/getters.js'

import iconVerde       from '../assets/icons/transicao-verde.png'
import iconDigital     from '../assets/icons/transformacao-digital.png'
import iconCrescimento from '../assets/icons/crescimento.png'
import iconCoesao      from '../assets/icons/coesao.png'
import iconSaude       from '../assets/icons/saude.png'
import iconPoliticas   from '../assets/icons/politicas.png'

const paisSelecionado = ref(null)
const paises = ref([])
const gastos = ref([])

onMounted(async () => {
  const [p, g] = await Promise.all([getPaises(dbAPI), getGastosRRP(dbAPI)])
  paises.value = p
  gastos.value = g
})

const pilares = [
  { icon: iconVerde,       label: 'Transição Verde',                                  value: 'transicao-verde',        cor: 'var(--cor-verde-escuro)' },
  { icon: iconDigital,     label: 'Transformação Digital',                            value: 'transformacao-digital',  cor: 'var(--cor-roxo-escuro)' },
  { icon: iconCrescimento, label: 'Crescimento inteligente, sustentável e inclusivo', value: 'crescimento',            cor: 'var(--cor-azul-ue)' },
  { icon: iconCoesao,      label: 'Coesão social e territorial',                      value: 'coesao',                 cor: 'var(--cor-vermelho-escuro)' },
  { icon: iconSaude,       label: 'Saúde e resiliência económica, social e institucional',       value: 'saude',                  cor: 'var(--cor-azul-ciano-claro)' },
  { icon: iconPoliticas,   label: 'Políticas para a próxima geração',                 value: 'politicas',              cor: 'var(--cor-laranja-escuro)' },
]

</script>

<style scoped>
.page {
  background-color: var(--cor-sidebar-bg);
  min-height: 100vh;
  padding: 2rem;
  display: flex;
  flex-direction: column;
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

/* Tabela à esquerda, gráfico à direita */
.secao-inferior {
  display: flex;
  gap: 1.5rem;
  align-items: stretch; /* Alinha o topo dos dois cards */
  width: 100%;
  margin-top: 1.5rem;
}

.calendario-col {
  flex: 1; 
  min-width: 0; /* Evita que a tabela quebre o layout flex */
  display: flex;        
  flex-direction: column;
}

.calendario-placeholder {
  flex: 1;
  background: white;
  border-radius: 12px;
  padding: 1.5rem;
  border: 1px solid var(--cor-border);
}

/* Wrapper do componente com o seu próprio header */
.pilares-wrapper {
  background: white;
  border-radius: 12px;
  padding: 1.25rem;
  min-width: 280px;
  max-width: 340px;
  border: 1px solid var(--cor-border);
}

.pilares-header {
  display: flex;
  flex-direction: column;  
  gap: 0.5rem;
  margin-bottom: 1rem;
}

.pilares-controls {
  display: flex;
  align-items: center;
  gap: 0.4rem;
}

.pilares-titulo {
  font-size: 1rem;
  font-weight: 700;
  color: black;
  margin: 0;
}

@media (max-width: 768px) {
  .page {
    padding: 1rem;
  }

  .titulo {
    font-size: 1.3rem;
  }

  .secao-inferior {
    flex-direction: column;
  }

  .calendario-col {
    width: 100%;
  }
}
</style>