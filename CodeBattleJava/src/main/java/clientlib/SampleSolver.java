package clientlib;


import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class SampleSolver implements Solver {

    protected int size;
    protected Elements[][][] field;
    protected List<String> layersString = new LinkedList<>();

    /**
     * Метод парсинга игрового поля. Вызывается после ответа сервера
     * @param boardString игровое поле
     */
    @Override
    public Solver parseField(String boardString) {
        String[] layers = new String[]{boardString};
        layersString.clear();
        layersString.addAll(Arrays.asList(layers));

        String board = layers[0].replaceAll("\n", "");
        size = (int) Math.sqrt(board.length());
        field = new Elements[layers.length][size][size];

        for (int i = 0; i < layers.length; ++i) {
            board = layers[i].replaceAll("\n", "");

            char[] temp = board.toCharArray();
            for (int y = 0; y < size; y++) {
                int dy = y * size;
                for (int x = 0; x < size; x++) {
                    field[i][x][y] = Elements.valueOf(temp[dy + x]);
                }
            }
        }

        return this;
    }

    /**
     * @return Действие - результат принятия решения на основе игрового поля, полученного в методе {@link Solver#parseField}
     */
    @Override
    public String act() {
        return Direction.ACT.toString();
    }
}
