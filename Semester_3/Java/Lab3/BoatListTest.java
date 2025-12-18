import org.example.Boat;
import org.example.BoatList;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class BoatListTest {
    private BoatList boats = new BoatList();

    @Test
    public void boatListSizeTest()
    {
        for (int i = 0; i < 3; i++) {
            Boat boat = new Boat();
            boats.add(boat);
        }

        assertEquals(boats.size(), 3);
    }

    @Test
    public void boatListSortByIdTest()
    {
        Boat boat1 = new Boat(1839, "aaa", "01.01.2001", "AAA-111", 20, 460);
        Boat boat2 = new Boat(1002, "ccc", "02.02.2002", "CCC-111", 30, 560);
        Boat boat3 = new Boat(1452, "bbb", "03.03.2003", "BBB-111", 10, 200);

        boats.add(boat1);
        boats.add(boat2);
        boats.add(boat3);

        assertEquals(boats.get(0), boat1);
        assertEquals(boats.get(1), boat2);
        assertEquals(boats.get(2), boat3);

        boats.sortById();

        assertEquals(boats.get(0), boat2);
        assertEquals(boats.get(1), boat3);
        assertEquals(boats.get(2), boat1);
    }

    @Test
    public void boatListSortByDateTest()
    {
        Boat boat1 = new Boat(1839, "aaa", "04.12.2013", "AAA-111", 20, 460);
        Boat boat2 = new Boat(1654, "eee", "15.13.2008", "EEE-555", 5, 120);
        Boat boat3 = new Boat(1002, "ccc", "21.05.2019", "CCC-222", 30, 560);
        Boat boat4 = new Boat(1452, "bbb", "16.07.2003", "BBB-333", 10, 200);
        Boat boat5 = new Boat(1789, "ddd", "15.07.2003", "DDD-444", 15, 310);

        boats.add(boat1);
        boats.add(boat2);
        boats.add(boat3);
        boats.add(boat4);
        boats.add(boat5);

        assertEquals(boats.get(0), boat1);
        assertEquals(boats.get(1), boat2);
        assertEquals(boats.get(2), boat3);
        assertEquals(boats.get(3), boat4);
        assertEquals(boats.get(4), boat5);

        boats.sortByProductionDate();

        assertEquals(boats.get(0), boat5);
        assertEquals(boats.get(1), boat4);
        assertEquals(boats.get(2), boat1);
        assertEquals(boats.get(3), boat3);
        assertEquals(boats.get(4), boat2);
    }

    @Test
    public void boatListSortByModelTest()
    {
        Boat boat1 = new Boat(1839, "aaa", "01.01.2001", "VEN-132", 20, 460);
        Boat boat2 = new Boat(1002, "ccc", "02.02.2002", "LCK-808", 30, 560);
        Boat boat3 = new Boat(1452, "bbb", "03.03.2003", "XMN-151", 60, 760);
        Boat boat4 = new Boat(1908, "ddd", "04.04.2004", "LCJ-564", 25, 510);
        Boat boat5 = new Boat(1523, "eee", "05.05.2005", "XMN-150", 58, 715);
        Boat boat6 = new Boat(1317, "ggg", "07.07.2007", "AbD-125", 17, 240);
        Boat boat7 = new Boat(1303, "fff", "06.06.2006", "aBC-123", 15, 200);

        boats.add(boat1);
        boats.add(boat2);
        boats.add(boat3);
        boats.add(boat4);
        boats.add(boat5);
        boats.add(boat6);
        boats.add(boat7);

        assertEquals(boats.get(0), boat1);
        assertEquals(boats.get(1), boat2);
        assertEquals(boats.get(2), boat3);
        assertEquals(boats.get(3), boat4);
        assertEquals(boats.get(4), boat5);
        assertEquals(boats.get(5), boat6);
        assertEquals(boats.get(6), boat7);

        boats.sortByModel();

        assertEquals(boats.get(0), boat7);
        assertEquals(boats.get(1), boat6);
        assertEquals(boats.get(2), boat4);
        assertEquals(boats.get(3), boat2);
        assertEquals(boats.get(4), boat1);
        assertEquals(boats.get(5), boat5);
        assertEquals(boats.get(6), boat3);
    }
}
