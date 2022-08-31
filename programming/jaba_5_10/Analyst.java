import java.io.Serializable;

public class Analyst extends Employee implements Serializable {
	private static final long serialVersionUID = 1L;
	public Analyst(String name, int age) throws Exception {
		super(name, age, Employee.Education.SECONDARY);
	}
	public Analyst() {}
}