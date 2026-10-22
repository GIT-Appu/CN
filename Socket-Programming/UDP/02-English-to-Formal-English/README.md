# UDP English-to-Formal-English

The server maps a small set of informal phrases to formal alternatives. It is deliberately easy to extend: add entries in `formalize()`.

```sh
gcc -Wall -Wextra server.c -o server
gcc -Wall -Wextra client.c -o client
./server
./client
```
