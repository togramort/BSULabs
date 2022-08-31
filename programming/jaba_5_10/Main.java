
public class Main {
	
	public static Employee[] createCompany() throws Exception {
		Employee[] company = new Employee[5];
		
		company[0] = new Analyst("ppavel", 45);
		company[1] = new Manager("masha", 18);
		company[2] = new Programmer("alex", 22);
		company[3] = new Tester("liam", 36);
		company[4] = new Designer("dora", 13);
		
		return company;
	}

	public static void main(String[] args) {
		
		try {
			Connector con = new Connector("employee.dat");	
			con.write(createCompany());
			Employee[] company = con.read();
			System.out.println("Cool game company: ");
			for (Employee n : company) {
				System.out.println(n);
			}
		}
		catch (Exception e) {
			System.err.println(e);
		}
	}
}