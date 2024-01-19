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

public class OptimisticList {
    private Node head;

    public OptimisticList() {
        this.head = new Node(Integer.MIN_VALUE);
        this.head.next = new Node(Integer.MAX_VALUE);
        this.head.next.prev = this.head;
    }

    private class Node {
        int key;
        Node next;
        Node prev;  // Added prev reference
        Lock lock;

        Node(int item) {
            this.key = item;
            this.next = null;
            this.prev = null;
            this.lock = new ReentrantLock();
        }

        void lock() {
            lock.lock();
        }

        void unlock() {
            lock.unlock();
        }
    }

    private boolean validate(Node pred, Node curr) {
        Node node = head;
        while (node.key <= pred.key) {
            if (node == pred) {
                return pred.next == curr;
            }
            node = node.next;
        }
        return false;
    }

    public boolean add(int item) {
        Node pred = null, curr = null;
        int key = item;
        while (true) {
            pred = this.head;
            curr = pred.next;
            while (curr.key < key) {
                pred = curr;
                curr = curr.next;
            }
            pred.lock();
            // 
            try {
                curr.lock();
                if (validate(pred, curr)) {
                    if (curr.key == key) {
                        return false;
                    } else {
                        Node node = new Node(item);
                        node.next = curr;
                        node.prev = pred;  // Set the previous reference
                        pred.next = node;
                        curr.prev = node;  // Set the previous reference for the next node
                        return true;
                    }
                }
            } finally {
                // pred.unlock();
                curr.unlock();
            }
        }
    }

    public boolean remove(int item) {
        Node pred = null, curr = null;
        int key = item;
        while (true) {
            pred = this.head;
            curr = pred.next;
            while (curr.key < key) {
                pred = curr;
                curr = curr.next;
            }
            pred.lock();
            // 
            try {
                curr.lock();
                if (validate(pred, curr)) {
                    if (curr.key == key) {
                        pred.next = curr.next;
                        curr.next.prev = pred;  // Update the previous reference for the next node
                        return true;
                    } else {
                        return false;
                    }
                }
            } finally {
                pred.unlock();
                curr.unlock();
            }
        }
    }

    public boolean contains(int item) {
        Node pred = null, curr = null;
        int key = item;
        while (true) {
            pred = this.head;
            curr = pred.next;
            while (curr.key < key) {
                pred = curr;
                curr = curr.next;
            }
            try {
                pred.lock();
                curr.lock();
                if (validate(pred, curr)) {
                    return (curr.key == key);
                }
            } finally {
                pred.unlock();
                curr.unlock();
            }
        }
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
//public class OptimisticList 
//{
//    private Node head;
//    
//    public OptimisticList()
//    {
//        this.head= new Node(Integer.MIN_VALUE);
//        this.head.next= new Node(Integer.MAX_VALUE);
//    }
//    private class Node
//    {
//        int key;
//        Node next;
//        Lock lock;
//        Node (int item) {this.key=item;this.next=null;this.lock=new ReentrantLock();}
//        void lock(){lock.lock();}
//        void unlock(){lock.unlock();}
//    }
//    private boolean validate(Node pred,Node curr)
//    {
//        Node node = head;
//        while(node.key<=pred.key)
//        {
//            if (node==pred)
//            {
//                return pred.next==curr;
//            }
//            node=node.next;
//        }
//        return false;
//    }
//    public boolean add(int item)
//    {
//        Node pred=null,curr=null;
//        int key=item;
//        while(true)
//        {
//            pred=this.head;
//            curr=pred.next;
//            while(curr.key<key)
//            {
//                pred=curr;
//                curr=curr.next;
//            }
//            pred.lock();
//            curr.lock();
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
//                        Node node = new Node(item);
//                        node.next=curr;
//                        pred.next=node;
//                        return true;    
//                    }
//                }
//            }
//            finally
//            {
//                pred.unlock();
//                curr.unlock();      
//            }
//        }     
//    }
//    
//    public boolean remove(int item)
//    {
//        Node pred=null,curr=null;
//        int key=item;
//        while(true)
//        {
//            pred=this.head;
//            curr=pred.next;
//            while(curr.key<key)
//            {
//                pred=curr;
//                curr=curr.next;
//            }
//            pred.lock();
//            curr.lock();
//            try
//            {
//               if(validate(pred,curr))
//               {
//                    if (curr.key==key)
//                    {
//                        pred.next=curr.next;
//                        return true;
//                    }
//                    else
//                    {
//                        return false;
//                    }
//                }
//            }
//            finally
//            {
//                pred.unlock();
//                curr.unlock();   
//            } 
//        }
//    }
//    
//    public boolean contains(int item)
//    {
//        Node pred=null,curr=null;
//        int key=item;
//        while(true)
//        {
//            pred=this.head;
//            curr=pred.next;
//            while(curr.key<key)
//            {
//                pred=curr;
//                curr=curr.next;
//            }
//            try
//            {
//                pred.lock();
//                curr.lock();
//                if(validate(pred,curr))
//                {
//                    return(curr.key==key);
//                }
//            }
//            finally
//            {  
//                pred.unlock();
//                curr.unlock();      
//            }
//        }
//
//            
//    }
//    
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
//
//    
//    
//}
