# Atividade Prática 2

## Testes

Os seguintes parâmetros de testes estão definidos no arquivo **test.h**:

```TESTS_PER_SIZE```: determina quantos vezes o teste será executado para cada tamanho de mensagem.

```MESSAGES_PER_SIZE```: determina quantas mensagens serão enviadas a cada teste. Esse parâmetro é muito útil para quando se quer que os resultados sejam gerados rapidamente.

<br>

Para rodar os testes, execute:
```sh
make run_tests
```
Será feita a build dos códigos necessários. Após isso os testes serão executados. Os resultados ficarão disponíveis em arquivos CSV na raiz dessa pasta.

<br>

## Resultados

Para gerar os gráficos, os resultados precisão estar disponíveis na raiz dessa pasta.

Para gerar os gráficos dos resultados obtidos, execute:

```
python3 generate_charts.py
```

Os arquivos serão salvos como PNG na pasta **images**. Caso essa pasta não exista, ela será criada automaticamente.

Ao rodar o script, talvez ocorram erros por conta de depêndencias faltantes. Caso isso ocorra, as dependências faltantes serão descritas no log de erro.