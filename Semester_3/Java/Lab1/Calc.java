import java.math.BigDecimal;
import java.math.MathContext;
import java.math.RoundingMode;

public class Calc {
    public double calculate(double x, int k){
        double e = Math.pow(10, -k);
        double slag = -x;
        double sum = 0;
        int n = 1;
        while(Math.abs(slag) >= e){
            sum += slag;
            slag = slag * x * n / (n + 1);
            n++;
        }
        return sum;
    }
    public BigDecimal big_calculate(BigDecimal big_x, int k){
        int acc = k + 10;
        MathContext r = new MathContext(acc, RoundingMode.HALF_UP);
        BigDecimal e = BigDecimal.ONE.divide(BigDecimal.TEN.pow(k), r);
        BigDecimal sum = BigDecimal.ZERO;
        BigDecimal slag = big_x.negate();
        int n = 1;
        while(slag.abs().compareTo(e) >= 0){
            sum = sum.add(slag);
            slag = slag.multiply(big_x).multiply(new BigDecimal(n)).divide(new BigDecimal(n + 1), r);
            n++;
        }
        return sum;
    }
}
