import pyscipopt as pcp

# Instancia um objeto para a modelagem
model = pcp.Model()

# Adiciona as variáveis da modelagem, x1 e x2, no caso, variáveis inteiras
x1 = model.addVar(name="x1", vtype="I", ub=2) # ub == upper bound, ou seja, o maior valor de x1 é 2 (já que x1 <= 2 e x1 é inteiro)
x2 = model.addVar(name="x2", vtype="I", ub=3) # ub == upper bound, ou seja, o maior valor de x1 é 3 (já que x2 <= 3 e x2 é inteiro)

# PS: O lb (lower bound) é definido por padrão como 0, dessa forma, temos as restrições:    
# 0 <= x1 <= 2
# 0 <= x2 <= 3

# Adicionando as restrições adicionais 
model.addCons(x1 + x2 <= 4)

# Função objetivo: Max(x1 + 2x2)
model.setObjective(x1 + 2*x2, sense="maximize")

# Esconde as informações de output
model.hideOutput()

# Otimiza (encontra a solução)
model.optimize()

# Exibe o resultado final
print(model.getObjVal())