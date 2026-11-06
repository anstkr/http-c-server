# compile command:
gcc server.c -o server
gcc client.c -o client

# run commands:
./server
./client

gcc -o server server.c && ./server
gcc -o client client.c && ./client