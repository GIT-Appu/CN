# TCP Matrix Classification

The client sends an `n × n` integer matrix. The server counts its positive, negative, and zero elements and returns the three counts. Integers are sent in network byte order.

```sh
gcc -Wall -Wextra server.c -o server
gcc -Wall -Wextra client.c -o client
./server
./client
```
