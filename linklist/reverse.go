package main

import (
	"fmt"
)

type INode struct {
	data int
	next *INode
}

func LinkInit() *INode {
	head := new(INode)
	if head == nil {
		fmt.Println("new() error.")
		return nil
	}
	head.data = 0
	head.next = nil

	return head
}

func LinkInsert(head *INode, value int) *INode {
	if head == nil {
		return nil
	}

	p := new(INode)
	if p == nil {
		return nil
	}

	p.data = value
	p.next = head.next
	head.next = p

	return head
}

/* 将p作为反转链表的尾节点，尾节点的下一个位置是q, 始终将q插入到head的下
   一个位置 */
func LinkReversal(head *INode) *INode {
	if head == nil && head.next == nil {
		return nil
	}

	var p, q *INode
	p = head.next
	for ; p.next != nil; {
		q = p.next
		p.next = q.next
		q.next = head.next
		head.next = q
	}

	return head
}

func LinkTraversal(head *INode) *INode {
	if  head == nil {
		return nil
	}

	var p *INode
	for p = head.next; p != nil; {
		fmt.Printf("%d ", p.data)
		p = p.next
	}
	fmt.Println("")

	return head
}

func main() {
	var head *INode

	head = LinkInit()
	if head == nil {
		return
	}

	err := LinkInsert(head, 1)
	err = LinkInsert(head, 2)
	err = LinkInsert(head, 3)

	err = LinkTraversal(head)
	if err == nil {
		return
	}

	err = LinkReversal(head)
	if err == nil {
		return
	}

	err = LinkTraversal(head)
	if err == nil {
		return
	}
}
