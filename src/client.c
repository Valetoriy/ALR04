#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MYPORT 9002

int main() {
    while (1) {
        int net_sock = socket(AF_INET, SOCK_STREAM, 0);

        struct sockaddr_in srv_addr = {.sin_family = AF_INET,
                                       .sin_port = htons(MYPORT),
                                       .sin_addr.s_addr = INADDR_ANY};

        if (connect(net_sock, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) ==
            -1) {
            puts("Oshibka soedineniya!");
            return -1;
        } else
            puts("Soedineniye ustanovleno");

        char msg[64] = {0};
        puts("Vvedite soobsheniye:");
        fgets(msg, sizeof(msg), stdin);
        send(net_sock, msg, sizeof(msg), 0);

        char response[64] = {0};
        recv(net_sock, response, sizeof(response), 0);
        printf("Otvet ot servera: %s\n\n", response);

        close(net_sock);

        if (strstr(msg, "<TheEnd>")) break;
    }

    return 0;
}
