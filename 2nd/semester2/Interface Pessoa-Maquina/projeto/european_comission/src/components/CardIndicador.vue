<template>
  <div class="card">

    <!-- Topo: título + ícone + bolinhas juntos -->
    <div class="card-topo">
      <div class="card-header">
        <span class="titulo">({{ indicador.numero }}) {{ indicador.titulo }}</span>
        <div class="header-direita">
          <span class="icone">{{ indicador.icone }}</span>
          <!-- Bolinhas dos pilares associados — coladas ao ícone -->
          <div class="pilares">
            <span
              v-for="cor in coresPilares"
              :key="cor"
              class="bolinha"
              :style="{ background: cor }"
            ></span>
          </div>
        </div>
      </div>
    </div>

    <!-- Rodapé com label e valor — sempre no fundo -->
    <div class="card-footer">
      <span class="label">{{ indicador.label }}</span>
      <span class="valor">{{ valorExibido }}</span>
    </div>

  </div>
</template>

<script setup>
import { computed } from 'vue'


// Recebe o objeto do indicador como prop
const props = defineProps({
  indicador: { type: Object, required: true },
  pais:      { type: Object, default: null  }, 
})

const mapaCorPilar = {
  'transicao-verde':       'var(--cor-verde-escuro)',
  'transformacao-digital': 'var(--cor-roxo-escuro)',
  'crescimento':           'var(--cor-azul-ue)',
  'coesao':                'var(--cor-vermelho-escuro)',
  'saude':                 'var(--cor-azul-ciano-claro)',
  'politicas':             'var(--cor-laranja-escuro)',
}

const coresPilares = computed(() =>
  (props.indicador.pilaresIds ?? []).map(id => mapaCorPilar[id] ?? '#ccc')
)

const valorExibido = computed(() => {
  if (props.pais && props.indicador.valorPorPais?.[props.pais.id]) {
    return props.indicador.valorPorPais[props.pais.id]
  }
  return props.indicador.valorTotal
})
</script>

<style scoped>
.card {
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 10px;
  padding: 1rem;
  display: flex;
  flex-direction: column;
  font-family: var(--font-principal);
  height: 100%;
}

.card-topo {
  flex: 1; /* ocupa todo o espaço disponível empurrando o footer para baixo */
}

/* Cabeçalho — título à esquerda, ícone + bolinhas à direita */
.card-header {
  display: flex;
  justify-content: space-between;
  align-items: flex-start;
  gap: 0.5rem;
}

.titulo {
  font-size: 0.8rem;
  color: var(--cor-texto);
  line-height: 1.4;
  flex: 1;
}

/* Coluna da direita: ícone em cima, bolinhas em baixo */
.header-direita {
  display: flex;
  flex-direction: column;
  align-items: flex-end;
  gap: 0.4rem;
  flex-shrink: 0;
}

.icone {
  font-size: 1.2rem;
}

/* Bolinhas coladas ao ícone, alinhadas à direita */
.pilares {
  display: flex;
  flex-direction: column;
  gap: 0.3rem;
  align-items: flex-end;
}

.bolinha {
  width: 12px;
  height: 12px;
  border-radius: 50%;
  flex-shrink: 0;
}

/* Rodapé com label e valor — sempre no fundo do card */
.card-footer {
  display: flex;
  flex-direction: column;
  gap: 0.15rem;
  margin-top: 1rem;
  padding-top: 0.25rem;
}

.label {
  font-size: 0.75rem;
  color: var(--cor-texto);
}

.valor {
  font-size: 1rem;
  font-weight: bold;
  color: var(--cor-azul-primario);
}
</style>