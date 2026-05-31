import pyscipopt as pcp

# Número de linhas 'n' e colunas 'm' da matriz de constantes

m: int = int(input())   # Além do número de colunas, m representa o número de variáveis do problema

n: int = int(input())   # Além do número de linhas, n representa o número de restrições do problema


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

x_list: list = []

# Adicionando variáveis:
for i in range(0,m):
    x_list.append(model.addVar(name=f"x{i}", vtype="C",lb=0))   # m variáveis reais

# Adicionando restrições:
for i in range(0,n):

    # Para cada i, faz com que o somatório de a[i][j]*x[j] seja <= 10, criando as n restrições com as m variáveis (e colunas) -> pcp.quicksum faz esse somatório
    model.addCons(pcp.quicksum(
        a[i][j] * x_list[j] for j in range(0,m)
    ) <= 10)

# Função objetivo
model.setObjective(pcp.quicksum(x_list[i] for i in range(0,m)), sense='maximize')

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
