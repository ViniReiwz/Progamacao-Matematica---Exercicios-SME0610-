import pyscipopt as pcp

# Iniciando modelagem
model = pcp.Model()

# Cria vetor bidimensional que contém x1 e x2 (x pertence aos pares de inteiros positivos [Z²+])
x = []
for i in range(0,2):
    x.append(model.addVar(name=f"x{i+1}", vtype="I"))

# Adicionando as restrições:
model.addCons(9*x[0] + 5*x[1] <= 45)    # 9x1 + 5x2 <= 45
model.addCons(-4*x[0] + 5*x[1] <= 5)    # -4x1 + 5x2 <=5

# Função objetivo: Max(10x1 + 6x2)
model.setObjective(10*x[0] + 6*x[1], sense="maximize")

# Esconde as informações de output e otimiza o resultado
model.hideOutput()
model.optimize()

print(model.getObjVal())