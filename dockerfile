FROM guilhermegouveia/inicient-env
COPY src /home/project
VOLUME /home
WORKDIR /home/project