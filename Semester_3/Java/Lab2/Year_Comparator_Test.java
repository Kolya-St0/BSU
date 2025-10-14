import java.util.Comparator;

import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class Year_Comparator_Test {
    private Comparator<String> comparator = new Year_Comparator();

    @Test
    public void compare_test()
    {
        int result_l0 = comparator.compare("22.11.17", "08.08.23");
        assertTrue(result_l0 < 0);

        int result_e0 = comparator.compare("13.01.21", "25.09.21");
        assertEquals(0, result_e0);

        int result_g0 = comparator.compare("28.03.23", "11.02.18");
        assertTrue(result_g0 > 0);
    }
}
