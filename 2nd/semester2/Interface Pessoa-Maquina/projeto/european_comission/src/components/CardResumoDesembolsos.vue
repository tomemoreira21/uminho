<template>
  <div class="secao-card">
    <div class="grafico-header">
      <h2 class="secao-titulo-dark">Desembolsos</h2>
      <RouterLink to="/desembolsos" class="btn-ver-mais">Ver mais</RouterLink>
    </div>

    <div class="desembolsos-layout">
      <div class="desembolso-bloco">
        <p class="desembolso-titulo">Subsídios da RRF desembolsados</p>
        
        <svg viewBox="0 0 120 70" class="gauge-desembolso">
          <path d="M 15 60 A 45 45 0 0 1 105 60" fill="none" stroke="#e0e0e0" stroke-width="18" />
          <path d="M 15 60 A 45 45 0 0 1 105 60" fill="none" stroke="var(--cor-azul-primario, #4a73b1)" stroke-width="18"
                :stroke-dasharray="141.37" 
                :stroke-dashoffset="141.37 - (dados.pctSubsidios / 100 * 141.37)" />
          
          <line x1="5"  y1="60" x2="25"  y2="60" stroke="#333" stroke-width="1.5"/>
          <line x1="95" y1="60" x2="115" y2="60" stroke="#333" stroke-width="1.5"/>
        </svg>

        <p class="desembolso-valor">€{{ dados.subsidios }}</p>
        <p class="nota-desembolso">Este gráfico exibe a quantidade de subsídios desembolsados até agora sob a RRF. 
            Subsídios não são reembolsáveis contribuições financeiras. O montante total das  subvenções concedidas a cada Estado-Membro é determinado 
            por um chave de alocação e o custo total estimado do  respectivo plano de recuperação e resiliência.
        </p>
      </div>

      <div class="desembolso-bloco">
        <p class="desembolso-titulo">Empréstimos da RRF desembolsados</p>
        
        <svg viewBox="0 0 120 70" class="gauge-desembolso">
          <path d="M 15 60 A 45 45 0 0 1 105 60" fill="none" stroke="#e0e0e0" stroke-width="18" />
          <path d="M 15 60 A 45 45 0 0 1 105 60" fill="none" stroke="var(--cor-azul-primario, #4a73b1)" stroke-width="18"
                :stroke-dasharray="141.37" 
                :stroke-dashoffset="141.37 - (dados.pctEmprestimos / 100 * 141.37)" />
                
          <line x1="5"  y1="60" x2="25"  y2="60" stroke="#333" stroke-width="1.5"/>
          <line x1="95" y1="60" x2="115" y2="60" stroke="#333" stroke-width="1.5"/>
        </svg>

        <p class="desembolso-valor">€{{ dados.emprestimos }}</p>
        <p class="nota-desembolso">Este gráfico exibe o montante de empréstimos desembolsados até agora sob a RRF. 
            Empréstimos são reembolsáveis contribuições financeiras. 
            O montante total dos  empréstimos concedidos a cada Estado-Membro é determinado pela avaliação de sua solicitação de empréstimo e não pode exceder 6,8% de seu RNB de 2019.
        </p>
      </div>
    </div>
  </div>
</template>

<script setup>
defineProps({
  dados: {
    type: Object,
    required: true
  }
})
</script>

<style scoped>
.secao-card {
  background: white;
  border: 1px solid var(--cor-border);
  border-radius: 10px;
  padding: 1.5rem;
  display: flex;
  flex-direction: column;
  height: 100%;
}

.grafico-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 1.5rem;
}

.secao-titulo-dark {
  font-size: 1.2rem;
  font-weight: bold;
  font-family: monospace;
  color: black;
  margin: 0;
}

.btn-ver-mais {
  background: var(--cor-azul-escuro);
  color: white;
  border-radius: 4px;
  padding: 0.4rem 1rem;
  font-size: 0.85rem;
  text-decoration: none;
}

.desembolsos-layout {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 1.5rem;
}

.desembolso-bloco {
  border: 1px solid var(--cor-border);
  border-radius: 8px;
  padding: 1.5rem;
  display: flex;
  flex-direction: column;
  align-items: center;
}

.desembolso-titulo {
  font-size: 0.85rem;
  font-weight: bold;
  text-align: center;
  margin-bottom: 1.5rem;
  height: 2em;
  color: black; 
}

.gauge-desembolso {
  width: 180px;
  margin-bottom: 0.5rem;
}

.desembolso-valor {
  font-size: 1.1rem;
  font-weight: bold;
  font-family: monospace;
  margin: 0.5rem 0 1rem 0;
  color: black;
}

.nota-desembolso {
  font-size: 0.75rem;
  color: #666;
  text-align: justify;
  line-height: 1.5;
}

@media (max-width: 768px) {
  .desembolsos-layout {
    grid-template-columns: 1fr;
  }
}
</style>