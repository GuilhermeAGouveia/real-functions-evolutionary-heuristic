FROM gcc:4.9
COPY src /home/project
VOLUME /home
WORKDIR /home/project
RUN gcc -std=c99 traveling.c -o traveling
CMD ["./traveling"]