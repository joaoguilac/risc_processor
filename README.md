# Processador RISC

Implementação de um processador RISC com pipeline para a disciplina de Organização de Computadores DIM0129 do curso Bacharelado em Tecnologia da Informação da Universidade Federal do Rio Grande do Norte período 2023.1.

Alunos:

-   Isaque Barbosa Martins (2020119856)
-   João Guilherme Lopes Alves da Costa (20200045609)

## Compilação

### Makefile
OBS: Não está funcionando corretamente

```
make FILE=NOME_DO_ARQUIVO EXECUTABLE=NOME_DO_EXECUTAVEL
```

### Manual

```bash
g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -o build/main src/main.cpp -lsystemc -lm
```

### Carregamento de dados

```bash
./build/main ../data/<algoritmo>.dat
```
São disponíveis alguns algoritmos na pasta data.

### Execução

Após a execução, será gerado um arquivo de onda após a compilação, para executá-lo basta rodar o comando:

```bash
gtkwave wave.vcd
```
