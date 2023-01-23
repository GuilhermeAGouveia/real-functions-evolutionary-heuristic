FROM gcc:4.9
COPY src /home/project
VOLUME /home
WORKDIR /home/project
RUN gcc -std=c99 evolucao_simples.c -o evolucao_simples
CMD ["./evolucao_simples"]