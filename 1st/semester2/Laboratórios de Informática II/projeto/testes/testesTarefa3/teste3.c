#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>
#include "../../lib/func.h"
#include "../testesTarefa1/teste1.h"
#include "teste3.h"

void testa_existeCaminho () {
    Tabuleiro t1 = criaTabuleiroDeTeste(3, 3, 'a');
    Tabuleiro t2 = criaTabuleiroDeTeste(3, 3, '#');
    Tabuleiro t3 = criaTabuleiroDeTeste (2,2,'a');

    CU_ASSERT_EQUAL (existeCaminho(t1),1);

    t3->tabuleiro[1][1] = 'A';
    t3->tabuleiro[1][0] = '#';
    t3->tabuleiro[0][1] = 'A';
    CU_ASSERT_EQUAL (existeCaminho(t3),1);

    t1->tabuleiro[0][0] = 'A';
    t1->tabuleiro[1][0] = '#';
    CU_ASSERT_EQUAL (existeCaminho(t1),1);

    CU_ASSERT_EQUAL (existeCaminho(t2),0);

    liberaTabuleiro(t1);
    liberaTabuleiro(t2);
    liberaTabuleiro(t3);
}
