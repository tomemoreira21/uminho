<template>
  <div class="legenda" aria-label="Legenda dos pilares do plano de recuperação">
    <ul class="legenda-lista">
      <li class="legenda-item" v-for="pilar in pilares" :key="pilar.nome">
        <span class="bolinha" aria-hidden="true" :style="{ background: pilar.cor }"></span>
        <span class="texto">{{ pilar.nome }}</span>
      </li>
    </ul>
  </div>
</template>

<script setup>
const pilares = [
  { nome: 'Transição verde',                                cor: 'var(--cor-verde-escuro)' },
  { nome: 'Transformação digital',                          cor: 'var(--cor-roxo-escuro)' },
  { nome: 'Crescimento inteligente, sustentável e inclusivo', cor: 'var(--cor-azul-ue)' },
  { nome: 'Coesão social e territorial',                    cor: 'var(--cor-vermelho-escuro)' },
  { nome: 'Saúde e resiliência económica, social e institucional', cor: 'var(--cor-azul-ciano-claro)' },
  { nome: 'Políticas para a próxima geração',               cor: 'var(--cor-laranja-escuro)' },
]
</script>

<style scoped>
.legenda {
  padding: 0.75rem 1rem;
  background: white;
  border: 1px solid #e0e6ed;
  border-radius: 8px;
  margin-bottom: 1rem;
  overflow-x: auto;
}

.legenda-lista {
  display: flex;
  flex-wrap: wrap;
  gap: 1rem 0.9rem;
  list-style: none;
  margin: 0;
  padding: 0;
}

.legenda-item {
  display: flex;
  align-items: center;
  gap: 0.4rem;
}

.bolinha {
  width: 14px;
  height: 14px;
  border-radius: 50%;
  flex-shrink: 0;
}

.texto {
  font-size: 0.71rem;
  color: var(--cor-texto);
}

@media (max-width: 768px) {
  .legenda-lista {
    flex-direction: column;
    gap: 0;
  }

  .legenda-item {
    padding: 0.5rem 0;
  }
}
</style>