<template>
  <header class="topbar">
    <div class="topbar-logo">
      <img src="../assets/logo.png" alt="EU Logo" class="logo" />
      <span class="topbar-title">European Commission</span>
    </div>
  </header>
</template>

<style scoped>
.topbar {
  background-color: white;
  color: var(--cor-azul-escuro);
  padding: 0.75rem 1.5rem;
  display: flex;
  align-items: center;
  border-bottom: 3px solid var(--cor-azul-escuro);
}

.topbar-logo {
  display: flex;
  align-items: center;
  gap: 0.75rem;
}

.logo {
  height: 40px;
}

.topbar-title {
  font-size: 1.2rem;
  font-weight: bold;
  letter-spacing: 0.05em;
}
</style>

