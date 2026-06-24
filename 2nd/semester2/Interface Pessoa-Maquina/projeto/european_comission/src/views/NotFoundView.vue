<template>
  <div class="page">
    <div class="conteudo">
      <span class="codigo">404</span>
      <h1 class="titulo">Página não encontrada</h1>
      <p class="descricao">A página que procuras não existe ou foi removida.</p>
      <RouterLink to="/" class="btn-voltar">🏠 Voltar ao início</RouterLink>
    </div>
  </div>
</template>

<style scoped>
.page {
  display: flex;
  align-items: center;
  justify-content: center;
  min-height: 100%;
  background-color: var(--cor-sidebar-bg);
}

.conteudo {
  text-align: center;
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 1rem;
}

.codigo {
  font-size: 6rem;
  font-weight: 900;
  font-family: monospace;
  color: var(--cor-azul-primario);
  line-height: 1;
}

.titulo {
  font-size: 1.5rem;
  font-weight: 700;
  color: var(--cor-azul-primario);
  margin: 0;
}

.descricao {
  font-size: 0.95rem;
  color: var(--cor-texto);
  margin: 0;
}

.btn-voltar {
  margin-top: 1rem;
  background: var(--cor-azul-primario);
  color: white;
  padding: 0.6rem 1.5rem;
  border-radius: 8px;
  text-decoration: none;
  font-weight: 600;
  font-size: 0.9rem;
  transition: opacity 0.2s;
}

.btn-voltar:hover {
  opacity: 0.85;
}
</style>