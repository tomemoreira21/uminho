<template>
  <div class="secao-card">
    <div class="grafico-header">
      <h2 class="secao-titulo-dark">Investimentos e reformas por categoria social</h2>
      <BotaoExportar 
        :elemento-grafico="graficoRef"
        :dados="dadosExportar"
        nome-ficheiro="investimentos-reformas-sociais"      
      />
    </div>

    <div class="barras-empilhadas-wrapper" ref="graficoRef">
      <div class="barras-area-social">
        <div class="grade-social">
          <div
            v-for="t in ticksSociais"
            :key="t"
            class="grade-linha-social"
            :style="{ bottom: (t / maxSocial * 100) + '%' }"
          >
            <span class="tick-y-label">{{ t }}</span>
          </div>
        </div>

        <div class="barras-container">
          <div
            v-for="cat in categoriasSociais"
            :key="cat.nome"
            class="barra-col"
          >
            <div class="barra-stack">
              <div
                class="segmento-inv"
                :style="{ height: (cat.investimentos / maxSocial * 100) + '%' }"
              ></div>
              <div
                class="segmento-ref"
                :style="{ height: (cat.reformas / maxSocial * 100) + '%' }"
              ></div>
            </div>
            <span class="label-x">{{ cat.nome }}</span>
          </div>
        </div>
      </div>
    </div>

    <div class="legenda-social">
      <div class="legenda-item"><span class="cor-ref"></span> Reformas</div>
      <div class="legenda-item"><span class="cor-inv"></span> Investimentos</div>
    </div>
    
    <p class="nota-social">
      Este gráfico exibe o número de medidas (reformas e investimentos) incluídas na recuperação e plano de resiliência que contribua para cada categoria social.
    </p>
  </div>
</template>

<script setup>
import { computed, ref } from 'vue'
import BotaoExportar from './BotaoExportar.vue'

const graficoRef = ref(null)

const props = defineProps({
  categoriasSociais: { type: Array, required: true }
})

const dadosExportar = computed(() =>
  props.categoriasSociais.map(c => ({
    'Categoria':      c.nome,
    'Reformas':       c.reformas ?? 0,
    'Investimentos':  c.investimentos ?? 0,
    'Total':          (c.reformas ?? 0) + (c.investimentos ?? 0),
  }))
)

const maxSocial = computed(() => {
  const totais = props.categoriasSociais.map(c => (c.reformas || 0) + (c.investimentos || 0))
  const max = Math.max(...totais, 0)
  return Math.ceil(max / 2) * 2 || 8
})

const ticksSociais = computed(() => {
  let ticks = []
  for (let i = 0; i <= maxSocial.value; i += 2) ticks.push(i)
  return ticks
})
</script>

<style scoped>
.secao-card {
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 10px;
  padding: 1.25rem 1.5rem;
  display: flex;
  flex-direction: column;
}

.grafico-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 2rem;
}

.secao-titulo-dark {
  font-size: 1rem;
  font-weight: 700;
  font-family: monospace;
  color: black;
  margin: 0;
}

.barras-empilhadas-wrapper {
  flex: 1;
  min-height: 250px;
  margin-bottom: 3.5rem;
}

.barras-area-social {
  position: relative;
  height: 100%;
  margin-left: 30px;
}

.grade-social {
  position: absolute;
  inset: 0;
}

.grade-linha-social {
  position: absolute;
  left: 0;
  right: 0;
  height: 1px;
  background: var(--cor-border);
}

.tick-y-label {
  position: absolute;
  left: -30px;
  transform: translateY(-50%);
  font-size: 0.75rem;
  color: black;
  font-weight: 500;
  width: 25px;
  text-align: right;
}

.barras-container {
  position: absolute;
  inset: 0;
  display: flex;
  justify-content: space-around;
  align-items: flex-end;
}

.barra-col {
  display: flex;
  flex-direction: column;
  align-items: center;
  width: 35px;
  height: 100%; /* Essencial para os cálculos de % */
  justify-content: flex-end;
}

.barra-stack {
  width: 100%;
  height: 100%; /* Essencial para que os filhos com % apareçam */
  display: flex;
  flex-direction: column;
  justify-content: flex-end;
  border-radius: 3px 3px 0 0;
  overflow: hidden;
}

.segmento-inv { background: #C05CB5; transition: height 0.3s ease; }
.segmento-ref { background: #8C59C3; transition: height 0.3s ease; }

.label-x {
  position: absolute;
  bottom: -45px;
  font-size: 0.7rem;
  text-align: center;
  color: #000; /* Texto X a preto também para consistência */
  width: 90px;
  line-height: 1.2;
}

.legenda-social {
  display: flex;
  gap: 1.5rem;
  margin-bottom: 1rem;
}

.legenda-item {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  font-size: 0.85rem;
  color: var(--cor-texto);
}

.legenda-item span { width: 12px; height: 12px; border-radius: 3px; }
.cor-ref { background: #8C59C3; }
.cor-inv { background: #C05CB5; }

.nota-social {
  font-size: 0.75rem;
  color: var(--cor-texto);
  line-height: 1.4;
  margin: 0;
}

@media (max-width: 768px) {
  .barras-empilhadas-wrapper {
    min-height: 180px;
  }
}
</style>