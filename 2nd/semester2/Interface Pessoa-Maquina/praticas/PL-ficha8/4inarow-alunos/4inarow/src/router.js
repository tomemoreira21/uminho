import { createRouter, createWebHistory } from 'vue-router';
import GamePage from './pages/GamePage.vue';
import StatisticsPage from './pages/StatisticsPage.vue';
import SimulationPage from './pages/SimulationPage.vue';
import NotFoundPage from './pages/NotFoundPage.vue';
import GameResultPage from './pages/GameResultPage.vue';


const routes = [
  {path: '/', redirect: '/game'}, // força a rota
  {path: '/game', component: GamePage},
  {path: '/game/:id', component: GameResultPage, props:true},
  {path: '/statistics', component: StatisticsPage},
  {path: '/simulation', component: SimulationPage},
  {path: '/:rotaDesconhecida(.*)*', component: NotFoundPage}
]

// . -> qualquer caractere, * -> um ou mais caracteres

const router = createRouter({
  history: createWebHistory(),
  routes
});

export default router;