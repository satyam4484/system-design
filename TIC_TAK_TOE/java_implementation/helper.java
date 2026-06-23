package TIC_TAK_TOE.java_implementation;

import java.util.concurrent.ThreadLocalRandom;

public class helper {

    public static int getRandomId() {
        return  ThreadLocalRandom.current().nextInt(1, 100000);
    }

    
}
