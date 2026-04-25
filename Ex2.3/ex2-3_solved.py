import pyscipopt as pcp

# Iniciando modelagem
model = pcp.Model()

# Adicionando variáveis do problema
x1 = model.addVar(name="x1", vtype="C") # Variável contínua
x2 = model.addVar(name="x2", vtype="I") # Variável inteira

# Adicionando as restrições:
model.addCons(9*x1 + 5*x2 <= 45)
model.addCons(-4*x1 + 5*x2 <= 5)

# Função objetivo: Max(10x1 + 6x2)
model.setObjective(10*x1 + 6*x2, sense="maximize")

# Esconde as informações de output e otimiza o resultado
model.hideOutput()
model.optimize()

# Exibe o resultado final e os valores de x1 e x2
print(f'{model.getObjVal():.2f}')
print(f'{model.getVal(x1):.2f}')
print(f'{model.getVal(x2):.1f}')