import java.util.*;
import java.io.*;


public class GPA {

    public static void main(String args[]) {
        double[] gpa = total("gg/gpa.txt");
        System.out.println("\n" + gpa[0]);
        System.out.println(gpa[1]);
        

        System.out.printf("Your avg GPA is: %.2f\n", +gpa[0] / gpa[1]);
    }
    
    public static double[] total(String fileName) {
      double[] total = new double[2];
      total[0] = 0.0;
      total[1] = 0.0;
      
      try {
         Scanner file = new Scanner(new File(fileName));
         
         while(file.hasNext()) {
            String toprint = file.next();           
            double loading = file.nextDouble();
            
            System.out.println(toprint + ": " + loading);
            total[0]+=loading;
            total[1]++;
            total[0] = Math.round(total[0] * 10.0) / 10.0;
            System.out.println(total[0]);
         }
         
      
      } catch(FileNotFoundException e) {
         System.out.println("Cannot load: " + fileName);
      } catch(InputMismatchException e) {
         System.out.println(fileName + " does not meet format expectations.");
      }
    
      return total;
    }
    
}