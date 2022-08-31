import java.io.Serializable;

public abstract class Employee implements Serializable {
	private static final long serialVersionUID = 1L;
	public Employee() {}	
	public Employee (String name, int age, Education edu) throws Exception {
		this.name = name;
		this.age = age;
		if (age > 78) {
			throw new Exception("ur too old...");
		}
		this.edu = edu;
	}
	
	private String name;
	public String getName() {
		return name;
	}
	
	private int age;
	public int getAge() {
		return age;
	}
	
	public enum Education {
		MASTERS,
		BACHELORS,
		SECONDARY,
		GENERAL,
		NONE
	}
	private Education edu;
	public Education getEdu() {
		return edu;
	}
	
	public String toString() {
		return new String ("Name: " + name + "\nAge: " + age + "\nEducation: " + edu + "\n");
	}
}