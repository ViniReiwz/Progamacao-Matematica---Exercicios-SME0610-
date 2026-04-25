import pyscipopt as pcp

# Iniciando modelagem
model = pcp.Model()

# Cria vetor bidimensional que contém x1 e x2, variáveis binárias
x = []
for i in range(0,2):
    x.append(model.addVar(name=f"x{i+1}", vtype="B"))

# Adicionando as restrições:
model.addCons(6*x[0] + 8*x[1] <= 10)    # 6x1 + 8x2 <= 10

# Função objetivo: Max(10x1 + 6x2)
model.setObjective(2*x[0] + 3*x[1], sense="maximize")

# Esconde as informações de output e otimiza o resultado
model.hideOutput()
model.optimize()

# Exibe o resultado final e os valores de x1 e x2
print(model.getObjVal())
for xn in x:
    print(model.getVal(xn)) 