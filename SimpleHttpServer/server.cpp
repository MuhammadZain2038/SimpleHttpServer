#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <thread>
#include <unordered_map>
#include <openssl/sha.h> // For password hashing
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std; // This line allows you to avoid using 'std::' for standard C++ types/functions

#define PORT 9090
bool running = true;

unordered_map<string, string> users;

string readFile(const string& path) {
    ifstream file(path);
    if (!file.is_open()) return "<h1>File Not Found</h1>";
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void loadUsers() {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        size_t sep = line.find(':');
        if (sep != string::npos) {
            string user = line.substr(0, sep);
            string pass = line.substr(sep + 1);
            users[user] = pass;
        }
    }
}

string hashPassword(const string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password.c_str(), password.size(), hash);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        ss << hex << (int)hash[i];
    return ss.str();
}

void saveUser(const string& user, const string& pass) {
    ofstream file("users.txt", ios::app);
    file << user << ":" << hashPassword(pass) << endl;
    users[user] = hashPassword(pass);
}

string parsePostData(const string& request) {
    size_t pos = request.find("\r\n\r\n");
    if (pos != string::npos) {
        return request.substr(pos + 4);
    }
    return "";
}

string urlDecode(const string &src) {
    string ret;
    char ch;
    int i, ii;
    for (i = 0; i < src.length(); i++) {
        if (src[i] == '%') {
            sscanf(src.substr(i + 1, 2).c_str(), "%x", &ii);
            ch = static_cast<char>(ii);
            ret += ch;
            i = i + 2;
        } else if (src[i] == '+') {
            ret += ' ';
        } else {
            ret += src[i];
        }
    }
    return ret;
}

void sendResponse(int client_socket, const string& content, const string& content_type = "text/html") {
    stringstream response;
    response << "HTTP/1.1 200 OK\r\n"
             << "Content-Type: " << content_type << "\r\n"
             << "Content-Length: " << content.length() << "\r\n"
             << "Connection: close\r\n\r\n"
             << content;
    string res = response.str();
    send(client_socket, res.c_str(), res.length(), 0);
}

string getField(const string& data, const string& key) {
    size_t keyPos = data.find(key + "=");
    if (keyPos == string::npos) return "";
    size_t start = keyPos + key.length() + 1;
    size_t end = data.find("&", start);
    if (end == string::npos) end = data.length();
    return data.substr(start, end - start);
}

void handleClient(int client_socket) {
    char buffer[15000] = {0};
    read(client_socket, buffer, 15000);
    string request(buffer);

    cout << "Request:\n" << request << endl;

    if (request.find("GET / ") != string::npos || request.find("GET /index.html") != string::npos) {
        sendResponse(client_socket, readFile("templates/login.html"));
    } else if (request.find("GET /register") != string::npos) {
        sendResponse(client_socket, readFile("templates/register.html"));
    } else if (request.find("GET /style.css") != string::npos) {
        sendResponse(client_socket, readFile("static/style.css"), "text/css");
    } else if (request.find("POST /register") != string::npos) {
        string data = urlDecode(parsePostData(request));
        string user = getField(data, "username");
        string pass = getField(data, "password");
        if (!user.empty() && !pass.empty()) {
            saveUser(user, pass);
            sendResponse(client_socket, "<html><body><p>Registered! <a href='/'>Login now</a></p></body></html>");
        } else {
            sendResponse(client_socket, "<html><body><p>Error: Username or Password cannot be empty. <a href='/register'>Try Again</a></p></body></html>");
        }
    } else if (request.find("POST /login") != string::npos) {
        string data = urlDecode(parsePostData(request));
        string user = getField(data, "username");
        string pass = getField(data, "password");
        if (!user.empty() && !pass.empty() && users.count(user) && users[user] == hashPassword(pass)) {
            sendResponse(client_socket, readFile("templates/info.html"));
        } else {
            sendResponse(client_socket, "<html><body><p>Invalid login. <a href='/'>Try again</a></p></body></html>");
        }
    } else if (request.find("POST /finish") != string::npos) {
        sendResponse(client_socket, readFile("templates/thankyou.html"));
        running = false;
    } else {
        sendResponse(client_socket, readFile("templates/404.html"));
    }

    close(client_socket);
}

int main() {
    loadUsers();
    int server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 10);
    cout << "Final improved server running on port " << PORT << "...\n";

    while (running) {
        client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        thread(handleClient, client_socket).detach();
    }

    cout << "Server stopped gracefully.\n";
    return 0;
}

