package pack;
import java.io.Serializable;
import java.util.Date;

public abstract class Employee implements Serializable {
	private static final long serialVersionUID = 1L;
	public Employee() {}	
	public Employee (String name, int age, Education edu) throws Exception {
		this.name = name;
		this.age = age;
		if (age > 78) {
			throw new Exception(AppLocale.getString(AppLocale.exp));
		}
		this.edu = edu;
		this.time = new Date();
	}
	
	private Date time;
	
	private String name;
	public String getName() {
		return name;
	}
	
	private int age;
	public int getAge() {
		return age;
	}
	
	public enum Education {
		masters,
		bachelors,
		secondary,
		general,
		none
	}
	private Education edu;
	public Education getEdu() { 
		return edu;
	}
	
	public String toString() {
		return new String (AppLocale.getString(AppLocale.name) + ": " + name + "\n" + AppLocale.getString(AppLocale.age) + ": " + age + "\n" + AppLocale.getString(AppLocale.education) + ": " + AppLocale.getString(edu.toString()) + "\n" + AppLocale.getString(AppLocale.time) + ": " + time + "\n");
	}
}