<template>
  <div class="app-layout">
    <Toast position="top-right" />
    <TopBar />
    <div class="content-layout">
      <SidebarNav />
      <main class="main-content">
        <RouterView :key="$route.fullPath"/>
      </main>
    </div>
  </div>
</template>

<script setup>
import Toast from 'primevue/toast'
import TopBar from './components/TopBar.vue'
import SidebarNav from './components/SidebarNav.vue'
</script>

<style scoped>
.app-layout {
  display: flex;
  flex-direction: column;
  height: 100vh;
}

.content-layout {
  display: flex;
  flex: 1;
  overflow: hidden;
}

.main-content {
  flex: 1;
  overflow-y: auto;
  background-color: var(--cor-sidebar-bg);
}
</style>