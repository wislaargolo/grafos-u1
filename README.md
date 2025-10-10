# Grafos-U1
Repositório contendo soluções para os exercícios da Unidade 1 do curso de Grafos.

## Compilação e Execução
Para compilar e executar os programas, siga os passos abaixo:

Compilar todos os arquivos .cpp
```bash
make
```

Compilar apenas um arquivo específico, por exemplo, q1.cpp
```bash
make tests/q1
```

Executar o programa desejado, por exemplo, para q1
```bash
./build/tests/q1
```

Limpar os arquivos compilados
```bash
make clean
```

Testar todos os programas de uma vez
```bash
# Torna o script executável, somente na primeira vez
chmod +x test-all.sh 
# Executa todos os testes, informa os resultados e exibe a saída dos que falharam
./test-all.sh 
# Executa todos os testes com saída detalhada de cada teste
./test-all.sh --verbose
# Executa todos os testes, mas só exibe a saída dos que falharam
./test-all.sh --verbose-fail
```
