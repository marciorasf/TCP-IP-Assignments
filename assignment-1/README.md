# Trabalho 1

## Importante!

Alguns scripts utilizam o ZShell e o Konsole (KDE). Caso sejam necessárias versões utilizando bash e terminal, é só fazer uma cópia e alterar o necessário.

## Experimentos

Os experimentos sâo baseados nos exercícios do capítulo 1 do livro Peterson, Davie: Computer Networks: A Systems Aproach, 5th Edition. 

    1. (Setup) Implementar código de servidor e cliente descrito na seção 1.4 do livro.

    2. Experimento 1: Fazer exercício 32.

    3. Experimento 2: Fazer exercício 33.

    4. Experimento 3: Fazer exercício 34.

## Organização das pastas

- A pasta original contém os arquivos tais como escritos no livro, com modificações apenas para fazê-los compilar e executar corretamente.
  
- A pasta setup contém as modificações feitas baseadas nos comentários do professor.
  
- O código de cada experimento, está em uma pasta separada. Para implementação dos experimentos, deve-se modificar o mínimo possível para facilitar a localização das modificações.


## Como executar 

  1. Mova o terminal para a pasta contendo os arquivos desejados.
   ```
   $ cd experiment-1
   ```

  2. Execute o Makefile para compilar os arquivos. O nome dos executáveis gerados são: server.out e client.out.
   ```
   $ make
   ```

  3. No arquivo run_client.sh, troque o IP pelo seu IP local. O IP local pode ser obtido com o comando:
   ```
   $ hostname -I
   ```

  4. Execute o script run_server.sh.
   ```
    $ ./run_server.sh
   ```

  5. Em outro terminal, execute o script run_client.sh.
   ```
   $ ./run_client.sh
   ```

  6. Se tudo der certo, agora tanto o servidor quanto o cliente estarão ativos e prontos para uso.