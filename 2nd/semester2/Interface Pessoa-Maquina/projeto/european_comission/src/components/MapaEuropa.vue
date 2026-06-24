<template>
  <div class="mapa-wrapper">
    <div class="mapa-layout" :class="{ 'mapa-deslocado': pais || modoComparar }">
      <div ref="mapaEl" class="mapa-container" />
    </div>

    <CardComparacaoPais
      v-if="modoComparar"
      :paisA="paisA"
      :paisB="paisB"
      @fechar="fecharTudo"
    />
    <CardDetalhesPais
      v-else-if="pais"
      :pais="pais"
      @fechar="fecharPais"
      @comparar="iniciarComparar"
    />
  </div>
</template>

<script setup>
import { ref, onMounted, onBeforeUnmount, watch } from 'vue'
import L from 'leaflet'
import 'leaflet/dist/leaflet.css'
import CardDetalhesPais   from './CardDetalhesPais.vue'
import CardComparacaoPais from './CardComparacaoPais.vue'
import { dbAPI } from '../database/index.js'
import { getMapaPaises } from '../services/getters.js'

const mapaEl       = ref(null)
const pais         = ref(null)
const modoComparar = ref(false)
const paisA        = ref(null)
const paisB        = ref(null)
let mapa, geojsonLayer
let dados = {}

onMounted(async () => {
  // Carrega países da API
  const paisesDB = await getMapaPaises(dbAPI)
  dados = Object.fromEntries(
    paisesDB.map(p => [
      p.codigo,
      {
        id:           p.id,
        codigo:       p.codigo,
        nome:         p.nome,
        dotacao:      p.dotacao ?? 'N/D',
        desembolsado: p.desembolsado ?? 'N/D',
        marcos:       p.marcos ?? 'N/D',
        execucao:     p.execucao ?? 0,
        historico:    p.historico ?? [],
      }
    ])
  )

  mapa = L.map(mapaEl.value, {
    zoomControl: false, attributionControl: false,
    dragging: false, scrollWheelZoom: false, doubleClickZoom: false,
    touchZoom: false, boxZoom: false, keyboard: false,
  })

  mapaEl.value.addEventListener('wheel', (e) => {
    window.scrollBy({ top: e.deltaY, behavior: 'smooth' })
  }, { passive: true })

  const res  = await fetch('https://raw.githubusercontent.com/leakyMirror/map-of-europe/master/GeoJSON/europe.geojson')
  const data = await res.json()

  geojsonLayer = L.geoJSON(data, {
    filter: f => !!dados[f.properties?.ISO2],
    style:  () => ({ fillColor: 'white', fillOpacity: 0.9, color: 'var(--cor-azul-primario)', weight: 1.5 }),
    onEachFeature(f, layer) {
      const d = dados[f.properties?.ISO2]
      if (!d) return
      layer.on({
        mouseover(e) { e.target.setStyle({ fillOpacity: 1, weight: 2.5, color: 'white' }); e.target.bringToFront() },
        mouseout(e)  {
          const iso = f.properties?.ISO2
          const selecionado =
            pais.value?.codigo === iso ||
            (modoComparar.value && paisA.value?.codigo === iso) ||
            (modoComparar.value && paisB.value?.codigo === iso)
          if (selecionado) {
            e.target.setStyle({ fillColor: '#4a9eff', fillOpacity: 1, weight: 2.5, color: 'white' })
          } else {
            e.target.setStyle(estiloDefault())
          }
        },
        click() {
          if (modoComparar.value) {
            paisB.value = d
            geojsonLayer.eachLayer(l => {
              const iso = l.feature?.properties?.ISO2
              if (iso === d.codigo || iso === paisA.value?.codigo) {
                l.setStyle({ fillColor: '#4a9eff', fillOpacity: 1, weight: 2.5, color: 'white' })
                l.bringToFront()
              } else {
                l.setStyle(estiloDefault())
              }
            })
          } else {
            resetTodos()
            modoComparar.value = false
            paisA.value = null
            paisB.value = null
            pais.value = d
            layer.setStyle({ fillColor: '#4a9eff', fillOpacity: 1, weight: 2.5, color: 'white' })
            layer.bringToFront()
          }
        },
      })
    },
  }).addTo(mapa)

  mapa.fitBounds(geojsonLayer.getBounds(), { padding: [-10, -10] })
})

function estiloDefault() {
  return { fillColor: 'white', fillOpacity: 0.9, color: 'var(--cor-azul-primario)', weight: 1.5 }
}

function resetTodos() {
  geojsonLayer?.eachLayer(l => l.setStyle(estiloDefault()))
}

onBeforeUnmount(() => mapa?.remove())

// Chama invalidateSize continuamente durante a transição para animação suave
watch([pais, modoComparar], () => {
  const duracao = 300
  const intervalo = 16 // ~60fps
  let elapsed = 0
  const timer = setInterval(() => {
    mapa?.invalidateSize()
    elapsed += intervalo
    if (elapsed >= duracao) clearInterval(timer)
  }, intervalo)
})

function fecharPais() {
  pais.value = null
  resetTodos()
}

function iniciarComparar() {
  paisA.value = pais.value
  paisB.value = null
  pais.value  = null
  modoComparar.value = true
  resetTodos()
  geojsonLayer?.eachLayer(l => {
    if (l.feature?.properties?.ISO2 === paisA.value?.codigo) {
      l.setStyle({ fillColor: '#4a9eff', fillOpacity: 1, weight: 2.5, color: 'white' })
    }
  })
}

function fecharTudo() {
  modoComparar.value = false
  paisA.value = null
  paisB.value = null
  pais.value  = null
  resetTodos()
}
</script>

<style scoped>
.mapa-wrapper {
  position: relative;
  width: 100%;
  padding: 0 3rem;
  box-sizing: border-box;
}

.mapa-layout {
  display: flex;
  align-items: flex-start;
}

.mapa-container {
  width: 100%;
  height: 900px;
  border-radius: 12px;
  overflow: hidden;
  transition: width 0.3s ease;
}

.mapa-deslocado .mapa-container {
  width: calc(100% - 430px);
}

:deep(.leaflet-container) {
  background: var(--cor-azul-primario) !important;
}

@media (max-width: 768px) {
  .mapa-wrapper { padding: 0 1rem; }
  .mapa-layout { flex-direction: column; }
  .mapa-container { height: 360px; }
}
</style>