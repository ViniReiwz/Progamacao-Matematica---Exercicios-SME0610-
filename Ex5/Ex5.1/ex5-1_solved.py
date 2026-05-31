import pyscipopt as pcp

# Recebendo as variáveis a[n], na forma de valores separados por espaço (a1 a2 a3)
vals = input()  # Chega no formato de string 'a1 a2 a3'

# Cria uma lista de números reais, seprando cada valor pelos espaços em branco
# 'a1 a2 a3' ==> [a1,a2,a3]
a: list[float] = vals.split()

# Iniciando modelagem
model = pcp.Model()

# Adicionando variáveis:
x1 = model.addVar(name='x1',vtype='C',lb=0, ub=10) # x1 pertence aos Reais não-negativos ( x1 >= 0)
x2 = model.addVar(name='x2',vtype='C',lb=0, ub=10) # x2 pertence aos Reais não-negativos (x2 >= 0 )
x3 = model.addVar(name='x3',vtype='I',lb=0, ub=10) # x3 pertence aos Inteiros não-negativos (x2 >= 0 )

# Adicionando restrições:
model.addCons(a[0]*x1 + a[1]*x2 + a[2]*x3 <= 12)

# Função objetivo
model.setObjective(1.1*x1 + 1.2*x2 + 1.3*x3, sense='maximize')

# Otimizando:
model.hideOutput()
model.optimize()

# Verifica se o resultado é possível (se não, status retorna infeasible)
if (model.getStatus() != 'infeasible'):
    # Exibindo resultados com 2 casas decimais de precisão
    print(round(model.getObjVal(),2))

else:
    print("INFACTÍVEL")
