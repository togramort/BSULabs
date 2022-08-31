public enum Color {
    RED(1),
    ORANGE(2),
    YELLOW(3),
    GREEN(4),
    LIGHT_BLUE(5),
    BLUE(6),
    PURPLE(7);

    private final int _value;

    Color(int i) {
        _value = i;
    }

    public int GetValue(){
        return _value;
    }
}