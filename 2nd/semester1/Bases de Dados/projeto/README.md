<div align="center">

# 🌍 DigiTrip

A relational database system for managing and sharing travel experiences, developed using **SQL** and **MySQL**.

![MySQL](https://img.shields.io/badge/-MySQL-4479A1?style=for-the-badge\&logo=mysql\&logoColor=white)
![SQL](https://img.shields.io/badge/-SQL-336791?style=for-the-badge\&logo=postgresql\&logoColor=white)
![MySQL Workbench](https://img.shields.io/badge/-MySQL%20Workbench-F29111?style=for-the-badge\&logo=mysql\&logoColor=white)

</div>

## 📖 About the Project

**DigiTrip** is a relational database system designed to support a travel application where users can register their trips, explore locations, share content and interact with other travelers.

The database manages information about **travelers, trips, countries, locations, comments and multimedia content**, while ensuring data consistency and integrity through relational constraints.

The project covers the different stages of database development, from conceptual modeling and requirements analysis to the final implementation in **MySQL**.

## 🌍 Main Features

The database supports several aspects of the travel platform:

* 👤 **Travelers** — Manage users and their travel information.
* ✈️ **Trips** — Register and manage trips created by travelers.
* 🌎 **Countries** — Store geographical information about countries.
* 📍 **Locations** — Manage places visited during trips.
* 💬 **Comments** — Allow travelers to leave comments and ratings.
* 📸 **Content** — Associate photos and videos with trips and locations.
* 🔐 **Access Control** — Manage database users, roles and permissions.
* 📊 **Data Analysis** — Provide queries and views for accessing relevant information.

## 🗂️ Database Entities

| Entity          | Description                                                                |
| --------------- | -------------------------------------------------------------------------- |
| 👤 **Traveler** | Users who register, create trips and interact with the application.        |
| ✈️ **Trip**     | A journey created by a traveler, including dates, description and purpose. |
| 🌎 **Country**  | Geographical information including country, continent and languages.       |
| 📍 **Location** | Places and points of interest visited during trips.                        |
| 💬 **Comment**  | Comments and ratings associated with trips.                                |
| 📸 **Content**  | Photos and videos associated with trips and locations.                     |

## 🧩 Database Design

The project includes the complete design and implementation of a relational database.

### 📐 Conceptual Model

The database was first designed using an **Entity-Relationship model**, defining the entities, attributes and relationships between them.

### 🔄 Logical Model

The conceptual model was transformed into a relational model and normalized up to **Third Normal Form (3NF)** to reduce redundancy and improve data consistency.

### 🧮 Relational Algebra

The required queries were also represented and validated using **Relational Algebra**.

## 🛠️ Database Implementation

The database is implemented in **MySQL** and includes:

* 🏗️ Table creation and relationships.
* 🔗 Primary and foreign keys.
* ✅ Integrity constraints.
* 🔒 Users, roles and permissions.
* 📝 Data insertion and population.
* 👁️ Database views.
* ⚡ Indexes for query optimization.
* 🔧 Stored procedures.
* 🧮 Stored functions.
* 🔄 Triggers.

## 🔐 Data Integrity

The database uses several mechanisms to ensure that the stored information remains consistent and valid.

These include:

* 🔑 `PRIMARY KEY`
* 🔗 `FOREIGN KEY`
* ✅ `UNIQUE`
* ✔️ `CHECK`
* 🔒 Referential integrity constraints
* 🔄 Database triggers and stored procedures

## ⚙️ Database Setup

The SQL scripts required to create and configure the database are available in the `scriptsSQL/` directory.

The scripts include:

* 🏗️ Database and table creation
* 📝 Data insertion and population
* 🔐 Users, roles and permissions
* 👁️ Views
* ⚡ Indexes
* 🔧 Stored procedures and functions
* 🔄 Triggers

The database can be set up using **MySQL** or **MySQL Workbench**.

To set up the database, open the required SQL scripts from the `scriptsSQL/` directory and execute them in the appropriate order using **MySQL Workbench** or another MySQL-compatible environment.

## 📚 Documentation

The project documentation contains the different stages of the database development process, including:

* 📋 Requirements analysis.
* 📐 Entity-Relationship model.
* 🧩 Logical model.
* 📖 Data dictionary.
* 🔄 Database normalization.
* 🧮 Relational Algebra queries.
* 🗄️ SQL implementation.

## 🛠️ Technologies

* 🐬 **MySQL** — Relational Database Management System.
* 🧑‍💻 **SQL** — Database definition, manipulation and control.
* 🖥️ **MySQL Workbench** — Database design and management.
* 📐 **TerraER** — Entity-Relationship modeling.
* 🧮 **Relax** — Relational Algebra validation.

## 📁 Project Structure

```text
projeto/
├── scriptsSQL/       # SQL scripts for the database
├── Relatorio/        # Project report and documentation
└── README.md         # Project documentation
```

## 🎯 Objective

The main objective of **DigiTrip** is to design and implement a complete relational database capable of supporting a travel-sharing application.

The project applies concepts such as **database modeling, relational algebra, normalization, SQL, data integrity, access control and database optimization**.

---
