<template>
  <Teleport to="body">
    <div
      class="overlay"
      role="dialog"
      aria-modal="true"
      :aria-labelledby="'modal-titulo-' + medida.medida"
      @click.self="emit('fechar')"
      @keydown.escape="emit('fechar')"
    >
      <div class="modal" ref="modalRef">

        <template v-if="vistaHistorico">
          <div class="modal-header">
            <span :id="'modal-titulo-' + medida.medida" class="modal-titulo">{{ medida.medida }}</span>
            <button class="btn-fechar" @click="emit('fechar')" aria-label="Fechar modal">✕</button>
          </div>
          <div class="modal-body">
            <div class="historico-header">
              <h3 class="hist-titulo">Histórico de revisões</h3>
              <BotaoExportar
                :dados="detalhes.historico"
                :nome-ficheiro="`historico-${medida.medida}`"
              />
              <button class="btn-voltar" @click="vistaHistorico = false" aria-label="Voltar ao detalhe da medida">◀ Voltar</button>
            </div>
            <ol class="timeline" aria-label="Histórico de revisões">
              <li v-for="(item, i) in detalhes.historico" :key="i" class="timeline-item">
                <div class="timeline-dot" aria-hidden="true"></div>
                <div class="timeline-conteudo">
                  <div class="timeline-data">{{ item.data }} — <strong>{{ item.tipo }}</strong></div>
                  <div class="timeline-secao"><span class="timeline-label">Descrição:</span> {{ item.descricao }}</div>
                  <div v-if="item.justificacao" class="timeline-secao"><span class="timeline-label">Justificação:</span> {{ item.justificacao }}</div>
                  <div v-if="item.impacto" class="timeline-secao"><span class="timeline-label">Impacto:</span> {{ item.impacto }}</div>
                </div>
              </li>
            </ol>
          </div>
        </template>

        <template v-else>
          <div class="modal-header">
            <span :id="'modal-titulo-' + medida.medida" class="modal-titulo">{{ medida.medida }}</span>
            <button class="btn-fechar" @click="emit('fechar')" aria-label="Fechar modal">✕</button>
          </div>
          <div class="modal-body">
            <div class="meta-row">
              <span class="badge-tipo" :class="medida.tipo === 'Investimento' ? 'badge-investimento' : 'badge-reforma'">
                {{ medida.tipo }}
              </span>
              <span class="badge-pais">{{ medida.bandeira }} {{ medida.pais }}</span>
            </div>

            <section class="secao" aria-label="Progresso de implementação">
              <h3 class="secao-label">Progresso de implementação</h3>
              <div class="progresso-row">
                <span class="badge-estado" :class="classeEstado(medida.estado)">{{ medida.estado }}</span>
                <span class="progresso-pct" :aria-label="`${medida.progresso} por cento`">{{ medida.progresso }}%</span>
              </div>
              <div class="barra-bg" role="progressbar" :aria-valuenow="medida.progresso" aria-valuemin="0" aria-valuemax="100" :aria-label="`Progresso: ${medida.progresso}%`">
                <div class="barra-fill" :style="{ width: medida.progresso + '%' }"></div>
              </div>
            </section>

            <section class="secao" aria-label="Pilares associados">
              <h3 class="secao-label">Pilares</h3>
              <ul class="pilares-lista">
                <li v-for="(p, i) in detalhes.pilares" :key="i" class="pilar-chip"
                  :style="{ backgroundColor: p.cor + '22', color: p.cor, borderColor: p.cor }">
                  <span class="pilar-dot" aria-hidden="true" :style="{ backgroundColor: p.cor }"></span>
                  {{ p.label }}
                </li>
              </ul>
            </section>

            <section class="secao" aria-label="Histórico de revisões resumido">
              <div class="hist-resumo-header">
                <h3 class="secao-label">Histórico de revisões</h3>
                <div class="hist-resumo-btns">
                  <button class="btn-ver-hist" @click="vistaHistorico = true" aria-label="Ver histórico completo de revisões">Ver histórico completo</button>
                  <BotaoExportar
                    :dados="detalhes.historico"
                    :nome-ficheiro="`historico-${medida.medida}`"
                  />
                </div>
              </div>
              <ol class="timeline timeline--resumo" aria-label="Últimas 3 revisões">
                <li v-for="(item, i) in detalhes.historico.slice(0, 3)" :key="i" class="timeline-item">
                  <div class="timeline-dot" aria-hidden="true"></div>
                  <div class="timeline-conteudo">
                    <div class="timeline-data">{{ item.data }}</div>
                    <div class="timeline-desc">{{ item.descricao.slice(0, 60) }}...</div>
                  </div>
                </li>
              </ol>
            </section>
          </div>
        </template>
      </div>
    </div>
  </Teleport>
</template>

<script setup>
import { ref, onMounted, onUnmounted } from 'vue'
import BotaoExportar from './BotaoExportar.vue'

const props = defineProps({
  medida:   { type: Object, required: true },
  detalhes: { type: Object, required: true },
})

const emit = defineEmits(['fechar'])
const vistaHistorico = ref(false)
const modalRef = ref(null)

onMounted(() => {
  modalRef.value?.querySelector('button')?.focus()
})

function classeEstado(estado) {
  if (estado === 'Atrasado')        return 'estado-atrasado'
  if (estado === 'Em risco')        return 'estado-risco'
  if (estado === 'Dentro do Prazo') return 'estado-ok'
  return ''
}
</script>

<style scoped>
.overlay {
  position: fixed;
  inset: 0;
  background: rgba(0, 0, 0, 0.45);
  z-index: 1000;
  display: flex;
  align-items: center;
  justify-content: center;
}

