/* Experiment 7(a) - TCP Hello + Chatbot Server (port 5000) */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <winsock2.h>

#define PORT 5000
#define BUF_SIZE 1024

static void to_lower(char *s)
{
    for (; *s; s++) *s = (char)tolower((unsigned char)*s);
}

static const char *answer(const char *q)
{
    if (strstr(q, "hello") || strcmp(q, "hi") == 0) return "Hello from Server!";
    if (strstr(q, "your name"))                return "I am a TCP chatbot server.";
    if (strstr(q, "how are you"))              return "I am fine, thank you.";
    if (strstr(q, "tcp"))                      return "TCP is a reliable, connection-oriented protocol.";
    if (strstr(q, "udp"))                      return "UDP is a fast, connectionless protocol.";
    if (strstr(q, "port"))                     return "This server is running on port 5000.";
    if (strstr(q, "socket"))                   return "A socket is an endpoint made of an IP address and a port.";
    if (strstr(q, "time"))                     return "Sorry, I cannot tell the time yet.";
    if (strstr(q, "bye"))                      return "Bye! Connection closed.";
    return "Sorry, I don't understand. Try: hello, your name, how are you, tcp, udp, port, socket, bye";
}

int main(void)
{
    WSADATA wsa;
    SOCKET server, client;
    struct sockaddr_in server_addr, client_addr;
    int client_len = sizeof(client_addr);
    char buffer[BUF_SIZE], q[BUF_SIZE];
    const char *reply;
    int n;

    WSAStartup(MAKEWORD(2, 2), &wsa);
    server = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        return 1;
    }
    listen(server, 1);
    printf("Chat Server started on port %d. Waiting for client...\n", PORT);

    client = accept(server, (struct sockaddr *)&client_addr, &client_len);
    printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

    while ((n = recv(client, buffer, BUF_SIZE - 1, 0)) > 0) {
        buffer[n] = '\0';
        printf("Client: %s\n", buffer);
        strcpy(q, buffer);
        to_lower(q);
        reply = answer(q);
        send(client, reply, (int)strlen(reply), 0);
        printf("Server: %s\n", reply);
        if (strcmp(q, "bye") == 0) break;
    }

    closesocket(client);
    closesocket(server);
    WSACleanup();
    return 0;
}
