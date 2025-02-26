# Inventory Management System - C - IFCE

<a href="https://learn.microsoft.com/pt-br/cpp/c-language/?view=msvc-170" target="_blank"><code><img height="45" title="c" src="https://skillicons.dev/icons?i=c" /></code></a>
<a href="https://cmake.org/" target="_blank"><code><img height="45" title="cmake" src="https://skillicons.dev/icons?i=cmake" /></code></a>
<a href="https://www.gtk.org/" target="_blank"><code><img height="45" title="gtk" src="https://skillicons.dev/icons?i=gtk" /></code></a>
<a href="https://learn.microsoft.com/pt-br/cpp/c-language/?view=msvc-170" target="_blank"><code><img height="45" title="cc" src="https://skillicons.dev/icons?i=css" /></code></a>

## About
Um sistema robusto de gerenciamento de inventário desenvolvido em C utilizando GTK para a interface gráfica do usuário. Este sistema permite aos usuários gerenciar produtos, controlar níveis de estoque e gerar vários relatórios para um controle efetivo de inventário.

## Getting Started
Esta seção fornece instruções sobre como configurar e executar o sistema de gerenciamento de inventário em sua máquina local.

## Seed Data
O sistema utiliza dados iniciais (seed) para popular o banco de dados com informações de exemplo:

- `data/seeds/products.csv`: Contém dados iniciais dos produtos
  - Formato: ID, Nome, Descrição, Preço, Quantidade Mínima
- `data/seeds/stocks.csv`: Contém dados iniciais do estoque
  - Formato: ID do Produto, Quantidade, Data de Entrada, Localização

Os dados seed são carregados automaticamente na primeira execução do sistema ou quando o banco de dados está vazio.

## Project Structure
```
- apps/          # Ponto de entrada principal da aplicação
- assets/        # Estilos CSS e outros recursos
- bin/           # Binários compilados
- data/          # Armazenamento de dados e arquivos seed
- include/       # Arquivos de cabeçalho
- lib/           # Bibliotecas estáticas
- services/      # Implementação da lógica de negócios
- views/         # Componentes e visualizações da UI
```

## Initial Configuration
1. Certifique-se de ter todas as dependências necessárias instaladas
2. Configure as permissões do diretório de dados
3. Configure o ambiente de desenvolvimento

## Compilation and Execution
1. Compile o projeto usando make:
```bash
make
```
2. Execute a aplicação:
```bash
./bin/app
```

## System Feature Mapping
- **Dashboard**
  - Visão geral do total de produtos
  - Contagem de entradas no estoque
  - Total de itens em estoque
  - Valor total do estoque
  - Alertas de baixo estoque

- **Product Management**
  - Adicionar novos produtos
  - Editar produtos existentes
  - Visualizar detalhes do produto
  - Excluir produtos

- **Stock Management**
  - Registrar entradas de estoque
  - Acompanhar movimentações de estoque
  - Gerenciar localizações de estoque

- **Reporting**
  - Produtos fora de estoque
  - Produtos por localização
  - Produtos recentemente adicionados
  - Estatísticas por categoria
  - Avaliação de estoque

## Approaches
- **Data Storage**: Armazenamento baseado em arquivos binários para dados de produtos e estoque
- **UI Framework**: GTK3 para criar uma interface responsiva e amigável
- **Architecture**: Design modular com separação de responsabilidades
  - Camada de serviços para lógica de negócios
  - Camada de visualização para componentes da UI
  - Camada de dados para operações de armazenamento

## Dependencies
- GTK 3.0 ou superior
- GCC compiler
- Make build system

## Requirements
- Sistema operacional baseado em Linux (Ubuntu recomendado)
- Bibliotecas de desenvolvimento GTK
- Ferramentas de desenvolvimento C

## Starting the Application
1. Clone o repositório
2. Instale as dependências:
```bash
sudo apt-get install build-essential
sudo apt-get install libgtk-3-dev
```

3. Compile o projeto usando os comandos do Makefile:

### Comandos do Makefile Disponíveis
```bash
# Compilação completa do projeto
make all

# Compilação rápida (apenas arquivos modificados)
make

# Limpar arquivos compilados
make clean

# Recompilar todo o projeto
make rebuild

# Compilar em modo debug
make debug

# Executar testes
make test
```

### Detalhes dos Comandos
- `make all`: Compila todo o projeto, incluindo bibliotecas e executável principal
- `make`: Compilação incremental (recompila apenas arquivos modificados)
- `make clean`: Remove todos os arquivos compilados e temporários
- `make rebuild`: Executa clean seguido de all para recompilar todo o projeto
- `make debug`: Compila com símbolos de debug para uso com GDB
- `make test`: Executa a suite de testes do projeto

4. Execute a aplicação:
```bash
./bin/app
```

### Observações Importantes
- Certifique-se de que todas as dependências estão instaladas antes de compilar
- Em caso de erros de compilação, execute `make clean` seguido de `make all`
- Para desenvolvimento, recomenda-se usar `make debug` para incluir informações de debug
- Os arquivos compilados são armazenados no diretório `bin/`

## License
Este projeto é parte do currículo acadêmico do IFCE (Instituto Federal de Educação, Ciência e Tecnologia do Ceará).
