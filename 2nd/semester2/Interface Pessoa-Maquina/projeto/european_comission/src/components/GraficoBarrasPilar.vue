<template>
    <div class="grafico-corpo">

      <div v-for="cat in categorias" :key="cat.nome" class="linha">
        <div class="label-item">{{ cat.nome }}</div>
        <div class="barra-fundo">
          <div class="barra-fill" :style="{ width: (cat.valor / maxTick * 100) + '%', background: cor }"></div>
        </div>
      </div>
      <div class="eixo">
        <div v-for="tick in ticks" :key="tick" class="tick">
          <div class="tick-linha"></div>
          <span class="tick-label">{{ tick }}%</span>
        </div>
      </div>
    </div>
</template>

<script setup>
const props = defineProps({
  categorias: { type: Array,  required: true },
  cor:        { type: String, default: '#2e7d32' }
})

const ticks  = [0, 5, 10, 15, 20, 25, 30, 35]
const maxTick = 35
</script>

<style scoped>
.grafico-corpo {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  width: 100%;
}

.linha {
  display: flex;
  align-items: center;
  gap: 0.75rem;
}

.label-item {
  width: 200px;
  flex-shrink: 0;
  font-size: 0.78rem;
  color: var(--cor-texto);
  text-align: right;
}

.barra-fundo {
  flex: 1;
  height: 18px;
  background: #f0f0f0;
  border-radius: 3px;
  overflow: hidden;
}

.barra-fill {
  height: 100%;
  border-radius: 3px;
  transition: width 0.4s ease;
}

.eixo {
  display: flex;
  justify-content: space-between;
  margin-left: 200px;
}

.tick {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.tick-linha {
  width: 1px;
  height: 8px;
  background: var(--cor-texto);
  opacity: 0.3;
}

.tick-label {
  font-size: 0.68rem;
  color: var(--cor-texto);
  opacity: 0.6;
  margin-top: 2px;
}

@media (max-width: 768px) {
  .label-item {
    width: 90px;
    font-size: 0.62rem;
    white-space: normal;
    line-height: 1.2;
  }

  .eixo {
    margin-left: 90px;
  }
}
</style>