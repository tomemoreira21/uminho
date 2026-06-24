/**
 * @file priority_queue.h
 * @brief Implementação de uma fila de prioridade genérica.
 *
 * Estrutura baseada em heap binária que suporta elementos genéricos (void*),
 * com prioridade definida por uma função de comparação. Pode ser usada tanto
 * como max-heap quanto min-heap, conforme a função de heapify escolhida.
 *
 */
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stddef.h>


/**
 * @brief Estrutura abstrata de uma fila de prioridade.
 *
 * Implementada internamente como uma heap binária.
 * Suporta elementos genéricos através de apontadores void*,
 * sendo a ordem definida por uma função de comparação.
 */
typedef struct priority_queue PriorityQueue;


/**
 * @brief Troca dois elementos genéricos.
 *
 * Função auxiliar usada na manutenção da heap.
 *
 * @param a Apontador para o primeiro elemento.
 * @param b Apontador para o segundo elemento.
 */
void pq_swap(void **a, void **b);


/**
 * @brief Reorganiza a heap de baixo para cima(max-heap).
 *
 * Usada após a inserção de um novo elemento para restaurar
 * a propriedade da heap.
 *
 * @param pq Apontador para a fila de prioridade.
 * @param index Índice inicial do elemento a ajustar.
 */
void pq_heapify_up(PriorityQueue *pq, int index);

/**
 * @brief Reorganiza a heap de baixo para cima (min-heap).
 *
 * Começa no índice fornecido e move o elemento para cima
 * até restaurar a propriedade da min-heap.
 *
 * Usada em filas de tipo "gasto" após inserir um elemento
 * quando ainda não atingiu a capacidade máxima.
 *
 * @param pq Apontador para a fila de prioridade.
 * @param index Índice inicial do elemento a ajustar.
 */
void pq_heapify_upMin(PriorityQueue *pq, int index);


/**
 * @brief Reorganiza a heap de cima para baixo(max-heap).
 *
 * Usada após a remoção do elemento de maior prioridade.
 *
 * @param pq Apontador para a fila de prioridade.
 * @param index Índice inicial do elemento a ajustar.
 */
void pq_heapify_down(PriorityQueue *pq, int index);


/**
 * @brief Reorganiza a heap de cima para baixo (min-heap).
 *
 * Começa no índice fornecido e move o elemento para baixo
 * até restaurar a propriedade da min-heap.
 *
 * Usada em filas específicas de tipo "gasto" para manter
 * o elemento de menor prioridade no topo.
 *
 * @param pq Apontador para a fila de prioridade.
 * @param index Índice inicial do elemento a ajustar.
 */
void pq_heapify_downMin(PriorityQueue *pq, int index);


/**
 * @brief Cria uma nova priority queue (max-heap).
 *
 * A função de comparação define a prioridade dos elementos.
 * Pode ainda ser fornecida uma função para libertação dos
 * elementos armazenados.
 *
 * @param compare Função de comparação entre dois elementos.
 * @param free_func Função para libertar cada elemento.
 * @return Apontador para a nova fila de prioridade.
 */
PriorityQueue *pq_new(int (*compare)(const void *, const void *), void (*free_func)(void *));

/**
 * @brief Cria uma fila de prioridade com capacidade inicial pequena,
 *        usada em situações específicas de "gasto" (min-heap).
 *
 * @param compare Função de comparação que define a prioridade.
 * @param free_func Função opcional para libertar os elementos.
 * @return Apontador para a nova fila de prioridade.
 */
PriorityQueue *pq_newGasto(int (*compare)(const void *, const void *), void (*free_func)(void *));

/**
 * @brief Liberta a fila de prioridade.
 *
 * Liberta a estrutura interna e, caso exista, invoca a função
 * de libertação sobre todos os elementos ainda presentes.
 *
 * @param pq Apontador para a fila de prioridade.
 */
void pq_free(PriorityQueue *pq);

/**
 * @brief Insere um elemento na fila de prioridade (max-heap).
 *
 * O elemento é colocado na posição correta de acordo com
 * a função de comparação.
 *
 * @param pq Apontador para a fila de prioridade.
 * @param element Apontador para o elemento a inserir.
 */
void pq_push(PriorityQueue *pq, void *element);

/**
 * @brief Insere um elemento numa fila de prioridade de tipo "gasto",
 *        removendo o elemento de menor prioridade se necessário (min-heap).
 *
 * @param pq Apontador para a fila de prioridade.
 * @param element Apontador para o elemento a inserir.
 */
void pq_pushGasto(PriorityQueue *pq, void *element);

/**
 * @brief Remove e devolve o elemento de maior prioridade.
 *
 * @param pq Apontador para a fila de prioridade.
 * @return Apontador para o elemento removido, ou NULL se vazia.
 */
void *pq_pop(PriorityQueue *pq);

/**
 * @brief Verifica se a fila de prioridade está vazia.
 *
 * @param pq Apontador para a fila de prioridade.
 * @return 1 se estiver vazia, 0 caso contrário.
 */
int pq_is_empty(const PriorityQueue *pq);

/**
 * @brief Obtém o número de elementos atualmente na fila.
 *
 * @param pq Apontador para a fila de prioridade.
 * @return Número de elementos.
 */
int get_pq_size (const PriorityQueue *pq);

/**
 * @brief Obtém o elemento no índice `i` da fila (sem remover).
 *
 * @param pq Apontador para a fila de prioridade.
 * @param i Índice do elemento.
 * @return Apontador para o elemento ou NULL se inválido.
 */
const void *get_pq_data (const PriorityQueue *pq, int i);

#endif