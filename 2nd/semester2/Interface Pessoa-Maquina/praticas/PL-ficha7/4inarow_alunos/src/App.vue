<!-- Este documento apresenta uma solução em construção. É fornecido como 
     material de estudo. Recomenda-se que o revejam e melhorem conforme   
     forem adquirindo novos conhecimentos. -->

<script>
import OJogo from './components/OJogo.vue';
import Navbar from './components/Navbar.vue';


export default {
  components: {
    Navbar,
    OJogo      // equivalente a: 'OJogo': OJogo, permite também usar <o-jogo>
  },
  data() {
    return {
      jogador: false,
      vencedor: null
    }
  },
  methods: { 
    alterarJogadorAJogar(jogador) {
      this.jogador = jogador;
    },
    determinarVencedor(jogador) {
      this.vencedor = jogador;
    },
    reset(jogador) {
      this.jogador = jogador;
      this.vencedor = null;
    }
  }
}
</script>

<template>
  <Navbar :jogadorAJogar="this.jogador" :vencedor="this.vencedor"/>
  <OJogo @jogadorAJogar="alterarJogadorAJogar" 
         @reset="reset" 
         @jogoTerminou="determinarVencedor" />
</template>

<!-- :prop no sentido pai para filho, 
     @event no sentido filho para pai, através do emits -->
