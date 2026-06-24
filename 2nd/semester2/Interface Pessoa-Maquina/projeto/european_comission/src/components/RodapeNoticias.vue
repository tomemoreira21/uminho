<template>
  <!-- Barra fixa no fundo da página -->
  <div class="rodape-noticias">

    <!-- Wrapper que esconde o overflow do ticker -->
    <div class="ticker-wrapper">

      <!-- A faixa animada — a duração é calculada dinamicamente consoante o nº de items -->
      <div class="ticker-track" :style="{ animationDuration: duracaoAnimacao + 's' }">

        <!-- Cada item é duplicado (itemsDuplicados) para criar o efeito de loop contínuo -->
        <div v-for="(item, i) in itemsDuplicados" :key="i" class="ticker-item">
          <!-- Bandeira do país via flagcdn -->
          <img
            class="ticker-bandeira"
            :src="`https://flagcdn.com/w40/${item.codigoBandeira}.png`"
            :alt="item.nome"
          />
          <!-- Nome do país -->
          <span class="ticker-pais">{{ item.nome }}</span>
          <span class="ticker-separador">—</span>
          <!-- Último evento do histórico do país -->
          <span class="ticker-texto">{{ item.descricao }}</span>
          <!-- Data formatada em pt-PT (ex: 09 mar. 2026) -->
          <span class="ticker-data">{{ formatarData(item.data) }}</span>
          <!-- Separador visual entre items -->
          <span class="ticker-divider">⬥</span>
        </div>

      </div>
    </div>
  </div>
</template>

<script setup>
import { ref, computed, onMounted } from 'vue'
import { dbAPI } from '../database/index.js'
import { getMapaPaises } from '../services/getters.js'

// Lista de países carregada da API
const paises = ref([])

onMounted(async () => {
  paises.value = await getMapaPaises(dbAPI)
})

// Converte "2026-03-09" → "09 mar. 2026"
function formatarData(data) {
  if (!data) return ''
  const d = new Date(data)
  return d.toLocaleDateString('pt-PT', { day: '2-digit', month: 'short', year: 'numeric' })
}

// Para cada país, pega no evento mais recente do histórico (índice 0)
const items = computed(() => {
  const resultado = []
  for (const p of paises.value) {
    const ultimo = p.historico?.[0]
    if (ultimo) {
      resultado.push({
        nome:           p.nome,
        codigoBandeira: p.codigo.toLowerCase(), // "PT" → "pt" para a URL da bandeira
        data:           ultimo.data,
        descricao:      ultimo.descricao,
      })
    }
  }
  return resultado
})

// Duplica os items para que a animação pareça infinita sem salto
const itemsDuplicados = computed(() => [...items.value, ...items.value])

// Cada item tem ~6s de tempo de leitura; mínimo de 10s
const duracaoAnimacao = computed(() => Math.max(items.value.length * 6, 10))
</script>

<style scoped>
/* Barra fixa no fundo, à direita da sidebar (240px) */
.rodape-noticias {
  position: fixed;
  bottom: 0;
  left: 240px;
  right: 0;
  height: 44px;
  background: #1a3a8f;
  border-top: 2px solid rgba(255,255,255,0.15);
  display: flex;
  align-items: center;
  z-index: 999;
  overflow: hidden;
  font-family: monospace;
}

/* Esconde o que sai fora */
.ticker-wrapper {
  flex: 1;
  overflow: hidden;
  height: 100%;
  display: flex;
  align-items: center;
}

/* A faixa que se move da direita para a esquerda */
.ticker-track {
  display: flex;
  align-items: center;
  white-space: nowrap;
  animation: ticker linear infinite;
}

/* Move 50% (metade = 1 cópia dos items) para criar loop sem salto */
@keyframes ticker {
  from { transform: translateX(0); }
  to   { transform: translateX(-50%); }
}

.ticker-item {
  display: inline-flex;
  align-items: center;
  gap: 0.6rem;
  padding: 0 1rem;
}

.ticker-bandeira {
  width: 22px;
  height: auto;
  border-radius: 2px;
  flex-shrink: 0;
  box-shadow: 0 1px 3px rgba(0,0,0,0.3);
}

.ticker-pais     { font-size: 0.75rem; font-weight: 700; color: white; }
.ticker-separador { color: rgba(255,255,255,0.3); font-size: 0.7rem; }
.ticker-texto    { font-size: 0.73rem; color: rgba(255,255,255,0.85); }
.ticker-data     { font-size: 0.68rem; color: rgba(255,255,255,0.5); font-style: italic; }
.ticker-divider  { color: rgba(255,255,255,0.3); font-size: 0.65rem; margin: 0 0.75rem; }
</style>