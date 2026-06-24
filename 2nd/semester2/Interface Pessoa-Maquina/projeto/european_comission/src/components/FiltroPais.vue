<template>
  <div class="seletor" ref="seletorRef">
    <button
      class="btn-seletor"
      :aria-expanded="aberto"
      aria-haspopup="listbox"
      :aria-label="'Filtrar por país: ' + (paisSelecionado ? paisSelecionado.nome : props.labelTodos)"
      @click="aberto = !aberto"
      @keydown="fechar"
    >
      {{ paisSelecionado ? paisSelecionado.bandeira + ' ' + paisSelecionado.nome : props.labelTodos }}
      <span class="seta" aria-hidden="true">▼</span>
    </button>

    <ul
      v-if="aberto"
      class="dropdown"
      role="listbox"
      :aria-label="'Opções de país'"
    >
      <li
        class="opcao"
        role="option"
        :aria-selected="!paisSelecionado"
        @click="selecionar(null)"
        @keydown.enter.space.prevent="selecionar(null)"
        tabindex="0"
      >
        {{ props.labelTodos }}
      </li>
      <li
        v-for="p in paises"
        :key="p.id"
        class="opcao"
        role="option"
        :aria-selected="paisSelecionado?.id === p.id"
        :class="{ ativo: paisSelecionado?.id === p.id }"
        @click="selecionar(p)"
        @keydown.enter.space.prevent="selecionar(p)"
        tabindex="0"
      >
        {{ p.bandeira }} {{ p.nome }}
      </li>
    </ul>
  </div>
</template>

<script setup>
import { ref, onMounted, onUnmounted } from 'vue'

const props = defineProps({
  paises:     { type: Array,  required: true },
  labelTodos: { type: String, default: 'Todos os países' },
})

const emit = defineEmits(['update:modelValue'])

const aberto          = ref(false)
const paisSelecionado = ref(null)
const seletorRef      = ref(null)

function selecionar(pais) {
  paisSelecionado.value = pais
  emit('update:modelValue', pais)
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
  width: 200px;
}

.btn-seletor {
  width: 100%;
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0.5rem 0.75rem;
  border: 1px solid var(--cor-border);
  border-radius: 6px;
  background: white;
  color: var(--cor-texto);
  font-family: var(--font-principal);
  font-size: 0.85rem;
  font-weight: 700;
  cursor: pointer;
}

.btn-seletor:hover {
  background-color: var(--cor-azul-selecao);
}

.seta {
  font-size: 0.65rem;
  color: var(--cor-texto);
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
  max-height: 220px;   /* ← limita altura e activa scroll */
  overflow-y: auto;
  z-index: 100;
}

.opcao {
  padding: 0.5rem 0.75rem;
  font-family: var(--font-principal);
  font-size: 0.85rem;
  color: var(--cor-texto);
  cursor: pointer;
  transition: background 0.15s;
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