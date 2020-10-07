Para gerar so resultados execute:
```sh
make run_tests
```
A build será feita automaticamente antes de rodar os testes
Serão gerados dois arquivos com extensão csv com os resultados dos testes a e b.

Para gerar os gráficos basta executar:
```
python3 generate_charts.py
```

Os arquivos serão salvos como .png na pasta images (será criada caso não exista)

Talvez algumas depêndencias precisem ser instaladas antes de conseguir executar o script corretamente. Para descobrir quais as dependências que faltam, basta rodar o script e no log de erro será mostrado o que está faltando