import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class String_Processer_Test {
    private String_Processer str_pr = new String_Processer();

    @Test
    public void split_str_test()
    {
        String str1 = "al.|br_ch";

        String[] leks1 = str_pr.split_str(str1, ".|_");
        String[] expected1 = {"al", "br", "ch"};

        assertEquals(expected1, leks1);

        String[] leks2 = str_pr.split_str(str1, "lbc");
        String[] expected2 = {"a", ".|", "r_", "h"};

        assertEquals(expected2, leks2);
    }

    @Test
    public void find_leks_test()
    {
        String[] leks = {"alpha", "123", "b?@>o", "=!#", "chArliE", "2077"};

        String[] words = str_pr.find_leks(leks, "^[a-zA-Z]+$");
        String[] words_expected = {"alpha", "chArliE"};

        assertEquals(words_expected, words);

        String[] nums = str_pr.find_leks(leks, "^\\d+$");
        String[] nums_expected = {"123", "2077"};

        assertEquals(nums_expected, nums);

        String[] symbols = str_pr.find_leks(leks, ".*\\W+.*");
        String[] symbols_expected = {"b?@>o", "=!#"};

        assertEquals(symbols_expected, symbols);
    }

    @Test
    public void reverse_str_test()
    {
        String str = "abcde";
        str = str_pr.reverse_str(str);
        assertEquals("edcba", str);
    }

    @Test
    public void input_num_test()
    {
        String str1 = "+][delta_@?<::golf";
        String[] words1 = {"delta", "golf"};
        str1 = str_pr.input_num(str1, words1);

        assertTrue(str1.matches(".{8}\\d+.*"));

        String str2 = "08-;<?";
        String[] words2 = {};
        str2 = str_pr.input_num(str2, words2);

        assertTrue(str2.matches(".{3}\\d+.*"));
    }

    @Test
    public void delete_min_substr_test()
    {
        String str1 = "523/.f345+=pk9>";
        str1 = str_pr.delete_min_substr(str1);

        assertEquals("523/.45+=pk9>", str1);

        String str2 = "]::;>.?o7)(";
        str2 = str_pr.delete_min_substr(str2);

        assertEquals("]::;>.?)(", str2);

        String str3 = "30=)(]]]:;:>";
        str3 = str_pr.delete_min_substr(str3);

        assertEquals("30=)(]]]:;:>", str3);
    }

    @Test
    public void date_sort_test()
    {
        String[] dates1 = {"06.11.90", "29.03.82", "27.03.84"};
        str_pr.date_sort(dates1);
        String[] expected1 = {"29.03.82", "27.03.84", "06.11.90"};

        assertEquals(expected1, dates1);

        String[] dates2 = {"16.01.24", "07.03.21", "27.06.23", "13.11.22", "28.08.20"};
        str_pr.date_sort(dates2);
        String[] expected2 = {"28.08.20", "07.03.21", "13.11.22", "27.06.23", "16.01.24"};

        assertEquals(expected2, dates2);
    }

    @Test
    public void convert_to_str_test()
    {
        String[] leks1 = {"hl", "2012", "ind", "-<?", "jul"};
        String leks1_str = str_pr.convert_to_str(leks1);
        String expected1 = "hl|2012|ind|-<?|jul";

        assertEquals(expected1, leks1_str);

        String[] leks2 = {"klo - ", ">?=0-lim::", "&mik3;"};
        String leks2_str = str_pr.convert_to_str(leks2);
        String expected2 = "klo - |>?=0-lim::|&mik3;";

        assertEquals(expected2, leks2_str);
    }
}
