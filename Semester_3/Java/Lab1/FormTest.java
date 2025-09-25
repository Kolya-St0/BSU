import org.junit.Test;

import java.math.BigDecimal;

import static org.junit.Assert.assertEquals;

public class FormTest {
    @Test
    public void test_format(){
        Form formatter = new Form();
        assertEquals("-000,57970",formatter.format(-0.5797043307413114, 4));
        assertEquals("-000,1272",formatter.format(-0.1272, 3));
    }

    @Test
    public void test_OH_form(){
        Form formatter = new Form();
        assertEquals("Round: 1 | Oct: 1 | Hex: 1", formatter.OH_form(0.6936474305598217));
    }

    @Test
    public void test_Big_format(){
        Form formatter = new Form();
        BigDecimal big_x = new BigDecimal("-1.7147534441480315070");
        assertEquals("-1,714753", formatter.Big_format(big_x, 5));
    }

    @Test
    public void test_Big_OH_format(){
        Form formatter = new Form();
        BigDecimal big_x = new BigDecimal("0.63652928526408024");
        assertEquals("Round: 1 | Oct: 1 | Hex: 1", formatter.OH_Big_format(big_x));
    }
}
