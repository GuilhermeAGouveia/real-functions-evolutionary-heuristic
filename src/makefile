

run:;
	rm -rf ./statistics/*.dat; \
	gcc -o evol evolution_simple.c ./libs/statistics.c ./libs/types.c ./libs/utils.c ./libs/funcoes_cec_2015/cec15_test_func.c ./libs/funcoes_cec_2015/ecr_iml.c ./libs/funcoes_cec_2015/evaluation_count_iml.c ./libs/funcoes_cec_2015/record_result_iml.c ./libs/funcoes_cec_2015/rp_iml.c -lm; \
	./evol; \

prepare:;
	chmod +x -R ./scripts/*; \

statistics: run; \

	./scripts/sh/gerar_todas_estatisticas.sh; \
