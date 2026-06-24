<script>
import { Game } from "../models/game";
import { useSimulationStore } from "../stores/simulationStore";

export default {
  data() {
    return {
      game: new Game(),
      running: false,
      simulation: useSimulationStore()
    }
  },
  methods: {
    play(column) {
      this.game.play(column);
    },
    simulate() {
      /* 2) Check if store contains a simulation to run.
            If there is no simulation then inform the user about it */
      if (!this.simulation.containsSimulation) {
        alert("There is no simulation");
        return;
      }


      let i = 0;
      this.running = true;
      this.game.reset();

      /* 3) Init the game.player variable with the simulation store start player */
      this.game.player = this.simulation.startPlayer;

      /* 4) Get simulation store array of plays and uncomment the code bellow */
      const plays = this.simulation.plays;

      const interval = setInterval(() => {
        this.play(plays[i]);
        i++;

        if (i === plays.length) {
          clearInterval(interval);
          this.running = false;
        }
      }, 1000);
    }
  }
}
</script>

<template>
<div class="title">Simulate Last Game</div>
  <game-board :game="game"></game-board>
  <div class="button-container">
    <button-component @click="simulate" :disabled="running">Simulate</button-component>
  </div>
</template>

<style scoped>
.title {
  font-size: 1.2rem;
  font-weight: 600;
  text-align: center;
  margin: 40px 0;
}

.button-container {
  display: flex;
  justify-content: center;
  margin-top: 40px;
}
</style>