<template>
  <nav class="sidebar">
    <RouterLink
      v-for="item in navItems"
      :key="item.path"
      :to="item.path"
      class="nav-link"
      :class="{ 'nav-link--active': isActive(item.path) }"
    >
      <span class="nav-icon">{{ item.icon }}</span>
      <span>{{ item.label }}</span>
    </RouterLink>
  </nav>
</template>

<script setup>
import { useRoute } from 'vue-router'

const route = useRoute()

function isActive(path) {
  if (path === '/') return route.path === '/'
  return route.path.startsWith(path)
}

const navItems = [
  { path: '/',              icon: '🏠', label: 'Home' },
  { path: '/paises',        icon: '🌍', label: 'Países' },
  { path: '/pilares',       icon: '🏛️', label: 'Pilares' },
  { path: '/indicadores',   icon: '📊', label: 'Indicadores Comuns' },
  { path: '/marcos-metas',  icon: '🎯', label: 'Marcos e Metas' },
  { path: '/desembolsos',   icon: '💰', label: 'Desembolsos' },
]
</script>

<style scoped>
.sidebar {
  width: 240px;
  min-height: 100%;
  background-color: var(--cor-sidebar-bg);
  border-right: 1px solid var(--cor-border);
  display: flex;
  flex-direction: column;
  padding: 1rem 0;
}

/*  estilo base de todos os links */
.nav-link {
  display: flex;
  align-items: center;
  gap: 0.6rem;
  padding: 0.75rem 1.25rem;
  text-decoration: none;
  color: #333;
  font-size: 0.95rem;
  transition: background 0.2s;
  white-space: nowrap; /* impede o texto de mudar de linha */
}

/* estilo quando passa com o rato por cima */
.nav-link:hover {
  background-color: var(--cor-azul-selecao)
}

/* efeito quando está na página */
.nav-link--active {
  background-color: var(--cor-azul-selecao);
  color: var(--cor-azul-primario);
  font-weight: bold;
  border-left: 3px solid var(--cor-azul-primario);
}

</style>

