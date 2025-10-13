import java.io.*;
import java.util.Random;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.util.Arrays;

public class String_Processer {
    public void read_two_str(String[] strs, String filename) {
        try(BufferedReader reader = new BufferedReader(new FileReader(filename))){
            strs[0] = reader.readLine();
            strs[1] = reader.readLine();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void print_leks(String[] leks){
        for(String l:leks){
            System.out.println(l);
        }
    }

    public String[] split_str(String str, String sep){
        String[] leks = str.split("[" + sep + "]+");
        return leks;
    }

    public String[] find_leks(String[] leks, String regex){
        int size = 0;
        for(String l:leks){
            if(l.matches(regex)){
                size++;
            }
        }

        String[] found = new String[size];
        int i = 0;
        for(String l:leks){
            if(l.matches(regex)){
                found[i] = l;
                i++;
            }
        }
        return found;
    }

    public String reverse_str(String str)
    {
        StringBuilder sb = new StringBuilder(str);
        sb.reverse();
        return sb.toString();
    }

    public String input_num(String str, String[] words){
        int pos = str.length() / 2;
        if(words.length != 0){
            pos = str.indexOf(words[0]) + words[0].length();
        }

        Random rand = new Random();
        int rand_num = rand.nextInt(100);

        StringBuilder sb = new StringBuilder(str);
        sb.insert(pos, rand_num);
        return sb.toString();
    }

    public String delete_min_substr(String str){
        Pattern pattern = Pattern.compile("[a-zA-Z][0-9]");
        Matcher matcher = pattern.matcher(str);

        boolean found = false;

        int min_length = str.length(), cur_length;
        int substr_start = 0, substr_end = 0;

        while(matcher.find()){
            found = true;
            cur_length = matcher.group().length();
            if(cur_length < min_length){
                min_length = cur_length;
                substr_start = matcher.start();
                substr_end = matcher.end();
            }
        }

        if(found) {
            StringBuilder sb = new StringBuilder(str);
            sb.delete(substr_start, substr_end);
            return sb.toString();
        }
        else{
            System.out.println("no matches found");
            return str;
        }
    }

    public void date_sort(String[] dates)
    {
        Arrays.sort(dates, new Year_Comparator());
    }

    public String convert_to_str(String[] strings)
    {
        String str = String.join("|", strings);
        return str;
    }

    public void write_to_file(String[] result, String filename)
    {
        try(BufferedWriter writer = new BufferedWriter(new FileWriter(filename))){
            for(String str:result){
                writer.write(str);
                writer.newLine();
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}