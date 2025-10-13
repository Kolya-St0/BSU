import java.util.Comparator;

public class Year_Comparator implements Comparator<String> {
    public int compare(String date1, String date2)
    {
        int year1 = Integer.parseInt(date1.substring(6, 8));
        int year2 = Integer.parseInt(date2.substring(6, 8));
        return Integer.compare(year1, year2);
    }
}
