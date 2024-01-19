/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.hpc_assignment2;

/**
 *
 * @author apple
 */
public class ThreadID {
    /**
   * The next thread ID to be assigned
   **/
  private static volatile int nextID = 0;
  /**
   * My thread-local ID.
   **/
  private static ThreadLocalID threadID = new ThreadLocalID();
  public static int get() {
    return threadID.get();
  }
  public static void reset() {
    nextID = 0;
  }
  private static class ThreadLocalID extends ThreadLocal<Integer> {
    protected synchronized Integer initialValue() {
      return nextID++;
    }
  }
    
}
