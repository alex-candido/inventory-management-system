# Inventory Management System - C - IFCE

## About
A robust inventory management system developed in C using GTK for the graphical user interface. This system allows users to manage products, track stock levels, and generate various reports for effective inventory control.

## Getting Started
This section provides instructions on how to set up and run the inventory management system on your local machine.

## Project Structure
```
- apps/          # Main application entry point
- assets/        # CSS styles and other assets
- bin/           # Compiled binaries
- data/          # Data storage and seed files
- include/       # Header files
- lib/           # Static libraries
- services/      # Business logic implementation
- views/         # UI components and views
```

## Initial Configuration
1. Ensure you have all required dependencies installed
2. Configure the data directory permissions
3. Set up the development environment

## Compilation and Execution
1. Build the project using make:
```bash
make
```
2. Run the application:
```bash
./bin/app
```

## System Feature Mapping
- **Dashboard**
  - Overview of total products
  - Stock entry count
  - Total items in stock
  - Total stock value
  - Low stock alerts

- **Product Management**
  - Add new products
  - Edit existing products
  - View product details
  - Delete products

- **Stock Management**
  - Record stock entries
  - Track stock movements
  - Manage stock locations

- **Reporting**
  - Out of stock products
  - Products by location
  - Recently added products
  - Category-wise statistics
  - Stock valuation

## Approaches
- **Data Storage**: Binary file-based storage for products and stock data
- **UI Framework**: GTK3 for creating a responsive and user-friendly interface
- **Architecture**: Modular design with separation of concerns
  - Services layer for business logic
  - Views layer for UI components
  - Data layer for storage operations

## Dependencies
- GTK 3.0 or higher
- GCC compiler
- Make build system

## Requirements
- Linux-based operating system (Ubuntu recommended)
- GTK development libraries
- C development tools

## Starting the Application
1. Clone the repository
2. Install dependencies:
```bash
sudo apt-get install build-essential
sudo apt-get install libgtk-3-dev
```
3. Build the project:
```bash
make
```
4. Run the application:
```bash
./bin/app
```

## License
This project is part of the academic curriculum at IFCE (Federal Institute of Education, Science and Technology of Ceará).
