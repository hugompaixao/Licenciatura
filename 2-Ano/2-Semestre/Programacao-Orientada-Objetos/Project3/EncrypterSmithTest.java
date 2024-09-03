
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class EncrypterSmithTest {
    @Test
    public void smithTest() {
        String test1 = EncrypterSmith.smith("bugIncacheMemory", 2, 2);
        assertEquals("t{dwiKpecejgOgoq", test1);
        String test2 = EncrypterSmith.smith("t{dwiKpecejgOgoq", 0, 0);
        assertEquals("bugIncacheMemory", test2);
    }

    @Test
    public void encrypterTest() {
        String test1 = EncrypterSmith.encrypt(2, 2, "bugIncacheMemory");
        assertEquals("t{dwiKpecejgOgoq", test1);
        String test2 = EncrypterSmith.encrypt(-2, -2, "bugIncacheMemory");
        assertEquals("eGla_afcKckmpw`s", test2);
        String test3 = EncrypterSmith.encrypt(0, 2, "bugIncacheMemory");
        assertEquals("dwiKpecejgOgoqt{", test3);
        String test4 = EncrypterSmith.encrypt(2, 0, "bugIncacheMemory");
        assertEquals("rybugIncacheMemo", test4);
    }

    @Test
    public void decrypterTest() {
        String test1 = EncrypterSmith.decrypt(2, 2, "pw`seGla_afcKckm");
        assertEquals("bugIncacheMemory", test1);
        String test2 = EncrypterSmith.decrypt(-7, -1, "difNfnpszcvhJodb");
        assertEquals("bugIncacheMemory", test2);
        String test3 = EncrypterSmith.decrypt(5, 0, "emorybugIncacheM");
        assertEquals("bugIncacheMemory", test3);
        String test4 = EncrypterSmith.decrypt(0, 4, "^qcEj_]_daIaiknu");
        assertEquals("bugIncacheMemory", test4);
    }

    @Test
    public void changeCharTest() {
        String test1 = EncrypterSmith.changeChar("^qcEj_]_daIaiknu", 4);
        assertEquals("bugIncacheMemory", test1);
        String test2 = EncrypterSmith.changeChar("dwiKpecejgOgoqt{", -2);
        assertEquals("bugIncacheMemory", test2);
    }

    @Test
    public void stringRotateLeftTest() {
        String test1 = EncrypterSmith.stringRotateLeft("rybugIncacheMemo", 2);
        assertEquals("bugIncacheMemory", test1);
    }
    @Test
    public void stringRotateRightTest() {
        String test1 = EncrypterSmith.stringRotateRight("gIncacheMemorybu", 2);
        assertEquals("bugIncacheMemory", test1);
    }

    @Test
    public void findKeyTest() {
        int[] test1 = EncrypterSmith.findKey("t{dwiKpecejgOgoq", "bug");
        assertEquals(2, test1[0]);
        assertEquals(-2, test1[1]);
    }
}
