# Given the head of a singly linked list, reverse the list, and return the reversed list.
#
# Example 1:
# Input: head = [1,2,3,4,5]
# Output: [5,4,3,2,1]
#
# Example 2:
# Input: head = [1,2]
# Output: [2,1]
#
# Example 3:
# Input: head = []
# Output: []
#
# Constraints:
# The number of nodes in the list is the range [0, 5000].
# -5000 <= Node.val <= 5000
#
# Follow up: A linked list can be reversed either iteratively or recursively. Could you implement both?

from typing import Optional

class ListNode:
    def __init__(self, val: int = 0):
        """
        Initializes a ListNode with a given value and sets the next node to None.
        
        Args:
        val (int): The value of the node. Default is 0.
        """
        self.val = val
        self.next = None

def reverseList(head: Optional[ListNode]) -> Optional[ListNode]:
    """
    Reverses a singly linked list.
    
    Args:
    head (Optional[ListNode]): The head of the singly linked list.
    
    Returns:
    Optional[ListNode]: The new head of the reversed singly linked list.
    """
    prev = None
    current = head
    next = None
    
    while current:
        next = current.next
        current.next = prev
        prev = current
        current = next
    
    return prev

def printList(head: Optional[ListNode]) -> None:
    node = head  # Initialize the node to the head of the list
    while node:
        print(node.val, end=' ')
        node = node.next
    print()

if __name__ == "__main__":
    """
    This block creates a linked list, prints it, reverses it, and prints the reversed list.
    """
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(4)
    head.next.next.next.next = ListNode(5)

    printList(head)
    head = reverseList(head)
    printList(head)
