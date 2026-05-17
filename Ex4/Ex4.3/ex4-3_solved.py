import pyscipopt as pcp

# Recebendo as variáveis b[n], na forma de valores separados por espaço (b1 b2 b3 b4)
vals = input()  # Chega no formato de string 'b1 b2 b3 b4'

# Cria uma lista, seprando cada valor pelos espaços em branco
# 'b1 b2 b3 b4' ==> [b1,b2,b3,b4]
b_list = vals.split()

# Iniciando modelagem
model = pcp.Model()

# Adicionando variáveis:
x1 = model.addVar(name='x1',vtype='C',lb=0) # x1 pertence aos Reais não-negativos ( x1 >= 0)
x2 = model.addVar(name='x2',vtype='I',lb=0) # x2 pertence aos Inteiros não-negativos (x2 >= 0 )

# Adicionando restrições:
model.addCons(-1*x1 + x2 >= b_list[0])
model.addCons(x1 + x2 <= b_list[1])
model.addCons(x1 >= b_list[2])
model.addCons(x2 >= b_list[3])

# Função objetivo
model.setObjective(x1 + 2*x2, sense='minimize')

# Otimizando:
model.hideOutput()
model.optimize()

# Verifica se o resultado é possível (se não, status retorna infeasible)
if (model.getStatus() != 'infeasible'):
    # Exibindo resultados com 2 casas decimais de precisão
    print(round(model.getObjVal(),2))
    print(round(model.getVal(x1),2))
    print(round(model.getVal(x2),2))

else:
    print("INFACTÍVEL")
