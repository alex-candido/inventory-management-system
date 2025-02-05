```bash
$ ./inventory_management
### Welcome to Inventory Management System ###
1. Manage Products
2. Manage Stocks
3. Reports
4. Exit
Choose any option: 1
Wed Sep 09 16:32:48 2025
```
```bash
$ ./manage_products
### Welcome to Product Management View ###
1. View Products
2. Add New Product
3. Update Existing Product
4. Delete Existing Product
5. Search Existing Product
6. Back to Main Menu
Choose any option: 1
Wed Sep 09 16:32:48 2025
```
```bash
$ ./view_products
### Inventory Products ###
| s/n | ID   | Name           | Category | Quantity | Price | created_at          | updated_at          |
|-----|------|----------------|----------|----------|-------|---------------------|---------------------|
| 1   | 1001 | Product A      | Category 1| 10       | 50.00 | 2025-09-01 10:00:00 | 2025-09-02 12:30:00 |
| 2   | 1002 | Product B      | Category 2| 5        | 25.00 | 2025-09-01 11:00:00 | 2025-09-02 13:00:00 |
| 3   | 1003 | Product C      | Category 3| 20       | 10.00 | 2025-09-01 12:00:00 | 2025-09-02 14:00:00 |
| 4   | 1004 | Product D      | Category 1| 30       | 60.00 | 2025-09-01 13:00:00 | 2025-09-02 15:00:00 |
| 5   | 1005 | Product E      | Category 2| 7        | 40.00 | 2025-09-01 14:00:00 | 2025-09-02 16:00:00 |
Current Page: 1  Total Pages: 100
Pagination (which page to view): 1
Wed Sep 09 16:32:48 2025
```

```bash
$ ./add_product
### Add New Product ###
Enter Product Name: Product F
Enter Product Category: Category 3
Enter Product Quantity: 15
Enter Product Price: 30.00
Product added successfully!
```

```bash
$ ./view_products
### Inventory Products ###
| s/n | ID   | Name           | Category | Quantity | Price | created_at          | updated_at          |
|-----|------|----------------|----------|----------|-------|---------------------|---------------------|
| 1   | 1001 | Product A      | Category 1| 10       | 50.00 | 2025-09-01 10:00:00 | 2025-09-02 12:30:00 |
| 2   | 1002 | Product B      | Category 2| 5        | 25.00 | 2025-09-01 11:00:00 | 2025-09-02 13:00:00 |
| 3   | 1003 | Product C      | Category 3| 20       | 10.00 | 2025-09-01 12:00:00 | 2025-09-02 14:00:00 |
| 4   | 1004 | Product D      | Category 1| 30       | 60.00 | 2025-09-01 13:00:00 | 2025-09-02 15:00:00 |
| 5   | 1005 | Product E      | Category 2| 7        | 40.00 | 2025-09-01 14:00:00 | 2025-09-02 16:00:00 |
| 6   | 1006 | Product F      | Category 3| 15       | 30.00 | 2025-09-01 15:00:00 | 2025-09-02 17:00:00 |
Press Enter to continue...
Wed Sep 09 16:32:48 2025
```

```bash
$ ./update_product
### Update Existing Product ###
Select Product ID to update: 1002
Enter New Name (Leave empty to keep current): Updated Product B
Enter New Category (Leave empty to keep current): Category 2
Enter New Quantity (Leave empty to keep current): 10
Enter New Price (Leave empty to keep current): 35.00
Product updated successfully!
```

```bash
$ ./view_products
### Inventory Products ###
| s/n | ID   | Name           | Category | Quantity | Price | created_at          | updated_at          |
|-----|------|----------------|----------|----------|-------|---------------------|---------------------|
| 1   | 1001 | Product A      | Category 1| 10       | 50.00 | 2025-09-01 10:00:00 | 2025-09-02 12:30:00 |
| 2   | 1002 | Updated Product B | Category 2| 10       | 35.00 | 2025-09-01 11:00:00 | 2025-09-02 18:00:00 |
| 3   | 1003 | Product C      | Category 3| 20       | 10.00 | 2025-09-01 12:00:00 | 2025-09-02 14:00:00 |
| 4   | 1004 | Product D      | Category 1| 30       | 60.00 | 2025-09-01 13:00:00 | 2025-09-02 15:00:00 |
| 5   | 1005 | Product E      | Category 2| 7        | 40.00 | 2025-09-01 14:00:00 | 2025-09-02 16:00:00 |
Press Enter to continue...
Wed Sep 09 16:32:48 2025
```

```bash
$ ./delete_product
### Delete Existing Product ###
Select Product ID to delete: 1003
Product deleted successfully!
```

```bash
$ ./view_products
### Inventory Products ###
| s/n | ID   | Name           | Category | Quantity | Price | created_at          | updated_at          |
|-----|------|----------------|----------|----------|-------|---------------------|---------------------|
| 1   | 1001 | Product A      | Category 1| 10       | 50.00 | 2025-09-01 10:00:00 | 2025-09-02 12:30:00 |
| 2   | 1002 | Updated Product B | Category 2| 10       | 35.00 | 2025-09-01 11:00:00 | 2025-09-02 18:00:00 |
| 3   | 1004 | Product D      | Category 1| 30       | 60.00 | 2025-09-01 13:00:00 | 2025-09-02 15:00:00 |
| 4   | 1005 | Product E      | Category 2| 7        | 40.00 | 2025-09-01 14:00:00 | 2025-09-02 16:00:00 |
Press Enter to continue...
Wed Sep 09 16:32:48 2025
```

```bash
$ ./search_product
### Search Existing Product ###
1. Search by ID
2. Search by Name
3. Search by Category
4. Search by Price
5. Back to Main Menu
Choose any option: 3
```

```bash
$ ./search_by_category
### Search by Category ###
Category: Category 2
### Inventory Products ###
| s/n | ID   | Name           | Category | Quantity | Price | created_at          | updated_at          |
|-----|------|----------------|----------|----------|-------|---------------------|---------------------|
| 1   | 1002 | Updated Product B | Category 2| 10       | 35.00 | 2025-09-01 11:00:00 | 2025-09-02 18:00:00 |
| 2   | 1005 | Product E      | Category 2| 7        | 40.00 | 2025-09-01 14:00:00 | 2025-09-02 16:00:00 |
Press Enter to continue...
Wed Sep 09 16:32:48 2025
```

```bash
$ ./view_reports
### Viewing Reports ###
1. Price Details
2. Selling Details
3. Complete Details
4. Profit/Loss
5. Back to Main Menu
Choose any option: 1
```

```bash
$ ./view_reports_price_details
### Price Details ###
### Inventory Products ###
| s/n | ID   | Name           | Category | Quantity | Price | created_at          | updated_at          |
|-----|------|----------------|----------|----------|-------|---------------------|---------------------|
| 1   | 1001 | Product A      | Category 1| 10       | 50.00 | 2025-09-01 10:00:00 | 2025-09-02 12:30:00 |
| 2   | 1002 | Updated Product B | Category 2| 10       | 35.00 | 2025-09-01 11:00:00 | 2025-09-02 18:00:00 |
| 3   | 1004 | Product D      | Category 1| 30       | 60.00 | 2025-09-01 13:00:00 | 2025-09-02 15:00:00 |
| 4   | 1005 | Product E      | Category 2| 7        | 40.00 | 2025-09-01 14:00:00 | 2025-09-02 16:00:00 |
Press Enter to continue...
Wed Sep 09 16:32:48 2025
```
