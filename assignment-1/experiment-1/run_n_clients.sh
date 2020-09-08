#!/bin/zsh
nClients=10

for client in {1..$nClients}; do
    konsole -e "bash -c './run_client.sh <<< client$client'" &;
done;