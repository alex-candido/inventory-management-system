# Inventory Management System - C - IFCE

## 📌 Sobre o Projeto

O **Inventory Management System** é um sistema desenvolvido em C para gerenciamento de inventário. Ele permite adicionar, remover, listar e atualizar produtos armazenados, garantindo um controle eficiente dos itens disponíveis.

## 🚀 Getting Started

Este guia ajudará você a configurar o projeto, compilar os arquivos e executar as funcionalidades básicas.

### 📂 Estrutura do Projeto

```plaintext
inventory-management-system/
├── apps/           # Aplicações que usam a biblioteca
├── bin/            # Arquivos executáveis (gerados pelo Makefile)
├── data/           # Arquivos de dados (CSV, JSON, etc.)
├── doc/            # Documentação do projeto
├── include/        # Arquivos de cabeçalho (.h)
├── lib/            # Biblioteca compilada (.a) (gerada pelo Makefile)
├── obj/            # Arquivos objeto (.o) (gerados pelo Makefile)
├── src/            # Código-fonte principal (.c)
├── Makefile        # Arquivo de automação da compilação
└── README.md       # Explicação sobre o projeto
```

### 📌 Resumo do Fluxo Completo

```bash
Etapa	Ação	Criado/Modificado Manualmente	Comando
1️⃣	Criar estrutura do projeto	mkdir -p e touch arquivos iniciais	Nenhum
2️⃣	Criar cabeçalho .h	include/inventory.h	Nenhum
3️⃣	Criar implementação .c	src/inventory.c	Nenhum
4️⃣	Criar aplicativo principal	apps/app.c	Nenhum
5️⃣	Criar Makefile	Makefile	Nenhum
6️⃣	Compilar biblioteca	lib/libed.a	make libed
7️⃣	Compilar executável	bin/app	make myapps
8️⃣	Executar e testar	bin/app	make run
```

### 🔧 Configuração Inicial

Criação dos diretórios e arquivos iniciais:

```bash
mkdir -p inventory-management-system/{apps,bin,data,doc,include,lib,obj,src}
touch inventory-management-system/Makefile
```

Criando arquivos básicos:

```bash
touch inventory-management-system/include/inventory.h
touch inventory-management-system/src/inventory.c
touch inventory-management-system/apps/app.c
```

### 🛠️ Implementação da Funcionalidade "Remover Produto"

📄 **Definir a Função no Arquivo de Cabeçalho (`include/inventory.h`)**

```c
#ifndef INVENTORY_H
#define INVENTORY_H

void remove_product(int id);

#endif
```

📄 **Implementar a Função no Código-Fonte (`src/inventory.c`)**

```c
#include <stdio.h>
#include "inventory.h"

void remove_product(int id) {
    printf("Produto de ID %d removido com sucesso!\n", id);
}
```

📄 **Criar o Aplicativo Principal (`apps/app.c`)**

```c
#include <stdio.h>
#include "inventory.h"

int main() {
    printf("Bem-vindo ao Sistema de Inventário!\n");
    remove_product(101);
    return 0;
}
```

### 🔨 Compilação e Execução

📌 **Passo 1: Criar a Biblioteca**

```bash
make libed
```

📌 **Passo 2: Compilar o Aplicativo**

```bash
make myapps
```

📌 **Passo 3: Executar e Testar**

```bash
make run
```

## 🔍 Mapeamento de Features do Sistema

### ✅ **Requisitos Funcionais**

1. **Adicionar Produto**: O sistema deve permitir que novos produtos sejam adicionados ao inventário com um identificador único.
2. **Remover Produto**: O usuário deve ser capaz de remover um produto do inventário pelo seu ID.
3. **Listar Produtos**: O sistema deve exibir uma lista de todos os produtos cadastrados.
4. **Atualizar Produto**: O usuário pode modificar informações de um produto existente, como nome e quantidade.
5. **Persistência de Dados**: O inventário deve ser armazenado em arquivos para manter os dados após a execução do programa.
6. **Busca por Produto**: O usuário pode pesquisar produtos por nome ou ID.
7. **Relatórios de Inventário**: O sistema deve gerar relatórios básicos, como o total de produtos em estoque.

### 🔧 **Requisitos Não-Funcionais**

1. **Desempenho**: O sistema deve processar operações como adição e remoção de produtos em tempo real.
2. **Usabilidade**: A interface deve ser simples e intuitiva para facilitar o uso por qualquer usuário.
3. **Portabilidade**: O código deve ser compatível com sistemas Unix/Linux e Windows.
4. **Modularidade**: O código deve seguir um modelo modular para facilitar manutenção e expansão.
5. **Gerenciamento de Erros**: O sistema deve tratar erros, como tentativas de remover um produto inexistente.
6. **Compilação Automatizada**: O sistema deve ser compilado com um único comando usando `Makefile`.

---

## 📚 Approaches

- **Modularidade**: O código é dividido em arquivos `.h` e `.c` para facilitar manutenção.
- **Uso de Makefile**: Automação do processo de compilação.
- **Persistência de Dados**: O sistema pode salvar e recuperar dados armazenados.

## 📦 Dependencies

- **GCC** (Compilador C)
- **Make** (Automação da compilação)

## 📋 Prerequisites

Certifique-se de ter o GCC e o Make instalados antes de compilar o projeto:

```bash
sudo apt update && sudo apt install build-essential
```

Para sistemas Windows, use o **MinGW**.

## 🚀 Starting the Application

Clone o repositório e siga os passos:

```bash
git clone https://github.com/seu-usuario/inventory-management-system.git
cd inventory-management-system
make libed
make myapps
make run
```

Este documento serve como um guia para a configuração e uso do projeto, garantindo que novos desenvolvedores consigam entender e contribuir facilmente! 🚀

