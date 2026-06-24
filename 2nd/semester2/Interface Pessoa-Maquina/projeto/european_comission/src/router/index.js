import { createRouter, createWebHistory } from 'vue-router'

import HomeView from '../views/HomeView.vue'
import PaisesView from '../views/PaisesView.vue'
import PilaresView from '../views/PilaresView.vue'
import PilarDetalheView  from '../views/PilarDetalheView.vue'
import IndicadoresView from '../views/IndicadoresView.vue'
import MarcosMetasView from '../views/MarcosMetasView.vue'
import DesembolsosView from '../views/DesembolsosView.vue'
import PaisDetalheView   from '../views/PaisDetalheView.vue'
import NotFoundView from '../views/NotFoundView.vue'

const routes = [
  { path: '/',             component: HomeView },
  { path: '/paises',       component: PaisesView },
  { path: '/paises/:id',    component: PaisDetalheView },
  { path: '/pilares',      component: PilaresView },
  { path: '/pilares/:id',  component: PilarDetalheView },
  { path: '/indicadores',  component: IndicadoresView },
  { path: '/marcos-metas', component: MarcosMetasView },
  { path: '/desembolsos',  component: DesembolsosView },
  { path: '/:pathMatch(.*)*', component: NotFoundView }
]

export default createRouter({
  history: createWebHistory(),
  routes,
})