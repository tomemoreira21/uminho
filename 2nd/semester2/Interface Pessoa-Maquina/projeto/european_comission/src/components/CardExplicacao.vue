<template>
  <div class="card">
    <h2 class="card-titulo">Como funciona o pagamento?</h2>
    <p class="card-texto">
      Cada país tem objetivos definidos pelo
      <strong>Conselho da União Europeia</strong>
      e precisa de provar à
      <strong>Comissão Europeia</strong>
      que os cumpriu para receber o pagamento. Se algum objetivo ainda não for considerado
      cumprido, isso não significa necessariamente que não esteja a ser implementado.
    </p>
  </div>
</template>

<style scoped>
.card {
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 10px;
  padding: 1.5rem 1.75rem;
  display: flex;
  flex-direction: column;
  gap: 0.85rem;
}

.card-titulo {
  font-size: 1.1rem;
  font-weight: 400;
  color: var(--cor-azul-primario);
  margin: 0;
}

.card-texto {
  font-size: 0.875rem;
  line-height: 1.65;
  color: var(--cor-texto);
  margin: 0;
}

.card-texto strong {
  font-weight: 700;
  color: var(--cor-azul-primario);
}
</style>