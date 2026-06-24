<template>
  <button class="btn-voltar" @click="emit('voltar')">
    ◀ Voltar
  </button>
</template>

<script setup>
const emit = defineEmits(['voltar'])
</script>

<style scoped>
.btn-voltar {
  display: flex;
  align-items: center;
  gap: 0.4rem;
  padding: 0.4rem 1rem;
  border: 1px solid var(--cor-border);
  border-radius: 6px;
  background-color: white;
  color: var(--cor-texto);
  font-family: var(--font-principal);
  font-size: 0.85rem;
  font-weight: 700;
  cursor: pointer;
  transition: background-color 0.2s ease;
}

.btn-voltar:hover {
  background-color: var(--cor-azul-selecao);
}
</style>