//-----------------------CLIENT----------------------
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const* argv[])
{
    int size = 1024;
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[size];
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "172.20.10.7", &serv_addr.sin_addr)
        <= 0) {
        printf(
                "\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    int n = 1;
    int sended;
    FILE *ptr;
    ptr = fopen(argv[1],"rb");

    if(ptr != NULL) {
        while(n) {
            memset(buffer,0,size);
            n = fread(buffer,1,size,ptr);
            do{
                sended += send(sock, buffer, n, 0);
            } while(n - sended);
            sended = 0;
        }
    } else {
        printf("File Error");
    }

    // closing the connected socket
    close(client_fd);
    return 0;

}
