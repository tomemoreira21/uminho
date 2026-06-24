<template>
  <div class="seletor" ref="seletorRef">
    <button
      class="btn-seletor"
      :aria-expanded="aberto"
      aria-haspopup="listbox"
      :aria-label="'Filtrar por estado: ' + (selecionado ? selecionado.label : labelTodos)"
      @click="aberto = !aberto"
      @keydown="fechar"
    >
      <span v-if="selecionado" class="bolinha" aria-hidden="true" :style="{ backgroundColor: selecionado.cor }"></span>
      <span>{{ selecionado ? selecionado.label : labelTodos }}</span>
      <span class="seta" aria-hidden="true">▼</span>
    </button>
    <ul v-if="aberto" class="dropdown" role="listbox" aria-label="Opções de estado">
      <li
        class="opcao"
        role="option"
        :aria-selected="!selecionado"
        tabindex="0"
        @click="selecionar(null)"
        @keydown.enter.space.prevent="selecionar(null)"
      >{{ labelTodos }}</li>
      <li
        v-for="opcao in opcoes"
        :key="opcao.value"
        class="opcao"
        role="option"
        :aria-selected="selecionado?.value === opcao.value"
        :class="{ ativo: selecionado?.value === opcao.value }"
        tabindex="0"
        @click="selecionar(opcao)"
        @keydown.enter.space.prevent="selecionar(opcao)"
      >
        <span class="bolinha" aria-hidden="true" :style="{ backgroundColor: opcao.cor }"></span>
        {{ opcao.label }}
      </li>
    </ul>
  </div>
</template>

<script setup>
import { ref, onMounted, onUnmounted } from 'vue'

const props = defineProps({
  opcoes:     { type: Array,  required: true },
  labelTodos: { type: String, default: 'Estado' },
})

const emit = defineEmits(['update:modelValue'])

const aberto      = ref(false)
const selecionado = ref(null)
const seletorRef  = ref(null)

function selecionar(opcao) {
  selecionado.value = opcao
  emit('update:modelValue', opcao)
  aberto.value = false
}

function fechar(e) {
  if (e.key === 'Escape') aberto.value = false
}

function fecharFora(e) {
  if (seletorRef.value && !seletorRef.value.contains(e.target))
    aberto.value = false
}

onMounted(()  => document.addEventListener('click', fecharFora))
onUnmounted(() => document.removeEventListener('click', fecharFora))
</script>

<style scoped>
.seletor {
  position: relative;
  width: 175px;
}

.btn-seletor {
  width: 100%;
  display: flex;
  align-items: center;
  gap: 0.4rem;
  padding: 0.45rem 0.75rem;
  border: 1px solid var(--cor-border);
  border-radius: 6px;
  background: white;
  color: var(--cor-texto);
  font-family: var(--font-principal);
  font-size: 0.85rem;
  font-weight: 700;
  cursor: pointer;
}

/* o span do texto cresce, a bolinha e a seta não */
.btn-seletor span:not(.bolinha):not(.seta) {
  flex: 1;
  text-align: left;
  overflow: hidden;
  white-space: nowrap;
  text-overflow: ellipsis;
}

.btn-seletor:hover {
  background-color: var(--cor-azul-selecao);
}

.seta {
  font-size: 0.65rem;
  flex-shrink: 0;
}

.bolinha {
  width: 9px;
  height: 9px;
  border-radius: 50%;
  flex-shrink: 0;
  display: inline-block;
}

.dropdown {
  position: absolute;
  top: calc(100% + 4px);
  left: 0;
  width: 100%;
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 6px;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
  z-index: 100;
}

.opcao {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  padding: 0.5rem 0.75rem;
  font-family: var(--font-principal);
  font-size: 0.85rem;
  color: var(--cor-texto);
  cursor: pointer;
}

.opcao:hover,
.opcao.ativo {
  background-color: var(--cor-azul-selecao);
}

@media (max-width: 768px) {
  .seletor {
    width: 100%;
  }
}
</style>