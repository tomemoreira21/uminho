<template>
  <div class="grafico-wrapper">
      <div class="grafico-topo">
        <p v-if="titulo" class="grafico-titulo" :style="{ color: corTexto }">{{ titulo }}</p>
        <div class="exportar-wrapper" v-if="mostrarBotao">    
          <BotaoExportar 
            :elemento-grafico="graficoRef"
            :dados="dadosExportar"
            :nome-ficheiro="titulo || 'grafico-pilares'"
          />
        </div>
      </div>
    <div class="grafico-corpo" :style="{ height: altura + 'px' }" ref="graficoRef">
      <div class="eixo-y">
        <span v-for="tick in ticksY" :key="tick" class="tick-y" :style="{bottom: (tick / maxTick * 100) + '%', color: corTexto }">
          {{ tick }}%</span>
      </div>
      <div class="barras-area">
        <div class="grid">
          <div v-for="tick in ticksY" :key="tick" class="grid-linha" :style="{ bottom: (tick / maxTick * 100) + '%', opacity: opacidadeLinha}"></div>
        </div>
        <div class="barras">
          <div v-for="cat in categorias" :key="cat.nome" class="barra-col">
            <div class="barra-fundo">
              <span class="barra-label" :style="{ color: corTexto }">{{ cat.valor.toFixed(2) }}%</span>
              <div
                class="barra-fill"
                :style="{ height: (cat.valor / maxTick * 100) + '%', background: cat.cor || cor }"
              ></div>
            </div>
            <div class="barra-icone">
              <img v-if="cat.icone" :src="cat.icone" :alt="cat.nome" class="icone-img" />
              <span class="icone-nome" :style="{ color: corTexto }">{{ cat.nome }}</span>
            </div>
          </div>
        </div>
      </div>
    </div>
    <p v-if="nota" class="nota" :style="{ color: corTexto }">{{ nota }}</p>
  </div>
</template>

<script setup>
import { computed, ref } from 'vue'
import BotaoExportar from './BotaoExportar.vue'

const props = defineProps({
  categorias: { type: Array,   required: true },
  cor:        { type: String,  default: '#003399' },
  nota:       { type: String,  default: '' },
  titulo:     { type: String,  default: 'Percentagem dos fundos do RRF que contribuem para cada pilar de política' },
  tema:       { type: String,  default: 'escuro' },  // 'escuro' ou 'claro'
  altura:     { type: Number,  default: 600 },
  mostrarBotao:  { type: Boolean, default: true}
})

const graficoRef = ref(null)

const maxTick = 70
const ticksY  = [0, 10, 20, 30, 40, 50, 60]

const dadosExportar = computed(() =>
  props.categorias.map(c => ({
    nome:   c.nome ?? c.label ?? '',
    valor:  Number(c.valor ?? 0),
  }))
)

const corTexto = computed(() =>
  props.tema === 'claro' ? 'var(--cor-texto)' : 'white'
)

const opacidadeLinha = computed(() => 
  props.tema === 'claro' ? 0.2 : 0.8 
)
</script>

<style scoped>
.grafico-wrapper {
  width: 100%;
  max-width: 1000px;
  margin: 0 auto;
  font-family: var(--font-principal);
  padding: 1rem 0;
}

.grafico-titulo {
  font-size: 1.55rem;
  font-weight: 700;
  text-align: center;
  margin-bottom: 1.5rem;
  line-height: 1.4;
}

.grafico-corpo {
  display: flex;
  align-items: flex-end;
  gap: 0.5rem;
}

.grafico-topo {
  position: relative;
  margin-bottom: 1.5rem;
}

.exportar-wrapper {
  position: absolute;
  top: 3.8rem;
  right: 0;
  z-index: 10;
}
.eixo-y {
  position: relative; 
  flex-shrink: 0;
  width: 45px; 
  height: calc(100% - 48px); 
  margin-bottom: 48px; 
}

.tick-y {
  position: absolute;
  right: 8px; /* Espaço entre o número e a linha */
  transform: translateY(40%); 
  font-size: 0.72rem;
  text-align: right;
  white-space: nowrap;
}

.barras-area {
  flex: 1;
  height: 100%;
  position: relative;
  display: flex;
  flex-direction: column;
}

.grid {
  position: absolute;
  inset: 0;
  bottom: 48px;
  pointer-events: none;
}

.grid-linha {
  position: absolute;
  left: 0;
  right: 0;
  height: 1px;
  background: currentColor;
}

.barras {
  flex: 1;
  display: flex;
  align-items: flex-end;
  gap: 0.75rem;
  position: relative;
  z-index: 1;
}

.barra-col {
  flex: 1;
  display: flex;
  flex-direction: column;
  align-items: center;
  height: 100%;
  justify-content: flex-end;
}

.barra-label {
  font-size: 0.72rem;
  font-weight: 700;
  margin-bottom: 6px;
  text-align: center;
}

.barra-fundo {
  width: 60%;
  flex: 1;
  display: flex;
  flex-direction: column;
  justify-content: flex-end;
  align-items: center;
  border-radius: 4px 4px 0 0;
}

.barra-fill {
  width: 100%;
  border-radius: 4px 4px 0 0;
  transition: height 0.5s ease;
  min-height: 4px;
}

.barra-icone {
  height: 45px;
  display: flex;
  flex-direction: column;
  padding-top: 48px;
  align-items: center;
  justify-content: center;
  gap: 0.3rem;
  overflow: visible;
}

.icone-nome {
  font-size: 0.62rem;
  font-weight: 600;
  text-align: center;
  line-height: 1.3;
  max-width: 80px;
}

.icone-img {
  width: 98px;
  height: 98px;
  object-fit: contain;
}

.nota {
  margin-top: 7rem;
  font-size: 0.9rem;
  text-align: center;
  line-height: 1.5;
}
</style>