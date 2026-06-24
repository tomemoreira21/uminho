<template>
  <div class="detalhe-page">

    <div class="breadcrumb">
      <BotaoVoltar @voltar="router.push('/pilares')" />
      <span class="breadcrumb-texto">
        Pilares > <strong>{{ pilar?.titulo }}</strong>
      </span>
    </div>

    <div v-if="pilar">
      <h1 class="titulo" :style="{ color: estilo.corTexto }">{{ pilar.titulo }}</h1>

      <div class="topo">
        <p class="descricao">{{ pilar.descricao }}</p>
        <div class="metricas">
          <div class="metrica-card">
            <span class="metrica-valor" :style="{ color: estilo.corTexto }">{{ marcosAtivos }}</span>
            <span class="metrica-label">Marcos/Alvo</span>
          </div>
          <div class="metrica-card">
            <span class="metrica-valor" :style="{ color: estilo.corTexto }">{{ medidasAtivas }}</span>
            <span class="metrica-label">Medidas</span>
          </div>
      </div>
    </div>

    <FiltroPais :paises="paises" label-todos="Todos os países" v-model="paisSelecionado" />

    <div class="graficos">
      <div class="grafico-bloco">
        <div class="grafico-header">
          <span class="grafico-titulo">{{ pilar.tituloGrafico1 }}</span>
          <BotaoExportar 
            :elemento-grafico="grafico1Ref"
            :dados="categoriasGrafico1"
            :nome-ficheiro="`${pilar.titulo}-grafico1`"
          />
        </div>
        <div ref="grafico1Ref">
          <GraficoBarras :categorias="categoriasGrafico1" :cor="estilo.corTexto" />
        </div>
      </div>

      <div class="grafico-bloco">
        <div class="grafico-header">
          <span class="grafico-titulo">{{ pilar.tituloGrafico2 }}</span>
          <BotaoExportar 
            :elemento-grafico="grafico2Ref"
            :dados="categoriasGrafico2"
            :nome-ficheiro="`${pilar.titulo}-grafico2`"
          />
        </div>
        <div ref="grafico2Ref">
          <GraficoBarras :categorias="categoriasGrafico2" :cor="estilo.corTexto" />
        </div>
      </div>

      </div>
    </div>
   </div>
</template>

<script setup>
import { ref, computed, watch, onMounted } from 'vue'
import { useRoute, useRouter } from 'vue-router'
import { dbAPI } from '../database/index.js'
import { getPilarInfoPorId, getPaises, getPilarCategoriasParaPais, getPilarCategoriasMediaUE, getPilarCategorias } from '../services/getters.js'
import BotaoVoltar   from '../components/BotaoVoltar.vue'
import BotaoExportar from '../components/BotaoExportar.vue'
import FiltroPais    from '../components/FiltroPais.vue'
import GraficoBarras from '../components/GraficoBarrasPilar.vue'

import iconVerde       from '../assets/icons/transicao-verde.png'
import iconDigital     from '../assets/icons/transformacao-digital.png'
import iconCrescimento from '../assets/icons/crescimento.png'
import iconCoesao      from '../assets/icons/coesao.png'
import iconSaude       from '../assets/icons/saude.png'
import iconPoliticas   from '../assets/icons/politicas.png'

const route  = useRoute()
const router = useRouter()

const estilosPilar = {
  1: { corTexto: 'var(--cor-verde-escuro)',      corFundoIcone: 'var(--cor-verde-claro)',     imagem: iconVerde       },
  2: { corTexto: 'var(--cor-roxo-escuro)',       corFundoIcone: 'var(--cor-roxo-claro)',      imagem: iconDigital     },
  3: { corTexto: 'var(--cor-azul-ue)',           corFundoIcone: 'var(--cor-azul-claro)',      imagem: iconCrescimento },
  4: { corTexto: 'var(--cor-vermelho-escuro)',   corFundoIcone: 'var(--cor-vermelho-claro)',  imagem: iconCoesao      },
  5: { corTexto: 'var(--cor-azul-ciano-claro)',  corFundoIcone: 'var(--cor-azul-ciano)',      imagem: iconSaude       },
  6: { corTexto: 'var(--cor-laranja-escuro)',    corFundoIcone: 'var(--cor-laranja-claro)',   imagem: iconPoliticas   },
}

