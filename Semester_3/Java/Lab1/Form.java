import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.RoundingMode;

public class Form {
    public String format(double x, int k){
        int acc = k + 1;
        int width = acc + 4;
        return String.format("%0" + width + "." + acc + "f", x);
    }

    public String OH_form(double x){
        int form_x = (int)Math.round(x);
        return String.format("Round: %d | Oct: %o | Hex: %x", form_x, form_x, form_x);
    }

    public String Big_format(BigDecimal x, int k){
        int acc = k + 1;
        return String.format("%." + acc + "f", x);
    }

    public String OH_Big_format(BigDecimal x){
        BigInteger rx = x.setScale(0, RoundingMode.HALF_UP).toBigInteger();
        return String.format("Round: %d | Oct: %o | Hex: %x", rx, rx, rx);
    }
}
