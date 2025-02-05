# Inventory Management System - User Flow

## **Initial View** (Tela inicial)
**Objetivo:** Apresentar as principais opções para o usuário.

### Welcome to Inventory Management System
1. **Manage Products**
2. **Manage Stocks**
3. **Reports**
4. **Exit**

**Ação:** O usuário escolhe uma opção para seguir.

**Nota:** Deixe claro ao usuário que ele pode digitar o número da opção desejada ou pressionar 'Exit' para sair.

---

## **Manage Products View** (Gerenciar Produtos)
**Objetivo:** Opções de gerenciamento de produtos no inventário.

### Welcome to Product Management View
1. **View Products** (Visualizar produtos)
2. **Add New Product** (Adicionar novo produto)
3. **Update Existing Product** (Atualizar produto existente)
4. **Delete Existing Product** (Deletar produto existente)
5. **Search Existing Product** (Buscar produto existente)
6. **Back to Main Menu** (Voltar ao menu principal)

**Ação:** O usuário escolhe a opção que deseja gerenciar.

---

### **View Existing Products** (Visualizar Produtos Existentes)
**Objetivo:** Exibir todos os produtos no inventário com paginação.

### Inventory Products
| s/n | ID | Name | Category | Quantity | Price | Created At | Updated At |
| --- | --- | ---- | -------- | -------- | ----- | ---------- | ---------- |
| -> items... |
**Current Page:** 1 / **Total Pages:** 100
**Pagination:** Digite o número da página ou pressione Enter para continuar.

**Ação:** O usuário navega pela tabela de produtos ou escolhe outra ação.

---

### **Add New Product** (Adicionar Novo Produto)
**Objetivo:** Capturar dados do novo produto a ser adicionado.

### Add New Product
- **UUID:** Gerado automaticamente.
- **Product Name:** [Campo de texto]
- **Product Category:** [Campo de texto ou lista suspensa]
- **Product Quantity:** [Campo numérico]
- **Product Price:** [Campo numérico]

**Ação:** O usuário preenche os campos e pressiona Enter para continuar.

---

### **Add New Product Success** (Produto Adicionado com Sucesso)
**Objetivo:** Confirmar a adição do novo produto ao inventário.

### Inventory Products
| s/n | ID | Name | Category | Quantity | Price | Created At | Updated At |
| --- | --- | ---- | -------- | -------- | ----- | ---------- | ---------- |
| -> item adicionado | **ADDED**

**Mensagem:** "Product with ID 1002 added successfully"
**Ação:** O usuário pressiona Enter para voltar.

---

### **Update Existing Product** (Atualizar Produto Existente)
**Objetivo:** Permitir que o usuário atualize um produto existente.

### Inventory Products
| s/n | ID | Name | Category | Quantity | Price | Created At | Updated At |
| --- | --- | ---- | -------- | -------- | ----- | ---------- | ---------- |
| -> items...
**Current Page:** 1 / **Total Pages:** 100
**Pagination:** Digite o número da página ou pressione Enter para continuar.

**Ação:** O usuário escolhe o **ID do produto** que deseja atualizar.

---

### **Update Existing Product View** (Atualizar Produto: Preenchimento dos Dados)
**Objetivo:** Atualizar os campos de um produto selecionado.

### Update Existing Product
- **Product Name:** [Campo de texto ou deixe em branco para manter o nome atual]
- **Product Category:** [Campo de texto ou deixe em branco para manter a categoria atual]
- **Product Quantity:** [Campo numérico ou deixe em branco para manter a quantidade atual]
- **Product Price:** [Campo numérico ou deixe em branco para manter o preço atual]

**Ação:** O usuário preenche os campos e pressiona Enter para confirmar.

---

### **Update Existing Product Success** (Produto Atualizado com Sucesso)
**Objetivo:** Confirmar a atualização do produto no inventário.

### Inventory Products
| s/n | ID | Name | Category | Quantity | Price | Created At | Updated At |
| --- | --- | ---- | -------- | -------- | ----- | ---------- | ---------- |
| -> item atualizado | **UPDATED**

**Mensagem:** "Product with ID 1002 updated successfully"
**Ação:** O usuário pressiona Enter para voltar.

---

### **Delete Existing Product** (Deletar Produto Existente)
**Objetivo:** Permitir que o usuário delete um produto.

### Delete Existing Product
| s/n | ID | Name | Category | Quantity | Price | Created At | Updated At |
| --- | --- | ---- | -------- | -------- | ----- | ---------- | ---------- |
| -> items...
**Current Page:** 1 / **Total Pages:** 100
**Pagination:** Digite o número da página ou pressione Enter para continuar.

**Ação:** O usuário escolhe o **ID do produto** que deseja deletar.

---

### **Delete Existing Product Success** (Produto Deletado com Sucesso)
**Objetivo:** Confirmar a remoção do produto.

### Inventory Products
| s/n | ID | Name | Category | Quantity | Price | Created At | Updated At |
| --- | --- | ---- | -------- | -------- | ----- | ---------- | ---------- |
| -> item removido | **DELETED**

**Mensagem:** "Product with ID 1002 deleted successfully"
**Ação:** O usuário pressiona Enter para voltar.

---

### **Search Existing Product** (Buscar Produto Existente)
**Objetivo:** Permitir ao usuário buscar produtos por diferentes critérios.

### Search Existing Product
1. **Search by Id**
2. **Search by Name**
3. **Search by Category**
4. **Search by Price**
5. **Back to Main Menu**

**Ação:** O usuário escolhe o tipo de pesquisa.

---

### **Search by Category** (Buscar por Categoria)
**Objetivo:** Filtrar produtos por categoria.

### Search by Category
- **Category:** [Campo de texto ou lista suspensa]

### Inventory Products
| s/n | ID | Name | Category | Quantity | Price | Created At | Updated At |
| --- | --- | ---- | -------- | -------- | ----- | ---------- | ---------- |
| -> items filtrados...
**Current Page:** 1 / **Total Pages:** 100
**Pagination:** Digite o número da página ou pressione Enter para continuar.

**Ação:** O usuário visualiza os produtos filtrados por categoria ou escolhe outra ação.

---

### **Viewing Reports** (Visualizar Relatórios)
**Objetivo:** Exibir relatórios detalhados sobre o inventário.

### Viewing Reports
1. **Price details**
2. **Selling details**
3. **Complete details**
4. **Profit/loss**
5. **Back to Main Menu**

**Ação:** O usuário escolhe o tipo de relatório.

---

### **Price Details Report** (Relatório de Detalhes de Preço)
**Objetivo:** Exibir o total de preço e quantidade dos produtos.

### Price Details
### Inventory Products
| s/n | ID | Name | Category | Quantity | Price | Created At | Updated At |
| --- | --- | ---- | -------- | -------- | ----- | ---------- | ---------- |
| -> items...
**Current Page:** 1 / **Total Pages:** 100
**Pagination:** Digite o número da página ou pressione Enter para continuar.

**Detalhes:**
- **Total Quantity:** [Total de produtos]
- **Total Rate:** [Valor total]
- **Total Cost:** [Custo total]

**Ação:** O usuário visualiza os dados ou escolhe outra opção de relatório.
