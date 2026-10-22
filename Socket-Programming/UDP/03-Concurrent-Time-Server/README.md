# Concurrent UDP Time Server

The server creates a child process for every time request, allowing other datagrams to be handled without waiting for a client-specific task.

```sh
gcc -Wall -Wextra server.c -o server
gcc -Wall -Wextra client.c -o client
./server
./client
```

On production systems, reap child processes and authenticate requests; those concerns are kept out of this compact lab illustration.
