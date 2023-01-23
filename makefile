#include ./.env
image_name = real-functions-heuristic

#Deve ser executado na primeira interação com o projeto
run: ;
	@echo -e "\nBuild $(image_name) image\n"; \
	docker build -t $(image_name) .; \
	echo -e "\nRunning $(image_name) container\n"; \
	docker run -it --rm --name $(image_name)-container $(image_name); \

