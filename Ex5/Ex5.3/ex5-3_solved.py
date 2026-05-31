import pyscipopt as pcp

# Número de linhas 'n' e colunas 'm' da matriz de constantes
n: int = int(input())   # Além do número de linhas, n representa o número de restrições do problema
m = 3


# Cria uma lista de listas (matriz) de floats vazia (matriz de constantes a)
a: list[list[float]] = []

count = 0   # Variável auxiliar
while True:
    vals: list[float] = input().split()   # Pega a entrada no formato (i j k) e converte pra uma lista

    if(len(vals) > m):  # Verifica se o número de colunas da lista btida não ultrapassa m
        print(f"O número máximo de valores por linha é de {m} !")
    else:               # Caso não, atribui a matriz e incrementa o contador de linhas inseridas
        a.append(vals)
        count += 1
    if (count == n):    # Termina o loop ao inserir todas as linhas
        break

# Iniciando modelagem
model = pcp.Model()

# Adicionando variáveis:
x1 = model.addVar(name='x1',vtype='C',lb=0) # x1 pertence aos Reais não-negativos ( x1 >= 0)
x2 = model.addVar(name='x2',vtype='C',lb=0) # x2 pertence aos Reais não-negativos (x2 >= 0 )
x3 = model.addVar(name='x3',vtype='I',lb=0) # x3 pertence aos Inteiros não-negativos (x2 >= 0 )

# Adicionando restrições:
for i in range(0,n):
    model.addCons(a[i][0]*x1 + a[i][1]*x2 + a[i][2]*x3 <= 0)

# Função objetivo
model.setObjective(10*x1 + 5*x2 + x3, sense='maximize')

# Otimizando:
model.hideOutput()
model.optimize()

status = model.getStatus()

# Verifica se o resultado é possível (se não, status retorna infeasible)
if (status == 'infeasible'):
    print("INFACTÍVEL")

# Verifica s eo resultado é finito (se não, status retorna unbounded)
elif(status == 'unbounded'):
    print("ILIMITADO")
    
else:
    # Exibindo resultados com 2 casas decimais de precisão
    print(round(model.getObjVal(),2))
