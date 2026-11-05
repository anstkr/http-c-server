# compile command:
gcc client.c -o client
gcc server.c -o server

# run commands:
./server
./client

gcc -o client client.c && ./client
gcc -o server server.c && ./server