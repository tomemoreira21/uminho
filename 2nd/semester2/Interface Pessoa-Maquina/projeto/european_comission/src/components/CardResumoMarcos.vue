<template>
  <div class="secao-card">
    <div class="grafico-header">
      <h2 class="secao-titulo-dark">Marcos e Metas</h2>
      <RouterLink to="/marcos-metas" class="btn-ver-mais">Ver mais</RouterLink>
    </div>

    <div class="marcos-layout">
      <div class="marcos-metricas">
        <MetricaCard 
          label="TOTAL DE MARCOS" 
          :valor="dados.total"     
          sufixo="medidas monitorizadas"    
          cor="var(--cor-azul-primario)" 
        />
        <MetricaCard 
          label="CUMPRIDOS"        
          :valor="dados.cumpridos" 
          :pct="dados.pctCumpridos" 
          cor="var(--cor-verde-escuro)"   
          cor-donut="var(--cor-verde-escuro)" 
        />
        <MetricaCard 
          label="EM RISCO"         
          :valor="dados.emRisco"   
          :pct="dados.pctEmRisco"   
          cor="var(--cor-laranja-escuro)" 
          cor-donut="var(--cor-laranja-escuro)" 
        />
        <MetricaCard 
          label="ATRASADOS"        
          :valor="dados.atrasados" 
          :pct="dados.pctAtrasados" 
          cor="var(--cor-vermelho-escuro)" 
          cor-donut="var(--cor-vermelho-escuro)" 
        />
      </div>

      <div class="marcos-grafico">
        <div class="marcos-grafico-topo">
          <p class="marcos-grafico-titulo">Marcos e status de cumprimento de metas</p>
          <BotaoExportar 
            :elemento-grafico="graficoRef"
            :dados="dadosExportar"
            :nome-ficheiro="`marcos-metas-${dados.total ?? ''}`"
          />
        </div>
       
       <div ref="graficoRef" style="width:100%; display:flex; flex-direction:column; align-items:center;">
          <svg viewBox="0 0 220 150" class="pie-marcos-completo">
                <g transform="translate(110, 75)">
                    <circle cx="0" cy="0" r="25" fill="transparent" stroke="#d3d3d3" stroke-width="50" />
                    
                    <circle cx="0" cy="0" r="25" fill="transparent"
                    stroke="var(--cor-laranja-escuro, #f28c28)" stroke-width="50"
                    :stroke-dasharray="`${(dados.pctCumpridos / 100) * 157.08} 157.08`"
                    stroke-dashoffset="0"
                    transform="rotate(-90)"
                    />
                </g>

                <g class="legenda-svg">
                    <line x1="65" y1="75" x2="45" y2="75" stroke="#b0b0b0" stroke-width="1" />
                    <text x="40" y="72" text-anchor="end" class="pct-legenda">{{ pctNaoAvaliado }}%</text>
                    <text x="40" y="82" text-anchor="end" class="label-legenda">Não Avaliado</text>
                </g>

                <g class="legenda-svg">
                    <line x1="155" y1="75" x2="175" y2="75" stroke="#b0b0b0" stroke-width="1" />
                    <text x="180" y="72" text-anchor="start" class="pct-legenda cumprido">{{ dados.pctCumpridos }}%</text>
                    <text x="180" y="82" text-anchor="start" class="label-legenda cumprido">Cumprido</text>
                </g>
          </svg>
        </div>
                
        <p class="nota-marcos">
            Este gráfico exibe a parcela de marcos e metas cumpridos. Um marco ou alvo é cumprido uma vez que um Estado-Membro tenha fornecido dados dos elementos de prova de que concluiu o marco ou meta 
            e a Comissão os avaliou positivamente em uma decisão de execução.
        </p>
      </div>
    </div>
  </div>
</template>

<script setup>
import { computed, ref } from 'vue'
import MetricaCard from './CardMetrica.vue'
import BotaoExportar from './BotaoExportar.vue'

const graficoRef = ref(null)

const props = defineProps({
  dados: {
    type: Object,
    required: true
  }
})

const dadosExportar = computed(() => [
  { 'Estado': 'Cumprido',      'Valor (%)': props.dados.pctCumpridos, 'Total': props.dados.cumpridos },
  { 'Estado': 'Não Avaliado',  'Valor (%)': pctNaoAvaliado.value,     'Total': props.dados.total - props.dados.cumpridos },
  { 'Estado': 'Em Risco',      'Valor (%)': props.dados.pctEmRisco,   'Total': props.dados.emRisco },
  { 'Estado': 'Atrasado',      'Valor (%)': props.dados.pctAtrasados, 'Total': props.dados.atrasados },
])

// Cálculo reativo da percentagem não avaliada
const pctNaoAvaliado = computed(() => {
  return (100 - props.dados.pctCumpridos).toFixed(1)
})
</script>

<style scoped>
.secao-card {
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 10px;
  padding: 1.5rem;
  display: flex;
  flex-direction: column;
  height: 100%;
}

.grafico-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 1.5rem;
}

.secao-titulo-dark {
  font-size: 1.2rem;
  font-weight: bold;
  font-family: monospace;
  color: black;
  margin: 0;
}

.btn-ver-mais {
  background: var(--cor-azul-escuro);
  color: white;
  border-radius: 4px;
  padding: 0.4rem 1rem;
  font-size: 0.85rem;
  text-decoration: none;
}

.marcos-layout {
  display: grid;
  grid-template-columns: 1fr 1.5fr;
  gap: 2rem;
}

.marcos-metricas {
  display: flex;
  flex-direction: column;
  gap: 0.75rem;
}

.marcos-grafico {
  border: 1px solid var(--cor-border);
  border-radius: 8px;
  padding: 1rem;
  display: flex;
  flex-direction: column;
  align-items: center;
}

.marcos-grafico-topo {
  display: flex;
  justify-content: space-between;
  align-items: center;
  width: 100%;
  margin-bottom: 1rem;
}

.marcos-grafico-titulo {
  font-size: 0.85rem;
  font-weight: bold;
  color: black;
  margin: 0;
}

/* Novo tamanho para acomodar legendas */
.pie-marcos-completo {
  width: 100%;       /* O SVG vai ocupar a largura do container */
  max-width: 320px;  /* Limite para não ficar gigante */
  height: auto;
  overflow: visible; /* Garante que o texto que "saia" um pouco não seja cortado */
  margin: 1rem 0;
}

/* Estilos para textos dentro do SVG */
.pct-legenda {
  font-size: 10px;
  font-weight: bold;
  fill: #666;
  font-family: sans-serif;
}

.pct-legenda.cumprido {
  fill: var(--cor-laranja-escuro, #f28c28);
}

.label-legenda {
  font-size: 8px;
  fill: #888;
  font-family: sans-serif;
}

.label-legenda.cumprido {
  fill: #666;
  font-weight: 500;
}

.nota-marcos {
  font-size: 0.75rem;
  color: var(--cor-texto);
  line-height: 1.5;
  text-align: justify;
}

@media (max-width: 768px) {
  .marcos-layout {
    grid-template-columns: 1fr;
  }
}
</style>