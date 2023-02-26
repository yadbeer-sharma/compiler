nonts = []
with open("grammar.txt", "r") as f:
    for line in f:
        word = ""  
        flag = 0      
        for c in line:
            if c == '<':
                flag = 1
                #word += c
            elif c == '>':
                #word += c
                flag = 0
                #if word not in nonts:
                nonts.append(word)
                word = ""
            else:
                if flag == 1:
                    word += c
f.close()


print("\n")


hashvals = []
uniq = sorted(set(nonts))

# primenos = [307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397]

# for j in range(0, len(primenos)):
#     hashvals = []
#     for word in uniq:
#         hashvals.append((sum(ord(c) for c in word) - 60 * len(word)) % primenos[j] + 100)    
#     print(len(set(hashvals)), primenos[j])
#     print("\n")

for word in uniq:
        hashvals.append((sum(ord(c) for c in word) - 60 * len(word)) % 389 + 100)

for i in range(0, len(hashvals)):
    print(uniq[i], hashvals[i])

# print(*sorted(hashvals))

print("\n")
print(len(set(nonts)))
print(len(set(hashvals)))
print(max(hashvals))
print(min(hashvals))
print("\n")

enums = "{\n"
for i in range(0, len(hashvals)):
    enums += "\t"
    enums += (uniq[i])
    enums += (" = ")
    enums += str(hashvals[i])
    enums += (",\n")
enums += "};\n"

print(enums)