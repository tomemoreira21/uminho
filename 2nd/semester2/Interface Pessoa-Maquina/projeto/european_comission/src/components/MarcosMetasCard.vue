<template>
  <article class="card" :aria-label="titulo + ': ' + subtitulo">
    <div class="card-header">
      <div class="card-icon" aria-hidden="true" :style="{ backgroundColor: 'var(--cor-azul-primario)'}">
        <img v-if="iconSrc" :src="iconSrc" :alt="tipo" class="icon-img" />
        <span v-else class="icon-fallback">{{ tipo === 'marco' ? '🏁' : '📊' }}</span>
      </div>
      <div class="card-heading">
        <h2 class="card-title">{{ titulo }}</h2>
        <span class="card-subtitulo">{{ subtitulo }}</span>
      </div>
    </div>
    <p class="card-descricao">{{ descricao }}</p>
  </article>
</template>
 
<script setup>
import { computed } from 'vue'
 
const props = defineProps({
  /**
   * 'marco' ou 'meta'
   */
  tipo: {
    type: String,
    required: true,
    validator: (v) => ['marco', 'meta'].includes(v),
  },
  titulo: {
    type: String,
    default: null,
  },
  descricao: {
    type: String,
    default: '',
  },
  /**
   * Caminho opcional para um ícone personalizado
   */
  iconSrc: {
    type: String,
    default: null,
  },
})
 
const isMeta = computed(() => props.tipo === 'meta')
 
const subtitulo = computed(() =>
  isMeta.value ? 'Objetivo quantitativo' : 'Objetivo qualitativo'
)
 
const iconBgColor = computed(() =>
  isMeta.value ? '#1a5276' : '#1a3a5c'
)
 
const titulo = computed(() =>
  props.titulo ?? (isMeta.value ? 'Metas' : 'Marcos')
)
</script>
 
<style scoped>
.card {
  background-color: #ffffff;
  border: 1px solid #e0e6ef;
  border-radius: 10px;
  padding: 1.25rem 1.5rem;
  flex: 1 1 0;
  min-width: 0;
  min-height: 130px;
  display: flex;
  flex-direction: column;
  gap: 0.85rem;
  box-shadow: 0 1px 4px rgba(0, 0, 0, 0.06);
  transition: box-shadow 0.2s ease;
}
 
 
.card-header {
  display: flex;
  align-items: center;
  gap: 0.9rem;
}
 
.card-icon {
  width: 42px;
  height: 42px;
  border-radius: 8px;
  display: flex;
  align-items: center;
  justify-content: center;
  flex-shrink: 0;
}
 
.icon-img {
  width: 26px;
  height: 26px;
  object-fit: contain;
  filter: brightness(0) invert(1);
}
 
.icon-fallback {
  font-size: 1.2rem;
}
 
.card-heading {
  display: flex;
  flex-direction: column;
  gap: 0.1rem;
}
 
.card-title {
  font-size: 1.3rem;
  font-weight: 700;
  color: var(--cor-azul-primario);
  margin: 0;
  line-height: 1.2;
}
 
.card-subtitulo {
  font-size: 0.85rem;
  color: var(--cor-azul-primario);
  opacity: 0.75;
  font-weight: 400;
}
 
.card-descricao {
  font-size: 0.95rem;
  color: var(--cor-texto);
  line-height: 1.55;
  margin: 0;
}

@media (max-width: 768px) {
  .card {
    flex: 1 1 100%;
    width: 100%;
  }
}
</style>