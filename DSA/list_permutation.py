# Print all the permutations of a list
# O(n!)

from itertools import permutations

def permute(data: list, i: int, length: int) -> None:
   if i == length:
      print(data)
   else:
      for j in range(i, length):
         data[i], data[j] = data[j], data[i]
         permute(data, i + 1, length)
         data[i], data[j] = data[j], data[i]

def main():
   data = ['a', 'b', 'c']
   permute(data, 0, len(data))
   print(list(permutations(data)))

if __name__ == "__main__":
   main()
