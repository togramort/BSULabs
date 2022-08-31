package pack;
import java.io.Serializable;

public class Manager extends Employee implements Serializable {
	private static final long serialVersionUID = 1L;
	public Manager(String name, int age) throws Exception {
		super(name, age, Employee.Education.bachelors);
	}
	public Manager() {}
}