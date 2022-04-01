#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MYPORT 9002

int main() {
    int srv_sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in srv_addr = {.sin_family = AF_INET,
                                   .sin_port = htons(MYPORT),
                                   .sin_addr.s_addr = INADDR_ANY};

    if (bind(srv_sock, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) == -1) {
        puts("Oshibka privyazki!");
        return -1;
    }

    listen(srv_sock, 10);

    while (1) {
        printf("Ozhidayem soyedineniye cherez port %d...\n", MYPORT);

        int clnt_sock = accept(srv_sock, NULL, NULL);

        char response[64] = {0};
        recv(clnt_sock, response, sizeof(response), 0);
        printf("Poluchenniy text: %s\n", response);

        char msg[64] = {0};
        unsigned int size = strlen(response);
        sprintf(msg, "Spasibo za zapros v %u simvolov", size);
        send(clnt_sock, msg, sizeof(msg), 0);

        close(clnt_sock);

        if (strstr(response, "<TheEnd>")) {
            puts("Server zavershil soedineniye s klientom");
            break;
        }
    }

    close(srv_sock);
    return 0;
}
