# TCP Matrix Classification

Enter an `n × n` integer matrix in the client (`1 ≤ n ≤ 10`). The server identifies whether it is a diagonal, upper-triangular, lower-triangular, or ordinary matrix.

```sh
gcc -Wall -Wextra server.c -o server
gcc -Wall -Wextra client.c -o client
./server
./client
```
