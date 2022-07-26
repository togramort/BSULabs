package com.company;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Main {
    public static int Arr_Binary_Search(ArrayList<Integer> arr, int key, int begin, int end) {
        int mid = (begin + end) / 2;
        if (begin == end) {
            return -1;
        }
        if (key == arr.get(mid)) {
            return mid;
        } else if (key < arr.get(mid)) {
            return Arr_Binary_Search(arr, key, begin, mid);
        }
        return Arr_Binary_Search(arr, key, mid + 1, end);
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        System.out.println("enter array size");
        int size = in.nextInt();
        System.out.println("enter elements of array");
        ArrayList<Integer> arr = new ArrayList<>(size);
        for (int i = 0; i < size; ++i) {
            arr.add(in.nextInt());
        }
        Collections.sort(arr);

        System.out.println("sorted array: ");
        for (int i = 0; i < size; ++i) {
            System.out.print(arr.get(i) + " ");
        }
        System.out.println();

        System.out.println("enter amount of your future requests:");
        int request = in.nextInt();

        for (int i = 0; i < request; ++i) {
            System.out.println("enter key:");
            int key = in.nextInt();
            int j = Arr_Binary_Search(arr, key, 0, size);
            if (j == -1) {
                System.out.println("key not found!");
            } else {
                System.out.println("index of the key: " + (j + 1));
                System.out.println("result of search: " + true);
            }
        }
    }
}