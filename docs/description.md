# Trabalho da disciplina DIM0129 - ORGANIZAÇÃO DE COMPUTADORES

## 1- Descrição do Trabalho:

Implementar a arquitetura para um conjunto de instruções (ISA, Instruction-Set Architecture) composta por Parte de Controle e Parte Operativa, compatíveis com a filosofia RISC (Reduced Instruction-Set Computer) e que executam em “Pipeline” o seguinte conjunto de instruções:

**Lógicas e Aritméticas**
- [x] AND —> operação booleana AND
- [x] OR —> operação booleana OR
- [x] XOR —> operação booleana XOR
- [x] NOT —> operação booleana NOT
- [ ] CMP —> comparação
- [x] ADD —> soma
- [x] SUB —> subtração

**Memória**
- [x] LD —> leitura em memória (memória -> registradores)
- [x] ST —> armazenamento em memória (registradores -> memória)

**Jumps**
- [ ] J —> salto incondicional
- [ ] JN —> salto condicional; salta se (N)egativo
- [ ] JZ —> salto condicional; salta se (Z)ero


O pipeline pode ser implementado com 4 ou 5 estágios.

## 2- Decisões de projeto:

    2.1- o tamanho da palavra do processador;

    2.2- o formato da palavra de instrução;

    2.3- os modos de endereçamento de operandos;

    2.4- o tamanho do banco de registradores;

    2.5- o tamanho das memórias de instruções e de dados;

    2.6- o número e tipos de barramentos (ou canais dedicados) da parte operativa; e

    2.7- a organização do pipeline.

## 3- O trabalho:

    3.1- Implementação do modelo da arquitetura em linguagem para descrição de hardware (VHDL ou SystemC);

    3.2- Resultados de simulações da execução de instruções de pelo menos 3 algoritmos na arquitetura. Os resultados podem ser apresentados em diagramas de forma de onda e/ou textual. Esses resultados serão colocados no relatório e apresentados em sala de aula;

    3.3- Relatório explicando e exemplificando a implementação da arquitetura e justificando as decisões de projeto acima elencadas (seção 2). O relatório deve conter pelo menos:

    	3.3.1- os diagramas de bloco da parte de controle;

    	3.3.2- os diagramas de bloco da parte operativa; e

        3.3.3- análises de desempenho (ciclos de relógio necessários à execução das instruções) em função dos comportamentos do pipeline. Entende-se por comportamentos do pipeline, os tratamentos implementados para as dependências de dados e de controle;

## 4- Apresentação

Ocorrerá nos dias 08 e 10/05 em sala de aula, exemplificando o funcionando do modelo de processador implementado. A apresentação deve mostrar:

    4.1 - os diagramas de bloco da organização do processador, os quais foram projetados de acordo com as decisões de projeto (seção 2) e o número de estágios do Pipeline; e

    4.2 - resultados de simulação (telas ou demonstração).

## 5- Entrega

Dia 07/05/22 via tarefa SIGAA.

O trabalho pode ser feito individualmente ou em duplas.
