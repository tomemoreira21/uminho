#include <CUnit/Basic.h>         
#include <stdlib.h>               
#include <string.h>               
#include "testesTarefa1/teste1.h"
#include "testesTarefa2/teste2.h"
#include "testesTarefa3/teste3.h"
#include "testesTarefa4/teste4.h"
#include "testesTarefa5/teste5.h"
#include "testesExtra/teste6.h"

int main() {
    if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error(); 

    CU_basic_set_mode(CU_BRM_VERBOSE);
  
    CU_pSuite pSuite1 = NULL;
    CU_pSuite pSuite2 = NULL;
    CU_pSuite pSuite3 = NULL;
    CU_pSuite pSuite4 = NULL;
    CU_pSuite pSuite5 = NULL;
    CU_pSuite pSuite6 = NULL;

    pSuite1 = CU_add_suite("Suite_Tarefa1", 0,0);
    pSuite2 = CU_add_suite ("Suite_Tarefa2",0,0);
    pSuite3 = CU_add_suite ("Suite_Tarefa3",0,0);
    pSuite4 = CU_add_suite ("Suite_Tarefa4",0,0);
    pSuite5 = CU_add_suite ("Suite_Tarefa5",0,0);
    pSuite6 = CU_add_suite ("Suite_Extra",0,0);

    if (NULL == pSuite1) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == pSuite2) {
      CU_cleanup_registry();
      return CU_get_error();
    }
    
    if (NULL == pSuite3) {
      CU_cleanup_registry();
      return CU_get_error();
    }
    
    if (NULL == pSuite4) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == pSuite5) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == pSuite6) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_leLinha", testa_leLinha)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_leLinha", testa_leLinha)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_devolveJogada", testa_devolveJogada)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_gravarJogo", testa_gravarJogo)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_ClearFicheiro", testa_ClearFicheiro)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_coordValido", testa_coordValida)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_comandoRBValido", testa_comandoRBValido)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_inicializaJogo", testa_inicializaJogo)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_inicializaStack", testa_inicializaStack)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_comandoB", testa_comandoB)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_comandoR", testa_comandoR)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_comandoG", testa_comandoG)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_comandoL", testa_comandoL)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_pushJogada", testa_pushJogada)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_addMaiuscula", testa_addMaiuscula)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_addRiscar", testa_addRiscar)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_liberaTabuleiro", testa_liberaTabuleiro)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_liberaJogadas", testa_liberaJogadas)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite1, "testa_liberaStack", testa_liberaStack)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite2, "testa_verificaSemConflitos", testa_verificaSemConflitos)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite2, "testa_verificaConflitos1", testa_verificaConflitos1)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite2, "testa_verificaConflitos2", testa_verificaConflitos2)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite2, "testa_verificaConflitos3", testa_verificaConflitos3)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite2, "testa_verificaConflitos4", testa_verificaConflitos4)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite2, "testa_insereOrdenado", testa_insereOrdenado)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite2, "testa_verificaRiscadas", testa_verificarRiscadas)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite2, "testa_verificaVizinhosBrancos", testa_verificarVizinhosBrancos)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite2, "testa_verificaRepetições", testa_verificarRepeticoes)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite2, "testa_verificaFaltaRiscar", testa_verificarFaltaRiscar)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite2, "testa_liberaLista", testa_liberaLista)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite2, "testa_undoStack", testa_undoStack)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite2, "testa_comandoD", testa_comandoD)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite3, "testa_existeCaminho", testa_existeCaminho)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_ajudaUilizador1", testa_ajudaUtilizador1)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_ajudaUilizador2", testa_ajudaUtilizador2)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_ajudaUilizador3", testa_ajudaUtilizador3)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_devolveJogadaAjuda", testa_devolveJogadaAjuda)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_permiteRiscar", testa_permiteRiscar)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_ajudaIsolarNaoBranco", testa_ajudaIsolarNaoBranco)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_ajudaPintarVizinhosNaoBranco", testa_ajudaPintarVizinhosNaoBranco)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_addBrancoRiscar", testa_addBrancoRiscar)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_ajudaRiscarDuplicadosLinhaColuna", testa_ajudaRiscarDuplicadosLinhaColuna)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_ajudaRiscarLinhaColuna", testa_ajudaRiscarLinhaColuna)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_ajudaRiscarDuplicadosColuna", testa_ajudaRiscarDuplicadosColuna)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_ajudaRiscarColuna", testa_ajudaRiscarColuna)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_ajudaRiscarDuplicadosLinha", testa_ajudaRiscarDuplicadosLinha)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_ajudaRiscarLinha", testa_ajudaRiscarLinha)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_comandoA1", testa_comandoA1)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite4, "testa_comandoA2", testa_comandoA2)) {
      CU_cleanup_registry();
      return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite5, "testa_jogoResolvido", testa_jogoResolvido)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_copiaJogada", testa_copiaJogada)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_letraRepeteNaLinhaOuColuna", testa_letraRepeteNaLinhaOuColuna)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_backTrack", testa_backTrack)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_desfazStack", testa_desfazStack)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_resolveJogo1", testa_resolveJogo1)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_resolveJogo2", testa_resolveJogo2)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_resolveJogo3", testa_resolveJogo3)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_resolveJogo4", testa_resolveJogo4)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_resolveJogoEstadoInvalido1", testa_resolveJogoEstadoInvalido1)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_resolveJogoEstadoInvalido2", testa_resolveJogoEstadoInvalido2)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_possuiConflitos1", testa_possuiConflitos1)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_possuiConflitos2", testa_possuiConflitos2)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_possuiConflitos3", testa_possuiConflitos3)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_pintarMaisPropagacao", testa_pintarMaisPropagacao)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_riscarMaisPropagacao", testa_riscarMaisPropagacao)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_recuperaTabuleiroInicial", testa_recuperaTabuleiroInicial)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_copiaTabuleiro", testa_copiaTabuleiro)) {
      CU_cleanup_registry();
      return CU_get_error();
    }


    if (NULL == CU_add_test(pSuite5, "testa_contaMin1", testa_contaMin1)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_contaMin2", testa_contaMin2)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_verificaEstadoJogo1", testa_verificaEstadoJogo1)) {
      CU_cleanup_registry();
      return CU_get_error();
    }
      
    if (NULL == CU_add_test(pSuite5, "testa_verificaEstadoJogo2", testa_verificaEstadoJogo2)) {
      CU_cleanup_registry();
      return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite5, "testa_verificaEstadoJogo3", testa_verificaEstadoJogo3)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_verificaVitoria1", testa_verificaVitoria1)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_verificaVitoria2", testa_verificaVitoria2)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite5, "testa_verificaVitoria3", testa_verificaVitoria3)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite6, "testa_gravaStack", testa_gravaStack)) {
      CU_cleanup_registry();
      return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite6, "testa_restauraStack1", testa_restauraStack1)) {
      CU_cleanup_registry();
      return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite6, "testa_restauraStack2", testa_restauraStack2)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    return CU_get_error();
  }