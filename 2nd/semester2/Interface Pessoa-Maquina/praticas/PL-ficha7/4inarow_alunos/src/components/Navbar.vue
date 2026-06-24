<script>
import { ResultadoJogo } from '@/models/resultadoJogo';

export default {
  props: ['jogadorAJogar', 'vencedor'],
  computed: {
    textoVencedor() {
      if (this.vencedor === ResultadoJogo.VERMELHO) {
        return "Vencedor -> Vermelho"
      } else if(this.vencedor === ResultadoJogo.AMARELO) {
        return "Vencedor -> Amarelo"
      } else {
        return "EMPATE";
      }
    }
  }
}
</script>

<template>
  <div class="navbar">
    <h3>4 em linha</h3>

    <button 
      v-if= "this.vencedor == null" 
      class="button"
      :class="{
        red: this.jogadorAJogar,
        yellow: !this.jogadorAJogar
      }"
    >

    {{ this.jogadorAJogar ? 'Vermelho' : 'Amarelo' }}

    </button>

    <button v-else class="button" disabled>
      {{ textoVencedor }}

    </button>
  </div>



</template>

<style scoped>
.button {
  border: 1px solid black;
  border-radius: 5px;
  text-align: center;
  padding: 10px;
  font-weight: 600;
}

.navbar {
  display: flex;
  padding: 0 20px;
  justify-content: space-between;
  align-items: center;
  width: 100%;
  height: 50px;
  background: #93a2e0;

}

.yellow {
  background-color: var(--color-yellow);
}

.red {
  background-color: var(--color-red);
}
</style>