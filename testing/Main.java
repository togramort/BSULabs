package com.company;
import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws Exception {
        int first, second, third;
        int flag = 1;
        Scanner scanner = new Scanner(System.in);
        while (flag != 0) {
            System.out.println("enter values of the sides");
            try {
                first = scanner.nextInt();
                second = scanner.nextInt();
                third = scanner.nextInt();
                Triangle triangle = new Triangle(first, second, third);
                System.out.println(triangle);
            } catch (InputMismatchException e) {
                System.out.println("your input isn't integer or out of integer");
                scanner.nextLine();
                continue;
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
                scanner.nextLine();
                continue;
            }
            System.out.println("continue - 1\nelse - 0");
            flag = scanner.nextInt();
        }
    }
}