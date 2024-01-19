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

public class FineList  {
    private Node head;
    
    public FineList () {
        head = new Node(Integer.MIN_VALUE);
        head.next = new Node(Integer.MAX_VALUE);
        head.next.prev = head;  // Initialize the previous reference for the tail node
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
    
    public boolean add(int item) {
        Node pred = null, curr = null;
        int key = item;
        head.lock();
        try {
            pred = head;
            curr = pred.next;
            curr.lock();
            try {
                while (curr.key < key) {
                    pred.unlock();
                    pred = curr;
                    curr = curr.next;
                    curr.lock();
                }
                if (curr.key == key) {
                    return false;
                }
                Node newNode = new Node(item);
                newNode.next = curr;
                newNode.prev = pred;  // Set the previous reference for the new node
                pred.next = newNode;
                curr.prev = newNode;  // Set the previous reference for the next node
                return true;
            } finally {
                curr.unlock();
            }
        } finally {
            pred.unlock();
        }
    }
    
    public boolean remove(int item) {
        Node pred = null, curr = null;
        int key = item;
        head.lock();
        try {
            pred = head;
            curr = pred.next;
            curr.lock();
            try {
                while (curr.key < key) {
                    pred.unlock();
                    pred = curr;
                    curr = curr.next;
                    curr.lock();
                }
                if (curr.key == key) {
                    pred.next = curr.next;
                    curr.next.prev = pred;  // Update the previous reference for the next node
                    return true;
                }
                return false;
            } finally {
                curr.unlock();
            }
        } finally {
            pred.unlock();
        }
    }
    
    public boolean contains(int item) {
        Node pred = null, curr = null;
        int key = item;
        head.lock();
        try {
            pred = head;
            curr = pred.next;
            curr.lock();
            try {
                while (curr.key < key) {
                    pred.unlock();
                    pred = curr;
                    curr = curr.next;
                    curr.lock();
                }
                return (curr.key == key);
            } finally {
                curr.unlock();
            }
        } finally {
            pred.unlock();
        }
    }
}

////Singly Link List
//public class FineList 
//{
//    private Node head;
//    public FineList()
//    {
//        head = new Node(Integer.MIN_VALUE);
//        head.next = new Node(Integer.MAX_VALUE);
//    }
//    private class Node
//    {
//        int key;
//        
//        Node next;
//        Lock lock;
//        Node (int item) {this.key=item;this.next=null;this.lock=new ReentrantLock();}
//        void lock(){lock.lock();}
//        void unlock(){lock.unlock();}
//    }
//    public boolean add (int item)
//    {
//        Node pred=null,curr=null;
//        int key=item;
//        head.lock();
//        try
//        {
//            pred=head;
//            curr=pred.next;
//            curr.lock();
//            try
//            {
//                while(curr.key<key)
//                {
//                    pred.unlock();
//                    pred=curr;
//                    curr=curr.next;
//                    curr.lock();
//                }
//                if (curr.key==key)
//                {
//                    return false;
//                }
//                Node newNode= new Node (item);
//                newNode.next=curr;
//                pred.next=newNode;
//                return true;
//            }
//            finally
//            {
//                curr.unlock();
//            }
//        }
//         finally
//        {
//                pred.unlock();
//        }
//    }
//    
//    public boolean remove(int item)
//    {
//        Node pred=null,curr=null;
//        int key=item;
//        head.lock();
//        try
//        {
//            pred=head;
//            curr=pred.next;
//            curr.lock();
//            try
//            {
//                while(curr.key<key)
//                {
//                    pred.unlock();
//                    pred=curr;
//                    curr=curr.next;
//                    curr.lock();
//                }
//                if (curr.key ==key)
//                {
//                    pred.next=curr.next;
//                    return true;
//                }
//                return false; 
//            }
//            finally
//            {
//                curr.unlock();
//            }
//        }
//        finally
//            {
//                pred.unlock();
//            }
//        
//    }
//    public boolean contains(int item)
//    {
//        Node pred=null,curr=null;
//        int key=item;
//        head.lock();
//        try
//        {
//            pred=head;
//            curr=pred.next;
//            curr.lock();
//            try
//            {
//                while(curr.key<key)
//                {
//                    pred.unlock();
//                    pred=curr;
//                    curr=curr.next;
//                    curr.lock();   
//                }
//                return (curr.key==key);
//            }
//            finally
//            {
//                curr.unlock();
//            }
//        }
//        finally
//        {
//            pred.unlock();
//        }
//    }
//    
//    
//}
