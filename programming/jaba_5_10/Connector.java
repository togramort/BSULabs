import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class Connector {
	private String filename;

	public Connector(String filename) {
		this.filename = filename;
	}

	public void write(Employee[] company) throws IOException {
		FileOutputStream fos = new FileOutputStream (filename);
		try (ObjectOutputStream oos = new ObjectOutputStream(fos)) {
			oos.writeInt(company.length );
			for (int i = 0; i < company.length; ++i) {
				oos.writeObject(company[i]);		
			}
			oos.flush();
		}
	}

	public Employee[] read() throws IOException, ClassNotFoundException {
		FileInputStream fis = new FileInputStream(filename);
		try (ObjectInputStream ois = new ObjectInputStream(fis)) {
			int length = ois.readInt();
			Employee[] result = new Employee[length];
			for (int i = 0; i < length; ++i) {
				result[i] = (Employee) ois.readObject();
			}
			return result;	
		}
	}
}