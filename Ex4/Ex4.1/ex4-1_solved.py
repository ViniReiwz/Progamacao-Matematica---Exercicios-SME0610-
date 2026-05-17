import pyscipopt as pcp

# Recebendo a variável 'b' da entrada:
b = float(input())

# Iniciando modelagem
model = pcp.Model()

# Adicionando variáveis:
x1 = model.addVar(name='x1',vtype='C',lb=0) # x1 pertence aos Reais não-negativos ( x1 >= 0)
x2 = model.addVar(name='x2',vtype='I',lb=0) # x2 pertence aos Inteiros não-negativos (x2 >= 0 )

# Adicionando restrições:
model.addCons(x1 + x2 <= b)
model.addCons(x1 <= 10)
model.addCons(x2 <= 10)

# Função objetivo
model.setObjective(x1-x2, sense='minimize')

# Otimizando:
model.hideOutput()
model.optimize()

# Exibindo resultados com 2 casas decimais de precisão
print(round(model.getObjVal(),2))
print(round(model.getVal(x1),2))
print(round(model.getVal(x2),2))
