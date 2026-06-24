<template>
  <!-- RouterLink torna o card clicável e navega para a página do país -->
  <RouterLink :to="`/paises/${pais.id}`" class="card">
    <span class="bandeira">{{ pais.bandeira }}</span>
    <span class="nome">{{ pais.nome }}</span>
  </RouterLink>
</template>

<script setup>
// Recebe o objeto do país como prop do componente pai
defineProps({
  pais: {
    type: Object,
    required: true
  }
})
</script>

<style scoped>
.card {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  gap: 0.75rem;
  background-color: var(--cor-azul-primario);
  border-radius: 12px;
  padding: 1.5rem;
  text-decoration: none;
  cursor: pointer;
  transition: transform 0.2s, box-shadow 0.2s;
  aspect-ratio: 1 / 1;        /* ← garante cards quadrados */
  min-height: 0;
}

/* Efeito hover — sobe ligeiramente para indicar que é clicável */
.card:hover {
  transform: translateY(-4px);
  box-shadow: 0 8px 20px rgba(0, 0, 0, 0.2);
}

.bandeira {
  font-size: 2.5rem;
}

.nome {
  color: white;
  font-size: 0.9rem;
  font-weight: 700;
  font-family: var(--font-principal);
  text-align: center;
}
</style>