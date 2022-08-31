package pack;

/*Определить класс Interval - хранит левую и правую границы интервала. Определить несколько конструкторов и методы: длина интервала,
 * смещение интервала (влево, вправо), сжатие (растяжение) на заданный коэффициент, сравнение двух интервалов,
 * сумма, разность двух интервалов*/

public class Interval {
    private double _leftBorder, _rightBorder;

    public Interval () {
        _leftBorder = 0;
        _rightBorder = 0;
    }

    public Interval (double leftBorder, double rightBorder) {
        assert (Double.compare(leftBorder, rightBorder) < 0): "Left border is greater than right\n";
        _leftBorder = leftBorder;
        _rightBorder = rightBorder;
    }

    public double GetLeftBorder () {
        return this._leftBorder;
    }

    public double GetRightBorder () {
        return this._rightBorder;
    }

    public double GetLength () {
        return this._rightBorder - this._leftBorder;
    }

    public void MoveLeft (double x) {
        assert (Double.compare(x, 0) >= 0): "Offset distance is negative or == 0\n";
        this._leftBorder -= x;
        this._rightBorder -= x;
    }

    public void MoveRight (double x) {
        assert (Double.compare(x, 0) >= 0): "Offset distance is negative or == 0\n";
        this._leftBorder += x;
        this._rightBorder += x;
    }

    public void Stretch (double factor) {
        assert (Double.compare(factor, 0) >= 0): "Stretching factor equals zero\n";
        this._leftBorder *= factor;
        this._rightBorder *= factor;
    }

    public int CompareTo (Interval b) {
        return Compare(this, b);
    }

    static public int Compare (Interval a, Interval b) {
        double len1 = a.GetLength();
        double len2 = b.GetLength();
        if (Double.compare(len1, len2) == 0) {
            return 0;
        }
        else if (Double.compare(len1, len2) > 0) {
            return 1;
        }
        else {
            return -1;
        }
    }

    static public Interval Add(Interval a, Interval b) {
        boolean IsALeftBorderInB = Double.compare(a._leftBorder, b._rightBorder) <= 0 && Double.compare(a._leftBorder, b._leftBorder) >= 0;
        boolean IsARightBorderInB = Double.compare(a._rightBorder, b._rightBorder) <= 0 && Double.compare(a._rightBorder, b._leftBorder) >= 0;
        assert (IsALeftBorderInB || IsARightBorderInB): "Intervals do not intersect\n";
        if (IsALeftBorderInB) {
            return new Interval(b._leftBorder, a._rightBorder);
        }
        else {
            return new Interval(a._leftBorder, b._rightBorder);
        }
    }

    public Interval Add(Interval b) {
        return Add(this, b);
    }

    static public Interval Subtract(Interval a, Interval b) {
        boolean IsALeftBorderInB = Double.compare(a._leftBorder, b._rightBorder) <= 0 && Double.compare(a._leftBorder, b._leftBorder) >= 0;
        boolean IsARightBorderInB = Double.compare(a._rightBorder, b._rightBorder) <= 0 && Double.compare(a._rightBorder, b._leftBorder) >= 0;
        boolean DoBAndAHaveSameLeftBorders = Double.compare(a._leftBorder, b._leftBorder) == 0;
        boolean DoBAndAHaveSameRightBorders = Double.compare(a._rightBorder, b._rightBorder) == 0;
        boolean DoBAndAHaveSameBorders = DoBAndAHaveSameLeftBorders && DoBAndAHaveSameRightBorders;
        if (DoBAndAHaveSameBorders) {
            return new Interval();
        }
        if (IsALeftBorderInB) {
            return new Interval(b._rightBorder, a._rightBorder);
        }
        else if (IsARightBorderInB){
            return new Interval(a._leftBorder, b._leftBorder);
        }
        else {
            return a;
        }
    }

    public Interval Subtract(Interval b) {
        return Subtract(this, b);
    }
    public void Print (int i) {
        System.out.println("Interval #" + i + ":");
        System.out.println("Left border = " + this.GetLeftBorder());
        System.out.println("Right border = " + this.GetRightBorder());
        System.out.println("Length = " + this.GetLength());
        System.out.println();
    }
    public void Print () {
        System.out.println("Interval:");
        System.out.println("Left border = " + this.GetLeftBorder());
        System.out.println("Right border = " + this.GetRightBorder());
        System.out.println("Length = " + this.GetLength());
        System.out.println();
    }
}