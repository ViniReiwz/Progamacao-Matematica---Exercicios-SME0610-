import pyscipopt as pcp

# Recebendo a variável 'c' da entrada:
c = int(input())

# Iniciando modelagem
model = pcp.Model()

# Adicionando variáveis:
x1 = model.addVar(name='x1',vtype='C',lb=0) # x1 pertence aos Reais não-negativos ( x1 >= 0)
x2 = model.addVar(name='x2',vtype='I',lb=0) # x2 pertence aos inteiros não-negativos (x2 >= 0 )

# Adicionando restrições:
model.addCons(10*x1 + 18*x2 <= 52)
model.addCons(-1*x1 + x2 <= 2)

# Função objetivo
model.setObjective((c * x1) + (c+4)*x2, sense='maximize')

# Otimizando:
model.hideOutput()
model.optimize()

# Exibindo resultados com 2 casas decimais de precisão
print(round(model.getObjVal(),2))
print(round(model.getVal(x1),2))
print(round(model.getVal(x2),2))