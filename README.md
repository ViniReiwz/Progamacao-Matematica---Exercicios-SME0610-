Os exercícios neste repositório utilizam da bilbioteca `pySCIPOpt` para a modelagem e otimização dos problemas matemáticos.

Através dela, é possível adicionar variáveis, restrições e indicar a função objetivo do problema, bem como extrair informaçõs importantes da mesma.

# Iniciando a modelagem:

Inicialmente, importamos a biblioteca:
```python
    import pyscipopt as pcp
```
> Utilizaremos pcp para nos referir à biblioteca.

Agora, é necessário instanciar o ambiente de modelagem, fazemos de tal forma que:

```python
    model = pcp.Model()
```
onde `model` é nosso objeto da modelagem, e através dele adicionaremos todas as informações importantes.

# Adicionando variáveis

Através da isntancia da modelagem, podemos adicionar as variáveis do nosso problema, neste caso, adicionemos uma variável contínua e outra inteira:

```python
    x1 = model.addVar(name='x1', vtype='C', lb=-0.5, ub=1.7)
    x2 = model.addVar(name='x2', vtype='I', lb=0, ub=100)
```

Temos adicionados ao nosso problema agora, uma variável contínua `x1` e outra inteira `x2`

> Além de **C** (Contínua) e **I** (Inteira), têm-se também o tipo **B** (Binária), sempre especificado em vtype

Notemos ainda que `lb` e `ub` referem-se respectivamente à lower-bound e upper-bound, ou seja, os limites inferiores e superiores que aquela variável pode assumir, dessa forma, temos algo como:

> -0.5 <= x1 <= 1.7; 0 <= x2 <=1 00

# Adicionando restrições

Adicionar restrições ao problema é tão simples quanto adicionar variáveis. COnsiderando as mesmas variáveis x1 e x2, digamos que queremos:

> x1 + x2 <= 100
e
> 100x1 - 32x2 > 30

Façamos então:
```python
    model.addCons(x1 + x2 <= 100)
    model.addCons(100*x1 - 32*x2 > 30)
```
e temos as restrições adicionadas à modelagem.

# Função objetivo

Por fim, desejamos encontrar os valores das variáveis e os valores desejados para determinada função que relaciona as duas. Por exemplo, digamos que, dada as restrições anteriores, desejemos:

> Mín(22.5x1 + 15x2)

Logo, basta fazer:
```python
    model.setObjective(22.5*x1 + 15*x2, sense="minimize")
```

> Note que o parâmetro `sense` determina se queremos minimizar (_minimize_) ou maximizar (_maximize_)

# Resolvendo

Com um único método 
```python
    model.optimize()
```
O problema é otimizado de acordo com as restrições, variáveis e objetivos discutidos anteriormente.


# Adicional:

```python
    model.getVal(x1)    # Retorna o valor da variável x1
```

```python
    model.getObjVal(x1) # Retorna o valor ótimo da função objetivo
```

```python
    model.hideOutput()  # Esconde as informações sobre a resolução do problema (Utilize antes de model.optimize() para omitir a saida do método)
```
