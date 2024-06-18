from happyLittleTree import decrypt

def build_level(positions, dim):
    blocks = max(positions) // dim + 1
    level = ['0']*dim*blocks
    for pos in positions:
        level[pos]='1'
    level = [''.join(level[i:i+dim]) for i in range(0, len(level), dim)]
    level = [x for x in level if int(x) != 0]
    return level

def parsePos():
    littleTree = []
    dim = int(input())
    level = input()
    # leer hasta que haya un input vacío
    while level:
        positions = level[level.find(':')+1:].strip().split(' ')
        positions = [int(x) for x in positions]
        littleTree.append(build_level(positions, dim))
        level = input()

    return littleTree

def main():
    while True:
        print(decrypt(parsePos()))

main()
