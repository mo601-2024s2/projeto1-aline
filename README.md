# Projeto 1 de MO601 - Simulador RISC-V

## Identificação do Grupo

- RA: 291695
- Nome: Aline Santana Cordeiro

## Descrição Geral do Projeto

Desenvolvimento de um simulador RISC-V RV32IM, o qual inclui instruções básicas e multiplicação e divisão.


## Descrição do ambiente de desenvolvimento

- Instalação do cross-compiler para RISC-V 32b: https://github.com/stnolting/riscv-gcc-prebuilt
- Configuração do ambiente para uso direto do cross-compiler
- Diretório do projeto contendo as seguintes informações:
    - **projeto1:**
        - **tests:** contém os benchmarks para testes do simulador. O `Makefile` do benchmark ACStone foi modificado para execução dos testes.
        - **processador:** contém os arquivos source e header de desenvolvimento do simulador.
        - **resultados:** contém os arquivos de saída com o log de execução de cada aplicação.
        - **script.sh:** script responsável por compilar o benchmark ACStone e o simulador, por fazer o disassembly dos arquivos do benchmark e por executar o simulador com cada arquivo disassembly do benchmark em questão. Basta executar `./script.sh`. Quanto aos status de compilação do benchmark, ele vai dar erro nos benchmarks de ponto flutuante, mas compila corretamente os demais e quanto à execução do simulador, ele vai gerar inúmeros erros, mas os arquivos de log serão gerados no diretório `Resultados`.


## Descrição do algoritmo de simulação

O simulador lê o arquivo *.disasm, seleciona apenas o trecho do assembly que contém as seções _start, main e funções principais usadas pelo código. Na sequência, é feito um parse desse trecho de assembly de forma que cada instrução é armazenada individualmente em uma hash table. Essa hash table é indexada pelo PC e contém demais informações sobre mnemônicos e registradores. Na execução, avalia-se qual a instrução atrelada ao primeiro endereço do PC e executa-se as operações correspondentes. O log de cada instrução é feito logo na sequência de cada instrução executada.


### Parser

Responsável por ler os arquivos de entrada e popular as instruções conforme o tipo de instrução. Seu funcionamento é relativamente simples, dando-se pela leitura de cada linha do arquivo, gerando uma nova struct `instrInfo` e inserindo-a no banco de instruções, com o PC da instrução como chave. Essa struct contém todos os registradores existentes nos 3 tipos de instrução:
- rd
- rs1
- rs2
- imediato
- instrução
- mnemônico
- pc

Para cada instrução, todas essas informações são salvas como string e os registradores listados no código assembly são associados com os registradores da struct de acordo com o tipo de operação. Se o registrador não é usado, ele recebe uma string vazia. Nas funções de parse também é feita a correção das pseudo instruções para instruções equivalentes e existentes na arquitetura RISC-V RV32IM. As classes responsáveis pelo parse são as classes `FetchStage` e `decodeInstruction`, respectivamente nos arquivos `fetch.*` e `decode.*`.


### Banco de instruções

Esta estrutura é responsável por armazenar todas as instruções do programa. Foi implementada utilizando um `map` com a chave representando o PC da instrução e os registradores, endereço da instrução e mnemônico.

```cpp
        struct instrInfo {
            std::string pc;
            std::string instr;
            std::string rd;
            std::string rs1;
            std::string rs2;
            std::string imm;
            std::string mnemonic;    
        };

        std::map<uint32_t, instrInfo> instr_info;
```

A utilização de um `map` se dá não apenas pelo desempenho, pois o acesso aos valores é em tempo constante, mas também pela facilidade de utilização durante o desenvolvimento. Como o acesso do processador depende do valor do `PC` e como não se pode garantir que esse acesso será sempre sequencial, a estrutura pareceu uma boa opção, dado que o acesso é direto e depende apenas de descobrir o próximo valor do `PC`.

