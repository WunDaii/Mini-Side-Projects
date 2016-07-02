/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package calculator;

import java.util.Scanner;
import jdk.nashorn.internal.objects.NativeRegExp;

/**
 *
 * @author Daven
 */
public class Calculator {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        Scanner input = new Scanner(System.in);
        System.out.print("Enter the string you would like to calculate: ");

        String inputStr;
        if ((inputStr = input.nextLine()) != null) {

            // Remove whitespace:
            inputStr = inputStr.replaceAll("\\s+", "");

            // Create two arrays, one for operands and one for operators
            String operands[] = inputStr.split("[-+*/]");
            String operators[] = inputStr.split("[0-9]+");
    
            // Initialise the result to the first operand
            int result = Integer.parseInt(operands[0]);
            
            // Loop through the operands and perform the correct
            // operator, changing the result.
            for (int i = 1; i < operands.length; i++) {
                
                String operator = operators[i];
                String operand = operands[i];
                
                if (operator.equals("+")) {
                    result += Integer.parseInt(operand);
                } else if (operator.equals("-")) {
                    result -= Integer.parseInt(operand);
                } else if (operator.equals("*")) {
                    result = result * Integer.parseInt(operand);
                } else if (operator.equals("/")) {
                    result = result / Integer.parseInt(operand);
                }
            }
            
            // Print the result of the calculation
            System.out.println("The result is: " + result);
        }
    }
    
     static public void printStrArray(String[] array) {
        for (String s : array) {
            System.out.println("-- Str:  " + s);
        }
    }
}
