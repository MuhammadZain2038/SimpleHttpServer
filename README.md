<!-- Simple HTTP Web Server README -->

<h1 align="center">🌐 Simple HTTP Web Server</h1>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"/>
  <img src="https://img.shields.io/badge/Project-Simple%20HTTP%20Server-brightgreen?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Status-Completed-blue?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Type-Educational-orange?style=for-the-badge"/>
</p>

<p align="center">
  <strong>A lightweight HTTP web server built in C++ that serves static HTML pages and handles GET/POST requests.</strong>
</p>

---

## 🧠 Overview
**Simple HTTP Web Server** is a minimal yet functional web server implemented in **C++**.  
It demonstrates how web servers process **HTTP requests** and **responses**, handle **client connections**, and serve **static HTML content**.  

Developed by **Muzzamil (23k-2023)** and **Zain (23k-2038)**, this project provides hands-on experience in understanding **server-client architecture**, **HTTP protocols**, and **web communication**.

---

## ⚙️ Features
- 🧩 Serves static HTML pages from the `/pages` directory  
- 📬 Supports **HTTP GET** and **POST** requests  
- 🗂️ Uses `users.txt` to store form submissions (like registration data)  
- ❌ Custom **404 Error Page** for missing routes  
- ⚡ Lightweight & efficient, perfect for learning the basics of web servers  

---

## 📁 Project Structure
```text
  SimpleHttpServer/
  │
  ├── server.cpp           # Main C++ server code
  ├── users.txt            # Stores user data from forms
  ├── pages/               # Folder containing served web pages
  │   ├── 404.html         # Not found page
  │   ├── info.html        # Info / sample page
  │   ├── login.html       # Login form
  │   ├── register.html    # Registration form
  │   ├── thankyou.html    # Confirmation after form submission
  │   └── style.css        # Common page styling
```

---

## 🚀 Getting Started

### 🧰 Prerequisites
Make sure you have the following installed:
- **C++ Compiler** (e.g., g++, clang++)
- **Terminal or Command Prompt**

---

### ▶️ Run Instructions
1. **Clone this repository**
   ```bash
   git clone https://github.com/<your-username>/SimpleHttpServer.git
   cd SimpleHttpServer

2. **Compile the server**
   ```bash
   g++ server.cpp -o server


3. **Run the server**
   ```bash
   ./server


4. **Open in your browser**
   ```aurduino
   http://localhost:8080


🌍 Available Pages
| Page            | Description                          |
| --------------- | ------------------------------------ |
| `login.html`    | User login interface                 |
| `register.html` | New user registration page           |
| `thankyou.html` | Confirmation page after registration |
| `info.html`     | General information page             |
| `404.html`      | Error page for invalid routes        |


🧠 Learning Outcomes
Through this project, we explored:

-Fundamentals of HTTP protocols (GET/POST)
-Basics of web server architecture
-How to handle client-server communication
-Implementing simple data persistence
-Serving static web content using C++

👨‍💻 Contributors
| Name         | Roll No  | Role                                                 |
| ------------ | -------- | ---------------------------------------------------- |
| **Muzzamil** | 23k-2023 | GET request handling, setup & optimization           |
| **Zain**     | 23k-2038 | POST handling, HTML integration, testing & debugging |


📚 References
MDN – HTTP Overview
Flask Docs
Spring Boot Docs
Node.js Docs
