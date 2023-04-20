# Organização de Computadores

Implementação de um processador com pipeline para a disciplina de Organização de Computadores DIM0129 (2023.1).

Alunos: 
- Isaque Barbosa Martins (2020119856)
- João Guilherme Lopes Alves da Costa (20200045609)

## Compilação

### Makefile
```
make FILE=NOME_DO_ARQUIVO EXECUTABLE=NOME_DO_EXECUTAVEL
```

### Manual

```bash
g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl -rpath=$SYSTEMC_HOME/lib-linux64 -o ../build/<arquivo> <arquivo>.cpp -lsystemc -lm
```

### Execução

Após a execução, será gerado um arquivo de onda após a compilação, para executá-lo basta rodar o comando:

```bash
gtkwave wave.vcd
```
