package com.company;

import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static boolean Users_Search(String[] User_names, String Login) {
        for (String user_name : User_names)
            if (user_name.equals(Login)) {
                return true;
            }
        return false;
    }

    public static void main(String[] args) throws IOException {
        Scanner users_info_scan = new Scanner(new FileReader("info.txt"));
        if (!users_info_scan.hasNext())
            System.out.print("file with login and password data is empty!");
        else {
            int users_amount = users_info_scan.nextInt();
            if (users_amount > 10)
                System.out.print("too much users! maximum amount = 10");
            else {
                users_info_scan.nextLine();
                String[] User_names = new String[users_amount];
                String[] User_passwords = new String[users_amount];
                for (int i = 0; i < users_amount; i++) {
                    String[] User_data;
                    User_data = users_info_scan.nextLine().split("-");
                    User_names[i] = User_data[0];
                    User_passwords[i] = User_data[1];
                }
                Scanner scan = new Scanner(System.in);
                int remaining_number_of_attempts = 3;
                boolean check = false;
                while (remaining_number_of_attempts != 0) {
                    System.out.println("remaining number of attempts for correct input: " + remaining_number_of_attempts);
                    System.out.print("please, enter login: ");
                    String Login = scan.nextLine();
                    if (Login.length() == 0) {
                        System.out.println("login is empty!");
                        remaining_number_of_attempts--;
                        continue;
                    }
                    if (Login.length() > 10) {
                        System.out.println("your login is too long!");
                        remaining_number_of_attempts--;
                        continue;
                    }
                    if (Users_Search(User_names, Login)) {
                        System.out.println("hello, " + Login + "!");
                        remaining_number_of_attempts = 3;
                        while (remaining_number_of_attempts != 0) {
                            int True_Password_Index = 0;
                            for (int i = 0; i < User_names.length; i++)
                                if (User_names[i].equals(Login)) {
                                    True_Password_Index = i;
                                    break;
                                }
                            System.out.println("remaining number of attempts for correct input: " + remaining_number_of_attempts);
                            System.out.print("please, enter your password: ");
                            String Password = scan.nextLine();
                            if (Password.length() > 8) {
                                System.out.println("your password is too long!");
                                remaining_number_of_attempts--;
                                continue;
                            }
                            if (User_passwords[True_Password_Index].equals(Password)) {
                                System.out.println("correct password! welcome, " + Login + "!");
                                check = true;
                                break;
                            } else {
                                System.out.println("incorrect password!");
                                remaining_number_of_attempts--;
                            }
                        }
                        break;
                    } else {
                        System.out.println("there is no such login in data base!");
                        remaining_number_of_attempts--;
                    }
                }
                if (!check)
                    System.out.println("you dont have any attempts! impossible to enter!");
            }
        }
    }
}