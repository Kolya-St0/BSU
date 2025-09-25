import org.junit.Test;

import java.math.BigDecimal;

import static org.junit.Assert.assertEquals;

public class CalcTest {
    @Test
    public void test_calculate(){
        Calc calculator = new Calc();
        double x = 0.56;
        int k = 3;
        assertEquals(-0.8197559501804886, calculator.calculate(x, k),1e-12);
    }

    @Test
    public void test_big_calculate(){
        Calc calculator = new Calc();
        BigDecimal big_x = new BigDecimal("0.34");
        int k = 5;
        BigDecimal expected = new BigDecimal("-0.4155057049971597241");
        assertEquals(expected, calculator.big_calculate(big_x, k));
    }
}
