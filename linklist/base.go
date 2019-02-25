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

func LinkDelete(head *INode, value int) *INode {
	if head == nil || head.next == nil {
		return nil
	}

	for p := head; p.next != nil; {
		if p.next.data == value {
			p.next = p.next.next
			break
		} else {
			p = p.next
		}
	}

	return head
}

func LinkEmpty(head *INode) *INode {
	if head == nil || head.next == nil {
		return nil
	} else {
		return head
	}
}

func LinkTraverse(head *INode) {
	err := LinkEmpty(head)
	if err == nil {
		return
	}

	for p := head.next; p != nil; p = p.next {
		fmt.Println("p.data =", p.data)
	}
}

func LinkReversal(head *INode) *INode {
	var q, r *INode
	if head == nil || head.next == nil {
		return nil
	}

	q = head.next.next
	head.next.next = nil
	for ; q != nil; {
		r = q.next
		q.next = head.next
		head.next = q
		q = r
	}

	return head
}

func LinkCircle(head *INode) int {
	if head == nil || head.next == nil {
		return -1
	}

	p := head.next
	q := head.next
	for ; q.next != nil; {
		p = p.next
		q = q.next.next
		if p == nil {
			return 1
		}
	}

	return 0
}

func main() {
	var head *INode

	head = LinkInit()
	if head == nil {
		return
	}

	err := LinkInsert(head, 1)
	if err == nil {
		return
	}
	err = LinkInsert(head, 2)
	if err == nil {
		return
	}
	err = LinkInsert(head, 3)
	if err == nil {
		return
	}

	err = LinkReversal(head)
	if err == nil {
		return
	}

	ret := LinkCircle(head)
	if ret == 1 {
		fmt.Println("Circle")
	}

	err = LinkDelete(head, 1)
	if err == nil {
		return
	}

	LinkTraverse(head)
}
