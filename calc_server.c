/* Experiment 7(b) - TCP Calculator / Factorial Server (port 5001)
   Queries: "12 + 5", "7 * 3", "10 / 4", "9 - 2", "2 ^ 8", "fact 5" or "5!" */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <winsock2.h>

#define PORT 5001
#define BUF_SIZE 1024

static void compute(const char *q, char *out)
{
    double a, b;
    char op, bang;
    int n;
    unsigned long long f = 1;

    if (sscanf(q, "fact %d", &n) == 1 ||
        (sscanf(q, "%d%c", &n, &bang) == 2 && bang == '!')) {
        if (n < 0 || n > 20) { strcpy(out, "Error: factorial supported for 0 to 20"); return; }
        for (int i = 2; i <= n; i++) f *= i;
        sprintf(out, "%d! = %llu", n, f);
        return;
    }
    if (sscanf(q, "%lf %c %lf", &a, &op, &b) != 3) {
        strcpy(out, "Invalid query. Examples: 12 + 5 | 7 * 3 | 2 ^ 8 | fact 5");
        return;
    }
    switch (op) {
    case '+': sprintf(out, "%g + %g = %g", a, b, a + b); break;
    case '-': sprintf(out, "%g - %g = %g", a, b, a - b); break;
    case '*': sprintf(out, "%g * %g = %g", a, b, a * b); break;
    case '/':
        if (b == 0) strcpy(out, "Error: division by zero");
        else sprintf(out, "%g / %g = %g", a, b, a / b);
        break;
    case '%':
        if ((long)b == 0) strcpy(out, "Error: modulo by zero");
        else sprintf(out, "%ld %% %ld = %ld", (long)a, (long)b, (long)a % (long)b);
        break;
    case '^': sprintf(out, "%g ^ %g = %g", a, b, pow(a, b)); break;
    default:  strcpy(out, "Unknown operator. Use + - * / % ^");
    }
}

int main(void)
{
    WSADATA wsa;
    SOCKET server, client;
    struct sockaddr_in server_addr, client_addr;
    int client_len = sizeof(client_addr);
    char buffer[BUF_SIZE], result[BUF_SIZE];
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
    printf("Calculator Server started on port %d. Waiting for client...\n", PORT);

    client = accept(server, (struct sockaddr *)&client_addr, &client_len);
    printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));
    send(client, "Hello from Calculator Server!", 29, 0);

    while ((n = recv(client, buffer, BUF_SIZE - 1, 0)) > 0) {
        buffer[n] = '\0';
        printf("Query: %s\n", buffer);
        if (strcmp(buffer, "exit") == 0 || strcmp(buffer, "bye") == 0) break;
        compute(buffer, result);
        send(client, result, (int)strlen(result), 0);
        printf("Result: %s\n", result);
    }

    printf("Client disconnected.\n");
    closesocket(client);
    closesocket(server);
    WSACleanup();
    return 0;
}
