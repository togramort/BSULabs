import java.io.Serializable;

public class Programmer extends Employee implements Serializable {
	private static final long serialVersionUID = 1L;
	public Programmer(String name, int age) throws Exception {
		super(name, age, Employee.Education.MASTERS);
	}
	public Programmer() {}
}
