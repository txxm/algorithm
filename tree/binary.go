package main

import (
	"fmt"
)

type BinaryTreeNode struct {
	data int
	left *BinaryTreeNode
	right *BinaryTreeNode
}

func BinaryCreate() *BinaryTreeNode {
	var (
		ch int
		p *BinaryTreeNode
	)

	fmt.Scanf("%d", &ch)
	if ch == 0 {
		p = nil
	} else {
		p = new(BinaryTreeNode)
		if p == nil {
			return nil
		}
		p.data = ch
		p.left = BinaryCreate()
		p.right = BinaryCreate()
	}

	return p
}

func PrevBinary(PRoot *BinaryTreeNode) *BinaryTreeNode {
	if PRoot == nil {
		return nil
	} else {
		fmt.Printf("%d ", PRoot.data)
		PrevBinary(PRoot.left)
		PrevBinary(PRoot.right)
	}
	return PRoot
}

func MiddleBinary(PRoot *BinaryTreeNode) *BinaryTreeNode {
	if PRoot == nil {
		return nil
	} else {
		MiddleBinary(PRoot.left)
		fmt.Printf("%d ", PRoot.data)
		MiddleBinary(PRoot.right)
	}
	return PRoot
}

func BehindBinary(PRoot *BinaryTreeNode) *BinaryTreeNode {
	if PRoot == nil {
		return nil
	} else {
		BehindBinary(PRoot.left)
		BehindBinary(PRoot.right)
		fmt.Printf("%d ", PRoot.data)
	}
	return PRoot
}

func LevelBinary(PRoot *BinaryTreeNode) *BinaryTreeNode {
	if PRoot == nil {
		return nil
	}
	return nil
}

func NodeNumberBinary(PRoot *BinaryTreeNode) int {
	if PRoot == nil {
		return 0
	} else {
		return (1+NodeNumberBinary(PRoot.left)+
					NodeNumberBinary(PRoot.right))
	}
}

func DepthBinary(PRoot *BinaryTreeNode) int {
	if PRoot == nil {
		return 0
	} else {
		if DepthBinary(PRoot.left) > DepthBinary(PRoot.right) {
			return (1+DepthBinary(PRoot.left))
		} else {
			return (1+DepthBinary(PRoot.right))
		}
	}
}

func main() {
	var PRoot *BinaryTreeNode
	PRoot = BinaryCreate()
	if PRoot == nil {
		return
	}

	fmt.Printf("前序遍历：")
	PrevBinary(PRoot)
	fmt.Printf("\n中序遍历：")
	MiddleBinary(PRoot)
	fmt.Printf("\n后序遍历：")
	BehindBinary(PRoot)
	fmt.Println("")

	fmt.Println("节点个数：", NodeNumberBinary(PRoot))
	fmt.Println("二叉树深度：", DepthBinary(PRoot))
}
