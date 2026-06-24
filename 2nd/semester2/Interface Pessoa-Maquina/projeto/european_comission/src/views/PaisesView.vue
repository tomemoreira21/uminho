<template>
  <div class="page">
    <h1 class="titulo">Países</h1>

    <!-- Grid de cards — um por país -->
    <div class="grid">
      <CardPais
        v-for="pais in paises"
        :key="pais.id"
        :pais="pais"
      />
    </div>
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue'
import CardPais from '../components/CardPais.vue'
import { dbAPI } from '../database/index.js'
import { getPaises } from '../services/getters.js'

const paises = ref([])

onMounted(async () => {
  paises.value = await getPaises(dbAPI)
})
</script>

<style scoped>
.page {
  background-color: var(--cor-sidebar-bg);
  min-height: 100%;
  padding: 2rem;
}

.titulo {
  color: var(--cor-azul-primario);
  font-size: 2rem;
  margin-bottom: 2rem;
}

/* Grid responsivo — adapta o número de colunas ao espaço disponível */
.grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(130px, 1fr));
  gap: 1rem;
}

@media (max-width: 768px) {
  .page {
    padding: 1rem;
  }

  .titulo {
    font-size: 1.3rem;
  }
}
</style>