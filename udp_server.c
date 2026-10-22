/* Experiment 8 - UDP File Transfer Server (port 6000) */
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#define PORT 6000
#define BUF_SIZE 1024
#define END_MSG "__EOF__"
#define ERR_MSG "__ERROR__ File not found"

int main(void)
{
    WSADATA wsa;
    SOCKET server_sock;
    struct sockaddr_in server_addr, client_addr;
    int client_len;
    char buffer[BUF_SIZE];
    FILE *fp;
    int n, chunks;
    long total;

    WSAStartup(MAKEWORD(2, 2), &wsa);
    server_sock = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        return 1;
    }

    while (1) {
        printf("UDP File Server started. Waiting for file request on port %d...\n", PORT);
        client_len = sizeof(client_addr);
        n = recvfrom(server_sock, buffer, BUF_SIZE - 1, 0,
                     (struct sockaddr *)&client_addr, &client_len);
        if (n <= 0) continue;
        buffer[n] = '\0';
        printf("Request received from client %s for file: %s\n",
               inet_ntoa(client_addr.sin_addr), buffer);

        fp = fopen(buffer, "rb");
        if (fp == NULL) {
            sendto(server_sock, ERR_MSG, (int)strlen(ERR_MSG), 0,
                   (struct sockaddr *)&client_addr, client_len);
            printf("File not found. Error sent to client.\n\n");
            continue;
        }

        chunks = 0;
        total = 0;
        while ((n = (int)fread(buffer, 1, BUF_SIZE, fp)) > 0) {
            sendto(server_sock, buffer, n, 0, (struct sockaddr *)&client_addr, client_len);
            chunks++;
            total += n;
            Sleep(1); /* small gap so the receiver does not drop datagrams */
        }
        fclose(fp);

        sendto(server_sock, END_MSG, (int)strlen(END_MSG), 0,
               (struct sockaddr *)&client_addr, client_len);
        printf("File sent: %ld bytes in %d datagrams.\n\n", total, chunks);
    }

    closesocket(server_sock);
    WSACleanup();
    return 0;
}
