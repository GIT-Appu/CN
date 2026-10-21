# TCP Multi-User Chat

Threaded server that broadcasts every message to all other connected users. Start one server and multiple clients.

```sh
gcc -Wall -Wextra -pthread server.c -o server
gcc -Wall -Wextra -pthread client.c -o client
./server
./client       # run in two or more separate terminals
```

This is a learning example: it has no authentication or encryption.