.modal {
  background: white;
  border-radius: 12px;
  width: 560px;
  max-width: 95vw;
  max-height: 88vh;
  display: flex;
  flex-direction: column;
  overflow: hidden;
  box-shadow: 0 8px 32px rgba(0,0,0,0.18);
}

.modal-header {
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 1rem 1.25rem;
  background-color: var(--cor-azul-primario);
  gap: 1rem;
}

.modal-titulo {
  color: white;
  font-size: 0.9rem;
  font-weight: 700;
  font-family: monospace;
  flex: 1;
  line-height: 1.4;
}

.btn-fechar {
  background: none;
  border: none;
  color: white;
  font-size: 1.1rem;
  cursor: pointer;
  flex-shrink: 0;
  opacity: 0.8;
}

.btn-fechar:hover { opacity: 1; }

.modal-body {
  padding: 1.25rem;
  overflow-y: auto;
  display: flex;
  flex-direction: column;
  gap: 1.1rem;
}

.meta-row {
  display: flex;
  gap: 0.75rem;
  align-items: center;
}

.badge-tipo {
  display: inline-block;
  padding: 0.28rem 1rem;
  border-radius: 5px;
  font-size: 0.78rem;
  font-weight: 500;
}

.badge-reforma     { border: 1px solid var(--cor-border); color: var(--cor-texto); background: white; }
.badge-investimento { background-color: var(--cor-azul-primario); color: white; }

.badge-pais {
  font-size: 0.85rem;
  font-weight: 600;
  color: var(--cor-texto);
}

.secao { display: flex; flex-direction: column; gap: 0.5rem; }
.secao-label {
  font-size: 0.75rem;
  font-weight: 700;
  text-transform: uppercase;
  letter-spacing: 0.05em;
  color: var(--cor-azul-primario);
}

.progresso-row { display: flex; align-items: center; gap: 0.75rem; }
.progresso-pct  { font-size: 0.8rem; font-weight: 700; margin-left: auto; }

.barra-bg   { width: 100%; height: 6px; background: #dde3ef; border-radius: 3px; overflow: hidden; }
.barra-fill { height: 100%; background: var(--cor-azul-primario); border-radius: 3px; }

.badge-estado {
  display: inline-block;
  padding: 0.2rem 0.65rem;
  border-radius: 20px;
  font-size: 0.72rem;
  font-weight: 500;
}

.estado-atrasado { background: #fde8e8; color: #c0392b; }
.estado-risco    { background: #fef3cd; color: #9a6800; }
.estado-ok       { background: #e0f3e8; color: #1e7e45; }

.pilares-lista { 
  display: flex;
  gap: 0.5rem;
  flex-wrap: wrap; 
}

.pilar-chip {
  display: inline-flex;
  align-items: center;
  gap: 0.4rem;
  padding: 0.3rem 0.75rem;
  border-radius: 20px;
  border: 1px solid;
  font-size: 0.78rem;
  font-weight: 500;
}

.pilar-dot {
  width: 10px;
  height: 10px;
  border-radius: 50%;
  flex-shrink: 0;
}

.hist-resumo-header {
  display: flex;
  align-items: center;
  justify-content: space-between;
  flex-wrap: wrap;
  gap: 0.5rem;
}

.hist-resumo-btns { display: flex; gap: 0.5rem; }

.btn-ver-hist {
  font-size: 0.75rem;
  font-weight: 600;
  padding: 0.3rem 0.75rem;
  border-radius: 6px;
  cursor: pointer;
  border: 1px solid var(--cor-azul-primario);
  color: var(--cor-azul-primario);
  background: white;
  font-family: var(--font-principal);
}

.btn-ver-hist:hover { background: var(--cor-azul-selecao); }

.timeline {
  display: flex;
  flex-direction: column;
  gap: 0;
  padding-left: 0.5rem;
  border-left: 2px solid var(--cor-border);
  margin-left: 0.5rem;
  list-style: none;
}

.timeline-item {
  position: relative;
  padding: 0.6rem 0 0.6rem 1.25rem;
}

.timeline-dot {
  position: relative;
  left: -33px;
  top: 0.85rem;
  width: 8px;
  height: 8px;
  border-radius: 50%;
  background: var(--cor-azul-primario);
  border: 2px solid white;
  box-shadow: 0 0 0 2px var(--cor-azul-primario);
}

.timeline-data {
  font-size: 0.75rem;
  font-weight: 700;
  color: var(--cor-azul-primario);
  margin-bottom: 0.2rem;
}

.timeline-secao {
  font-size: 0.78rem;
  color: var(--cor-texto);
  line-height: 1.5;
  margin-bottom: 0.2rem;
}

.timeline-label { font-weight: 700; }

.timeline-desc {
  font-size: 0.78rem;
  color: var(--cor-texto);
  opacity: 0.75;
}

.historico-header {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  flex-wrap: wrap;
  margin-bottom: 0.5rem;
}

.hist-titulo {
  font-size: 0.9rem;
  font-weight: 700;
  color: var(--cor-azul-primario);
  margin: 0;
  flex: 1;
}

.btn-voltar {
  font-size: 0.75rem;
  font-weight: 600;
  padding: 0.3rem 0.75rem;
  border-radius: 6px;
  cursor: pointer;
  border: 1px solid var(--cor-border);
  color: var(--cor-texto);
  background: white;
  font-family: var(--font-principal);
  margin-left: auto;
}

.btn-voltar:hover { background: var(--cor-azul-selecao); }
</style>