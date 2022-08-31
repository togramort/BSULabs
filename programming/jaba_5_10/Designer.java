import java.io.Serializable;

public class Designer extends Employee implements Serializable {
	private static final long serialVersionUID = 1L;
	public Designer(String name, int age) throws Exception {
		super(name, age, Employee.Education.NONE);
	}
	public Designer() {}
}