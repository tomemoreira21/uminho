<template>
  <div class="home-container">
    <!-- ══ SECÇÃO 1: O que somos? ══ -->
    <section class="card-section" style="padding: 0 3rem" aria-labelledby="titulo-somos">
      <h1 class="titulo-secao" id="titulo-somos">O que somos?</h1>
      <div class="texto-intro" role="article">
        <span class="capitular" aria-hidden="true">E</span>
        <p>
          ste site é especialmente dedicado à consulta detalhada e transparente de dados informativos
          relacionados com os investimentos realizados pelos países da União Europeia, permitindo aos
          utilizadores acompanhar de forma clara e organizada onde, como e em que áreas os recursos
          financeiros estão a ser aplicados. Além disso, disponibiliza informação atualizada sobre as
          promessas assumidas por cada Estado-Membro, bem como o nível de cumprimento das metas
          estabelecidas, promovendo uma visão abrangente sobre o progresso alcançado e o grau de
          responsabilidade política e financeira no contexto europeu.
        </p>
      </div>
    </section>

    <!-- ══ SECÇÃO 2: Os 6 principais pilares ══ -->
    <section class="card-section" style="padding: 0 3rem" aria-labelledby="titulo-pilares">
      <h2 class="titulo-secao" id="titulo-pilares">Os 6 principais pilares</h2>
      <p class="subtexto">
        O Regulamento do Mecanismo de Recuperação e Resiliência (MRR) estabelece seis áreas estratégicas
        de relevância europeia, organizadas em seis pilares principais. O Painel de Avaliação da
        Recuperação e Resiliência apresenta o impacto do MRR nestes seis pilares:
      </p>
      <div class="pilares-wrapper">
        <CardsPilares />
      </div>
    </section>

    <!-- ══ SECÇÃO 3: Gráfico de barras ══ -->
    <section class="card-section" aria-labelledby="titulo-grafico">
      <h2 class="sr-only" id="titulo-grafico">Percentagem dos fundos do RRF por pilar de política</h2>
      <GraficoBarras
        v-if="categoriasGrafico.length"
        :categorias="categoriasGrafico"
        nota="Cada medida contribui para dois dos seis pilares políticos, pelo que a contribuição total para todos os pilares apresentada neste gráfico corresponde a 200% dos fundos do MRR atribuídos aos Estados-Membros."
      />
    </section>

    <!-- ══ SECÇÃO 4: Mapa Europa ══ -->
    <section class="card-section" aria-labelledby="titulo-mapa-heading">
      <h2 class="titulo-secao titulo-mapa" id="titulo-mapa-heading">Distribuição dos fundos do RRF por país</h2>
      <div class="mapa-info-wrapper">
        <div class="info-card" role="note" aria-label="Instrução de interação com o mapa">
          <p class="info-texto">Clique num país para obter informações sobre ele</p>
        </div>
        <MapaEuropa />
      </div>
    </section>
  </div>
  <RodapeNoticias aria-label="Últimas atualizações dos países" role="marquee" />
</template>

<script setup>
import { ref, onMounted, computed } from 'vue'
import { dbAPI } from '../database/index.js'
import { getGastosRRP } from '../services/getters.js'
import CardsPilares    from '../components/CardsPilares.vue'
import GraficoBarras   from '../components/GraficoBarras.vue'
import MapaEuropa      from '../components/MapaEuropa.vue'
import iconVerde       from '../assets/icons/transicao-verde.png'
import iconDigital     from '../assets/icons/transformacao-digital.png'
import iconCrescimento from '../assets/icons/crescimento.png'
import iconCoesao      from '../assets/icons/coesao.png'
import iconSaude       from '../assets/icons/saude.png'
import iconPoliticas   from '../assets/icons/politicas.png'
import RodapeNoticias from '../components/RodapeNoticias.vue'

const gastosGlobais = ref([])

const iconesPorPilar = {
  'transicao-verde':       iconVerde,
  'transformacao-digital': iconDigital,
  'crescimento':           iconCrescimento,
  'coesao':                iconCoesao,
  'saude':                 iconSaude,
  'politicas':             iconPoliticas,
}

const coresPorPilar = {
  'transicao-verde':       'var(--cor-verde-escuro)',
  'transformacao-digital': 'var(--cor-roxo-escuro)',
  'crescimento':           'var(--cor-azul-ue)',
  'coesao':                'var(--cor-vermelho-escuro)',
  'saude':                 'var(--cor-azul-ciano-claro)',
  'politicas':             'var(--cor-laranja-escuro)',
}

onMounted(async () => {
  const todos = await getGastosRRP(dbAPI)
  const global = todos.find(g => g.paisId === null)
  gastosGlobais.value = global?.gastosRRP ?? []
})

const categoriasGrafico = computed(() =>
  gastosGlobais.value.map(g => ({
    nome:  g.nome,
    valor: g.valorPct,
    cor:   coresPorPilar[g.pilarId],
    icone: iconesPorPilar[g.pilarId],
  }))
)
</script>

<style scoped>
.home-container {
  background-color: var(--cor-azul-primario);
  display: flex;
  flex-direction: column;
  gap: 3rem;
  min-height: 100vh;
  font-family: var(--font-principal);
  padding: 2rem 0 8rem;
}

/* Visível apenas para screen readers */
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

.card-section { background: transparent; }

.pilares-wrapper { padding: 0 17rem; }

.titulo-secao {
  font-size: 1.55rem;
  font-weight: 800;
  margin: 0 0 1.25rem;
  color: white;
}

.titulo-mapa {
  font-family: monospace;
  text-align: center;
}

.subtexto {
  font-size: 0.9rem;
  color: white;
  line-height: 1.65;
  margin: 0 0 1.5rem;
}

.texto-intro {
  display: flex;
  align-items: flex-start;
  gap: 0.5rem;
}

.capitular {
  font-size: 4rem;
  font-weight: 900;
  line-height: 0.85;
  color: white;
  flex-shrink: 0;
}

.texto-intro p {
  font-size: 0.92rem;
  color: white;
  line-height: 1.7;
  margin: 0;
}

.mapa-info-wrapper { position: relative; }

.info-card {
  position: absolute;
  left: calc(3rem + 100px);
  top: calc(6rem + 50px);
  width: 220px;
  background: #0e2044;
  border: 1px solid rgba(255,255,255,0.08);
  border-radius: 14px;
  padding: 1.5rem;
  text-align: center;
  z-index: 10;
}

.info-texto {
  font-size: 0.85rem;
  font-weight: 700;
  font-family: monospace;
  color: white;
  line-height: 1.6;
  margin: 0;
}

@media (max-width: 768px) {
  .home-container { gap: 2rem; }
  .titulo-secao { font-size: 1.3rem; }
  .capitular { font-size: 3rem; }
  .pilares-wrapper { padding: 0; }
}
</style>