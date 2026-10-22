# TCP Basic Client–Server

Demonstrates reliable, connection-oriented communication. The client sends a greeting and the server replies.

```sh
gcc -Wall -Wextra server.c -o server
gcc -Wall -Wextra client.c -o client
./server              # terminal 1
./client              # terminal 2
```

Expected result: the server prints `Hello from client`; the client prints `Hello from server`.
