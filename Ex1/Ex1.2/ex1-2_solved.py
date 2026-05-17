import pyscipopt as pcp

# Iniciando modelagem
model = pcp.Model()

# Lista de variáveis (armazena x1, x2 e x3)
var_list = []

# Cria todas as variáveis do tipo contínupo (vtype='C'), com nome x{i+1}
for i in range(0,3):
    var_list.append(model.addVar(name=f"x{i+1}", vtype="C"))

# Adicionando as restrições
model.addCons((0.2 * var_list[0]) + (0.5 * var_list[1]) + (0.4 * var_list[2]) >= 0.3)
model.addCons((0.6 * var_list[0]) + (0.4 * var_list[1]) + (0.4 * var_list[2]) >= 0.5)

# Função objetivo: Mín(0.56x1 + 0.81x2 + 0.46x3)
model.setObjective((0.56 * var_list[0]) + (0.81 * var_list[1]) + (0.46 * var_list[2]),sense='minimize')

# Esconde as informações de output e otimiza o resultado
model.hideOutput()
model.optimize()

print(model.getObjVal())