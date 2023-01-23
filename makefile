#include ./.env
image_name = traveling

#Deve ser executado na primeira interação com o projeto
run: ;
	@echo -e "\nBuild traveling image\n"; \
	docker build -t $(image_name) .; \
	echo -e "\nRunning traveling container\n"; \
	docker run -it --rm --name traveling-container traveling; \

