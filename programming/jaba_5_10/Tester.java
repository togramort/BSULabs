import java.io.Serializable;

public class Tester extends Employee implements Serializable {
	private static final long serialVersionUID = 1L;
	public Tester(String name, int age) throws Exception {
		super(name, age, Employee.Education.GENERAL);
	}
	public Tester() {}
}