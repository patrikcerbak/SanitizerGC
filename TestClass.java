class TestClass {
    public static void main (String args[]) {
        Integer printInt = new Integer(0);
        for (int i = 0; i < 1000; i++) {
            {
                Integer j = new Integer(123);
                if (i == 500) {
                    printInt = j;
                }
            }
        }

        System.gc();

        System.out.println("end " + printInt);
    }
}