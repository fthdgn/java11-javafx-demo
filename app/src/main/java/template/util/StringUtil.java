package template.util;

public class StringUtil {
    public static String reverse(String string) {
        StringBuilder r = new StringBuilder();

        for (int i = 0; i < string.length(); i++) {
            r.append(string.charAt(string.length() - 1 - i));
        }

        return r.toString();
    }
}
