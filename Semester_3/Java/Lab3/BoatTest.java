import org.example.Boat;
import org.junit.Test;

import java.util.Calendar;
import java.util.Date;

import static org.junit.Assert.assertEquals;

public class BoatTest {
    private Boat boat = new Boat();

    @Test
    public void boatParseDateTest()
    {
        Date date_exp = new Date(109, Calendar.MARCH, 15);
        Date date_parsed = boat.parseDate("15.03.2009");

        assertEquals(date_exp, date_parsed);
    }

    @Test
    public void boatFormatStringTest()
    {
        String date_formatted = boat.formatDate(new Date(112, Calendar.JUNE, 29));
        String date_exp = "29.06.2012";

        assertEquals(date_exp, date_formatted);
    }

    @Test
    public void boatToStringTest()
    {
        boat = new Boat(2984, "Boat", "13.08.1989", "HNT-896", 12, 362);
        String boat_str = boat.toString();
        String boat_exp = "Boat(2984) | type: Boat | production date: 13.08.1989 | model: HNT-896 | engine power: 12hp | max load: 362kg";

        assertEquals(boat_exp, boat_str);
    }
}
