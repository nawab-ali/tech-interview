# You are given the heads of two sorted linked lists list1 and list2. Merge the two lists into one sorted list.
# The list should be made by splicing together the nodes of the first two lists. Return the head of the merged linked
# list.
#
# Input: list1 = [1,2,4], list2 = [1,3,4]
# Output: [1,1,2,3,4,4]
#
# Input: list1 = [], list2 = []
# Output: []
#
# Input: list1 = [], list2 = [0]
# Output: [0]
#
# Constraints:
# The number of nodes in both lists is in the range [0, 50].
# -100 <= Node.val <= 100
# Both list1 and list2 are sorted in non-decreasing order.

# O(n + m) 
def merge_sorted_lists(list1: list, list2: list) -> list:
    i = 0
    j = 0
    sorted_list = []

    while i < len(list1) and j < len(list2):
        if list1[i] < list2[j]:
            sorted_list.append(list1[i])
            i = i + 1
        else:
            sorted_list.append(list2[j])
            j = j + 1
    
    while i < len(list1):
        sorted_list.append(list1[i])
        i = i + 1
    
    while j < len(list2):
        sorted_list.append(list2[j])
        j = j + 1
    
    return sorted_list

if __name__ == "__main__":
    print(merge_sorted_lists([1,2,4], [1,3,4]))
    print(merge_sorted_lists([], []))
    print(merge_sorted_lists([], [0] ))
