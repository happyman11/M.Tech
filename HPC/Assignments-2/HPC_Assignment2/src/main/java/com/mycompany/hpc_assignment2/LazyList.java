package com.mycompany.hpc_assignment2;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
/**
 *
 * @author apple
 */
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class LazyList {
    private Node head;
    
    private class Node {
        int key;
        Node next;
        Node prev;  // Added prev reference
        boolean marked;
        Lock lock;
        
        Node(int key) {
            this.key = key;
            this.next = null;
            this.prev = null;
            this.marked = false;
            this.lock = new ReentrantLock();
        }
        
        void lock() {
            lock.lock();
        }
        
        void unlock() {
            lock.unlock();
        }
    }
    
    public LazyList() {
        this.head = new Node(Integer.MIN_VALUE);
        this.head.next = new Node(Integer.MAX_VALUE);
        this.head.next.prev = this.head;
    }
    
    private boolean validate(Node pred, Node curr) {
        return !pred.marked && !curr.marked && pred.next == curr && curr.prev == pred;
    }
    
    public boolean add(int key) {
        while (true) {
            Node pred = this.head;
            Node curr = head.next;
            while (curr.key < key) {
                pred = curr;
                curr = curr.next;
            }
            pred.lock();
            curr.lock();
            try {
                if (validate(pred, curr)) {
                    if (curr.key == key) {
                        return false;
                    } else {
                        Node newNode = new Node(key);
                        newNode.next = curr;
                        newNode.prev = pred;  // Set the previous reference
                        pred.next = newNode;
                        curr.prev = newNode;  // Set the previous reference for the next node
                        return true;
                    }
                }
            } finally {
                pred.unlock();
                curr.unlock();
            }
        }
    }
    
    public boolean remove(int key) {
        while (true) {
            Node pred = this.head;
            Node curr = head.next;
            while (curr.key < key) {
                pred = curr;
                curr = curr.next;
            }
            pred.lock();
            curr.lock();
            try {
                if (validate(pred, curr)) {
                    if (curr.key != key) {
                        return false;
                    } else {
                        curr.marked = true;
                        pred.next = curr.next;
                        curr.next.prev = pred;  // Update the previous reference for the next node
                        return true;
                    }
                }
            } finally {
                pred.unlock();
                curr.unlock();
            }
        }
    }
    
    public boolean contains(int key) {
        Node curr = this.head;
        while (curr.key < key) {
            curr = curr.next;
        }
        return curr.key == key && !curr.marked;
    }
    
    public void display() {
        Node temp = head;
        while (temp.next != null) {
            System.out.println("\t" + temp.key);
            temp = temp.next;
        }
    }
}
////Singly Link List
//public class LazyList 
//{
//    private Node head;
//    private class Node
//    {
//        int key;
//        Node next;
//        boolean marked;
//        Lock lock;
//        Node(int key)
//        {
//            this.key=key;
//            this.next=null;
//            this.marked=false;
//            this.lock=new ReentrantLock();
//        }
//        void lock(){lock.lock();}
//        void unlock(){lock.unlock();}
//    }
//    public LazyList()
//    {
//        this.head= new Node(Integer.MIN_VALUE);
//        this.head.next= new Node(Integer.MAX_VALUE);
//    }
//    private boolean validate(Node pred, Node curr)
//    {
//        return !pred.marked&&!curr.marked&&pred.next==curr;
//    }
//    public boolean add(int key)
//    {
//        while(true)
//        {
//            Node pred=this.head;
//            Node curr=head.next;
//            while(curr.key<key)
//            {
//                pred=curr;
//                curr=curr.next;
//            }
//            pred.lock();
//            try
//            {
//                if(validate(pred,curr))
//                {
//                    if (curr.key==key)
//                    {
//                        return false;
//                    }
//                    else
//                    {
//                        Node Node =new Node(key);
//                        Node.next=curr;
//                        pred.next=Node;
//                        return true;
//                    }
//                }
//            }
//            finally
//            {
//                pred.unlock();
//            }
//                      
//        }
//    }
//    public boolean remove(int key)
//    {
//        while(true)
//        {
//            Node pred=this.head;
//            Node curr=head.next;
//            while(curr.key<key)
//            {
//                pred=curr;
//                curr=curr.next;
//            }
//            pred.lock();
//            try
//            {
//              curr.lock();
//              try
//                {
//                   if (validate(pred,curr))
//                   {
//                       if (curr.key!=key)
//                        {
//                         return false;
//                        }
//                        else
//                        {
//                         curr.marked=true;
//                         pred.next=curr.next;
//                         return true;
//                        }
//                    }
//                }
//                finally
//                {
//                  curr.unlock();
//                }
//            }
//            finally
//            {
//                pred.unlock();
//            }
//        }
//    }
//    public boolean contains(int key)
//    {
//        Node curr=this.head;
//        while(curr.key<key)
//        {
//            curr=curr.next;
//        }
//        return curr.key==key &&!curr.marked;
//    }
//    public void display()
//    {
//        Node temp=head;
//        while(temp.next!=null)
//        {
//         System.out.println("\t"+temp.key);
//         temp=temp.next;
//        }
//    }
//    
//}
