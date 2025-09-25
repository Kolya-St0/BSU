import java.math.BigDecimal;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Calc calculator = new Calc();
        Form formatter = new Form();

        int choice;
        System.out.println("Enter 0 for BigNumber calculations, enter any else for usual: ");
        choice = scanner.nextInt();
        if(choice != 0) {
            System.out.println("Usual mode");
            double x = 2;
            while (x < -1 || x >= 1) {
                System.out.print("Enter x: ");
                x = scanner.nextDouble();
            }

            System.out.print("Enter k: ");
            int k = scanner.nextInt();

            double sum = calculator.calculate(x, k);
            double ln = Math.log(1 - x);
            if (sum > 0) {
                System.out.println("Taylor ln(1-x): " + formatter.format(sum, k) + " Formatted: " + formatter.OH_form(sum));
                System.out.println("Exact ln(1-x): " + formatter.format(ln, k) + " Formatted: " + formatter.OH_form(ln));
            } else {
                System.out.println("Taylor ln(1-x): " + formatter.format(sum, k));
                System.out.println("Exact ln(1-x): " + formatter.format(ln, k));
            }
        }
        else {
            System.out.println("BigNumbers mode");
            BigDecimal big_x = new BigDecimal("2");
            while (big_x.compareTo(BigDecimal.ONE) > 0 || big_x.compareTo(BigDecimal.ONE.negate()) < 0) {
                System.out.print("Enter x: ");
                big_x = scanner.nextBigDecimal();
            }
            System.out.print("Enter k: ");
            int k = scanner.nextInt();

            BigDecimal sum = calculator.big_calculate(big_x, k);
            BigDecimal ln = new BigDecimal(Math.log(1 - big_x.doubleValue()));

            if (sum.compareTo(BigDecimal.ZERO) > 0) {
                System.out.println("Taylor ln(1-x): " + formatter.Big_format(sum, k) + " Formatted: " + formatter.OH_Big_format(sum));
                System.out.println("Exact ln(1-x): " + formatter.Big_format(ln, k) + " Formatted: " + formatter.OH_Big_format(ln));
            } else {
                System.out.println("Taylor ln(1-x): " + formatter.Big_format(sum, k));
                System.out.println("Exact ln(1-x): " + formatter.Big_format(ln, k));
            }
        }
        scanner.close();
    }
}