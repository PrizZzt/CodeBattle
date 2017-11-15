package clientlib;

public class ClientApp {

    private final static String URL = "52.232.32.105:8080";
    private final static String USERNAME = "test@mail.com";
    private final static String PASSWORD = "123456";

    public static void main(String[] args) {
        try {
            WebSocketRunner.run(URL, USERNAME, PASSWORD, new SampleSolver());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
