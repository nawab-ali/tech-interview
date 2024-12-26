# Given the head of a singly linked list, return the middle node of the linked list. If there are two middle
# nodes, return the second middle node.
#
# Example 1:
# Input: head = [1,2,3,4,5]
# Output: [3,4,5]
# Explanation: The middle node of the list is node 3.
#
# Example 2:
# Input: head = [1,2,3,4,5,6]
# Output: [4,5,6]
# Explanation: Since the list has two middle nodes with values 3 and 4, we return the second one.
#
# Constraints:
# The number of nodes in the list is in the range [1, 100].
# 1 <= Node.val <= 100

from typing import Optional

class ListNode:
    def __init__(self, val: int = 0, next: Optional['ListNode'] = None):
        self.val = val
        self.next = next

def middleNode(head: Optional[ListNode]) -> Optional[ListNode]:
    slow = fast = head

    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    
    return slow

if __name__ == "__main__":
    # Create a linked list with values 1 to 5
    node5 = ListNode(5)
    node4 = ListNode(4, node5)
    node3 = ListNode(3, node4)
    node2 = ListNode(2, node3)
    head = ListNode(1, node2)
    
    # Find the middle node
    middle = middleNode(head)
    
    # Print the values from the middle node to the end
    while middle:
        print(middle.val, end=" ")
        middle = middle.next
    print()
