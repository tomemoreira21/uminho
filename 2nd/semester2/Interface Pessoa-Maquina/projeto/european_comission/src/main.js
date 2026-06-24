import { createApp } from 'vue'
import { createPinia } from 'pinia'
import router from './router'
import './style.css'
import App from './App.vue'

import PrimeVue from 'primevue/config'
import ToastService from 'primevue/toastservice'
import Aura from '@primevue/themes/aura'

createApp(App)
  .use(router)
  .use(createPinia())
  .use(PrimeVue, { theme: { preset: Aura } })
  .use(ToastService)
  .mount('#app')