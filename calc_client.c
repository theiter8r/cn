/* Experiment 7(b) - TCP Calculator / Factorial Client (port 5001) */
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#define PORT 5001
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
    n = recv(sock, buffer, BUF_SIZE - 1, 0);
    if (n > 0) { buffer[n] = '\0'; printf("Server: %s\n", buffer); }
    printf("Enter queries like: 12 + 5 | 7 * 3 | 2 ^ 8 | fact 5 | 5!   ('exit' to quit)\n");

    while (1) {
        printf("Query: ");
        if (!fgets(buffer, BUF_SIZE, stdin)) break;
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (buffer[0] == '\0') continue;
        send(sock, buffer, (int)strlen(buffer), 0);
        if (strcmp(buffer, "exit") == 0 || strcmp(buffer, "bye") == 0) break;

        n = recv(sock, buffer, BUF_SIZE - 1, 0);
        if (n <= 0) break;
        buffer[n] = '\0';
        printf("Result: %s\n", buffer);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
