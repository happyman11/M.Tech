package AssingmentHPC;
import java.util.Random;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicReference;

class Node {
    int value;
    AtomicReference<Node> next;
    AtomicReference<Node> prev;

    Node(int value) {
        this.value = value;
        this.next = new AtomicReference<>(null);
        this.prev = new AtomicReference<>(null);
    }
}

class DoublyLinkedList {
    private AtomicReference<Node> head;

    DoublyLinkedList() {
        head = new AtomicReference<>(null);
    }

    // Insert with non-blocking synchronization
    public void insert(int value) {
        Node newNode = new Node(value);

        while (true) {
            Node current = head.get();
            Node next = null;

            if (current == null || value < current.value) {
                newNode.next.set(current);
                newNode.prev.set(null); // No previous node

                if (current != null) {
                    current.prev.set(newNode); // Update previous node
                }

                if (head.compareAndSet(current, newNode)) {
                    return;
                }
            } else {
                while (current != null && value >= current.value) {
                    next = current;
                    current = current.next.get();
                }

                newNode.next.set(current);
                newNode.prev.set(next);

                if (current != null) {
                    current.prev.set(newNode); // Update previous node of the current node
                }

                if (next != null) {
                    if (next.next.compareAndSet(current, newNode)) {
                        return;
                    }
                }
            }
        }
    }

    // Search with non-blocking synchronization
    public boolean search(int value) {
        Node current = head.get();

        while (current != null && current.value <= value) {
            if (current.value == value) {
                return true;
            }
            current = current.next.get();
        }

        return false;
    }

    // Delete with non-blocking synchronization
    public boolean delete(int value) {
        Node current = head.get();
        Node prev = null;

        while (current != null && current.value <= value) {
            if (current.value == value) {
                Node next = current.next.get();

                if (prev != null) {
                    prev.next.set(next); // Update next reference of the previous node
                    if (next != null) {
                        next.prev.set(prev); // Update previous reference of the next node
                    }
                } else {
                    if (next != null) {
                        next.prev.set(null); // Update previous reference of the next node
                    }
                    head.set(next); // Update the head
                }

                return true;
            }
            prev = current;
            current = current.next.get();
        }

        return false;
    }

    // Display
    public void display() {
        Node current = head.get();
        while (current != null) {
            System.out.print(current.value + " ");
            current = current.next.get();
        }
        System.out.println();
    }
}

public class NonBlockingSync1 {
    private static Random rand = new Random();
    private static DoublyLinkedList list;

    public static void main(String[] args) {
        int[] problemSizes = { 2000, 20000, 200000 };
        int[] threadCounts = { 1, 2, 4, 6, 8, 10, 12, 14, 16 };
        Runnable[] workloads = {
            () -> workload_0C_0I_50D(),
            () -> workload_50C_25I_25D(),
            () -> workload_100C_0I_0D()
        };

        for (int problemSize : problemSizes) {
            for (int numThreads : threadCounts) {
                for (Runnable workload : workloads) {
                    runTest(problemSize, numThreads, workload);
                }
            }
        }
    }

    private static void runTest(int problemSize, int numThreads, Runnable workload) {
        DoublyLinkedList list = new DoublyLinkedList();
        int[] data = generateTestData(problemSize);

        ExecutorService executorService = Executors.newFixedThreadPool(numThreads);

        long startTime = System.nanoTime();

        for (int i = 0; i < numThreads; i++) {
            executorService.submit(() -> workload.run()); // Pass the list instance to the workload
        }

        executorService.shutdown();

        try {
            executorService.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        long endTime = System.nanoTime();
        double executionTimeInSeconds = (endTime - startTime) / 1e9;

        double throughput = problemSize / executionTimeInSeconds;

        System.out.println("Problem Size: " + problemSize + ", Threads: " + numThreads +
                ", Workload: " + workload.getClass().getSimpleName());
        System.out.println("Execution Time: " + executionTimeInSeconds + " seconds");
        System.out.println("Throughput: " + throughput + " ops/s\n");
    }

    private static int[] generateTestData(int size) {
        int[] data = new int[size];

        for (int i = 0; i < size; i++) {
            data[i] = generateRandomValue();
        }

        return data;
    }

    private static int generateRandomValue() {
        return rand.nextInt(100); // Adjust range as needed
    }

    private static void workload_0C_0I_50D() {
        for (int i = 0; i < 50; i++) {
            int valueToDelete = generateRandomValue();
            list.delete(valueToDelete);
        }
    }

    private static void workload_50C_25I_25D() {
    	for (int i = 0; i < 50; i++) {
            int valueToSearch = generateRandomValue();
            list.search(valueToSearch);
        }
        for (int i = 0; i < 25; i++) {
            int valueToInsert = generateRandomValue();
            list.insert(valueToInsert);
        }
        for (int i = 0; i < 25; i++) {
            int valueToDelete = generateRandomValue();
            list.delete(valueToDelete);
        }
        
    }

    private static void workload_100C_0I_0D() {
        for (int i = 0; i < 100; i++) {
            int valueToSearch = generateRandomValue();
            list.search(valueToSearch);
        }
    }
}
