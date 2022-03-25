str = ''
for line in open('Python\yeast_gene.fa').readlines():
    if line[0] == '>': continue        
    else: str += line.strip()                
print(str.count('A') + str.count('T') + str.count('C') + str.count('G'), str.count('C') + str.count('G'), str.count('CG'))