<template>
  <div class="page">
    <div class="cabecalho">
      <h1 class="titulo">Pilares</h1>
    </div>

    <p class="descricao">
      <span class="letra-inicial">O</span>mecanismo de Recuperação e Resiliência (MRR) estrutura
      os investimentos em seis pilares estratégicos que orientam a transformação económica e social da
      União Europeia.
    </p>

    <div class="grid-pilares">
      <PilarCard
        v-for="p in listaDePilares"
        :key="p.id"
        :pilar="p"
      />
    </div>
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue'
import PilarCard from '../components/PilarCard.vue'
import { dbAPI } from '../database/index.js'
import { getPilaresInfo } from '../services/getters.js'

import iconVerde       from '../assets/icons/transicao-verde.png'
import iconDigital     from '../assets/icons/transformacao-digital.png'
import iconCrescimento from '../assets/icons/crescimento.png'
import iconCoesao      from '../assets/icons/coesao.png'
import iconSaude       from '../assets/icons/saude.png'
import iconPoliticas   from '../assets/icons/politicas.png'

const estilosPilar = {
  1: { corTexto: 'var(--cor-verde-escuro)',     corFundoIcone: 'var(--cor-verde-escuro)',     imagem: iconVerde       },
  2: { corTexto: 'var(--cor-roxo-escuro)',      corFundoIcone: 'var(--cor-roxo-claro)',      imagem: iconDigital     },
  3: { corTexto: 'var(--cor-azul-ue)',          corFundoIcone: 'var(--cor-azul-claro)',      imagem: iconCrescimento },
  4: { corTexto: 'var(--cor-vermelho-escuro)',  corFundoIcone: 'var(--cor-vermelho-claro)',  imagem: iconCoesao      },
  5: { corTexto: 'var(--cor-azul-ciano-claro)', corFundoIcone: 'var(--cor-azul-ciano)',     imagem: iconSaude       },
  6: { corTexto: 'var(--cor-laranja-escuro)',   corFundoIcone: 'var(--cor-laranja-claro)',   imagem: iconPoliticas   },
}

const listaDePilares = ref([])

onMounted(async () => {
  const dados = await getPilaresInfo(dbAPI)
  listaDePilares.value = dados.map(p => ({
    ...p,
    ...estilosPilar[p.id]
  }))
})
</script>

<style scoped>
.page {
  background-color: var(--cor-sidebar-bg);
  min-height: 100%;
  padding: 2rem;
}

.cabecalho {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 1rem;
  width: 100%;
}

.titulo {
  color: var(--cor-azul-primario);
  font-size: 2rem;
  margin-bottom: 1rem;
}

.descricao {
  color: black;
  font-size: 0.95rem;
  line-height: 1.6;
  margin-bottom: 2rem;
}

.letra-inicial {
  font-size: 2rem;
  font-weight: bold;
  float: left;
  line-height: 1;
  margin-right: 2px;
  margin-top: -8px;
  color: black;
}

.grid-pilares {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  gap: 1.5rem;
  width: 100%;
}

@media (max-width: 768px) {
  .page {
    padding: 1rem;
  }

  .titulo {
    font-size: 1.3rem;
  }

  .grid-pilares {
    grid-template-columns: 1fr;
  }
}
</style>