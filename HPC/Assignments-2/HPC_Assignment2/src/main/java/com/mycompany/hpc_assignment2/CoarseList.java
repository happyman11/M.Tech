/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.hpc_assignment2;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
/**
 *
 * @author apple
 */

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class CoarseList {
    private Node head;
    private Node tail;
    private Lock lock = new ReentrantLock();

    public CoarseList() {
        head = new Node(Integer.MIN_VALUE);
        tail = new Node(Integer.MAX_VALUE);
        head.next = tail;
        tail.prev = head;
    }

    private class Node {
        int key;
        Node prev;
        Node next;

        Node(int item) {
            this.key = item;
            this.prev = null;
            this.next = null;
        }
    }

    public boolean add(int item) {
        Node newNode = new Node(item);
        try {
            lock.lock();
            newNode.next = tail;
            newNode.prev = tail.prev;
            tail.prev.next = newNode;
            tail.prev = newNode;
            return true;
        } finally {
            lock.unlock();
        }
    }

    public boolean remove(int item) {
        try {
            lock.lock();
            Node current = head.next;
            while (current != tail) {
                if (current.key == item) {
                    current.prev.next = current.next;
                    current.next.prev = current.prev;
                    return true;
                }
                current = current.next;
            }
            return false;
        } finally {
            lock.unlock();
        }
    }

    public boolean contains(int item) {
        try {
            lock.lock();
            Node current = head.next;
            while (current != tail) {
                if (current.key == item) {
                    return true;
                }
                current = current.next;
            }
            return false;
        } finally {
            lock.unlock();
        }
    }

    public void displayForward() {
        Node current = head.next;
        while (current != tail) {
            System.out.println("\t" + current.key);
            current = current.next;
        }
    }

    public void displayBackward() {
        Node current = tail.prev;
        while (current != head) {
            System.out.println("\t" + current.key);
            current = current.prev;
        }
    }
}

//Singly Link List
//public class CoarseList 
//{
//    
//    private   Node head;
//    private  Node tail;
//    private  Lock lock = new ReentrantLock();
//    public CoarseList()
//    {
//        head = new Node(Integer.MIN_VALUE);
//        tail = new Node(Integer.MAX_VALUE);
//        head.next = this.tail;
//        
//    }
//    private class Node
//    {
//        int key;
//        Node next;
//        Node (int item) {this.key=item;this.next=null;}
//    }
//    
//    public boolean add(int item)
//    {
//        Node pred,curr;
//        int key =item;
//        try
//        {
//            lock.lock();
//            pred=head;
//            curr=pred.next;
//            while(curr.key < key)
//            {
//                pred=curr;
//                curr=curr.next;
//            }
//            if (key==curr.key)
//            {
//                return false;
//                
//            }
//            else
//            {
//                Node node = new Node(item);
//                node.next=curr;
//                node.next=node;
//                return true;
//                
//            }
//        }
//        finally
//        {
//            lock.unlock();
//        }
//    }
//    
//    public boolean remove(int item)
//    {
//        Node pred,curr;
//        int key =item;
//        try
//        {
//            lock.lock();
//            pred = this.head;
//            curr = pred.next;
//            while (curr.key < key)
//            {
//                pred = curr;
//                curr = curr.next;
//            }
//            if (key == curr.key)
//            {
//                pred.next = curr.next;
//                return true;
//            }
//            else
//            {
//                return false;
//                
//            }
//        }
//        finally
//        {
//            lock.unlock();
//        }
//        
//    }
//    
//    public boolean contains(int item)
//    {
//        Node pred,curr;
//        int key =item;
//        try
//        {
//            lock.lock();
//            pred = head;
//            curr = pred.next;
//            while (curr.key < key)
//            {
//                pred = curr;
//                curr = curr.next;
//            }
//            return(key== curr.key);  
//        }
//        finally
//        {
//           lock.unlock(); 
//        }
//    }
//    
//    public void display()
//    {
//        Node temp= head;
//        while (temp.next != null)
//        {
//            System.out.println("\t"+temp.key);
//            temp=temp.next;
//        }
//    }
//   
// }
