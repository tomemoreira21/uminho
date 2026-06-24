<template>
  <button class="btn-desfazer" @click="emit('desfazer')">
    <img src="../assets/undo.png" alt="undo" class="undo-icon" />
    Desfazer
  </button>
</template>

<script setup>
const emit = defineEmits(['desfazer'])
</script>

<style scoped>
.btn-desfazer {
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

.btn-desfazer:hover {
  background-color: var(--cor-azul-selecao);
}

.undo-icon {
  width: 16px;
  height: 16px;
  object-fit: contain;
}
</style>