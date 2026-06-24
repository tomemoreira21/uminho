<template>
  <div class="card-pilar" @click="irParaDetalhe" style="cursor: pointer">
    <div class="icon-container" :style="{ borderColor: pilar.corFundoIcone }">
      <img :src="pilar.imagem" :alt="pilar.titulo" class="icon-img" />
    </div>

    <div class="content">
      <h3 class="titulo" :style="{ color: pilar.corTexto }">{{ pilar.titulo }}</h3>
      <p class="descricao">{{ pilar.descricao }}</p>
    </div>

    <div class="footer">
      <div class="stats-group">
        <span class="valor" :style="{ color: pilar.corTexto }">{{ pilar.alocacao }}</span>
        <span class="label">Alocação UE</span>
      </div>
      <div class="stats-group">
        <span class="valor" :style="{ color: pilar.corTexto }">{{ pilar.totalInvestido }}</span>
        <span class="label">Total Investido</span>
      </div>
    </div>
  </div>
</template>

<script setup>
import { useRouter } from 'vue-router'

const props  = defineProps({ pilar: { type: Object, required: true } })
const router = useRouter()

function irParaDetalhe() {
  router.push(`/pilares/${props.pilar.id}`)
}
</script>

<style scoped>
.card-pilar {
  display: flex;
  flex-direction: column;
  background-color: white;
  border: 1px solid #e0e6ed; /* Borda leve */
  border-radius: 8px;
  padding: 1.5rem;
  transition: transform 0.2s ease;
  height: 100%;
}

.card-pilar:hover {
  transform: translateY(-4px);
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.08);
}

.icon-container {
  border: 2px solid;
  width: 70px;
  height: 70px;
  border-radius: 8px;
  display: flex;
  align-items: center;
  justify-content: center;
  margin-bottom: 1.5rem;
  align-self: center; /* Centraliza o ícone */
  opacity: 0.85;
}

.icon-img {
  width: 95px;
  height: 95px;
  object-fit: contain;
}

.content {
  flex-grow: 1; /* Faz o conteúdo ocupar o espaço para alinhar o footer embaixo */
  text-align: left;
  margin-bottom: 1.5rem;
}

.titulo {
  font-family: var(--font-principal);
  font-size: 1.1rem;
  font-weight: 700;
  margin-bottom: 0.75rem;
}

.descricao {
  font-size: 0.85rem;
  color: var(--cor-texto);
  line-height: 1.4;
}

.footer {
  display: grid;
  grid-template-columns: 1fr 1fr; /* Divide em duas colunas iguais */
  border-top: 1px solid #f0f0f0;
  padding-top: 1rem;
  gap: 1rem;
}

.stats-group {
  display: flex;
  flex-direction: column;
}

.valor {
  font-weight: 800;
  font-size: 1.2rem;
  font-family: var(--font-principal)
}

.label {
  font-size: 0.7rem;
  color: var(--cor-texto);
  text-transform: uppercase;
}

@media (max-width: 768px) {
  .card-pilar {
    flex-direction: row;
    align-items: flex-start;
    gap: 1rem;
    padding: 1rem;
  }

  .icon-container {
    width: 50px;
    height: 50px;
    flex-shrink: 0;
    margin-bottom: 0;
    align-self: flex-start;
  }

  .icon-img {
    width: 65px;
    height: 65px;
  }

  .valor {
    font-size: 1rem;
  }
}
</style>