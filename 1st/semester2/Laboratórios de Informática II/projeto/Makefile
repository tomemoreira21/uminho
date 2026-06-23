CC = gcc

CFLAGST = -Wall -Wextra -pedantic -O1 -fsanitize=address -fprofile-arcs -ftest-coverage -fno-omit-frame-pointer -fprofile-abs-path -g
CFLAGSJ = -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g

CUNIT_FLAGS = -lcunit

SRCT = testes/main.c testes/testesTarefa1/teste1.c testes/testesTarefa2/teste2.c testes/testesTarefa3/teste3.c testes/testesTarefa4/teste4.c testes/testesTarefa5/teste5.c testes/testesExtra/teste6.c 
SRCJ = lib/libTarefa1/func1.c lib/libTarefa2/func2.c lib/libTarefa3/func3.c lib/libTarefa4/func4.c lib/libTarefa5/func5.c lib/libExtra/func6.c 

test: $(SRCT) $(SRCJ) lib/func.h
	$(CC) $(CFLAGST) $(CUNIT_FLAGS) -o teste $(SRCT) $(SRCJ)

testar: test
	./teste
	@mv teste-func1.gcno func1.gcno 2>/dev/null || true && mv teste-func1.gcda func1.gcda 2>/dev/null || true && \
	gcov -o . lib/libTarefa1/func1.c | grep -v '/usr/include' | grep -v 'stdio.h' | grep -v 'stdio2.h'

	@mv teste-func2.gcno func2.gcno 2>/dev/null || true && mv teste-func2.gcda func2.gcda 2>/dev/null || true && \
	gcov -o . lib/libTarefa2/func2.c | grep -v '/usr/include' | grep -v 'stdio.h' | grep -v 'stdio2.h'

	@mv teste-func3.gcno func3.gcno 2>/dev/null || true && mv teste-func3.gcda func3.gcda 2>/dev/null || true && \
	gcov -o . lib/libTarefa3/func3.c | grep -v '/usr/include' | grep -v 'stdio.h' | grep -v 'stdio2.h'

	@mv teste-func4.gcno func4.gcno 2>/dev/null || true && mv teste-func4.gcda func4.gcda 2>/dev/null || true && \
	gcov -o . lib/libTarefa4/func4.c | grep -v '/usr/include' | grep -v 'stdio.h' | grep -v 'stdio2.h'

	@mv teste-func5.gcno func5.gcno 2>/dev/null || true && mv teste-func5.gcda func5.gcda 2>/dev/null || true && \
	gcov -o . lib/libTarefa5/func5.c | grep -v '/usr/include' | grep -v 'stdio.h' | grep -v 'stdio2.h'

	@mv teste-func6.gcno func6.gcno 2>/dev/null || true && mv teste-func6.gcda func6.gcda 2>/dev/null || true && \
	gcov -o . lib/libExtra/func6.c | grep -v '/usr/include' | grep -v 'stdio.h' | grep -v 'stdio2.h'

jogo: lib/main.c $(SRCJ) lib/repl.c lib/interface.c lib/func.h
	$(CC) $(CFLAGSJ) -o jogo lib/main.c $(SRCJ) lib/repl.c lib/interface.c

clean:
	rm -f teste *.gcno *.gcda *.gcov