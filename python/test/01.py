# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def isPalindrome(self, head: ListNode) -> bool:
        rhead = reverselinklist(getMiddle(head))
        
    def getMiddle(self, head: ListNode) -> ListNode:
        num = 0
        cur = head
        while cur:
            cur = cur.next
            num += 1
        num = num / 2
        while num > 0:
            head = head.next
            n -= 1
        return head
    def reverselinklist(head: ListNode) -> ListNode:
        prev = head
        cur = head.next
        head.next = None
        while cur:
            n = cur.next
            cur.next = prev
            prev = cur
            cur = n
        return prev
    
            