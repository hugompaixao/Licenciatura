
public class EncrypterSmith {

    static void checkValue(int n, int p) {
        if(Math.abs(n) > 9 || Math.abs(p) > 4) {
            System.out.println("ERRO, Values entered are out of range");
            System.exit(0);
        }
    }

    static String smith(String message, int n, int p) {
        checkValue(n, p);
        if(n == 0 && p == 0) {
            int[] keys = findKey(message, "bug");
            return decrypt(keys[0], keys[1], message);
        }
        return encrypt(n, p, message);

    }

    static String stringRotateLeft(String message, int n) {
        return message.substring(n) + message.substring(0,n);
    }

    static String stringRotateRight(String message, int n) {
        return stringRotateLeft(message,message.length() - n);
    }

    static String changeChar(String message, int p) {
        String tmp = new String();
        for(int i = 0; i <  message.length(); i++) {
            char tmpChar = (char) (message.charAt(i) + p);
            tmp += tmpChar;
        }
        return tmp;
    }


    static String encrypt(int n, int p, String message) {
        String tmp = changeChar(message, p);
        if(n == 0)
            return tmp;

        String encryptedMessage = null;
        if(n > 0)
            encryptedMessage = stringRotateRight(tmp, n);
        if(n < 0)
            encryptedMessage = stringRotateLeft(tmp, -n);
        return encryptedMessage;
    }

    static String decrypt(int n, int p, String message) {
        String tmp = changeChar(message, p);
        if(n == 0)
            return tmp;

        String decryptedMessage = null;
        if(n > 0)
            decryptedMessage = stringRotateLeft(tmp, n);
        if(n < 0)
            decryptedMessage = stringRotateRight(tmp, -n);
        return decryptedMessage;
    }

    static int[] findKey(String message, String word) {
        int[] keys = {0,0};
        for(int i = -9; i < 10; i++) {
            for(int j = -4; j < 5; j++) {
                String decstr = decrypt(i, j, message).toLowerCase().substring(0,3);
                if(decstr.equals(word)) {
                    keys = new int[]{i, j};
                    break;
                }
            }
        }
        return keys;
    }
}
