# Concurrent UDP File Server

Requests are filenames. A child process sends the requested file in 1024-byte UDP datagrams; the client writes them to `received_<filename>`.

```sh
gcc -Wall -Wextra server.c -o server
gcc -Wall -Wextra client.c -o client
./server
./client
```

Run the client from a separate directory or request only a controlled test file. This small lab protocol does **not** implement sequencing, retransmission, or safe path validation, so it is suitable only for localhost demonstrations.
