# Atividade Prática 2

Essa atividade consiste em fazer as letras **a** e **b** da questão 48 utilizando apenas o protocolo UDP, do livro Redes de Computadores: Uma Abordagem de Sistemas, Quinta Edição.

## Testes

Os seguintes parâmetros de testes estão definidos no arquivo **test.h**:

```TESTS_PER_SIZE```: determina quantos vezes o teste será executado para cada tamanho de mensagem.

```MESSAGES_PER_SIZE```: determina quantas mensagens serão enviadas a cada teste. Esse parâmetro é muito útil para quando se quer que os resultados sejam gerados rapidamente.

Para alterar o IP do servidor utilizado pelo cliente, basta colocar o IP dentro das aspas na última linha do **makefile**

<br>

Para rodar os testes localmente, execute:
```sh
make run_local_tests
```
Será feita a build dos códigos necessários. Após isso os testes serão executados. Dois terminais serão abertos, o terminal do cliente mostrará o progresso dos testes. Ao terminar, o terminal do cliente fechará automaticamente, mas o do servidor não. Então, uma indicação de que o teste terminou é quando um dos terminais fecha.

Os resultados ficarão disponíveis em arquivos CSV na raiz dessa pasta.

<br>

## Resultados

Para gerar os gráficos, os resultados precisão estar disponíveis na raiz dessa pasta.

Para gerar os gráficos dos resultados obtidos, execute:

```
python3 generate_charts.py
```

Os arquivos serão salvos como PNG na pasta **images**. Caso essa pasta não exista, ela será criada automaticamente.

Ao rodar o script, talvez ocorram erros por conta de depêndencias faltantes. Caso isso ocorra, as dependências faltantes serão descritas no log de erro.