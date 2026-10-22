/* Experiment 7(a) - TCP Hello + Chatbot Client (port 5000) */
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#define PORT 5000
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server_addr;
    char ip[64], buffer[BUF_SIZE];
    int n;

    if (argc > 1) {
        strncpy(ip, argv[1], sizeof(ip) - 1);
        ip[sizeof(ip) - 1] = '\0';
    } else {
        printf("Enter server IP (127.0.0.1 for same PC): ");
        scanf("%63s", ip);
        getchar();
    }

    WSAStartup(MAKEWORD(2, 2), &wsa);
    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Connection failed: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Connected to server %s:%d. Type 'bye' to exit.\n", ip, PORT);

    while (1) {
        printf("You: ");
        if (!fgets(buffer, BUF_SIZE, stdin)) break;
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (buffer[0] == '\0') continue;
        send(sock, buffer, (int)strlen(buffer), 0);

        n = recv(sock, buffer, BUF_SIZE - 1, 0);
        if (n <= 0) break;
        buffer[n] = '\0';
        printf("Server: %s\n", buffer);
        if (strncmp(buffer, "Bye!", 4) == 0) break;
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
