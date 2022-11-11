import math

DEBUG = 0

def decrypt(littleTree):
  dims = int(math.log2(len(littleTree[0][0])))
  binary_tuples = [['',] * dims]

  for level in littleTree:
    new_binary_tuples = []
    if DEBUG:
      print('level:', level)

    for i in range(len(level)):
      node = level[i]
      binary_tuple = binary_tuples[i]
      if DEBUG:
        print('  current node:', node, binary_tuple)

      for pos in range(len(node)):
        if int(node[pos]):
          new_binary_tuple = binary_tuple.copy()

          # transformar posicion en binario de dims bits y agregar a la tupla
          bin_pos = format(pos, f'0{dims}b')
          for k in range(dims):
            new_binary_tuple[k] += bin_pos[k]

          new_binary_tuples.append(new_binary_tuple)
          if DEBUG:
            print(f'    1 found on position {pos} ({bin_pos}), built {new_binary_tuples[-1]}')

    binary_tuples = new_binary_tuples
    if DEBUG:
      print('tuples:', binary_tuples, '\n')

  # convertir binarios a enteros
  pairs = []
  for binary_tuple in binary_tuples:
    pairs.append([int(binary, 2) for binary in binary_tuple])

  return pairs

def parseTree():
  littleTree = []

  level = input()
  # leer hasta que haya un input vacío
  while level:
    littleTree.append(level[level.find(':')+1:].strip().split(' '))
    level = input()

  return littleTree

def main():
  while True:
    print(decrypt(parseTree()), '\n')

  return

print('holi puh')
main()
