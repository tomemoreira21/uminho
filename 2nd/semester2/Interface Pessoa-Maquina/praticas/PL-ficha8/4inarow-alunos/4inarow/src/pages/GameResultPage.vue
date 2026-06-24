<script>
import { Game } from "../models/game.js";

export default {
  props: ['id'],
  data() {
    return {
      game: new Game()
    };
  },
  methods: {
    async getGame() {
      fetch('http://localhost:3000/games/' + this.id)
        .then(response => {
          if (!response.ok) {
            throw new Error('Not Found!')
          }


          return response.json();
        })

        .then(data => {
            this.game.board = data.game.board;
            this.game.winner = data.game.winner;
            this.game.player = data.game.player;
            this.game.isOver = data.game.isOver;
        })

        .catch(error => {
           console.log(error);
        })
    }
  },
  created() {
    this.getGame();
  }
}
</script>

<template>
  <game-board :game="game"></game-board>
</template>