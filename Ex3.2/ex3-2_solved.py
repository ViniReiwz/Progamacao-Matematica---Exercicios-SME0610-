import pyscipopt as pcp

# Recebendo a variável 'c' da entrada:
c = float(input())

# Iniciando modelagem
model = pcp.Model()

# Adicionando variáveis:
x1 = model.addVar(name='x1',vtype='C',lb=0) # x1 pertence aos Reais não-negativos ( x1 >= 0)
x2 = model.addVar(name='x2',vtype='I',lb=0) # x2 pertence aos Inteiros não-negativos (x2 >= 0 )

# Adicionando restrições:
model.addCons(5*x1 + x2 <= 100)
model.addCons(x1 - x2 <= 15)
model.addCons(-1*x1 + 12*x2 <= 225)
model.addCons(x1 + x2 >= 10)
model.addCons(x1 <= 20)
model.addCons(x2 <= 20)

# Função objetivo
model.setObjective(c * (c*x1 + x2), sense='minimize')

# Otimizando:
model.hideOutput()
model.optimize()

# Exibindo resultados com 2 casas decimais de precisão
print(round(model.getObjVal(),2))
print(round(model.getVal(x1),2))
print(round(model.getVal(x2),2))