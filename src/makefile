

run:;
	gcc -o evol evolution_simple.c statistics.c types.c utils.c ./funcoes_cec_2015/cec15_test_func.c ./funcoes_cec_2015/ecr_iml.c ./funcoes_cec_2015/evaluation_count_iml.c ./funcoes_cec_2015/record_result_iml.c ./funcoes_cec_2015/rp_iml.c -lm; \
	./evol; \

prepare:;
	chmod +x -R ./scripts/*; \

statistics:; \
	./scripts/sh/gerar_todas_estatisticas.sh; \
