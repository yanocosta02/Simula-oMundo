# 📢 Simulação de Mundo - Propagação de Rumores

## 📋 Visão Geral
Simulação de um mundo virtual onde 100 pessoas se movem entre 8 locais diferentes e compartilham 30 rumores únicos. O projeto implementa estruturas de dados avançadas em C para modelar as interações sociais baseadas em características individuais como extroversão, paciência e idade.

## 🏗️ Estrutura do Projeto
```
simulacao-mundo/
├── libconjunto.c   # Implementação do TAD Conjunto
├── libconjunto.h   # Interface do TAD Conjunto
├── libfila.c       # Implementação do TAD Fila
├── libfila.h       # Interface do TAD Fila
├── liblef.c        # Implementação do TAD LEF
├── liblef.h        # Interface do TAD LEF
├── libmundo.c      # Implementação da lógica do mundo
├── libmundo.h      # Definições de estruturas do mundo
└── mundo.c         # Programa principal da simulação
```

## 🚀 Como Executar

### Pré-requisitos
- Compilador **GCC**
- Sistema Unix-like (**Linux/MacOS**) ou **Windows com WSL**

### Compilação
```bash
gcc -std=c99 -Wall -o simulacao *.c
```

### Execução
```bash
./simulacao
```

## 🧩 Componentes Principais

### 🧑 Pessoas
Cada pessoa possui:
- `id_pessoa`: Identificador único
- `extroversao (0-100)`: Probabilidade de compartilhar rumores
- `paciencia (0-100)`: Tempo de permanência nos locais
- `idade (18-100)`: Influencia velocidade de movimento
- `crc`: Conjunto de rumores conhecidos

### 🏙️ Locais
Cada local possui:
- `id_local`: Identificador único
- `lotacao_max (5-30)`: Capacidade máxima
- `publico`: Conjunto de pessoas presentes
- `fila_local`: Fila de espera quando lotado
- Coordenadas `(x, y)` no mundo

### 📢 Rumores
- 30 rumores únicos identificados por `id_rumor`
- Propagação através de subconjuntos aleatórios

## ⏳ Dinâmica da Simulação

### Inicialização:
- Criação do mundo com parâmetros pré-definidos
- Geração aleatória de pessoas, locais e rumores

### Eventos:
- **CHEGADA**: Pessoa chega em um local
- **SAIDA**: Pessoa deixa o local
- **RUMOR**: Pessoa compartilha rumores
- **FIM**: Término da simulação

### Fluxo:
- Pessoas se movem entre locais
- Tempo de permanência baseado na paciência
- Rumores são compartilhados aleatoriamente
- Sistema de filas quando locais estão lotados

## 📊 Exemplo de Saída
```
1420:CHEGA Pessoa 12 Local 5 (8/15), ENTRA
1425:RUMOR Pessoa 12 Local 5 (P8:R3) (P15:R7)
1430:SAIDA Pessoa 12 Local 5 (7/15), REMOVE FILA Pessoa 23
```

## 📚 Documentação dos TADs

### Conjunto (libconjunto)
Operações implementadas:
- `cria_conjunto()`, `destroi_conjunto()`
- `insere_conjunto()`, `retira_conjunto()`
- `pertence()`, `contido()`, `sao_iguais()`

Operações entre conjuntos:
- `cria_uniao()`
- `cria_interseccao()`
- `cria_diferenca()`
- `cria_subconjunto()`: Gera subconjunto aleatório

Possui também um iterador para percorrer elementos.

### Fila (libfila)
Implementação com:
- Operações FIFO padrão (`insere_fila`, `retira_fila`)
- Mecanismo iterador
- Controle de tamanho
- Nodos duplamente encadeados

### LEF (liblef)
Lista de Eventos Futuros com:
- Inserção ordenada por tempo
- Diferentes tipos de eventos
- Mecanismo de processamento temporal

## ⚙️ Configurações do Mundo
- Tamanho: `20000x20000` unidades
- Duração: `34944` unidades de tempo (≈ 1 ano simulado)
- População: `100` pessoas
- Locais: `8` com lotação entre `5-30`
- Rumores: `30` únicos

## 📜 Licença
Projeto acadêmico desenvolvido para a disciplina de Programação 1 (CI1001).  
Código aberto para fins educacionais.
