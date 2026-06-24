<template>
  <div class="filtro-wrapper" ref="filtroRef">
    <button
      class="filtro-btn"
      :aria-expanded="aberto"
      aria-haspopup="listbox"
      :aria-label="'Filtrar por pilar: ' + (selecionado ? selecionado.label : labelTodos)"
      @click="aberto = !aberto"
      @keydown="fechar"
    >
      <span v-if="selecionado" class="pilar-circulo" aria-hidden="true" :style="{ backgroundColor: selecionado.cor }" />
      <span class="filtro-texto">{{ selecionado ? selecionado.label : labelTodos }}</span>
      <span class="seta" aria-hidden="true">▼</span>
    </button>

    <ul v-if="aberto" class="filtro-menu" role="listbox" aria-label="Opções de pilar">
      <li
        class="filtro-opcao"
        role="option"
        :aria-selected="!selecionado"
        :class="{ ativo: !selecionado }"
        tabindex="0"
        @click="selecionar(null)"
        @keydown.enter.space.prevent="selecionar(null)"
      >
        <span>{{ labelTodos }}</span>
      </li>
      <li
        v-for="pilar in pilares"
        :key="pilar.label"
        class="filtro-opcao"
        role="option"
        :aria-selected="selecionado?.label === pilar.label"
        :class="{ ativo: selecionado?.label === pilar.label }"
        tabindex="0"
        @click="selecionar(pilar)"
        @keydown.enter.space.prevent="selecionar(pilar)"
      >
        <span class="pilar-circulo" aria-hidden="true" :style="{ backgroundColor: pilar.cor }" />
        <span>{{ pilar.label }}</span>
      </li>
    </ul>
  </div>
</template>

<script setup>
import { ref, onMounted, onUnmounted } from 'vue'

const props = defineProps({
  labelTodos: { type: String, default: 'Todos os pilares' },
  pilares:    { type: Array,  default: () => [] },
})

const emit = defineEmits(['update:modelValue'])

const aberto      = ref(false)
const selecionado = ref(null)
const filtroRef   = ref(null)

function selecionar(pilar) {
  selecionado.value = pilar
  emit('update:modelValue', pilar)
  aberto.value = false
}

function fechar(e) {
  if (e.key === 'Escape') aberto.value = false
}

function fecharFora(e) {
  if (filtroRef.value && !filtroRef.value.contains(e.target))
    aberto.value = false
}

onMounted(()   => document.addEventListener('click', fecharFora))
onUnmounted(() => document.removeEventListener('click', fecharFora))
</script>

<style scoped>
.filtro-wrapper {
  position: relative;
  display: inline-block;
}

.filtro-btn {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  width: 300px;
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 6px;
  padding: 0.4rem 0.75rem;
  cursor: pointer;
  font-family: var(--font-principal);
  color: var(--cor-texto);
  font-size: 0.9rem;
  font-weight: 700;
  overflow: hidden;
}

.filtro-btn:hover {
  background-color: var(--cor-azul-selecao);
}

.filtro-texto {
  flex: 1;
  overflow: hidden;
  white-space: nowrap;
  text-overflow: ellipsis;
  text-align: left;
}

.seta {
  transition: transform 0.2s;
  font-size: 0.7rem;
  flex-shrink: 0;
}

.filtro-menu {
  position: absolute;
  top: 110%;
  left: 0;
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 6px;
  display: flex;
  flex-direction: column;
  min-width: 280px;
  z-index: 100;
  box-shadow: 0 4px 12px rgba(0,0,0,0.1);
  max-height: 280px;
  overflow-y: auto;
}

.filtro-opcao {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  padding: 0.65rem 1rem;
  background: none;
  border: none;
  border-bottom: 1px solid var(--cor-border);
  text-align: left;
  cursor: pointer;
  font-family: var(--font-principal);
  color: var(--cor-texto);
  font-size: 0.9rem;
  font-weight: 400;
}

.filtro-opcao:last-child {
  border-bottom: none;
}

.filtro-opcao:hover,
.filtro-opcao.ativo {
  background-color: var(--cor-azul-selecao);
}

.pilar-circulo {
  display: inline-block;
  width: 14px;
  height: 14px;
  border-radius: 50%;
  flex-shrink: 0;
}

@media (max-width: 768px) {
  .filtro-wrapper {
    display: block;
    width: 100%;
  }
  .filtro-btn {
    width: 100%;
  }
  .filtro-menu {
    min-width: unset;
    width: 100%;
  }
}
</style>