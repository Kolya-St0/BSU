public class Main {
    public static void main(String[] args) {
        String_Processer str_pr = new String_Processer();

        String[] strs = new String[2];
        str_pr.read_two_str(strs, "input.txt");
        String str1 = strs[0];
        String str2 = strs[1];
        System.out.println("str1 = " + str1 + "\nstr2 = " + str2);

        String[] leks = str_pr.split_str(str1, str2);
        System.out.println("leks:");
        str_pr.print_leks(leks);

        String[] not_nums = str_pr.find_leks(leks,".*\\D.*");
        System.out.println("not numbers:");
        str_pr.print_leks(not_nums);

        String[] words = str_pr.find_leks(not_nums,"^[a-zA-Z0-9]+$");
        System.out.println("words:");
        str_pr.print_leks(words);

        String[] dates = str_pr.find_leks(not_nums, "^(0[1-9]|1[0-9]|2[0-9]|3[01])\\.(0[1-9]|1[0-2])\\.\\d{2}$");
        System.out.println("dates:");
        str_pr.print_leks(dates);

        str_pr.date_sort(dates);
        System.out.println("sorted dates by year:");
        str_pr.print_leks(dates);

        str1 = str_pr.input_num(str1, words);
        System.out.println("str1 with random number = " + str1);

        str1 = str_pr.delete_min_substr(str1);
        System.out.println("str1 with deleted substr = " + str1);

        String not_nums_str = str_pr.convert_to_str(not_nums);
        System.out.println("not nums str: " + not_nums_str);

        String words_str = str_pr.convert_to_str(words);
        System.out.println("words str: " + words_str);

        String dates_str = str_pr.convert_to_str(dates);
        System.out.println("dates str: " + dates_str);

        String[] result = {str1, not_nums_str, words_str, dates_str};
        str_pr.write_to_file(result, "output.txt");
    }
}