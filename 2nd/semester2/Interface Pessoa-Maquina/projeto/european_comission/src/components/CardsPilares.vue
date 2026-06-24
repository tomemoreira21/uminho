<template>
  <section class="card-section">
    <div class="pilares-grid">
      <div
          class="pilar-card"
          v-for="pilar in pilares"
          :key="pilar.titulo"
          @click="irParaDetalhe(pilar.id)"
          @keydown.enter="irParaDetalhe(pilar.id)"
          @keydown.space.prevent="irParaDetalhe(pilar.id)"
          role="button"
          tabindex="0"
          :aria-label="`${pilar.titulo}: ${pilar.descricao}`"
        >
        <div class="pilar-icon">
          <img :src="pilar.icone" :alt="pilar.titulo" class="pilar-img" />
        </div>
        <h3 class="pilar-titulo">{{ pilar.titulo }}</h3>
        <p class="pilar-descricao">{{ pilar.descricao }}</p>
      </div>
    </div>
  </section>
</template>

<script setup>
import iconVerde       from '../assets/icons/transicao-verde.png'
import iconDigital     from '../assets/icons/transformacao-digital.png'
import iconCrescimento from '../assets/icons/crescimento.png'
import iconCoesao      from '../assets/icons/coesao.png'
import iconSaude       from '../assets/icons/saude.png'
import iconPoliticas   from '../assets/icons/politicas.png'

import { useRouter } from 'vue-router'

const router = useRouter()

function irParaDetalhe(id) {
  router.push(`/pilares/${id}`)
}

const pilares = [
  { id: 1, titulo: 'Transição Verde',          icone: iconVerde,       descricao: 'Apoio à transição climática e sustentabilidade ambiental' },
  { id: 2, titulo: 'Transformação Digital',    icone: iconDigital,     descricao: 'Aceleração da digitalização da economia e serviços públicos' },
  { id: 3, titulo: 'Crescimento Inteligente',  icone: iconCrescimento, descricao: 'Crescimento económico inteligente, sustentável e inclusivo' },
  { id: 4, titulo: 'Coesão Social e Territorial', icone: iconCoesao,   descricao: 'Redução das disparidades regionais e inclusão social' },
  { id: 5, titulo: 'Saúde e Resiliência',      icone: iconSaude,       descricao: 'Reforço da resiliência económica, social e institucional' },
  { id: 6, titulo: 'Políticas para a Próxima Geração', icone: iconPoliticas, descricao: 'Educação, competências e emprego juvenil' },
]
</script>

<style scoped>
.card-section {
  background: transparent;
}

.titulo-secao {
  font-size: 1.55rem;
  font-weight: 800;
  margin: 0 0 1.25rem;
  color: var(--cor-border);
}

.subtexto {
  font-size: 0.9rem;
  color: var(--cor-border);
  line-height: 1.65;
  margin: 0 0 1.5rem;
}

.pilares-grid {
  display: grid;
  grid-template-columns: repeat(3, minmax(0, 1fr));
  gap: 1.5rem;
}

.pilar-card {
  background: linear-gradient(135deg, var(--cor-azul-escuro) 0%, #1a2a4a 100%);
  border-radius: 12px;
  padding: 1.25rem 1rem;
  text-align: center;
  transition: transform 0.2s, box-shadow 0.2s;
  cursor: pointer;
}

.pilar-card:hover {
  transform: translateY(-4px);
  box-shadow: 0 4px 12px var(--cor-border);
}

.pilar-icon {
  height: 80px;
  display: flex;
  align-items: center;
  justify-content: center;
}

.pilar-img {
  max-height: 100%;
  max-width: 100%;
  object-fit: contain;
}

.pilar-titulo {
  font-size: 1rem;
  font-weight: 700;
  color: var(--cor-border);
  margin: 0 0 0.5rem;
}

.pilar-descricao {
  font-size: 0.78rem;
  color: var(--cor-border);
  line-height: 1.4;
  margin: 0;
}

@media (max-width: 1200px) {
  .pilares-grid {
    grid-template-columns: repeat(2, 1fr);
  }
}

@media (max-width: 600px) {
  .pilares-grid {
    grid-template-columns: 1fr;
  }
}
</style>