Apesar da struct `instrInfo` conter todos os campos necessários para todos os tipos de instruções, eles são inicializados conforme o tipo de instrução e sempre como string. Por exemplo, a instrução `add t0, t1, t2` utilizará as propriedades `rd`, `rs1` e `rs2`, enquanto a instrução `mv s0, s1` utilizará as propriedades `rd` e `rs1`. Esse banco de instruções acaba sendo usado para o Log das instruções, dado que ele permite armazenar a instrução assembly real referente ao processador do RISC-V.


### Banco de registradores

Implementado como um `map`, onde a chave representa o nome do registrador como uma string e o valor do `map` é o valor do registrador. Por exemplo, ainda considerando a instrução `add t0, t1, t2`, a chave do `map` se torna `rd`, dado que, durante o parse, para a instrução de `add`, o registrador `t0` foi mapeado para o registrador `rd`. Da mesma forma é feito com os registradores `t1` e `t2`, mapeados respectivamente em `rs1` e `rs2`, porém, nesse caso em específico, apenas buscados do `map` como `map[rd] = map[rs1] + map[rs2]`.


### Execução

Responsável por toda a lógica de execução do programa. Lê o primeiro `PC` da estrutura de `map`, verifica qual operação é executada, opera os registradores de acordo com a instrução e altera o `PC` da forma adequada (se for um salto, para o endereço do salto, caso contrário, `PC + 4`). Para cada tipo de instrução existe uma condicional, logo, foi escrita uma longa lista de condicionais dentro de um laço infinito. Quando a operação ebreak é executada, o programa é finalizado corretamete. Se existir alguma instrução desconhecida na lista de instruções, a execução finaliza. 


## Descrição de como o projeto foi testado

O projeto não foi testado amplamente e/ou comparado com o simulador `Spike`. O projeto foi testado apenas na questão de retornos e saltos do tipo `jal`. Os demais não foram verificados por falta de tempo hábil e a execução entra em loop infinito no teste 121.

## Considerações gerais sobre aprendizado no projeto

A implementação do simulador trouxe uma visão bastante rica sobre os passos usados pelo processador, memória e sistema operacional para a execução de instruções e, obviamente, uma série de dúvidas sobre como as coisas realmente devem acontecer e em que ordem. Nos força a observar os detalhes relacionados aos passos de execução que são muitos. Durante a implementação você começa a perceber que existem N coisas que poderiam ser implementadas de forma diferente no código, por exemplo, as estruturas de dados, as quais acabaram dificultando um pouco na criação do log.

De forma geral, achei o trabalho bastante interessante e me sente engajada no desenvolvimento dele, contudo, não tive tempo hábil para implementar e testar em detalhes todos os passos e todos os casos. Abaixo, segue uma lista de tarefas que faltam no desenvolvimento deste trabalho:

- Avaliar se todas as instruções estão recebendo e retornando os valores corretos.
- Fazer testes para validar a execução de todos os casos do benchmark ACStone.
- Avaliar o simulador com os demais benchmarks.
- Avaliar os resultados do simulador em comparação com o Spike.
- Imprimir o log exatamente da forma como foi pedido. Não compreendi muito bem a parte de mostrar os bits equivalentes aos registradores do endereço após a execução. Não entendi de que endereço se trata, talvez precise mudar toda a minha estrutura de dados para conseguir fazer isso funcionar da forma correta e esperada.
- O uso de uma estrutura simulando a memória e a contagem de ciclos para cada instrução. Criei uma estrutura de memória e usei nas instruções de sw e lw, porém não tenho certeza se era isso que era o esperado.


## Desempenho do simulador conforme DryStone e CoreMark

Os testes com DryStone e CoreMark não foram executados.


## Referências

- https://pages.hmc.edu/harris/ddca/ddcarv/DDCArv_AppB_Harris.pdf
- https://www.advania.co.uk/insights/blog/intro-to-basic-disassembly-reverse-engineering/
- https://www.ic.unicamp.br/~rodolfo/mc404/
- https://riscv.org/wp-content/uploads/2019/06/riscv-spec.pdf
- https://lists.riscv.org/g/tech-code-size/topic/whether_zcb_should_imply_zbb/93139131
