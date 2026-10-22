/* Experiment 8 - UDP File Transfer Client (port 6000) */
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#define PORT 6000
#define BUF_SIZE 1024
#define END_MSG "__EOF__"
#define ERR_PREFIX "__ERROR__"

int main(int argc, char *argv[])
{
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server_addr, from_addr;
    int from_len;
    char ip[64], filename[256], outname[300], buffer[BUF_SIZE + 1];
    FILE *fp;
    int n, chunks = 0;
    long total = 0;
    DWORD timeout = 5000;

    if (argc > 2) {
        strncpy(ip, argv[1], sizeof(ip) - 1);       ip[sizeof(ip) - 1] = '\0';
        strncpy(filename, argv[2], sizeof(filename) - 1); filename[sizeof(filename) - 1] = '\0';
    } else {
        printf("Enter server IP (127.0.0.1 for same PC): ");
        scanf("%63s", ip);
        printf("Enter file name to request: ");
        scanf("%255s", filename);
    }

    WSAStartup(MAKEWORD(2, 2), &wsa);
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(PORT);

    sendto(sock, filename, (int)strlen(filename), 0,
           (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Requested '%s' from %s:%d\n", filename, ip, PORT);

    sprintf(outname, "received_%s", filename);
    fp = NULL;

    while (1) {
        from_len = sizeof(from_addr);
        n = recvfrom(sock, buffer, BUF_SIZE, 0, (struct sockaddr *)&from_addr, &from_len);
        if (n == SOCKET_ERROR) {
            printf("Timed out waiting for server (is it running? firewall?).\n");
            break;
        }
        if (n == (int)strlen(END_MSG) && memcmp(buffer, END_MSG, n) == 0) {
            if (fp == NULL) fp = fopen(outname, "wb"); /* empty file */
            printf("File received: %ld bytes in %d datagrams -> %s\n", total, chunks, outname);
            break;
        }
        if (n >= (int)strlen(ERR_PREFIX) && memcmp(buffer, ERR_PREFIX, strlen(ERR_PREFIX)) == 0) {
            buffer[n] = '\0';
            printf("Server: %s\n", buffer + strlen(ERR_PREFIX) + 1);
            break;
        }
        if (fp == NULL) fp = fopen(outname, "wb");
        fwrite(buffer, 1, n, fp);
        chunks++;
        total += n;
    }

    if (fp) fclose(fp);
    closesocket(sock);
    WSACleanup();
    return 0;
}