const pilarId = Number(route.params.id)
const pilar   = ref(null)
const paises  = ref([])
const paisSelecionado    = ref(null)
const categoriasGrafico1 = ref([])
const categoriasGrafico2 = ref([])
const marcosAtivos  = ref(null)
const medidasAtivas = ref(null)
const grafico1Ref = ref(null)
const grafico2Ref = ref(null)

const estilo = computed(() => estilosPilar[pilarId] ?? {})

function formatarCategorias(cats) {
  if (!cats) return []
  return cats.map(c => ({ nome: c.nome, valor: c.valor ?? c.mediaUE ?? 0 }))
}

async function carregarCategorias(codigoPais) {
  const dadosPilarCategorias = await getPilarCategorias(dbAPI, pilarId)

  if (codigoPais) {
    const paisData = dadosPilarCategorias?.valorPorPais?.[codigoPais]
    const cats = await getPilarCategoriasParaPais(dbAPI, pilarId, codigoPais)
    categoriasGrafico1.value = formatarCategorias(cats)
    categoriasGrafico2.value = formatarCategorias(cats)
    marcosAtivos.value  = paisData?.marcos  ?? pilar.value?.marcos
    medidasAtivas.value = paisData?.medidas ?? pilar.value?.medidas
  } else {
    const mediaUE = await getPilarCategoriasMediaUE(dbAPI, pilarId)
    categoriasGrafico1.value = formatarCategorias(mediaUE)
    categoriasGrafico2.value = formatarCategorias(mediaUE)
    marcosAtivos.value  = pilar.value?.marcos
    medidasAtivas.value = pilar.value?.medidas
  }
}

onMounted(async () => {
  const [dadosPilar, dadosPaises] = await Promise.all([
    getPilarInfoPorId(dbAPI, pilarId),
    getPaises(dbAPI)
  ])
  pilar.value  = dadosPilar
  paises.value = dadosPaises
  marcosAtivos.value  = dadosPilar?.marcos
  medidasAtivas.value = dadosPilar?.medidas
  await carregarCategorias(null)
})

watch(paisSelecionado, (novoPais) => {
  carregarCategorias(novoPais?.codigoISO ?? null)
})
</script>

<style scoped>
.detalhe-page {
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

.breadcrumb-texto strong {
  font-weight: 700;
}

.titulo {
  font-size: 2rem;
  font-weight: 700;
  margin-bottom: 1rem;
}

.topo {
  display: flex;
  gap: 2rem;
  align-items: flex-start;
  margin-bottom: 1.5rem;
}

.descricao {
  flex: 1;
  font-size: 0.95rem;
  line-height: 1.6;
  color: black;
}

.metricas {
  display: flex;
  gap: 0.75rem;
  flex-shrink: 0;
}

.metrica-card {
  display: flex;
  flex-direction: column;
  align-items: center;
  background: white;
  border: 1px solid #e0e6ed;
  border-radius: 10px;
  padding: 1rem 1.5rem;
  gap: 0.25rem;
  min-width: 100px;
}

.metrica-valor {
  font-size: 1.4rem;
  font-weight: 800;
}

.metrica-label {
  font-size: 0.7rem;
  color: var(--cor-texto);
  text-transform: uppercase;
  letter-spacing: 0.05em;
}

.graficos {
  display: flex;
  flex-direction: column;
  gap: 1.5rem;
  margin-top: 1.5rem;
}

.grafico-bloco {
  background: white;
  border: 1px solid #e0e6ed;
  border-radius: 10px;
  padding: 1.25rem;
}

.grafico-header {
  display: flex;
  justify-content: space-between;
  align-items: flex-start;
  margin-bottom: 1rem;
  padding-bottom: 0.75rem;
  border-bottom: 1px solid #e0e6ed;
}

.grafico-titulo {
  font-size: 0.9rem;
  font-weight: 700;
  color: black;
  flex: 1;
  padding-right: 1rem;
}

@media (max-width: 768px) {
   .grafico-header {
    align-items: flex-start;
  }

  .grafico-titulo {
    font-size: 0.78rem;
    padding-right: 0.5rem;
    max-width: calc(100% - 50px);
  }
  
  .detalhe-page {
    padding: 1rem;
  }

  .titulo {
    font-size: 1.3rem;
  }

  .topo {
    flex-direction: column;
    gap: 1rem;
  }

  .metricas {
    width: 100%;
  }

  .metrica-card {
    flex: 1;
  }
}
</style>